# Cleaned pseudocode exhibit

Curated, readable extracts from the Hex-Rays AArch64 decompilation of ZygiskNext v1.5.0
(843-5217106).

**What was changed vs. the raw decompiler output:** every `&unk_XXXXXX` operand that the binary
XOR-decrypts at runtime has been substituted back in as a C string literal. Function bodies,
control flow, names and addresses are otherwise untouched.

Read [`../../07-pseudocode-walkthrough.md`](../../07-pseudocode-walkthrough.md) first — it
explains the files, the flattened control flow, and how to reproduce these dumps.

| File | Source binary | Functions |
|---|---|---:|
| `p01-libpayload-hook-and-notify.c` | `lib/arm64-v8a/libpayload.so` | 6 (the whole binary) |
| `p02-zygiskd-attach-and-inject.c` | `bin/arm64-v8a/zygiskd` | 4 |
| `p03-zygiskd-local-socket-and-auth.c` | `bin/arm64-v8a/zygiskd` | 3 |
| `p04-zygiskd-shell-and-startup-integrity.c` | `bin/arm64-v8a/zygiskd` | 3 |
| `p05-libzygisk-local-ipc-and-namespaces.c` | `lib/arm64-v8a/libzygisk.so` | 5 |
| `p06-libzn_loader-client-socket.c` | `lib/arm64-v8a/libzn_loader.so` | 5 |
| `p07-string-decryption-core.c` | `bin/arm64-v8a/zygiskd` | 2 |

These 28 functions are a **subset** of the 8,887 functions (13.8 MB, 0 failures) decompiled for
this research. They are chosen for readability and evidential value, not because the rest were
excluded from review.
