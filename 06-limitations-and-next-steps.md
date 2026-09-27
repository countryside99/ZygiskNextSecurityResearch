# 06 — Limitations and Next Steps

This document exists because "we didn't find malware" is only useful if it is explicit about what
was and was not actually checked.

## 6.1 What this analysis *does* establish

For the specific artifact `Zygisk-Next-1.5.0-843-5217106-release.zip`
(SHA-256 `474d58ab…1933b`, byte-identical to the official release asset):

- The module **cannot** reach an Internet endpoint: no name-resolution API, no address-conversion
  API, no HTTP/TLS API, and every `socket()` — imported or raw — is `AF_UNIX`.
- Every one of the **178** imported symbols across all 15 binaries was reviewed; every one of the
  **15** raw syscalls in `libzygisk.so` was identified; **`libzn_loader.so` has zero raw syscalls**;
  **`libpayload.so` has zero imports**.
- **8,887 functions / 13.8 MB** of arm64 pseudocode were produced with **0 decompiler failures**.
- **All 38 string-encryption keys** were recovered and every binary was swept exhaustively:
  **5,877** decrypted strings, **0** matching network/exfiltration/C2/credential patterns.
- The one aggressive technique present (`ptrace` + inline `execve` hook on `init`) is
  self-documented by its own progress-log strings and its purpose is reconstructable end-to-end.

## 6.2 What it does *not* establish

| # | Gap | Why it matters |
|---|---|---|
| **G1** | **No runtime observation.** Everything here is static. | Static analysis can prove a capability is absent from *this binary*; it cannot show what the installed system does over a week of normal use, nor what happens through paths only taken on a specific device/ROM. |
| **G2** | **Only arm64 was decompiled.** armeabi-v7a, x86 and x86_64 were import- and string-audited only. | A capability hidden *only* in a 32-bit binary would have been caught by the import/syscall/string layers but not by a line-by-line code review. |
| **G3** | **Not every one of the 8,887 functions was line-by-line reviewed.** | The corpus was searched systematically (network/exec/ptrace/chmod tokens, all imports, all raw syscalls, all strings). That is broad, but it is not a formal verification of every branch. |
| **G4** | **`machikado.*` / `mazoku` are unexplained.** | Six per-ABI 96-byte blobs plus `mazoku`, each with a `.sha256` sidecar, opened and checked by `zygiskd` (`open machikado failed`, `verify1 failed`, `verify2 failed`). They are **not** XOR keys (tested), **not** shellcode, and Ed25519 was falsified. Unknown inputs to a privileged process are exactly what should stay on the open list. |
| **G5** | **`exec_cmd` / `/system/bin/sh` was not observed.** | The daemon can spawn a shell. The strings indicate root-solution probing (`truncate su -c 'echo Success'`, `/data/adb/apd -V`), but the full set of commands it may issue on a given device is only visible at runtime. |
| **G6** | **The build is not reproducible from source.** | No source, no CI provenance, no signature over the binaries. The SHA-256 proves the artifact is unmodified; it does not prove what produced it. |
| **G7** | **`updateJson` is a live supply channel.** | `https://lsposed.zip/zygisk-next/update.json` can deliver a different binary later. A clean 1.5.0 says nothing about 1.5.1. |
| **G8** | **`libzygisk.so`'s control flow is compiler-flattened.** | Readable in bulk (hence the corpus-wide search), painful to audit branch-by-branch. Flattening itself is not evidence of malice, but it does raise review cost. |

**Honest overall statement:** high confidence that this build is not malware; the residual risk is
concentrated in G1, G2, G4, G5 and G7.

## 6.3 Next steps, ranked by confidence gained per unit of effort

### Tier 1 — highest value

1. **Dynamic socket audit on a rooted device / emulator.**
   Run `zygiskd` and exercise apps while tracing:
   ```sh
   strace -f -e trace=network,process -p $(pidof zygiskd)
   # or: eBPF/bpftrace on sys_enter_connect with family != AF_UNIX
   ```
   **Pass criterion:** *every* `socket()`/`connect()` is `AF_UNIX`; zero `AF_INET`/`AF_INET6`.
   This converts §3 from a static claim into an observed one.

2. **Egress capture while the module is under load.**
   `tcpdump`/`mitmproxy` on the device while installing modules, toggling denylist, running
   banking/root-detecting apps. **Pass criterion:** no traffic attributable to the module.

3. **Trace `exec_cmd`.** Log every `execve` of `/system/bin/sh` and its argv for a full boot +
   24 h. Directly closes G5.

### Tier 2 — cheap now that the pipeline exists

4. **Decompile the remaining 3 ABIs.** The headless pipeline (`idat.exe -A -S<script>`) already
   works and takes minutes per binary; then rerun the same corpus searches. Closes G2.

5. **Resolve `machikado`/`mazoku` (G4).** Dynamic approach: breakpoint `open`/`read` on those
   files, dump the consumer function and the buffer as it is used; diff the 96 bytes across
   releases. Static approach: locate the `verify1`/`verify2` functions and hand-decompile them.

6. **Re-run the analysis on every new release.** Because the keys, sweep, and corpus search are
   fully scripted, a future build can be re-audited in under an hour. Publish the script and the
   negative rules.

### Tier 3 — systemic

7. **Publish regression rules** so the community can test *any* build cheaply:
   - no `AF_INET`/`AF_INET6` socket creation in any shipped binary,
   - no `getaddrinfo`/`inet_*` imports,
   - no `bind`/`listen` outside `zygiskd`,
   - `libpayload.so` remains import-free and `AF_UNIX`-only,
   - decrypted strings must match the negative pattern list in [03](03-network-zero-capability.md).

8. **Request build provenance from the maintainers** (reproducible builds, CI logs, artifact
   attestation). Closes G6 — and note this is a *feature request*, not an accusation.

9. **Track `updateJson`** and pin SHA-256s of future releases; diff new builds against 843-5217106
   before updating. Closes G7.

## 6.4 What would change the verdict

Evidence that would move this from "high confidence benign" to a **finding**:

- any `socket(AF_INET*)` / `sendto` / name resolution in any binary or at runtime;
- decrypted strings containing endpoints, tokens, or harvested data fields;
- `machikado`/`mazoku` decoding into executable instructions or a network payload;
- `exec_cmd` issuing anything beyond local root-solution probing;
- a future build whose SHA-256 differs without a corresponding release note.

Evidence that would move it the other way: a reproducible build pipeline, signed releases, and a
clean dynamic trace — all achievable with the steps above.

## 6.5 Reproducibility of this research

| Step | How |
|---|---|
| Hash the artifact | `Get-FileHash -Algorithm SHA256 <zip>` |
| Compare tree vs zip | Re-extract and diff (0 differences expected) |
| Enumerate imports | `pyelftools`, `.dynsym` `st_shndx == SHN_UNDEF` |
| Decompile | IDA 9.1 + Hex-Rays AArch64; `idat.exe -A -S…` for headless |
| Recover keys | Read 32-byte slots at the table offsets in [04](04-string-crypto-method.md) |
| Decrypt strings | `blob[i] ^ key[i % 32]`, swept at every offset for every key |
| Re-check results | `artifacts/` contains every per-binary string table and `summary.json` |
