/*
 * zygiskd - shell execution and start-up file checks
 * ===================================================
 *   0xD8E38  exec_cmd wrapper ("exec_cmd: fork failed")
 *   0xDEF24  /system/bin/sh invocation - the most capability-dense routine in the
 *            module; used for root-solution probing (see 05-behavior-evidence-catalog.md
 *            row 7 and 06-limitations-and-next-steps.md gap G5 - NOT dynamically confirmed)
 *   0xE4800  opens and verifies ./machikado.<abi> and ./mazoku
 *            ("open machikado failed", "verify1 failed", "open mazoku failed",
 *             "verify2 failed")
 *
 * The purpose of the machikado/mazoku blobs is still unexplained - they are not XOR
 * key material (tested) and Ed25519 was falsified. Recorded as an open item, not
 * explained away.
 *
 * Auto-extracted from the Hex-Rays AArch64 decompilation of
 *   bin/arm64-v8a/zygiskd
 * Strings that the binary XOR-decrypts at runtime have been
 * substituted back in as C string literals. Nothing else was edited.
 */

// ===== 0xD8E38 sub_D8E38 =====
__int64 __fastcall sub_D8E38(__int64 a1, __int64 a2, __int64 a3, __int64 a4)
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

  sub_D9024("ksu KSU_IOCTL_GET_INFO failed failed with {}", "ksu KSU_IOCTL_GET_INFO failed failed with {}", 45, a4, 0);
  sub_D9024("ksu {} found in kernel but no ksud found, skip", "ksu {} found in kernel but no ksud found, skip", 47, v4, 0);
  sub_D9024("ksu uid_should_umount failed failed with {}", "ksu uid_should_umount failed failed with {}", 44, v5, 0);
  sub_D9024("ksu uid_should_umount failed", "ksu uid_should_umount failed", 29, v6, 0);
  sub_D9024("ksu uid_granted_root failed failed with {}", "ksu uid_granted_root failed failed with {}", 43, v7, 0);
  sub_D9024("ksu uid_granted_root failed", "ksu uid_granted_root failed", 28, v8, 0);
  sub_D9024("ksu CMD_GET_MANAGER_APPID failed failed with {}", "ksu CMD_GET_MANAGER_APPID failed failed with {}", 48, v9, 0);
  sub_D9024("ksu CMD_GET_MANAGER_UID failed", "ksu CMD_GET_MANAGER_UID failed", 31, v10, 0);
  sub_D9024("multiple versions: magisk={} ksu={} ap={}", "multiple versions: magisk={} ksu={} ap={}", 42, v11, 0);
  for ( i = -1777680508; i == -1777680508; i = 1582497966 )
  {
    sub_D9024("exec_cmd: pipe failed with {}", "exec_cmd: pipe failed with {}", 30, v12, 0);
    sub_D9024("exec_cmd: fork failed with {}", "exec_cmd: fork failed with {}", 30, v14, 0);
  }
  sub_D9024("exec_cmd: dup stdout failed with {}", "exec_cmd: dup stdout failed with {}", 36, v12, 0);
  return sub_D9024("exec_cmd: exec {} failed with {}", "exec_cmd: exec {} failed with {}", 33, v15, 0);
}


// ===== 0xDEF24 sub_DEF24 =====
__int64 __fastcall sub_DEF24(
        __int64 a1,
        int *a2,
        int8x16_t a3,
        int8x16_t a4,
        long double a5,
        long double a6,
        __int64 a7,
        int a8,
        __int64 a9,
        int a10,
        unsigned int a11,
        unsigned int a12)
{
  int v12; // w20
  unsigned int v13; // w24
  int i; // w27
  int v15; // w3
  int v16; // w5
  unsigned int v17; // w6
  unsigned int v18; // w7
  int8x16_t v19; // q0
  int8x16_t v20; // q1
  long double v21; // q2
  long double v22; // q3
  int v23; // w3
  int v24; // w5
  unsigned int v25; // w6
  unsigned int v26; // w7
  int8x16_t v27; // q0
  int8x16_t v28; // q1
  long double v29; // q2
  long double v30; // q3
  int v31; // w0
  int v32; // w0
  int v33; // w3
  int v34; // w5
  unsigned int v35; // w6
  unsigned int v36; // w7
  int8x16_t v37; // q0
  int8x16_t v38; // q1
  long double v39; // q2
  long double v40; // q3
  __int64 v41; // x0
  __int64 v43; // [xsp+8h] [xbp-C8h]
  __int64 v45; // [xsp+18h] [xbp-B8h]
  int v46; // [xsp+24h] [xbp-ACh]
  __int64 v47; // [xsp+28h] [xbp-A8h]
  int v48; // [xsp+34h] [xbp-9Ch]
  __int64 v49; // [xsp+38h] [xbp-98h]
  __int64 v50; // [xsp+40h] [xbp-90h]
  int v51; // [xsp+4Ch] [xbp-84h]
  int fd; // [xsp+50h] [xbp-80h]
  unsigned int v53; // [xsp+54h] [xbp-7Ch] BYREF
  int v54; // [xsp+58h] [xbp-78h] BYREF
  int v55; // [xsp+5Ch] [xbp-74h] BYREF
  int pipedes[2]; // [xsp+60h] [xbp-70h] BYREF
  __int64 v57; // [xsp+68h] [xbp-68h] BYREF

  v57 = a1;
  for ( i = -1556021924; ; i = -1682865605 )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        while ( 1 )
        {
          while ( 1 )
          {
            while ( i > -85825398 )
            {
              if ( i <= 580114738 )
              {
                if ( i > 192299382 )
                {
                  if ( i <= 337924770 )
                  {
                    if ( i == 192299383 )
                      i = -1787957917;
                    else
                      i = -60055266;
                  }
                  else if ( i == 337924771 )
                  {
                    a1 = (__int64)sub_3CDD4(&v55, pipedes[0]);
                    i = -919660797;
                  }
                  else if ( i == 505419092 )
                  {
                    sub_3CDD4(&v54, pipedes[1]);
                    i = -102533178;
                    a1 = fork();
                    v12 = a1;
                  }
                  else
                  {
                    i = 1360744200;
                    a1 = __errno(a1);
                    v47 = a1;
                  }
                }
                else if ( i <= 148056304 )
                {
                  if ( i == -85825397 )
                  {
                    v46 = v12;
                    i = 901245125;
                  }
                  else
                  {
                    if ( i != -37239481 )
                    {
                      sub_3CC3C(&byte_6, (__int64)"exec_cmd: dup stdout failed with {}", 35, v43);
                      _exit(127);
                    }
                    i = -1331677604;
                  }
                }
                else if ( i == 148056305 )
                {
                  i = 572177958;
                }
                else if ( i == 191267611 )
                {
                  a1 = (__int64)sub_3CC3C(&byte_6, (__int64)"exec_cmd: pipe failed with {}", 29, v47);
                  v13 = -1;
                  i = -37239481;
                }
                else
                {
                  a1 = (__int64)sub_3D40C(&v55);
                  i = 580114739;
                }
              }
              else if ( i <= 1234018647 )
              {
                if ( i > 901245124 )
                {
                  if ( i == 901245125 )
                  {
                    i = -194498368;
                  }
                  else
                  {
                    if ( i != 1125589078 )
                      _exit(127);
                    a1 = pipe2(pipedes, 0x80000);
                    if ( (_DWORD)a1 )
                      i = 148056305;
                    else
                      i = 337924771;
                  }
                }
                else if ( i == 580114739 )
                {
                  i = -37239481;
                }
                else if ( i == 624540381 )
                {
                  a1 = sub_AD06C(&v53);
                  v51 = a1;
                  i = -1252765971;
                }
                else
                {
                  a1 = sub_3CE18((__int64)&v54);
                  i = -85825397;
                }
              }
              else if ( i > 1715482829 )
              {
                if ( i == 1715482830 )
                {
                  a1 = sub_3CE18((__int64)&v55);
                  i = -1230863693;
                }
                else if ( i == 1796161160 )
                {
                  if ( v48 )
                    i = -1208180822;
                  else
                    i = 1715482830;
                }
                else
                {
                  a1 = (__int64)sub_3D40C(&v54);
                  i = 191338637;
                }
              }
              else if ( i == 1234018648 )
              {
                i = 194912610;
              }
              else if ( i == 1360744200 )
              {
                i = 191267611;
              }
              else
              {
                i = 1234018648;
                a1 = __errno(a1);
                v43 = a1;
              }
            }
            if ( i <= -1099032541 )
              break;
            if ( i <= -758953319 )
            {
              if ( i <= -1050336331 )
              {
                if ( i == -1099032540 )
                {
                  sub_D9024(
                    (__int64)&unk_1DD3D5,
                    (__int64)&unk_1DD3D5,
                    3u,
                    a8,
                    &dword_1E1108,
                    a10,
                    a11,
                    a12,
                    a3,
                    a4,
                    a5,
                    a6);
                  sub_D9024(
                    (__int64)&unk_1DD3D8,
                    (__int64)&unk_1DD3D8,
                    3u,
                    v33,
                    &dword_1E110C,
                    v34,
                    v35,
                    v36,
                    v37,
                    v38,
                    v39,
                    v40);
                  v41 = sub_19C948("/system/bin/sh", &unk_1DD3D2, &unk_1DD3D5, &unk_1DD3D8, v50);
                  i = -230444698;
                  a1 = __errno(v41);
                  v45 = a1;
                }
                else
                {
                  a1 = sub_3F040(&v53);
                  if ( (a1 & 1) != 0 )
                    i = 624540381;
                  else
                    i = -1683925029;
                }
              }
              else if ( i == -1050336330 )
              {
                i = -643100172;
                a1 = __errno(a1);
                v49 = a1;
              }
              else if ( i == -975595780 )
              {
                i = 2117210064;
              }
              else
              {
                i = 505419092;
              }
            }
            else if ( i > -230444699 )
            {
              if ( i == -230444698 )
              {
                a1 = sub_DFC10(a1, "exec_cmd: exec {} failed with {}", 32, &v57, v45);
                i = 1023647209;
              }
              else if ( i == -194498368 )
              {
                *a2 = v46;
                a1 = sub_3CF60((__int64)&v55);
                a2[1] = a1;
                v13 = 0;
                i = -975595780;
              }
              else if ( v12 >= 0 )
              {
                i = -1996918234;
              }
              else
              {
                i = 192299383;
              }
            }
            else if ( i == -758953318 )
            {
              i = 1125589078;
            }
            else if ( i == -643100172 )
            {
              a1 = (__int64)sub_3CC3C(&byte_6, (__int64)"exec_cmd: fork failed with {}", 29, v49);
              v13 = -1;
              i = -975595780;
            }
            else
            {
              v31 = open("/dev/null", 524290);
              a1 = (__int64)sub_3CDD4(&v53, v31);
              i = -2135458983;
            }
          }
          if ( i > -1556021925 )
            break;
          if ( i <= -1787957918 )
          {
            if ( i == -2135458983 )
            {
              v32 = sub_AD06C((unsigned int *)&v54);
              a1 = dup2(v32, 1);
              if ( (int)a1 >= 0 )
                i = -1050586416;
              else
                i = 1381262137;
            }
            else
            {
              v48 = v12;
              i = 1796161160;
            }
          }
          else if ( i == -1787957917 )
          {
            i = -1050336330;
          }
          else if ( i == -1683925029 )
          {
            sub_3CE18((__int64)&v53);
            sub_3CE18((__int64)&v54);
            v50 = v57;
            sub_D9024(
              (__int64)"/system/bin/sh",
              (__int64)"/system/bin/sh",
              0xFu,
              v15,
              &dword_1E1100,
              v16,
              v17,
              v18,
              v19,
              v20,
              v21,
              v22);
            a1 = sub_D9024(
                   (__int64)&unk_1DD3D2,
                   (__int64)&unk_1DD3D2,
                   3u,
                   v23,
                   &dword_1E1104,
                   v24,
                   v25,
                   v26,
                   v27,
                   v28,
                   v29,
                   v30);
            i = -1099032540;
          }
          else
          {
            a1 = sub_AD06C(&v53);
            fd = a1;
            i = -1118092455;
          }
        }
        if ( i <= -1230863694 )
          break;
        if ( i == -1230863693 )
        {
          a1 = sub_D9024(
                 (__int64)"/dev/null",
                 (__int64)"/dev/null",
                 0xAu,
                 a8,
                 &dword_1E10FC,
                 a10,
                 a11,
                 a12,
                 a3,
                 a4,
                 a5,
                 a6);
          i = -412856818;
        }
        else if ( i == -1208180822 )
        {
          i = 648026164;
        }
        else
        {
          a1 = dup2(fd, 2);
          i = -1683925029;
        }
      }
      if ( i != -1556021924 )
        break;
      i = -758953318;
    }
    if ( i != -1252765971 )
      break;
    a1 = dup2(v51, 0);
  }
  return v13;
}


// ===== 0xE4800 sub_E4800 =====
__int64 __fastcall sub_E4800(__int64 a1, __int64 a2, __int64 a3, __int64 a4)
{
  __int64 v4; // x3
  __int64 v5; // x3
  int i; // w8
  __int64 v7; // x3

  sub_E48FC("open module dir {} failed with {}", "open module dir {} failed with {}", 34, a4, 0);
  sub_E48FC("open machikado failed with {}", "open machikado failed with {}", 30, v4, 0);
  for ( i = 1393351263; i == 1393351263; i = 1276588181 )
  {
    sub_E48FC("verify1 failed", "verify1 failed", 15, v5, 0);
    sub_E48FC("open mazoku failed with {}", "open mazoku failed with {}", 27, v7, 0);
  }
  return sub_E48FC("verify2 failed", "verify2 failed", 15, v5, 0);
}


