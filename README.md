# ZygiskNext Security Research

**Public, independent security research** on [Zygisk Next](https://github.com/LSPosed/ZygiskNext), a **closed-source** implementation of Zygisk.

## About this research

I decided to make this research public to independently investigate the **security and runtime behavior** of Zygisk Next.

Due to its **privileged role** within Android and its closed-source nature, I believe independent analysis can help provide a better understanding of its behavior and **help ease concerns within the community**.

This research does **not** assume or claim malicious behavior. The goal is to investigate and document what can be established through technical analysis.

---

## Current status: analysis of v1.5.0 (843-5217106) completed

### Headline result

> **No malicious behavior was found.** The complete decompiled code and the complete decrypted string tables of the module — across **all 4 ABIs and all 15 shipped binaries** — contain **no network capability, no data-exfiltration path, and no indicator of compromise**.
>
> This is an *absence-of-evidence* result with a clearly stated residual risk (see [06-limitations-and-next-steps.md](06-limitations-and-next-steps.md)).

### What was actually done

| Step | Result |
|---|---|
| Provenance check | Extracted tree is **byte-identical** to the release zip; zip SHA-256 matches the published release hash |
| Static inventory | 15 binaries (4 ABIs × `zygiskd` / `libzygisk.so` / `libzn_loader.so` / `libpayload.so`), scripts, policies |
| Import audit | **178 distinct undefined symbols** across all 15 binaries — **zero** DNS / IP / URL APIs |
| Syscall audit | Full raw-`svc` census of `libzygisk.so` — **no** `bind`/`listen`/`execve`/`ptrace`/`sendto`/`recvfrom` |
| Full decompilation | **8,887 functions**, **13.8 MB** of Hex-Rays pseudocode, **0 decompiler failures** |
| String decryption | Recovered **38 XOR keys** from the binaries' own key tables → **complete** plaintext string corpora |
| String scan | **0 suspicious strings** in any of the 15 binaries (network / exfil / C2 / credential patterns) |

### Findings

1. **The module has no network capability at all.** Not "it didn't make network calls" — it *cannot*: no `getaddrinfo`, `gethostbyname`, `inet_*`, `htons`, `sendto`, `recvfrom`, no URLs, no IP literals, and the only `socket()` calls are `AF_UNIX`. → [03-network-zero-capability.md](03-network-zero-capability.md)

2. **The full architecture is understood and matches what a Zygisk implementation must do.** `zygiskd` is a local privileged daemon; it **`ptrace`-seizes `init` (PID 1), injects `libpayload.so`, inline-hooks `execve`/`execveat`** in order to observe process creation and inject `libzygisk.so` into zygote/app processes. This is the documented Zygisk injection mechanism, not hidden behavior. → [02-architecture-and-behavior.md](02-architecture-and-behavior.md)

3. **The obfuscation is string encryption only.** 38 XOR keys, all recovered and stored in plain `.rodata`/`.data` key tables inside each binary. There is no virtualization, no packing, no anti-disassembly, no network-loaded payload. → [04-string-crypto-method.md](04-string-crypto-method.md)

4. **Root-solution integration is explicit and benign**: detection of Magisk / KernelSU / APatch, a Magisk-compatibility stub module, denylist/unshare (mount-namespace) handling, and `bugreports` written to `/data/adb/zygisksu/bugreports` — all local. → [05-behavior-evidence-catalog.md](05-behavior-evidence-catalog.md)

5. **The "HyperOS Rust Runtime" strings are a documented feature**, not an anomaly: the official v1.5.0 release notes list *"Adds HyperOS Runtime support"*. → [01-provenance-and-integrity.md](01-provenance-and-integrity.md)

### Documents

| File | Contents |
|---|---|
| [01-provenance-and-integrity.md](01-provenance-and-integrity.md) | Release hash verification, file inventory, HyperOS explanation, remote update channel |
| [02-architecture-and-behavior.md](02-architecture-and-behavior.md) | Components, IPC surface, and the end-to-end injection pipeline |
| [03-network-zero-capability.md](03-network-zero-capability.md) | Imports, syscalls and strings proving zero network capability |
| [04-string-crypto-method.md](04-string-crypto-method.md) | The XOR obfuscation, the 38 keys, and how plaintext was recovered |
| [05-behavior-evidence-catalog.md](05-behavior-evidence-catalog.md) | Catalog of notable behaviors with decrypted-string evidence |
| [06-limitations-and-next-steps.md](06-limitations-and-next-steps.md) | **What this analysis does *not* prove**, and what to do next |
| [`artifacts/`](artifacts/) | Decrypted string table for each of the 15 binaries, plus [`recovered-keys.txt`](artifacts/recovered-keys.txt) and [`summary.json`](artifacts/summary.json) |

## If you wanna contribute

If you'd like to contribute to this research, you can:

- Open an **issue** with a technical observation or research lead.
- Open a **pull request** with additional analysis or documentation.
- Provide **reproducible evidence** supporting a finding.

Please keep contributions **technical, evidence-based, and respectful to LSPosed Developers**.

## Scope & Limitations

This is an **independent research project** and is not affiliated with or endorsed by the LSPosed developers.

The absence of identified security issues or malicious behavior does **not** guarantee that none exist. Findings are based on the evidence available at the time of analysis.

The module ships a remote update channel (`updateJson`), so a clean build today does not imply future builds are clean. Read [06-limitations-and-next-steps.md](06-limitations-and-next-steps.md) before drawing a conclusion.

## Stay Tuned

**Research is ongoing.**
