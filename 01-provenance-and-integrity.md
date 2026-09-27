# 01 — Provenance and Integrity

Everything in this research is about the **exact artifact** described below. Establishing that the
bytes under analysis are the bytes the project published is a prerequisite for any conclusion.

## 1.1 The artifact

| Field | Value |
|---|---|
| File | `Zygisk-Next-1.5.0-843-5217106-release.zip` |
| Size | **7,529,581 bytes** |
| SHA-256 | `474d58abc208c0779e7f8f1d8449db755a874d475c13b9cf8decf74bc171933b` |
| Publisher | https://github.com/LSPosed/ZygiskNext/releases/tag/1.5.0 |
| Released | 2026-09-20 |

The GitHub release metadata (`GET https://api.github.com/repos/LSPosed/ZygiskNext/releases`,
asset digest field) reports the identical `sha256:474d58ab…1933b` and the identical `size: 7529581`.
**The local zip is byte-identical to the official release asset.**

### `module.prop`

```
id=zygisksu
name=Zygisk Next
version=1.5.0 (843-5217106-release)
versionCode=843
author=5ec1cff, Nullptr, aviraxp
description=Standalone implementation of Zygisk.
updateJson=https://lsposed.zip/zygisk-next/update.json
```

`version=1.5.0 (843-5217106-release)` matches the asset name, so the packaging is internally
consistent.

## 1.2 Extracted tree vs. zip

| Check | Result |
|---|---|
| Files in zip (non-directory) | 74 |
| Files byte-differing from zip | **0** |
| Files missing from disk | **0** |
| Extra files on disk | 6 — all analysis artifacts produced by this research (`.i64`, logs), not part of the release |
| `*.sha256` sidecar files re-verified | **37 / 37 OK, 0 failures** |

Conclusion: the tree that was analyzed **is** the release zip, unmodified.

## 1.3 The "HyperOS Rust Runtime" question

The binaries contain strings such as:

```
failed to register HyperOS Rust Runtime hooks
HyperOS Rust Runtime hooks installed for {} module(s)
failed to initialize HyperOS Rust Runtime ELF at {}
HyperOS Rust Runtime is missing PLT symbol {}
HyperOS Rust Runtime specialization is missing package name or seinfo
/system_ext/bin/hyos_spawner
```

A closed-source component speaking undocumented hooks into a vendor process is exactly the kind of
thing this research should treat as suspicious. It is not.

- The **project's own README** documents the feature (v1.5.0 section).
- The **release notes** for 1.5.0 state verbatim: *"Adds
  [HyperOS Runtime support](https://github.com/LSPosed/ZygiskNext/blob/main/docs/hyos_runtime.md)"*.
- That document exists and describes a **module-facing API** (`ZygiskNextHyosModule`,
  `onAppSpecialized`) for applications running in Xiaomi's HyperOS Rust Runtime, which is
  *independent of ART and provides no JNI* — i.e. a second, non-Java app runtime that a Zygisk
  implementation must still be able to inject into.
- The recovered strings line up one-for-one with that document: `path=/system_ext/bin/hyos_spawner`,
  `package_name`, `se_info`, "specialization is missing package name or seinfo".

The release zip simply **does not ship** `docs/hyos_runtime.md` or `zygisk_next_api.h` (they live in
the source repository, not the packaged module). The absence of the docs from the zip is a
packaging choice, not concealment — the documentation is public.

**Verdict: explained, documented, benign.**

## 1.4 Things that are *not* explained by the local zip
1 Honest caveat belong here rather than being buried:

 **Remote update channel.** `updateJson=https://lsposed.zip/zygisk-next/update.json` means the
   installed module can be replaced by whatever that endpoint serves later. A clean 1.5.0 today
   says nothing about 1.5.1. Any conclusion from this research is scoped to **this build
   (843-5217106)**.


## 1.5 Reproduction

```powershell
# 1. hash of the local artifact
Get-FileHash -Algorithm SHA256 .\Zygisk-Next-1.5.0-843-5217106-release.zip
# -> 474d58abc208c0779e7f8f1d8449db755a874d475c13b9cf8decf74bc171933b

# 2. compare the extracted tree against the archive (0 differences expected)
# 3. re-check every bundled *.sha256 sidecar (37/37 expected)
```
