# 04 — String Obfuscation and How It Was Broken

## 4.1 What the obfuscation actually is

The module encrypts its string constants with a **single-byte-aligned repeating-key XOR**. That is
the entirety of the protection: no packing, no virtualization, no control-flow obfuscation beyond
ordinary compiler-generated flattening, no anti-debug, no anti-disassembly, no integrity self-check
of the code.

Each encrypted string is XORed with a **32-byte key**, and the key index restarts at 0 at the
beginning of *each* string:

```
plain[i] = enc[start + i]  XOR  key[i % 32]        for i in 0 .. length-1
```

A consequence worth stating precisely, because it is what made the sweep work: the key phase is a
property of the **string start**, not of the absolute address. Two strings in different sections
that use the same key are both decrypted by aligning the key to their own first byte.

In practice a call site looks like this (decompiled from `zygiskd`):

```c
sub_3D158(&byte_6, (__int64)&unk_1DB512, 13);   // decrypt 13 bytes at 0x1DB512
if ( ptrace(PTRACE_INTERRUPT, *v11, 0, 0) >= 0 )
```

Decrypting `0x1DB512` (file offset `0x1D3512`) with the correct key yields exactly 13 characters:
`"dumping regs:"`.

## 4.2 Where the keys live

The keys are stored **in the clear**, in 32-byte slots, inside each binary:

| Binary | Key table (file offsets) | Slots |
|---|---|---|
| `bin/arm64-v8a/zygiskd` | `0x5430` … `0x574F`, stride `0x20` | 25 |
| `lib/arm64-v8a/libzygisk.so` | `0x3410` … `0x35EF`, stride `0x20` | 16 |
| `lib/arm64-v8a/libzn_loader.so` | `0x1D00` … `0x1E7F`, stride `0x20` | 14 |
| **Union (de-duplicated)** | | **38 distinct keys** |

The three tables **overlap**: the same key bytes appear in more than one binary, which is why 55
slots reduce to 38 unique keys. Full listing: [`artifacts/recovered-keys.txt`](artifacts/recovered-keys.txt).

Some examples (hex, 32 bytes each):

| # | Value |
|---|---|
| k0 | `16f71d2e513e46f3913f76e6cb273dbe5a01a0319751fc1e41912910460097d6` |
| k1 | `6ebca9abe6dedf89013db39703c605ae8db3b486b8307555ff8a2aa1ac942205` |
| k9 | `b1cf440834a0eb421994b2bdddfc95eea8674a35398c7eb9497bd00a18e4d52e` |

Keys are **not** derived at runtime, **not** device-bound, **not** stored encrypted, and **not**
authenticated. Recovering them is a file-offset read plus a loop.

## 4.3 Method

1. **Locate the key tables.** The decryptor call sites (`sub_3D158(dst, src, len)`,
   `sub_3CC3C(dst, src, len, …)`, `sub_13EC8` in `libzn_loader.so`) gave known
   `(address, length)` pairs. Solving for the unknown key at one known plaintext
   (`"dumping regs:"`, 13 bytes) yielded the first key, which was then found verbatim at
   `zygiskd` file offset `0x55B0` — revealing that keys sit in a fixed 32-byte slot table.
2. **Dump every slot** in each binary's table.
3. **Sweep every binary** with all keys: for each key, vectorised over all file offsets, keeping
   runs of ≥ 10 printable bytes that pass alphanumeric/lowercase/vowel heuristics.
4. **Sanity-check every token** that matched a network/exfiltration pattern by hand
   ([03](03-network-zero-capability.md), §3.3).

### The step that had to be re-done honestly

An initial sweep with only **8** keys produced plausible-looking output but silently left a
~9.5 KB region of `zygiskd`'s `.data` (VA `0x1DBA69`–`0x1DDF95`) undecrypted. Two call sites in
the `ptrace` path pointed into it and produced garbage with every known key.

Rather than treat that as "already covered", the whole file was scanned for **any** 32-byte window
that would decrypt those two strings. Exactly one offset hit — `0x5730` — and it turned out to be
the **last slot of the key table**, i.e. a key that had simply been outside the range first dumped.
The recovered plaintexts were:

```
0x1DD533 (48 bytes) -> "!! init is not stopped, trying to interrupt init"
0x1DD7C8 (21 bytes) -> "** attaching init ..."
```

which are precisely the strings that describe the `init` ptrace/hook step in
[02](02-architecture-and-behavior.md). Re-running the sweep with the full 38-key set raised the
arm64 `zygiskd` corpus from 191 to **922** strings of ≥ 12 characters.

That gap matters methodologically: **a partial key set produces a partially complete — and
therefore misleadingly reassuring — string table.** All numbers in this research are from the
exhaustive 38-key pass.

## 4.4 Decryption reference implementation

```python
def decrypt(blob: bytes, key: bytes) -> bytes:
    return bytes(blob[i] ^ key[i % 32] for i in range(len(blob)))

# find the key for an address inside a binary:
#   off = va2off(va)          # via PT_LOAD segments
#   plain = decrypt(raw[off:off+n], key)
```

Sweeping is simply that function applied at every offset for every key, with a printable-string
filter.

## 4.5 Results

| Binary | Encrypted strings found | ≥ 12 chars | Suspicious |
|---|---:|---:|---:|
| `bin/arm64-v8a/zygiskd` | 1,370 | 922 | 0 |
| `bin/armeabi-v7a/zygiskd` | 510 | 152 | 0 |
| `bin/x86_64/zygiskd` | 731 | 205 | 0 |
| `bin/x86/zygiskd` | 331 | 128 | 0 |
| `lib/*/libzygisk.so` (4) | 2,168 | 982 | 0 |
| `lib/*/libzn_loader.so` (4) | 1,238 | 592 | 0 |
| `lib/*/libpayload.so` (3) | 30 | 26 | 0 |
| **Total** | **5,877** | **2,816** | **0** |

Raw per-binary tables: [`artifacts/`](artifacts/).
Counts: [`artifacts/summary.json`](artifacts/summary.json).

## 4.6 What this implies for the assessment

- The obfuscation **hid nothing interesting**. Once removed, the strings are ordinary developer
  logs, format-string errors from `{fmt}`, libc++ exception text, and file paths — all local.
- The obfuscation also has **no bearing on capability**: it protects *strings*, not behaviour.
  Behaviour was audited independently through the decompiled code and the import/syscall census.
- Because the keys are static and shared across builds, this is a **deterministic, fully
  reproducible** decryption — anyone can re-derive every string in `artifacts/`.
