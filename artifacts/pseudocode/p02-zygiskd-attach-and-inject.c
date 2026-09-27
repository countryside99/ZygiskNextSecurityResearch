/*
 * zygiskd - attach to init, deliver the payload, inject zygote
 * ============================================================
 * Selected functions from the arm64 control daemon:
 *
 *   0xF45D0  attach-to-init + payload load (progress logs "** attaching init ...",
 *            "** payload loaded", libpayload base reporting)
 *   0x85AC8  "send lib fd" - passes the payload fd over the local socket
 *   0x74B2C  injector naming / "inject {} {} succeed" + "Zygisk Next Controller"
 *   0x7E004  dump maps / dump regs helper used around ptrace stops
 *
 * Omitted here only because of size (both are the same flattened body, and both are
 * summarised in 02-architecture-and-behavior.md and 05-behavior-evidence-catalog.md):
 *   0xF59D0  the main inject_execve_monitor routine (3156 lines)
 *   0x8A1B8  PTRACE_SEIZE / PTRACE_ATTACH / PTRACE_DETACH wrappers (1839 lines)
 *
 * Auto-extracted from the Hex-Rays AArch64 decompilation of
 *   bin/arm64-v8a/zygiskd
 * Strings that the binary XOR-decrypts at runtime have been
 * substituted back in as C string literals. Nothing else was edited.
 */

// ===== 0x74B2C sub_74B2C =====
__int64 __fastcall sub_74B2C(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6)
{
  __int64 v6; // x3
  __int64 v7; // x5
  __int64 v8; // x3
  __int64 v9; // x5
  __int64 v10; // x3
  __int64 v11; // x5
  __int64 v12; // x3
  __int64 v13; // x5
  __int64 v14; // x3
  __int64 v15; // x5
  __int64 v16; // x3
  __int64 v17; // x5
  __int64 v18; // x3
  __int64 v19; // x5
  __int64 v20; // x3
  __int64 v21; // x5
  __int64 v22; // x3
  __int64 v23; // x5
  __int64 v24; // x3
  __int64 v25; // x5
  __int64 v26; // x3
  __int64 v27; // x5
  __int64 v28; // x3
  __int64 v29; // x5
  __int64 v30; // x3
  __int64 v31; // x5
  __int64 v32; // x3
  __int64 v33; // x5
  __int64 v34; // x3
  __int64 v35; // x5
  __int64 v36; // x3
  __int64 v37; // x5
  __int64 v38; // x3
  __int64 v39; // x5
  __int64 v40; // x3
  __int64 v41; // x5
  __int64 v42; // x3
  __int64 v43; // x5
  __int64 v44; // x3
  __int64 v45; // x5
  __int64 v46; // x3
  __int64 v47; // x5
  __int64 v48; // x3
  __int64 v49; // x5
  __int64 v50; // x3
  __int64 v51; // x5
  __int64 v52; // x3
  __int64 v53; // x5
  __int64 v54; // x3
  __int64 v55; // x5
  __int64 v56; // x3
  __int64 v57; // x5
  __int64 v58; // x3
  __int64 v59; // x5
  __int64 v60; // x3
  __int64 v61; // x5
  __int64 v62; // x3
  __int64 v63; // x5
  __int64 v64; // x3
  __int64 v65; // x5
  __int64 v66; // x3
  __int64 v67; // x5
  __int64 v68; // x3
  __int64 v69; // x5
  __int64 v70; // x3
  __int64 v71; // x5
  __int64 v72; // x3
  __int64 v73; // x5
  __int64 v74; // x3
  __int64 v75; // x5
  __int64 v76; // x3
  __int64 v77; // x5
  __int64 v78; // x3
  __int64 v79; // x5
  __int64 v80; // x3
  __int64 v81; // x5
  __int64 v82; // x3
  __int64 v83; // x5
  int i; // w8
  __int64 v85; // x3
  __int64 v86; // x5
  __int64 v87; // x3
  __int64 v88; // x5
  __int64 v89; // x3
  __int64 v90; // x5
  __int64 v91; // x3
  __int64 v92; // x5
  __int64 v93; // x3
  __int64 v94; // x5
  __int64 v95; // x3
  __int64 v96; // x5
  __int64 v97; // x3
  __int64 v98; // x5
  __int64 v99; // x3
  __int64 v100; // x5
  __int64 v101; // x3
  __int64 v102; // x5
  __int64 v103; // x3
  __int64 v104; // x5
  __int64 v105; // x3
  __int64 v106; // x5
  __int64 v107; // x3
  __int64 v108; // x5
  __int64 v109; // x3
  __int64 v110; // x5
  __int64 v111; // x3
  __int64 v112; // x5
  __int64 v113; // x3
  __int64 v114; // x5
  __int64 v115; // x3
  __int64 v116; // x5
  __int64 v117; // x3
  __int64 v118; // x5
  __int64 v119; // x3
  __int64 v120; // x5
  __int64 v121; // x3
  __int64 v122; // x5
  __int64 v123; // x3
  __int64 v124; // x5
  __int64 v125; // x3
  __int64 v126; // x5
  __int64 v127; // x3
  __int64 v128; // x5

  sub_751CC("daemon", "daemon", 7, a4, 0, a6);
  sub_751CC(&unk_1DAF9C, &unk_1DAF9C, 2, v6, 0, v7);
  sub_751CC("zygisk-companion", "zygisk-companion", 17, v8, 0, v9);
  sub_751CC("zn-companion", "zn-companion", 13, v10, 0, v11);
  sub_751CC("nsdaemon", "nsdaemon", 9, v12, 0, v13);
  sub_751CC("zygote-injector", "zygote-injector", 16, v14, 0, v15);
  sub_751CC("service-injector", "service-injector", 17, v16, 0, v17);
  sub_751CC("stub-zygote-injector", "stub-zygote-injector", 21, v18, 0, v19);
  sub_751CC("injecting {} {} (injector {})", "injecting {} {} (injector {})", 30, v20, 0, v21);
  sub_751CC("failed to inject {} {}: {}", "failed to inject {} {}: {}", 27, v22, 0, v23);
  sub_751CC("inject {} {} succeed", "inject {} {} succeed", 21, v24, 0, v25);
  sub_751CC("service-stage", "service-stage", 14, v26, 0, v27);
  sub_751CC(&unk_1DB065, &unk_1DB065, 5, v28, 0, v29);
  sub_751CC(&unk_1DB06A, &unk_1DB06A, 3, v30, 0, v31);
  sub_751CC("dump-ctx", "dump-ctx", 9, v32, 0, v33);
  sub_751CC(&unk_1DB08F, &unk_1DB08F, 6, v34, 0, v35);
  sub_751CC(&unk_1DB095, &unk_1DB095, 5, v36, 0, v37);
  sub_751CC(&unk_1DB09A, &unk_1DB09A, 5, v38, 0, v39);
  sub_751CC("status", "status", 7, v40, 0, v41);
  sub_751CC("denylist-policy", "denylist-policy", 16, v42, 0, v43);
  sub_751CC("default", "default", 8, v44, 0, v45);
  sub_751CC("whitelist", "whitelist", 10, v46, 0, v47);
  sub_751CC("unknown mode: {}, available: default, whitelist", "unknown mode: {}, available: default, whitelist", 49, v48, 0, v49);
  sub_751CC("enforce-denylist", "enforce-denylist", 17, v50, 0, v51);
  sub_751CC("disabled", "disabled", 9, v52, 0, v53);
  sub_751CC("enabled", "enabled", 8, v54, 0, v55);
  sub_751CC("just_umount", "just_umount", 12, v56, 0, v57);
  sub_751CC("unknown mode: {}, available: disabled, enabled, just_umount", "unknown mode: {}, available: disabled, enabled, just_umount", 61, v58, 0, v59);
  sub_751CC("memory-type", "memory-type", 12, v60, 0, v61);
  sub_751CC("anonymous", "anonymous", 10, v62, 0, v63);
  sub_751CC("unknown mode: {}, available: default, anonymous", "unknown mode: {}, available: default, anonymous", 49, v64, 0, v65);
  sub_751CC("linker", "linker", 7, v66, 0, v67);
  sub_751CC("system", "system", 7, v68, 0, v69);
  sub_751CC("builtin", "builtin", 8, v70, 0, v71);
  sub_751CC("unknown mode: {}, available: system, builtin", "unknown mode: {}, available: system, builtin", 46, v72, 0, v73);
  sub_751CC("exp_hook", "exp_hook", 9, v74, 0, v75);
  sub_751CC("enable", "enable", 7, v76, 0, v77);
  sub_751CC("disable", "disable", 8, v78, 0, v79);
  sub_751CC("unknown mode: {}, available: enable, disable", "unknown mode: {}, available: enable, disable", 46, v80, 0, v81);
  for ( i = 393204058; i == 393204058; i = 914414677 )
  {
    sub_751CC("disable-zygisk", "disable-zygisk", 15, v82, 0, v83);
    sub_751CC(&unk_1DB244, &unk_1DB244, 5, v85, 0, v86);
    sub_751CC(&unk_1DB249, &unk_1DB249, 6, v87, 0, v88);
    sub_751CC("unknown value: {}, available: true, false", "unknown value: {}, available: true, false", 43, v89, 0, v90);
    sub_751CC("dump-zn", "dump-zn", 8, v91, 0, v92);
    sub_751CC(&unk_1DB282, &unk_1DB282, 4, v93, 0, v94);
    sub_751CC("--webui", "--webui", 8, v95, 0, v96);
    sub_751CC(&unk_1DB28E, &unk_1DB28E, 6, v97, 0, v98);
    sub_751CC("reload", "reload", 7, v99, 0, v100);
    sub_751CC("unknown cmd: {}, enable, disable or reload is required.", "unknown cmd: {}, enable, disable or reload is required.", 56, v101, 0, v102);
    sub_751CC("Zygisk Next Controller {}", "Zygisk Next Controller {}", 27, v103, 0, v104);
  }
  sub_751CC("Usage:", "Usage:", 8, v82, 0, v83);
  sub_751CC("  znctl start|stop|exit|status", "  znctl start|stop|exit|status", 32, v105, 0, v106);
  sub_751CC("  znctl disable-zygisk <true|false>", "  znctl disable-zygisk <true|false>", 37, v107, 0, v108);
  sub_751CC("  znctl denylist-policy <default|whitelist>", "  znctl denylist-policy <default|whitelist>", 45, v109, 0, v110);
  sub_751CC("  znctl enforce-denylist <disabled|enabled|just_umount>", "  znctl enforce-denylist <disabled|enabled|just_umount>", 57, v111, 0, v112);
  sub_751CC("  znctl memory-type <default|anonymous>", "  znctl memory-type <default|anonymous>", 41, v113, 0, v114);
  sub_751CC("  znctl linker <system|builtin>", "  znctl linker <system|builtin>", 33, v115, 0, v116);
  sub_751CC("  znctl dump-zn [-sa] [--webui]", "  znctl dump-zn [-sa] [--webui]", 33, v117, 0, v118);
  sub_751CC("  znctl znmod <enable|disable|reload> <mod[:lib]> [svc]", "  znctl znmod <enable|disable|reload> <mod[:lib]> [svc]", 57, v119, 0, v120);
  sub_751CC("  znctl exp_hook <enable|disable>", "  znctl exp_hook <enable|disable>", 35, v121, 0, v122);
  sub_751CC("unsupported architecture", "unsupported architecture", 25, v123, 0, v124);
  sub_751CC("set arg start failed with {}", "set arg start failed with {}", 29, v125, 0, v126);
  return sub_751CC("set arg end failed with {}", "set arg end failed with {}", 27, v127, 0, v128);
}


// ===== 0x7E004 sub_7E004 =====
void __usercall sub_7E004(
        __int64 a1@<X0>,
        long double *a2@<X3>,
        __int64 a3@<X8>,
        double a4@<D0>,
        double a5@<D1>,
        long double a6@<Q2>,
        long double a7@<Q3>,
        int8x16_t a8@<Q4>,
        int8x16_t a9@<Q5>)
{
  int v9; // w28
  unsigned int *v11; // x21
  int i; // w8
  int v13; // w9
  bool v14; // zf
  unsigned int v15; // w29
  long double *v16; // x3
  double v17; // d0
  double v18; // d1
  long double v19; // q2
  long double v20; // q3
  int8x16_t v21; // q4
  int8x16_t v22; // q5
  int v23; // [xsp+Ch] [xbp-2F4h]
  unsigned int v24; // [xsp+10h] [xbp-2F0h]
  int v25; // [xsp+14h] [xbp-2ECh]
  _BYTE v26[32]; // [xsp+18h] [xbp-2E8h] BYREF
  __int64 v27[3]; // [xsp+38h] [xbp-2C8h] BYREF
  _QWORD v28[5]; // [xsp+50h] [xbp-2B0h] BYREF
  _BYTE v29[40]; // [xsp+78h] [xbp-288h] BYREF
  _BYTE v30[272]; // [xsp+A0h] [xbp-260h] BYREF
  _QWORD v31[4]; // [xsp+1B0h] [xbp-150h] BYREF
  __int64 v32[3]; // [xsp+1D0h] [xbp-130h] BYREF
  _QWORD v33[5]; // [xsp+1E8h] [xbp-118h] BYREF
  _BYTE v34[40]; // [xsp+210h] [xbp-F0h] BYREF
  __int64 v35[3]; // [xsp+238h] [xbp-C8h] BYREF
  _QWORD v36[4]; // [xsp+250h] [xbp-B0h] BYREF
  _BYTE v37[48]; // [xsp+270h] [xbp-90h] BYREF

  v11 = (unsigned int *)(a1 + 8);
  for ( i = -1760938298; ; i = -347679834 )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        while ( 1 )
        {
          while ( i <= -16776478 )
          {
            if ( i > -857526627 )
            {
              if ( i > -390279023 )
              {
                if ( i <= -323285090 )
                {
                  if ( i == -390279022 )
                  {
                    v9 = 0;
                    i = -514034491;
                  }
                  else
                  {
                    sub_7ECE8(v34);
                    v25 = v9;
                    i = 2044540678;
                  }
                }
                else if ( i == -323285089 )
                {
                  sub_3D158(&byte_6, (__int64)"dumping maps:", 13);
                  v15 = *v11;
                  sub_7E848(v37);
                  sub_1CDCCC(v15, v37);
                  sub_7E89C(v37);
                  sub_3D158(&byte_6, (__int64)"dumping regs:", 13);
                  if ( ptrace(PTRACE_INTERRUPT, *v11, 0, 0) >= 0 )
                    i = 509138053;
                  else
                    i = 1632373867;
                }
                else if ( i == -282669980 )
                {
                  sub_7DC10((__int64)"wait for stop", (__int64)"wait for stop", 0xEu, a2, &dword_1E0CF4, a4, a5, a6, a7, a8, a9);
                  sub_3D378(v32, "wait for stop");
                  sub_7EB40(v33, v32);
                  i = -1686885374;
                }
                else
                {
                  sub_7EAFC(a3, v26);
                  i = -715185779;
                }
              }
              else if ( i <= -726535687 )
              {
                if ( i == -857526626 )
                {
                  ((void (__fastcall *)(_QWORD, _BYTE *))loc_D4978)(*v11, v30);
                  i = 188353915;
                }
                else
                {
                  sub_7EDAC(v34);
                  i = 1158055772;
                }
              }
              else if ( i == -726535686 )
              {
                sub_7ED84(v31, v34);
                i = 414795649;
              }
              else if ( i == -715185779 )
              {
                sub_7B9B8((__int64)v26);
                i = 769603132;
              }
              else
              {
                sub_7B9C0((__int64)v29);
                v23 = v9;
                i = 1396844839;
              }
            }
            else if ( i > -1493102706 )
            {
              if ( i <= -1142708355 )
              {
                if ( i != -1493102705 )
                {
                  v9 = 1;
                  goto LABEL_54;
                }
                sub_7EDC0(v28, v27);
                sub_7EF34(v29, v28);
                if ( (v27[0] & 1) != 0 )
                  free((void *)v27[2]);
                sub_7B9C0((__int64)v28);
                if ( sub_7B320() )
                  i = -932510812;
                else
                  i = -1803041512;
              }
              else if ( i == -1142708354 )
              {
                sub_7B9B8((__int64)v31);
                i = 1992574248;
              }
              else if ( i == -932510812 )
              {
                sub_7B4D8();
                i = -58205863;
              }
              else
              {
                v9 = 0;
                i = -347679834;
              }
            }
            else if ( i <= -1760938299 )
            {
              if ( i == -1839761915 )
              {
                i = -16776477;
              }
              else
              {
                sub_7EF78(v29);
                i = -390279022;
              }
            }
            else
            {
              switch ( i )
              {
                case -1760938298:
                  i = 739882849;
                  break;
                case -1686885374:
                  sub_7ECA4(v34, v33);
                  if ( (v32[0] & 1) != 0 )
                    free((void *)v32[2]);
                  sub_7ECE8(v33);
                  if ( (sub_7ED2C(v34) & 1) != 0 )
                    i = -726535686;
                  else
                    i = -851532135;
                  break;
                case -1497726321:
                  sub_C8C60(v33, *v11);
                  i = -282669980;
                  break;
              }
            }
          }
          if ( i > 769603131 )
            break;
          if ( i > 260421999 )
          {
            if ( i <= 414795648 )
            {
              if ( i == 260422000 )
              {
                sub_C681C(v28, v24, v30);
                sub_7DC10(
                  (__int64)"get regs for dump",
                  (__int64)"get regs for dump",
                  0x12u,
                  v16,
                  &dword_1E0CF8,
                  v17,
                  v18,
                  v19,
                  v20,
                  v21,
                  v22);
                sub_3D378(v27, "get regs for dump");
                i = -1493102705;
              }
              else
              {
                i = 2035898867;
              }
            }
            else if ( i == 414795649 )
            {
              sub_7EAFC(a3, v31);
              i = -1142708354;
            }
            else if ( i == 509138053 )
            {
              i = -1497726321;
            }
            else
            {
              i = -323285089;
            }
          }
          else if ( i <= 68839444 )
          {
            if ( i == -16776477 )
            {
              v24 = *v11;
              i = 260422000;
            }
            else
            {
              i = -857526626;
            }
          }
          else
          {
            if ( i == 68839445 )
            {
              v13 = 1551021095;
              v14 = v25 == 1;
              i = 2035898867;
              goto LABEL_3;
            }
            if ( i == 185092941 )
            {
              sub_7E8E0(v36, v35);
              sub_7EAFC(a3, v36);
              i = 1722858041;
            }
            else
            {
              sub_7EFBC();
              i = -1216321412;
            }
          }
        }
        if ( i > 1632373866 )
          break;
        if ( i <= 1396844838 )
        {
          if ( i == 769603132 )
          {
            v9 = 1;
            i = -514034491;
          }
          else
          {
            i = -885997719;
          }
        }
        else if ( i == 1396844839 )
        {
          v13 = 1934954066;
          v14 = v23 == 0;
          i = 7265946;
LABEL_3:
          if ( !v14 )
            i = v13;
        }
        else if ( i == 1424623103 )
        {
          i = 2035898867;
        }
        else
        {
          i = -1760679292;
        }
      }
      if ( i > 1992574247 )
        break;
      if ( i == 1632373867 )
      {
        sub_7DC10((__int64)"interrupt", (__int64)"interrupt", 0xAu, a2, &dword_1E0CF0, a4, a5, a6, a7, a8, a9);
        sub_3D378(v35, "interrupt");
        i = 185092941;
      }
      else if ( i == 1722858041 )
      {
        sub_7B9B8((__int64)v36);
        i = 382509885;
        if ( (v35[0] & 1) != 0 )
        {
          free((void *)v35[2]);
          i = 382509885;
        }
      }
      else
      {
LABEL_54:
        i = 1424623103;
      }
    }
    if ( i != 1992574248 )
      break;
    v9 = 1;
  }
  if ( i == 2044540678 )
  {
    v13 = 68839445;
    v14 = v25 == 0;
    i = -1839761915;
    goto LABEL_3;
  }
}


// ===== 0x85AC8 sub_85AC8 =====
void __usercall sub_85AC8(__int64 a1@<X0>, __int64 a2@<X8>)
{
  int v2; // w27
  _BYTE *v3; // x21
  __int64 v6; // x0
  int8x16_t *v7; // x3
  __int64 v8; // x4
  unsigned int v9; // w5
  unsigned int v10; // w6
  char v11; // w7
  long double v12; // q0
  long double v13; // q1
  long double v14; // q2
  long double v15; // q3
  int8x16_t v16; // q4
  int8x16_t v17; // q5
  _BYTE *v18; // x10
  int i; // w8
  int v20; // w0
  char *file; // [xsp+10h] [xbp-170h]
  int v22; // [xsp+20h] [xbp-160h]
  int v23; // [xsp+24h] [xbp-15Ch]
  int v24; // [xsp+28h] [xbp-158h]
  int v25; // [xsp+2Ch] [xbp-154h]
  unsigned int v26; // [xsp+30h] [xbp-150h]
  int v27; // [xsp+34h] [xbp-14Ch]
  _BYTE v28[32]; // [xsp+38h] [xbp-148h] BYREF
  __int64 v29[3]; // [xsp+58h] [xbp-128h] BYREF
  _QWORD v30[5]; // [xsp+70h] [xbp-110h] BYREF
  _BYTE v31[40]; // [xsp+98h] [xbp-E8h] BYREF
  long double v32; // [xsp+C0h] [xbp-C0h] BYREF
  void *v33; // [xsp+D0h] [xbp-B0h]
  void *v34[3]; // [xsp+E0h] [xbp-A0h] BYREF
  _DWORD v35[9]; // [xsp+F8h] [xbp-88h] BYREF
  unsigned int v36; // [xsp+11Ch] [xbp-64h] BYREF

  v3 = (_BYTE *)(a1 + 624);
  v6 = sub_3CF1C(a1 + 624);
  sub_D234C(v6);
  file = (char *)sub_7D5B8(v3);
  v18 = v3;
  for ( i = -1831319587; ; i = -873247470 )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        while ( 1 )
        {
          while ( i > 520043929 )
          {
            if ( i <= 1007574561 )
            {
              if ( i > 657598466 )
              {
                if ( i == 657598467 )
                {
                  if ( v23 )
                    i = 750109833;
                  else
                    i = 1007574562;
                }
                else
                {
                  if ( i == 750109833 )
                    goto LABEL_61;
                  sub_7ED84((__int64)v31);
                  v18 = v3;
                  i = 1529888112;
                }
              }
              else if ( i == 520043930 )
              {
                sub_7ECE8((__int64)v31);
                v18 = v3;
                v23 = v2;
                i = 657598467;
              }
              else
              {
                if ( i == 593400355 )
                {
                  if ( ((__int64)v34[0] & 1) != 0 )
                  {
                    free(v34[2]);
                    v18 = v3;
                  }
                  if ( (LOBYTE(v32) & 1) != 0 )
                  {
                    free(v33);
                    v18 = v3;
                  }
                  goto LABEL_60;
                }
                v2 = 1;
                i = 520043930;
              }
            }
            else if ( i <= 1529888111 )
            {
              if ( i == 1007574562 )
              {
                i = -1164407721;
                v24 = v22;
              }
              else if ( i == 1181302248 )
              {
                *(_DWORD *)(a1 + 768) = v24;
                sub_7EFBC(a2);
                v18 = v3;
                i = -1760496713;
              }
              else
              {
                if ( (*v18 & 1) != 0 )
                {
                  sub_6D968((__int64)&v32, *(void **)(a1 + 640), *(_QWORD *)(a1 + 632), v7, v8, v9, v10, v11, v12, v13);
                  v18 = v3;
                }
                else
                {
                  v12 = *(long double *)v18;
                  v33 = (void *)*((_QWORD *)v18 + 2);
                  v32 = v12;
                }
                i = -947561812;
              }
            }
            else if ( i > 1590843869 )
            {
              if ( i == 1590843870 )
              {
                if ( v27 == -1 )
                  i = 1206493613;
                else
                  i = 1760105409;
              }
              else
              {
                i = -441555445;
              }
            }
            else if ( i == 1529888112 )
            {
              sub_7EAFC(a2, (__int64)v28);
              v18 = v3;
              i = -166157975;
            }
            else
            {
              i = -1760950075;
              v22 = v25;
            }
          }
          if ( i > -1087365427 )
            break;
          if ( i <= -1760496714 )
          {
            if ( i == -2011300451 )
            {
              sub_3D40C((int *)&v36);
              v18 = v3;
              i = -1087365426;
            }
            else if ( i == -1831319587 )
            {
              v20 = open(file, 0x80000);
              sub_3CDD4(&v36, v20);
              v18 = v3;
              i = -1743049016;
            }
            else
            {
              v18 = v3;
              v2 = 0;
              i = 520043930;
            }
          }
          else if ( i > -1676913194 )
          {
            if ( i == -1676913193 )
            {
              v25 = sub_7EDAC();
              v18 = v3;
              i = 1545589925;
            }
            else
            {
              i = 1181302248;
            }
          }
          else if ( i == -1760496713 )
          {
LABEL_60:
            v2 = 1;
LABEL_61:
            i = -2011300451;
          }
          else
          {
            v27 = v36;
            i = 1590843870;
          }
        }
        if ( i <= -166157976 )
          break;
        if ( i == -166157975 )
        {
          sub_7B9B8((__int64)v28);
          v18 = v3;
          i = 595206895;
        }
        else if ( i == 154395506 )
        {
          sub_7DC10(
            (__int64)"send lib fd",
            (__int64)"send lib fd",
            0xCu,
            (long double *)v7->n128_u64,
            &dword_1E0D3C,
            *(double *)&v12,
            *(double *)&v13,
            v14,
            v15,
            v16,
            v17);
          sub_3D378(v29, "send lib fd");
          sub_7EB40((__int64)v30, (__int64)v29);
          sub_7ECA4((__int64)v31);
          if ( (v29[0] & 1) != 0 )
            free((void *)v29[2]);
          sub_7ECE8((__int64)v30);
          if ( sub_7ED2C() )
            i = 811305667;
          else
            i = -1676913193;
          v18 = v3;
        }
        else
        {
          sub_86728(v30, a1, v26);
          v18 = v3;
          i = 154395506;
        }
      }
      if ( i <= -873247471 )
        break;
      if ( i == -873247470 )
      {
        sub_7E8E0((__int64)v34, v35);
        sub_7EAFC(a2, (__int64)v35);
        sub_7B9B8((__int64)v35);
        v18 = v3;
        i = 593400355;
      }
      else
      {
        v26 = v36;
        i = 464098088;
      }
    }
    if ( i != -947561812 )
      break;
    sub_862CC(v34, "open {}", 7, &v32);
    v18 = v3;
  }
}


// ===== 0xF45D0 sub_F45D0 =====
__int64 __fastcall sub_F45D0(__int64 a1, __int64 a2, __int64 a3, __int64 a4)
{
  __int64 v4; // x3
  __int64 v5; // x3
  __int64 v6; // x3
  __int64 v7; // x3
  __int64 v8; // x3
  __int64 v9; // x3
  __int64 v10; // x3
  __int64 v11; // x3
  __int64 v12; // x3
  int i; // w8
  __int64 v14; // x3
  __int64 v15; // x3
  __int64 v16; // x3
  __int64 v17; // x3
  __int64 v18; // x3
  __int64 v19; // x3
  __int64 v20; // x3
  __int64 v21; // x3
  __int64 v22; // x3
  __int64 v23; // x3
  __int64 v24; // x3
  __int64 v25; // x3
  __int64 v26; // x3
  __int64 v27; // x3
  __int64 v28; // x3
  __int64 v29; // x3
  __int64 v30; // x3
  __int64 v31; // x3
  __int64 v32; // x3
  __int64 v33; // x3
  __int64 v34; // x3
  __int64 v35; // x3
  __int64 v36; // x3
  __int64 v37; // x3
  __int64 v38; // x3
  __int64 v39; // x3
  __int64 v40; // x3
  __int64 v41; // x3
  __int64 v42; // x3
  __int64 v43; // x3
  __int64 v44; // x3
  __int64 v45; // x3
  __int64 v46; // x3
  __int64 v47; // x3
  __int64 v48; // x3
  __int64 v49; // x3
  __int64 v50; // x3
  __int64 v51; // x3
  __int64 v52; // x3
  __int64 v53; // x3
  __int64 v54; // x3
  __int64 v55; // x3

  sub_F4B80("inject success!", "inject success!", 16, a4, 0);
  sub_F4B80("inject failed: {}", "inject failed: {}", 18, v4, 0);
  sub_F4B80("** do cleanup", "** do cleanup", 14, v5, 0);
  sub_F4B80("** do restore", "** do restore", 14, v6, 0);
  sub_F4B80("!! init is not stopped, trying to interrupt init", "!! init is not stopped, trying to interrupt init", 49, v7, 0);
  sub_F4B80("failed to interrupt init failed with {}", "failed to interrupt init failed with {}", 40, v8, 0);
  sub_F4B80("wait {}", "wait {}", 8, v9, 0);
  sub_F4B80("restore {}", "restore {}", 11, v10, 0);
  sub_F4B80("detach failed with {}", "detach failed with {}", 22, v11, 0);
  for ( i = -13386003; i == -13386003; i = -497087347 )
  {
    sub_F4B80("dumping ctx {}", "dumping ctx {}", 16, v12, 0);
    sub_F4B80("failed to open", "failed to open", 15, v16, 0);
    sub_F4B80("failed to read", "failed to read", 15, v17, 0);
    sub_F4B80("payload_base=0x{:x}", "payload_base=0x{:x}", 87, v18, 0);
    sub_F4B80("execve_hook.target=0x{:x}", "execve_hook.target=0x{:x}", 293, v19, 0);
    sub_F4B80("** preparing payload ...", "** preparing payload ...", 25, v20, 0);
    sub_F4B80("** payload prepared", "** payload prepared", 20, v21, 0);
    sub_F4B80("** attaching init ...", "** attaching init ...", 22, v22, 0);
    sub_F4B80("seize {}", "seize {}", 9, v23, 0);
    sub_F4B80("get orig sigmask failed with {}", "get orig sigmask failed with {}", 32, v24, 0);
    sub_F4B80("block all sigmask failed with {}", "block all sigmask failed with {}", 33, v25, 0);
    sub_F4B80("** init attached", "** init attached", 17, v26, 0);
    sub_F4B80("** loading payload ...", "** loading payload ...", 23, v27, 0);
    sub_F4B80("libpayload base: {:x}", "libpayload base: {:x}", 22, v28, 0);
    sub_F4B80("** payload loaded", "** payload loaded", 18, v29, 0);
    sub_F4B80("** setting up payload ...", "** setting up payload ...", 26, v30, 0);
    sub_F4B80("** payload has been setup", "** payload has been setup", 26, v31, 0);
    sub_F4B80("** inline hook prepare ...", "** inline hook prepare ...", 27, v32, 0);
    sub_F4B80("/dev/.zn_helper", "/dev/.zn_helper", 16, v14, 0);
    sub_F4B80("set helper fd sys con failed with {}", "set helper fd sys con failed with {}", 37, v15, 0);
  }
  sub_F4B80("/proc/self/fd/{}", "/proc/self/fd/{}", 17, v12, 0);
  sub_F4B80("map seg {}", "map seg {}", 11, v33, 0);
  sub_F4B80("zeromap seg {}", "zeromap seg {}", 15, v34, 0);
  sub_F4B80("stat /proc/1/exe failed with {}", "stat /proc/1/exe failed with {}", 32, v35, 0);
  sub_F4B80("initialize /proc/1/exe", "initialize /proc/1/exe", 23, v36, 0);
  sub_F4B80("can not load libc", "can not load libc", 18, v37, 0);
  sub_F4B80("execve/execveat not found", "execve/execveat not found", 26, v38, 0);
  sub_F4B80("wait4 not found", "wait4 not found", 16, v39, 0);
  sub_F4B80("** using vphone compat", "** using vphone compat", 23, v40, 0);
  sub_F4B80("** hooking {}", "** hooking {}", 14, v41, 0);
  sub_F4B80("*** prepare trampoline", "*** prepare trampoline", 23, v42, 0);
  sub_F4B80("** inline hook commit", "** inline hook commit", 22, v43, 0);
  sub_F4B80("{} hook installed", "{} hook installed", 18, v44, 0);
  sub_F4B80("truncate helper_fd {} failed with {}", "truncate helper_fd {} failed with {}", 37, v45, 0);
  sub_F4B80("failed to map 0x{:x} {}, try next ({})", "failed to map 0x{:x} {}, try next ({})", 39, v46, 0);
  sub_F4B80("could not find map near from={} to={} sz={}", "could not find map near from={} to={} sz={}", 44, v47, 0);
  sub_F4B80("hook {}", "hook {}", 8, v48, 0);
  sub_F4B80("close remote helper fd: {}", "close remote helper fd: {}", 27, v49, 0);
  sub_F4B80("close remote lib fd: {}", "close remote lib fd: {}", 24, v50, 0);
  sub_F4B80("close remote socket fd: {}", "close remote socket fd: {}", 27, v51, 0);
  sub_F4B80("unmap tmp mem: {}", "unmap tmp mem: {}", 18, v52, 0);
  sub_F4B80("restore sigmask failed with {}", "restore sigmask failed with {}", 31, v53, 0);
  sub_F4B80("dump znctx to /data/adb/zygisksu/znctx failed with {}", "dump znctx to /data/adb/zygisksu/znctx failed with {}", 54, v54, 0);
  return sub_F4B80("dump write znctx to /data/adb/zygisksu/znctx failed with {}", "dump write znctx to /data/adb/zygisksu/znctx failed with {}", 60, v55, 0);
}


