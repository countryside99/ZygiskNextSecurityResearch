/*
 * libzygisk.so - in-process client: fd plumbing and denylist namespaces
 * ======================================================================
 *   0x9E35C  socketpair + sendmsg (SCM_RIGHTS fd passing to the companion)
 *   0xBB198  peer credential check on the received connection
 *   0xBC814  recv / recvmsg (MSG_PEEK length prefix, CMSG parsing)
 *   0x4D99C  setns - switch the denylist mount namespace
 *   0xAB04C  umount2 - the actual denylist unmount
 *
 * This library has 68 imported symbols and all 68 are called from code; the whole
 * import list is enumerated in 03-network-zero-capability.md.
 *
 * Auto-extracted from the Hex-Rays AArch64 decompilation of
 *   lib/arm64-v8a/libzygisk.so
 * Strings that the binary XOR-decrypts at runtime have been
 * substituted back in as C string literals. Nothing else was edited.
 */

// ===== 0x4D99C sub_4D99C =====
void __fastcall sub_4D99C(__int64 a1, __int64 a2)
{
  __int64 v2; // x20
  int v3; // w21
  int v4; // w22
  unsigned int v5; // w23
  int v6; // w26
  int v7; // w29
  int v8; // [xsp+Ch] [xbp-64h] BYREF

  v7 = 684033266;
  while ( 1 )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        while ( v7 > 684033265 )
        {
          if ( v7 <= 1117222558 )
          {
            if ( v7 == 684033266 )
            {
              byte_143C41 = 1;
              v7 = 944353491;
              a1 = sub_9C6B4();
              v5 = a1;
            }
            else if ( v7 == 874394391 )
            {
              v3 = v8;
              v7 = -1495231107;
            }
            else
            {
              a1 = sub_54744(&v8, v5);
              v6 = v8;
              v7 = 83770005;
            }
          }
          else if ( v7 > 1252908629 )
          {
            if ( v7 == 1252908630 )
            {
              a1 = sub_5478C(&v8);
              v7 = -208581163;
            }
            else
            {
              v7 = 1252908630;
            }
          }
          else if ( v7 == 1117222559 )
          {
            a1 = off_1469E8(a1, a2);
            v2 = a1;
            v7 = 539197885;
          }
          else
          {
            sub_4B5B8(a1, (__int64)&unk_143C03, 26, v2);
            v7 = 1528558113;
          }
        }
        if ( v7 > -208581164 )
          break;
        if ( v7 == -1584455442 )
        {
          if ( v4 >= 0 )
            v7 = 1528558113;
          else
            v7 = -1227587288;
        }
        else if ( v7 == -1495231107 )
        {
          a1 = setns(v3, 0x20000);
          v4 = a1;
          v7 = -1584455442;
        }
        else
        {
          v7 = 1117222559;
        }
      }
      if ( v7 <= 167352101 )
        break;
      if ( v7 == 167352102 )
        v7 = 874394391;
      else
        v7 = 1178406803;
    }
    if ( v7 != 83770005 )
      break;
    if ( v6 == -1 )
      v7 = 1252908630;
    else
      v7 = 167352102;
  }
}


// ===== 0x9E35C sub_9E35C =====
__int64 __fastcall sub_9E35C(__int64 a1, __int64 a2, __int64 a3)
{
  __int64 v3; // x19
  __int64 v4; // x20
  unsigned int v5; // w21
  int v6; // w22
  unsigned int v7; // w23
  int v8; // w24
  unsigned int v9; // w25
  _DWORD *msg_control; // x28
  int v11; // w8
  int v12; // w9
  int v13; // w9
  int v14; // w0
  struct msghdr v16; // [xsp+0h] [xbp-D0h] BYREF
  _QWORD v17[2]; // [xsp+38h] [xbp-98h] BYREF
  char v18; // [xsp+48h] [xbp-88h] BYREF
  char v19; // [xsp+4Ch] [xbp-84h] BYREF
  int fd; // [xsp+64h] [xbp-6Ch] BYREF
  unsigned int v21; // [xsp+68h] [xbp-68h] BYREF
  int v22; // [xsp+6Ch] [xbp-64h] BYREF
  int fds[2]; // [xsp+78h] [xbp-58h] BYREF

  v11 = -879918778;
  while ( 1 )
  {
    do
    {
      while ( 1 )
      {
        while ( 1 )
        {
          while ( 1 )
          {
            while ( 1 )
            {
              v12 = v11;
              if ( v11 <= 547402660 )
                break;
              if ( v11 > 1393715125 )
              {
                if ( v11 <= 1935983870 )
                {
                  if ( v11 <= 1630030967 )
                  {
                    if ( v11 == 1393715126 )
                    {
                      if ( v8 >= 0 )
                        v11 = -521242859;
                      else
                        v11 = -1692990735;
                    }
                    else
                    {
                      a1 = socketpair(1, 1, 0, fds);
                      v8 = a1;
                      v11 = 1393715126;
                    }
                  }
                  else if ( v11 == 1630030968 )
                  {
                    a1 = sub_5478C((__int64)&v21);
                    v11 = 404269616;
                  }
                  else if ( v11 == 1641782875 )
                  {
                    a1 = off_1469E8(a1, a2);
                    v3 = a1;
                    v11 = -159020675;
                  }
                  else
                  {
                    v11 = -11783688;
                  }
                }
                else if ( v11 > 2081049698 )
                {
                  if ( v11 == 2081049699 )
                  {
                    a1 = sub_9B480((__int64)&v21);
                    v7 = a1;
                    v11 = -636116294;
                  }
                  else if ( v11 == 2101968849 )
                  {
                    v11 = 216466938;
                  }
                  else
                  {
                    a1 = off_1469E8(a1, a2);
                    v4 = a1;
                    v11 = -1972338063;
                  }
                }
                else if ( v11 == 1935983871 )
                {
                  v11 = -1008561643;
                }
                else if ( v11 == 1939490945 )
                {
                  v9 = -1;
                  v11 = 736475115;
                }
                else
                {
                  v11 = -2092422854;
                }
              }
              else if ( v11 <= 798127696 )
              {
                if ( v11 <= 690774495 )
                {
                  if ( v11 == 547402661 )
                  {
                    v16.msg_control = &v19;
                    v16.msg_controllen = 24;
                    v11 = -865921465;
                  }
                  else
                  {
                    a1 = sub_BF1E4(a1, (unsigned int)dword_146FA4, a3, 0);
                    v6 = a1;
                    v11 = 798127697;
                  }
                }
                else if ( v11 == 690774496 )
                {
                  v18 = 0;
                  v11 = -336968918;
                }
                else
                {
                  v11 = -488080688;
                  if ( v12 != 736475115 )
                    v11 = -1656216950;
                }
              }
              else if ( v11 > 1221278600 )
              {
                v11 = -488080688;
                if ( v12 != 1221278601 )
                {
                  if ( v12 == 1330501982 )
                  {
                    v11 = 2072687014;
                  }
                  else
                  {
                    sub_54744(&v22, fds[0]);
                    a1 = (__int64)sub_54744(&v21, fds[1]);
                    v11 = 620447536;
                  }
                }
              }
              else if ( v11 == 798127697 )
              {
                sub_54744(&fd, v6);
                a1 = sub_96D48(&fd);
                if ( (a1 & 1) != 0 )
                  v11 = 690774496;
                else
                  v11 = 842122917;
              }
              else if ( v11 == 842122917 )
              {
                v9 = -1;
                v11 = 1695354396;
              }
              else
              {
                v5 = v21;
                v11 = 2101968849;
              }
            }
            if ( v11 <= -636116295 )
              break;
            if ( v11 <= -11783689 )
            {
              if ( v11 <= -488080689 )
              {
                if ( v11 == -636116294 )
                {
                  v9 = v7;
                  v11 = 1221278601;
                }
                else
                {
                  v11 = 1353495279;
                }
              }
              else if ( v11 == -488080688 )
              {
                v11 = 1330501982;
              }
              else if ( v11 == -336968918 )
              {
                v16.msg_name = 0;
                v17[0] = &v18;
                v17[1] = 1;
                v16.msg_iov = (struct iovec *)v17;
                v16.msg_iovlen = 1;
                v16.msg_namelen = 0;
                v11 = 547402661;
              }
              else
              {
                v11 = -1620827105;
              }
            }
            else if ( v11 > 320272002 )
            {
              if ( v11 == 320272003 )
              {
                v11 = 1641782875;
              }
              else if ( v11 == 404269616 )
              {
                v11 = 40577391;
              }
              else
              {
                a1 = sub_9D6D4((__int64)&v22);
                v11 = 965436914;
              }
            }
            else if ( v11 == -11783688 )
            {
              a1 = sub_5478C((__int64)&fd);
              v11 = 1630030968;
            }
            else if ( v11 == 40577391 )
            {
              a1 = sub_5478C((__int64)&v22);
              v11 = 1935983871;
            }
            else
            {
              a1 = sub_BD138(v5, 0);
              if ( (a1 & 1) != 0 )
                v11 = 2081049699;
              else
                v11 = 1939490945;
            }
          }
          if ( v11 > -1370786224 )
            break;
          if ( v11 <= -1692990736 )
          {
            if ( v11 == -2092422854 )
            {
              v11 = -11783688;
            }
            else
            {
              sub_4B5B8(a1, (__int64)"create pipe failed with {}", 26, v4);
              v9 = -1;
              v11 = -1370786223;
            }
          }
          else if ( v11 == -1692990735 )
          {
            v11 = 2124192264;
          }
          else if ( v11 == -1656216950 )
          {
            msg_control = v16.msg_control;
            v11 = -1073230896;
          }
          else
          {
            sub_4B5B8(a1, (__int64)"sendmsg failed with {}", 22, v3);
            v9 = -1;
            v11 = -488080688;
          }
        }
        if ( v11 <= -904509838 )
          break;
        if ( v11 == -904509837 )
        {
          msg_control = 0;
          v11 = -1073230896;
        }
        else if ( v11 == -879918778 )
        {
          v11 = 1543233934;
        }
        else
        {
          v16.msg_flags = 0;
          if ( v16.msg_controllen <= 0xF )
            v11 = -904509837;
          else
            v11 = 748871923;
        }
      }
      v11 = 1935983871;
    }
    while ( v12 == -1370786223 );
    if ( v12 != -1073230896 )
      break;
    v13 = v22;
    v14 = fd;
    *(_QWORD *)msg_control = 20;
    msg_control[4] = v13;
    *((_QWORD *)msg_control + 1) = 0x100000001LL;
    a1 = sendmsg(v14, &v16, 0);
    if ( a1 >= 0 )
      v11 = 476881499;
    else
      v11 = 320272003;
  }
  return v9;
}


// ===== 0xAB04C sub_AB04C =====
__int64 __fastcall sub_AB04C(__int64 result)
{
  const char *v1; // x19
  int v2; // w20
  int i; // w9
  int v4; // w8
  const char *v5; // [xsp+8h] [xbp-18h] BYREF

  v5 = (const char *)result;
  for ( i = -1889143012; ; i = -422144189 )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        while ( 1 )
        {
          v4 = i;
          if ( i <= 918920087 )
            break;
          if ( i > 1568748652 )
          {
            i = -1257964991;
            if ( v4 != 1568748653 )
              i = 1566374669;
          }
          else if ( i == 918920088 )
          {
            i = 2116115135;
          }
          else
          {
            i = 375714707;
          }
        }
        if ( i <= -422144190 )
          break;
        if ( i == -422144189 )
        {
          if ( v2 == -1 )
            i = 1568748653;
          else
            i = 918920088;
        }
        else
        {
          result = sub_26DD4(4, (__int64)"Unmounted ({})", 14, (__int64)&v5);
          i = -1257964991;
        }
      }
      if ( i != -1889143012 )
        break;
      v1 = v5;
      i = -1257082492;
    }
    if ( i != -1257082492 )
      break;
    result = umount2(v1, 2);
    v2 = result;
  }
  return result;
}


// ===== 0xBB198 sub_BB198 =====
__int64 __fastcall sub_BB198(__int64 a1, __int64 a2, __int64 a3, __int64 a4)
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
  __int64 v13; // x3
  __int64 v14; // x3
  __int64 v15; // x3
  __int64 v16; // x3
  __int64 v17; // x3
  int i; // w8
  __int64 v19; // x3
  __int64 v20; // x3
  __int64 v21; // x3
  __int64 v22; // x3
  __int64 v23; // x3
  __int64 v24; // x3
  __int64 v25; // x3
  __int64 v26; // x3

  sub_BB490("get peercred failed with {}", "get peercred failed with {}", 28, a4, 0);
  sub_BB490("get peersec failed with {}", "get peersec failed with {}", 27, v4, 0);
  sub_BB490("read failed with {}", "read failed with {}", 20, v5, 0);
  sub_BB490("read ({} != {}) failed with {}", "read ({} != {}) failed with {}", 31, v6, 0);
  sub_BB490("write failed with {}", "write failed with {}", 21, v7, 0);
  sub_BB490("write ({} != {}) failed with {}", "write ({} != {}) failed with {}", 32, v8, 0);
  sub_BB490("recvmsg failed with {}", "recvmsg failed with {}", 23, v9, 0);
  sub_BB490("sendmsg failed with {}", "sendmsg failed with {}", 23, v10, 0);
  sub_BB490("too big string to read: {}", "too big string to read: {}", 27, v11, 0);
  sub_BB490("too big string to write: {}", "too big string to write: {}", 28, v12, 0);
  sub_BB490("/proc/{}/attr/sockcreate", "/proc/{}/attr/sockcreate", 25, v13, 0);
  sub_BB490(s_145d79, s_145d79, 30, v14, 0);
  sub_BB490(s_145d97, s_145d97, 21, v15, 0);
  sub_BB490(s_145dac, s_145dac, 21, v16, 0);
  for ( i = 2113424991; i == 2113424991; i = -1836801447 )
  {
    sub_BB490(s_145dc1, s_145dc1, 17, v17, 0);
    sub_BB490(s_145dd2, s_145dd2, 34, v19, 0);
    sub_BB490(s_145df4, s_145df4, 23, v20, 0);
    sub_BB490(s_145e0b, s_145e0b, 29, v21, 0);
    sub_BB490(s_145e28, s_145e28, 26, v22, 0);
    sub_BB490("recv_fd: msg_flags = {}, msg_controllen({}) != {}", "recv_fd: msg_flags = {}, msg_controllen({}) != {}", 50, v23, 0);
    sub_BB490(s_145e74, s_145e74, 25, v24, 0);
  }
  sub_BB490("recv_fd: cmsg_len({}) != {}", "recv_fd: cmsg_len({}) != {}", 28, v17, 0);
  sub_BB490("recv_fd: cmsg_level != SOL_SOCKET", "recv_fd: cmsg_level != SOL_SOCKET", 34, v25, 0);
  return sub_BB490("recv_fd: cmsg_type != SCM_RIGHTS", "recv_fd: cmsg_type != SCM_RIGHTS", 33, v26, 0);
}


// ===== 0xBC814 sub_BC814 =====
__int64 __fastcall sub_BC814(ssize_t a1, struct msghdr *a2)
{
  ssize_t v2; // x23
  int v3; // w24
  int v4; // w29
  int i; // w8
  __int64 v7; // [xsp+8h] [xbp-78h]
  int fd; // [xsp+14h] [xbp-6Ch]

  fd = a1;
  for ( i = 1423018858; ; i = 582495395 )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        while ( i > 1114150380 )
        {
          if ( i <= 1605448828 )
          {
            if ( i == 1114150381 )
            {
              a1 = sub_4B5B8(a1, "recvmsg failed with {}", 22, v2);
              i = 1737364685;
            }
            else
            {
              i = -1946650499;
            }
          }
          else if ( i == 1605448829 )
          {
            a1 = off_1469E8();
            v2 = a1;
            i = 489285618;
          }
          else if ( i == 1737364685 )
          {
            v4 = v3;
            i = 790315532;
          }
          else
          {
            i = 1605448829;
          }
        }
        if ( i > 582495394 )
          break;
        if ( i == -1946650499 )
          i = 700700564;
        else
          i = 1114150381;
      }
      if ( i != 700700564 )
        break;
      a1 = recvmsg(fd, a2, 1073742080);
      v3 = a1;
      if ( (int)a1 >= 0 )
        i = 1737364685;
      else
        i = 1876765639;
    }
    if ( i != 790315532 )
      break;
    v7 = v4;
  }
  return v7;
}


