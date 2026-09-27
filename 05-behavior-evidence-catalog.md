# 05 — Behavior Evidence Catalog

A catalog of everything the module was found to *do*, with the evidence for each claim. Companion to
[02](02-architecture-and-behavior.md) (narrative) and
[03](03-network-zero-capability.md) (what it cannot do).

## 5.1 Coverage of the code review

| Binary | Functions decompiled | Pseudocode size | Decompiler failures |
|---|---:|---:|---:|
| `bin/arm64-v8a/zygiskd` | **4,508** | 6,901,884 B | **0** |
| `lib/arm64-v8a/libzygisk.so` | **2,812** | 4,515,125 B | **0** |
| `lib/arm64-v8a/libzn_loader.so` | **1,561** | 2,323,791 B | **0** |
| `lib/arm64-v8a/libpayload.so` | **6** | 11,112 B | **0** |
| **Total** | **8,887** | **13,751,912 B (~13.8 MB)** | **0** |

Method: IDA 9.1 + Hex-Rays AArch64. `libzygisk.so` was decompiled through the live MCP session;
`zygiskd`, `libzn_loader.so` and `libpayload.so` were decompiled headlessly with
`idat.exe -A -S…` against copies of the IDBs/binaries. `libpayload.so` (6 functions) was also read
in full as source.

Coverage caveat: the **non-arm64 ABIs were import- and string-audited but not decompiled** — see
[06](06-limitations-and-next-steps.md).

### `libzygisk.so`: every imported API accounted for

All **68** undefined symbols appear as calls somewhere in the pseudocode — there is no dead or
hidden import. The complete list of what it calls includes only:
`socketpair`, `sendmsg`, `recvmsg`, `recv` (local IPC), `fork`/`waitpid`/`dup2` (process setup),
`setns`/`unshare`/`umount2`/`getmntent`/`setmntent` (denylist mount namespaces),
`android_dlopen_ext`/`dlsym`/`dlclose` (module loading), `regcomp`/`regexec` (path matching),
`open`/`stat`/`statfs`/`pread64`/`readlinkat` (file access), pthread/`mmap`/`mprotect`/`madvise`
runtime, and `__android_log_*` logging.

A literal-token scan of the **entire 4.3 MB `libzygisk.so` pseudocode** returned zero matches for:
`http`, `https`, `www.`, `getaddrinfo`, `inet_`, `htons`, `recvfrom`, `sendto(`, `execve`,
`popen`, `system(`, `ptrace`, `chmod`, `chown`, `base64`, `pastebin`, `.onion`,
`/data/local/tmp`.

## 5.2 The `ptrace` surface (`zygiskd`) mapped to purpose

29 `ptrace` references, grouped by enclosing function:

| Group | Functions | Requests | Purpose |
|---|---|---|---|
| Attach / detach lifecycle | `sub_8A1B8`, `sub_9E594`, `sub_F4F84`, `sub_F59D0`, `sub_FA734`, `sub_89734`, `sub_7E004` | `SEIZE`, `ATTACH`, `INTERRUPT`, `DETACH`, `PEEKDATA`, `PEEKUSER` | Attach to `init` / zygote, keep them stopped only as long as needed |
| Register access | `sub_C681C`, `sub_C6A3C`, `sub_CC88C` | `GETREGSET`, `SETREGSET` | Read/patch registers for remote mmap + trampoline installation |
| Stepping | `sub_CC88C`, `sub_CE624`, `sub_CEEE0`, `sub_C73CC`, `sub_CBB80` | `SYSCALL`, `CONT` | Execute and single-step the remote syscall |
| Diagnostics | `sub_C8130`, `sub_CDAC4`, `sub_7E004` | `GETSIGINFO` | Distinguish stop reasons; `"dumping maps:"`, `"dumping regs:"` |
| Remote memory | `sub_C50F4`, `sub_C6138` | `process_vm_writev`, `process_vm_readv` | Write the payload / read remote state |

Supporting strings (all decrypted, all first-person progress logs):

```
ptrace_seize   attach wait   attach cont   wait for exec   ptrace_detach   re-seize wait
** attaching init ...      ** init attached      ** loading payload ...
** payload loaded          ** setting up payload ...   ** inline hook prepare ...
** inline hook commit      {} hook installed      inject success!
!! init is not stopped, trying to interrupt init
process {} not stopped, trying to interrupt to restore
unknown state {}, not SIGTRAP + EVENT_EXEC
```

`execv` appears exactly once in code (`sub_19C948`) — re-exec of `./bin/zygiskd64` /
`./bin/zygiskd32` for the 32-bit helper path.

## 5.3 Behavior catalog

| # | Behavior | Evidence | Assessment |
|---|---|---|---|
| 1 | **Attach to `init` (PID 1)** | `PTRACE_SEIZE` sites; `"** attaching init ..."`; `/proc/1/exe` | Necessary for process-creation notification; see 5.2 |
| 2 | **Inline-hook `execve`/`execveat` in `init`** | `libpayload.so` `my_execve`/`my_execveat`; `"execve_hook.target=0x{:x}"`, `"could not find execve/execveat"`, `"my_execveat"` | Hook *forwards* to the real syscall after notifying the daemon |
| 3 | **Notify daemon over AF_UNIX** | `socket(1, 0x80001, 0)` in `libpayload.so`; `daemon_addr` in `.bss` | Local only |
| 4 | **Inject `libzygisk.so` into zygote/service** | `"injecting {} {} (injector {})"`, `zygote-injector`, `service-injector`, `stub-zygote-injector` | The documented function of a Zygisk implementation |
| 5 | **Denylist / mount-namespace unmount** | `unshare(CLONE_NEWNS)`, `setns`, `umount2`, `/proc/{}/mountinfo`, `PutCleanNs`/`GetCleanNs` | Standard Zygisk denylist behavior |
| 6 | **Root-solution detection** | `multiple versions: magisk={} ksu={} ap={}`, `KSU_IOCTL_GET_INFO`, `/data/adb/apd -V`, `GetRootImpl` | Local probing only |
| 7 | **Shell execution for probing** | `exec_cmd: …`, `/system/bin/sh`, `truncate su -c 'echo Success'` | **Most capability-dense behavior**; local, non-networked; flagged in [06](06-limitations-and-next-steps.md) for dynamic confirmation |
| 8 | **Magisk-compat stub module** | `** magisk_compat: create magisk stub`, `id=zn_magisk_compat`, `post-fs-data.sh`, busybox paths | Recreates Magisk layout so existing modules keep working |
| 9 | **Peer-credential authorization** | `get peercred failed`, `get peersec failed`, `unknown action={} from uid={} pid={} sctx={}`, `u:r:init:s0`, `u:r:zygote:s0`, `u:r:logd:s0` | Access control is UID + SELinux context, not network |
| 10 | **Local bug reports** | `/data/adb/zygisksu/bugreports`, `bugreport written to {}`, `module {} appeared in crashing process {} backtrace` | Written under `/data/adb/…`, never transmitted |
| 11 | **HyperOS runtime support** | `/system_ext/bin/hyos_spawner`, `ZygiskNextHyosModule` strings; official release notes | Documented feature — see [01](01-provenance-and-integrity.md) |
| 12 | **VM/emulator compatibility** | `"** using vphone compat"`, `"failed to find map near from={} to={}"` | Fallback when `init` is virtualised |
| 13 | **Start-up file verification** | `"open machikado failed"`, `"verify1 failed"`, `"open mazoku failed"`, `"verify2 failed"`, `./machikado` | Two module files opened and checked; **purpose unknown** — see [06](06-limitations-and-next-steps.md) |
| 14 | **Config state on disk** | `/data/adb/zygisksu/{experimental_hook,no_check_companion_fd,zygisk_disabled,denylist_policy,memory_type,linker,znctx,.magic,.injecting}` | Local flag files |
| 15 | **Remote update channel** | `module.prop:updateJson` | Not behavior of this binary, but a supply-chain channel — see [01](01-provenance-and-integrity.md) |

## 5.4 First-glance "alarming" artifacts and their explanations

| Observation | Explanation |
|---|---|
| "It hooks `execve` in PID 1" | Forwarding hook used to learn about new processes; it calls the original syscall |
| "It uses `ptrace` 29 times" | Attach, register read/write, and single-step while patching `init` |
| "It has `bind`/`listen`" | Only `zygiskd`, only AF_UNIX/abstract, gated by `peercred`+`peersec` |
| "It can run `/system/bin/sh`" | Root-solution probing (`exec_cmd`); local, no transport to send anything with |
| "It sets SELinux contexts (`u:r:init:s0`)" | Required to talk to sockets created by `init`/`zygote` |
| "Strings are XOR-encrypted" | Static-string obfuscation only; keys are in `.rodata` — see [04](04-string-crypto-method.md) |
| "It talks about `hyos_spawner`" | Documented HyperOS Runtime feature |
| "`machikado`/`mazoku` are unknown" | Genuinely unresolved — recorded as an open item, not explained away |
| "Flattened control flow looks convoluted" | Compiler-generated state-machine flattening (common with `-O2` + obfuscating builds), not opaque-predicate malware packing |

## 5.5 Files examined that are *not* part of the release

The working tree also contains `.i64` IDA databases and analysis logs. These were produced by this
research and are excluded from all counts.
