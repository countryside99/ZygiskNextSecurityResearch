# 03 — Zero Network Capability

The central question for any privileged closed-source component is: *can it talk to anyone?*

For this build the answer is established at three independent layers — **imports**, **raw
syscalls**, and **decrypted strings**. Each layer on its own would be suggestive; together they
are conclusive for static analysis.

## 3.1 Layer 1 — Imported API surface (all 15 binaries)

Every ELF was parsed and its `.dynsym` undefined symbols enumerated.

| Metric | Value |
|---|---|
| Binaries audited | **15** (4 ABIs × `zygiskd`, `libzygisk.so`, `libzn_loader.so` + 3 × `libpayload.so`) |
| **Distinct undefined symbols, union of all 15** | **178** |
| DNS / name-resolution APIs present | **0** |
| IP-address APIs present (`inet_*`, `htons`, `ntohs`, `htonl`) | **0** |
| URL / HTTP / TLS APIs present | **0** |

Absent everywhere: `getaddrinfo`, `getaddrinfo_a`, `gethostbyname`, `freeaddrinfo`, `inet_addr`,
`inet_ntoa`, `inet_ntop`, `inet_pton`, `htons`, `ntohs`, `htonl`, `res_query`, `res_init`.

**Without a name-resolution or address-conversion function, a process cannot reach an Internet
endpoint even if it had a socket.**

### Which sockets-related symbols *are* present

| Symbol | Binaries | Meaning |
|---|---|---|
| `socketpair` | 12 | AF_UNIX socket pairs (fd plumbing) |
| `sendmsg` / `recvmsg` | 12 | `SCM_RIGHTS` fd passing + credentials |
| `recv` | 12 | local stream reads |
| `connect` | 8 | connect to a *pre-existing* local socket |
| `socket` | 8 | create a socket |
| `bind` / `listen` / `accept4` / `setsockopt` / `getsockopt` | **3** (only `zygiskd` arm64 / armeabi-v7a / x86_64) | the daemon is the server |

`bind`/`listen` appear **only** in the daemon, i.e. exactly one component can receive connections,
and it is the local control socket described in [02](02-architecture-and-behavior.md).

Per-binary detail:

```
bin\arm64-v8a\zygiskd        143 undef  bind,listen,accept4,connect,socket,socketpair,
                                        sendmsg,recvmsg,setsockopt,getsockopt,recv
                                        + execv,fork,ptrace,process_vm_readv,process_vm_writev
bin\armeabi-v7a\zygiskd      146 undef  (same set)
bin\x86_64\zygiskd           141 undef  (same set)
bin\x86\zygiskd              107 undef  connect,socket,socketpair,...   (NO bind/listen/accept4
                                        -> the 32-bit build is a client/helper, not the server)
lib\*\libzygisk.so            68 undef  socketpair,sendmsg,recvmsg,recv   (client only)
lib\*\libzn_loader.so        61-62 undef connect,socket,socketpair,sendmsg,recvmsg,recv
lib\*\libpayload.so           0 undef  <-- no imports at all; raw syscalls only
```

## 3.2 Layer 2 — AF_UNIX verification and raw-syscall census

Because `libzygisk.so` also contains hand-written `svc #0` stubs, imports alone are not enough.

### `libzygisk.so` (arm64) — complete raw-syscall census

15 `svc #0` sites in total, each with its syscall number identified from the `x8` immediate:

| # | Site | Nr | Call |
|---|---|---|---|
| 1 | `0x710f8` | 222 | `mmap` |
| 2 | `0x71640` | 216 | `mremap` |
| 3 | `0x139ff8` | 57 | `close` |
| 4 | `0x13a034` | 113 | `clock_gettime` |
| 5 | `0x13a078` | 24 | `dup3` |
| 6 | `0x13a0b8` | 25 | `fcntl` |
| 7 | `0x13a0f4` | 163 | `getrlimit` |
| 8 | `0x13a130` | 167 | `prctl` |
| 9 | `0x13a16c` | 63 | `read` |
| 10 | `0x13a1a8` | 64 | `write` |
| 11 | `0x13a1e4` | 66 | `writev` |
| 12 | `0x13a228` | 198 | `socket` |
| 13 | `0x13a264` | 178 | `gettid` |
| 14 | `0x13a29c` | 172 | `getpid` |
| 15 | `0x13a2d8` | 203 | `connect` |

**No `bind` (200), no `listen` (201), no `execve` (221), no `ptrace` (117), no `sendto` (206), no
`recvfrom` (207).**

The `socket`/`connect` pair is the abstract-namespace client path; its `sockaddr` is a `.bss`
buffer filled at runtime, and the abstract namespace is proven by the daemon-side string
`create abstract {} failed with {}` plus `/proc/thread-self/attr/sockcreate`.

The `syscall()` helper is used for only two numbers: `98` (`futex`, 10 sites) and `178`
(`gettid`, 2 sites).

The strings `bind {} failed with {}` and `listen socket failed with {}` *do* exist in
`libzygisk.so`'s data pool — but they are **dead table entries**: their only cross-references are
from the pool decryptor itself, never from code. (Contrast `zygiskd`, where the same strings are
live.)

### `libzn_loader.so` (arm64) — audited outside IDA (capstone + pyelftools)

- 150,892 instructions; all 59 `.rela.plt` entries resolved to real callees.
- **0 raw `svc` instructions.**
- `socket()` × 2 — **both `w0 = 1` (`AF_UNIX`)**, `w1 = 0x80002` (`SOCK_DGRAM|SOCK_CLOEXEC`).
- `connect()` × 2, `socketpair(1,1,0,…)` (`AF_UNIX`, `SOCK_STREAM`), `sendmsg` with
  `msg_controllen = 0x14` (`SCM_RIGHTS`), `recvmsg` with `MSG_CMSG_CLOEXEC|MSG_TRUNC`,
  `recv(fd, buf, 4, MSG_PEEK)` for a length-prefix peek.
- **No `bind`, `listen`, `accept`, `sendto`, `recvfrom`, `execve`, `system`, `ptrace`.**
- Its `connect()` targets are `.bss` (`SHT_NOBITS`) buffers built at start-up from decrypted
  `.data` strings — confirmed by decoding the `ADR` operands by hand
  (`0xb0ab8`, `0xb0b48`).

### `libpayload.so` — audited by full decompilation (6 functions, 0 imports)

```
linux_eabi_syscall(__NR_socket, 1, 524289, 0)
  -> domain = 1 (AF_UNIX), type = 0x80001 (SOCK_STREAM|SOCK_CLOEXEC), protocol = 0
linux_eabi_syscall(__NR_connect, fd, &daemon_addr, dword_8B50)
```

`daemon_addr` (size 116 = `sizeof(struct sockaddr_un)`) lives in **`.bss`** — the socket path is
written into the payload at injection time, not compiled into it. `libpayload.so` uses only
`socket`, `connect`, `read`, `write`, `close`, `getpid`, `execve`, `execveat`, `wait4` — and the
`exec*` calls are the *original* syscalls re-issued after the notification, not a privilege
escalation path.

### `zygiskd`

Imports `bind`, `listen`, `accept4` — the local control server. Its decrypted strings confirm the
address family unambiguously:

```
create abstract {} failed with {}
bind {} failed with {}
listen socket failed with {}
connect {} failed with {}
/proc/thread-self/attr/sockcreate
get peercred failed with {}
get peersec failed with {}
recv_fd: cmsg_level != SOL_SOCKET
recv_fd: cmsg_type != SCM_RIGHTS
```

## 3.3 Layer 3 — Complete decrypted string corpora

String encryption is the only obfuscation present (see
[04](04-string-crypto-method.md)). All 38 keys were recovered from the binaries' own key tables and
every binary was swept end-to-end.

| | |
|---|---|
| Keys used | **38** |
| Binaries swept | **15** |
| Encrypted strings recovered (all lengths) | **5,877** |
| Of those ≥ 12 characters (analyzable messages) | **2,816** |
| Strings matching network / exfiltration / C2 / credential patterns | **0** |

Patterns tested for and **not found** in any of the 5,877 strings:

```
http://   https://   www.   *.com|net|org|io|xyz|top|ru|cn   getaddrinfo
inet_     htons      dns    resolve   tcp   udp   ssh   ftp   smtp
wget      curl       base64 pastebin  .onion  /dev/tcp  analytics
upload    beacon     telemetr  exfil   backdoor   keylog   shellcode
/data/local/tmp   /etc/passwd   cookie   session   token   imei
```

The only hits for a few of these tokens were checked manually and are all innocuous:

| Token | Actual string |
|---|---|
| `execve` | `execve_hook.target=0x{:x}`, `inject_execve_monitor`, `could not find execve/execveat` (the init hook) |
| `dns` | substring inside a mis-decrypted 12-byte block in a pool belonging to another key (`igadnsetdpth`) — a false positive, not a real string |
| `phone` | `** using vphone compat` (virtualised-`init` compatibility mode) |

## 3.4 Conclusion

| Question | Answer |
|---|---|
| Can it resolve a hostname? | No — no API for it, in any ABI |
| Can it build an IPv4/IPv6 address? | No — no `inet_*`/`htons`, and no address literals in any string |
| Can it send to a non-local endpoint? | No — every `socket()` observed is `AF_UNIX`, and `sendto`/`recvfrom` are never imported or issued as raw syscalls |
| Does it have a server socket? | Yes, but only `zygiskd` (`bind`/`listen`/`accept4`), on an abstract/AF_UNIX address gated by peer credentials + SELinux context |
| Is there any hidden channel? | None found in imports, raw syscalls, or 5,877 decrypted strings |

**Static evidence: this build has no network transport, and therefore no exfiltration path.**

Residual caveat: static analysis proves the *absence of a capability*, not the absence of intent
that could be added in a future build delivered over `updateJson`. See
[06](06-limitations-and-next-steps.md).
