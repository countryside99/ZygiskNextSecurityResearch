# 07 — Reading the cleaned pseudocode

Raw Hex-Rays output from this module is nearly unreadable for two reasons, both of which
[`artifacts/pseudocode/`](artifacts/pseudocode/) fixes:

1. **Every string is an opaque pointer.** The module XOR-decrypts its string constants into a
   stack buffer at the point of use, so the decompiler shows `&unk_1DB512` plus a byte count
   instead of text. The exhibit below substitutes the actual plaintext back in as a C string
   literal — nothing else in the code was edited.
2. **Control flow is flattened.** Almost every non-trivial function is compiled into a state
   machine: an integer state variable (`i`, `v5`, `v23` …) is compared against magic constants and
   assigned the next value. That is compiler/obfuscator output, not logic — see §"Reading the
   flattening" below.

The complete pseudocode corpus produced for this research is **8,887 functions / 13.8 MB** with
**0 decompiler failures**. The exhibit is a curated subset chosen to be the parts a reader can
follow without specialism.

## The exhibit

| File | Functions | What it shows |
|---|---:|---|
| [`p01-libpayload-hook-and-notify.c`](artifacts/pseudocode/p01-libpayload-hook-and-notify.c) | 6 | **Start here.** The complete `libpayload.so` — every function in the binary. It is the `execve` monitor installed inside `init`: `socket(AF_UNIX, SOCK_STREAM\|SOCK_CLOEXEC)` → `connect(daemon_addr)` → notify → re-issue the original syscall. Zero imports, all raw `svc #0`. |
| [`p02-zygiskd-attach-and-inject.c`](artifacts/pseudocode/p02-zygiskd-attach-and-inject.c) | 4 | The daemon's attach/deliver/inject path and its progress logs (`"** preparing payload ..."`, `"** attaching init ..."`, `"** init attached"`, `"** payload loaded"`, `"inject {} {} succeed"`, `"inject success!"`). |
| [`p03-zygiskd-local-socket-and-auth.c`](artifacts/pseudocode/p03-zygiskd-local-socket-and-auth.c) | 3 | The local control server and its authorization: abstract-namespace bind, `getsockopt(SO_PEERCRED)`, `getsockopt(SO_PEERSEC)`, SCM_RIGHTS fd transfer. This is *why* a privileged binary has `bind`/`listen` and still has no network capability. |
| [`p04-zygiskd-shell-and-startup-integrity.c`](artifacts/pseudocode/p04-zygiskd-shell-and-startup-integrity.c) | 3 | The most capability-dense code in the module: `exec_cmd` → `/system/bin/sh`, plus the start-up check that opens `machikado.<abi>` and `mazoku`. Included because it is the honest weak point, not because it is suspicious — see [06](06-limitations-and-next-steps.md) gaps G4/G5. |
| [`p05-libzygisk-local-ipc-and-namespaces.c`](artifacts/pseudocode/p05-libzygisk-local-ipc-and-namespaces.c) | 5 | The in-process client: `socketpair` + `sendmsg(SCM_RIGHTS)`, peer credential check, `recvmsg`, and the denylist `setns`/`umount2` pair. |
| [`p06-libzn_loader-client-socket.c`](artifacts/pseudocode/p06-libzn_loader-client-socket.c) | 5 | The other end of the local channel, including the `socket()` calls whose first argument is literally `1` (`AF_UNIX`). |
| [`p07-string-decryption-core.c`](artifacts/pseudocode/p07-string-decryption-core.c) | 2 | The two wrappers every `sub_XXXX(&byte_6, "…", len)` call lands in — i.e. the obfuscation itself, in 121 lines. |

Total: **28 functions, ~4,000 lines.**

## Reading the flattening

A typical flattened body looks like this:

```c
for ( i = 1078696302; ; i = -1283271264 )
{
  while ( 1 )
  {
    while ( 1 )
    {
      if ( i > 1499420930 )      { i = -154311009; }
      else if ( i == 1078696302 ) { i = -1440074395; }
      else                        { result = sub_191B28(v5, v7); i = -287150771; }
      ...
```

How to read it:

- `i` is **not** a loop counter — it is a *program counter*. Each block computes the next value of
  `i`, which selects the next basic block in the following iteration.
- The magic integers are arbitrary labels. Ignore them; follow **what the block does**, then jump
  to where `i` is assigned.
- The real order of operations can be recovered by simulating the state variable, which is what a
  deobfuscator would do. For this research the ordering was not needed: the *calls* (`socket`,
  `connect`, `ptrace`, `sendmsg`, `execve`) and the *strings* are all visible directly, and those
  are what the capability analysis rests on.
- `sub_3D158(&byte_6, "some message", 19)` means "decrypt 19 bytes of `some message` into a
  stack buffer". The message then goes through a `{fmt}`-style formatter.

## Conventions in the dumps

| Token | Meaning |
|---|---|
| `// ===== 0xF45D0 sub_F45D0 =====` | runtime address + IDA's auto-generated name |
| `__fastcall`, `__usercall`, `@<X0>` | Hex-Rays' register-level calling-convention notation |
| `linux_eabi_syscall(__NR_*, …)` | hand-written `svc #0` wrapper (no libc import) |
| `v23 = …` inside `if/else` | flattened state transition |
| `"…"` (in this exhibit) | **restored plaintext**; in raw output it was `&unk_XXXXXX` |
| `&unk_XXXXXX` (still present) | 31 references across the exhibit that do not decrypt to printable text under any of the 38 keys — data, not strings; left untouched |
| `dword_8B50`, `byte_6`, … | ordinary IDA data symbols (`dword_8B50` is the `sockaddr` length passed to `connect`) |

## Reproducing the exhibit

```text
1. idat.exe -A -L<log> -S idc_headless3.py <binary>   # dumps <abi>__<name>.c
2. resolve.py  # 38 keys -> plaintext for any address
3. mkclean.py  # extract selected functions, substitute string literals, emit
```

Each file carries a header naming its source binary, so the exhibit is traceable back to the
artifact hash in [01](01-provenance-and-integrity.md).

## What the exhibit does *not* show

- **~8,857 other functions** — including the two largest injection routines
  (`0xF59D0`, 3156 lines and `0x8A1B8`, 1839 lines), which are deliberately omitted only for size;
  their behavior is summarized in [02](02-architecture-and-behavior.md) and
  [05](05-behavior-evidence-catalog.md).
- **The three non-arm64 ABIs**, which were import- and string-audited but not decompiled
  ([06](06-limitations-and-next-steps.md), gap G2).
- **Runtime behavior** — no trace, no dynamic confirmation (gap G1).
