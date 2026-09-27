# 02 — Architecture and Runtime Behavior

What the module is made of, what each piece does, and how they fit together. Every statement below
is traceable to either a decompiled function or a decrypted string (see `artifacts/`).

## 2.1 Components

| Component | ABIs | Role |
|---|---|---|
| `bin/<abi>/zygiskd` | arm64, armeabi-v7a, x86, x86_64 | **Root-side daemon.** Binds the local control socket, owns injection, module loading, denylist/unshare, root-solution integration. Runs as root. |
| `lib/<abi>/libzygisk.so` | 4 | **In-process Zygisk library.** Injected into zygote / service processes. Implements the Zygisk module API, talks to the daemon over local sockets. |
| `lib/<abi>/libzn_loader.so` | 4 | **Module loader.** `dlopen`s Zygisk module libraries, resolves their symbols. AF_UNIX `SOCK_DGRAM` client to the daemon. |
| `lib/<abi>/libpayload.so` | arm64, armeabi-v7a, x86_64 | **Exec monitor hook.** 1.5 KB, 6 functions, raw syscalls only. Installed inside `init` (PID 1) to observe process creation. |
| `zygiskd.i64`, `lib/*.i64` | — | IDA databases produced during this research (not part of the release). |

Division of labour is clean: the daemon is the only component that can *bind/listen/accept* and
the only one that holds privileges; everything else is a *client*.

## 2.2 The injection pipeline (recovered end-to-end)

Decrypted log strings from `zygiskd` give the sequence verbatim:

```
** preparing payload ...
init libpayload.so
** payload prepared
** attaching init ...
ptrace_interrupt
** init attached
** loading payload ...
open payload / read payload / write payload
set system con            -> u:r:init:s0
set sockcreate con
send lib fd
inject_execve_monitor
libpayload base: {:x}
** payload loaded
** setting up payload ...
daemon_addr
** inline hook prepare ...
could not find execve/execveat
my_execveat
** using vphone compat
*** prepare trampoline
** inline hook commit
{} hook installed
** payload has been setup
```

In other words:

1. `zygiskd` **`PTRACE_SEIZE`s `init` (PID 1)** (`sub_F59D0`, request `PTRACE_SEIZE` with
   `PTRACE_O_TRACEEXEC`-style flags), interrupting it only if it is not already stopped
   (`"!! init is not stopped, trying to interrupt init"`).
2. It writes **`libpayload.so`** into `init` (`AllocSafeMemory`, `remote mmap`, `map seg`,
   `zeromap seg`, `WriteProc`) and sets the SELinux context used for the socket to
   **`u:r:init:s0`**.
3. It performs an **inline hook of `execve` / `execveat` in `init`** — locating the trampoline
   target, mapping a page near it (`"could not find map near from={} to={} sz={}"`) and patching
   it. `libpayload.so` exports exactly `my_execve`, `my_execveat`, `my_wait4`.
4. Every `execve` in PID 1 now first notifies the daemon over an **`AF_UNIX` stream socket** to the
   runtime-filled `daemon_addr` (`libpayload.so`, `socket(1, 0x80001, 0)` → `AF_UNIX`,
   `SOCK_STREAM|SOCK_CLOEXEC`), then performs the real syscall. `my_wait4` additionally reports
   child termination status.
5. That is how `zygiskd` learns that `zygote` / `zygote64` / `app_process` / `service` processes
   were born, and then injects **`libzygisk.so`** (and `libzn_loader.so`) into them
   (`"injecting {} {} (injector {})"`, `"inject {} {} succeed"`, `"zygote-injector"`,
   `"service-injector"`, `"stub-zygote-injector"`).

Step 3 is the only genuinely aggressive technique in the module. It is also *necessary*: this is the
standard way a Zygisk implementation obtains process-creation notification on a stock Android, and
it is documented behaviour rather than concealed behaviour — the strings describing it are
first-person progress logs (`"** attaching init ..."`, `"** inline hook commit"`), not something an
author would write if they meant to hide it.

`zygiskd`'s other `ptrace` sites support this: `PTRACE_GETREGSET`/`SETREGSET` (register
read/write for the remote mmap / trampoline patch), `PTRACE_SYSCALL` (stepping the remote syscall),
`PTRACE_PEEKDATA`/`PEEKUSER` (reading remote memory), `PTRACE_CONT`, `PTRACE_DETACH`,
`PTRACE_GETSIGINFO`.

## 2.3 IPC surface

All IPC is **local Unix-domain sockets**; there is no other kind (see
[03-network-zero-capability.md](03-network-zero-capability.md)).

| Endpoint | Type | Purpose |
|---|---|---|
| `zn_zygote_{}` | abstract AF_UNIX | zygote ↔ daemon control channel |
| `zn_global_{}` | abstract AF_UNIX | global service channel (peer credential + peer security-context checks: `"get peercred failed"`, `"get peersec failed"`) |
| `zn-nsdaemon-` | AF_UNIX | mount-namespace cleaner (`ns-daemon`), `setns`/`/proc/self/mountinfo` |
| socketpair + `SCM_RIGHTS` | AF_UNIX | fd passing (`recv_fd: cmsg_type != SCM_RIGHTS` errors) |
| companion sockets | AF_UNIX | per-module `zn-companion` / `zygisk-companion` processes |

Access control is by **peer credentials and SELinux context**, not by network ACLs:

```
unknown action={} from uid={} pid={} sctx={}
permission denied
u:r:init:s0
u:r:zygote:s0
u:r:logd:s0
```

## 2.4 Command / status surface (CLI)

```
Zygisk Next Controller {}
Zygisk Next Daemon {}
Kernel: {}
unknown cmd: {}, enable, disable or reload is required.
denylist-policy      (default, whitelist)
enforce-denylist     (disabled, enabled, just_umount)
memory-type          (default, anonymous)
disable-zygisk       (true, false)
...
version:{}
zygote_states:{}
inject_state:{}
root_status:{}
denylist_policy:{}
root_impl:{}
modules64:{} modules32:{}
```

Plus diagnostic dumps (`DumpZnModules`, `zn_modules.txt`, `bugreports`).

## 2.5 Root-solution integration

```
multiple versions: magisk={} ksu={} ap={}
/data/adb/ksud
ksu KSU_IOCTL_GET_INFO failed
ksu uid_should_umount failed
ksu uid_granted_root failed
/data/adb/ap/package_config
/data/adb/apd -V
truncate su -c 'echo Success'
exec_cmd: fork failed / dup stdout failed / exec {} failed
/system/bin/sh
denylist policy is only supported in Magisk
magisk zygisk enabled, zygisk next's zygisk will not work!
```

`zygiskd` detects which root implementation is present (Magisk / KernelSU / APatch), can spawn
`/system/bin/sh` to probe it (`exec_cmd`), and installs a **Magisk-compatibility stub module**
(`zn_magisk_compat`) that re-creates the Magisk module layout so Zygisk-style `post-fs-data.sh`
scripts still run:

```
** magisk_compat: create magisk stub
/data/adb/modules/zn_magisk_compat/module.prop   (id=zn_magisk_compat)
** magisk_compat: exec {} of zygisk modules
** magisk_compat: link {}
** magisk_compat: add system.prop of {}
** magisk_compat: remove magisk stub
```

Shell execution here is a **local, non-networked** root-solution probe. It is the most
capability-dense behaviour in the module and is called out explicitly in
[06-limitations-and-next-steps.md](06-limitations-and-next-steps.md) as the thing a dynamic run
should confirm.

## 2.6 Process / namespace handling

```
unshare(CLONE_NEWNS)                 (libzygisk.so)
setns(...)                           (libzygisk.so, zygiskd)
/dev/.zn_unshare_lock
u:object_r:unshare_lock_file:s0
/proc/{}/mountinfo   /proc/{}/mounts
cleanns unshare failed / cleanns wait failed / Unmounted ({})
PutCleanNs / GetCleanNs / UnshareLock
```

This is Zygisk's denylist/"unmount sensitive paths" feature: each app process gets a private mount
namespace with Magisk/module mounts removed so banking/root-detection apps see a clean view.

## 2.7 Module loading (Zygisk API)

```
loading {}bit zygisk modules
loaded {} {}bit zygisk module(s)
zygisk/arm64-v8a.so  zygisk/armeabi-v7a.so
failed to init elf of zygisk module {}/{}
zygisk_shamiko / skip shamiko
{"modules":[  ,"processes":[
ReadModules / GetModuleDir / ConnectCompanion / GetUidFlags / Start / Stop / Exit
```

`libzn_loader.so` performs the actual `android_dlopen_ext` + `dlsym` + `dlclose` of module
libraries and passes file descriptors back to the daemon over `sendmsg`/`recvmsg` with
`SCM_RIGHTS`.

## 2.8 Miscellaneous, all local

| Behavior | Evidence |
|---|---|
| SELinux awareness | `/sys/fs/selinux`, `"selinuxfs not detected, disable selinux feature!"`, `security.selinux`, `getfilecon` |
| Bug reporting | `/data/adb/zygisksu/bugreports`, `bugreport written to {}`, crash backtrace scanning, `module {} appeared in crashing process {} backtrace` |
| Magic/nonce file | `/dev/urandom`, `/data/adb/zygisksu/.magic`, `"failed to generate magic"` |
| Config flags | `/data/adb/zygisksu/experimental_hook`, `no_check_companion_fd`, `zygisk_disabled`, `denylist_policy`, `memory_type`, `linker` |
| HyperOS runtime | `/system_ext/bin/hyos_spawner` — see [01](01-provenance-and-integrity.md) |
| VM compatibility | `"** using vphone compat"` — fallback path when hooking a virtualised `init` |
| Module file verification | `"open machikado failed"`, `"verify1 failed"`, `"open mazoku failed"`, `"verify2 failed"`, `./machikado` — two data files opened from the module directory and integrity-checked at start-up |
| Restriction key | `machikado`/`mazoku` purpose is still **not identified** (see [06](06-limitations-and-next-steps.md)) |

## 2.9 What the architecture implies

- The privileged component (`zygiskd`) exposes **only local sockets**, gated by UID + SELinux
  context.
- Every secondary component is a **client** of that daemon.
- The one technique that reaches outside normal process boundaries (`ptrace` + inline hook on
  `init`) exists solely to obtain process-creation notification, and is self-documented by its own
  progress logs.
- Nothing in the architecture has a place to *send* data anywhere: there is no transport.
