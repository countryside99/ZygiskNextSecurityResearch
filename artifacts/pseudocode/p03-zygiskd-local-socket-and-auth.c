/*
 * zygiskd - the local control socket and its authorization
 * ========================================================
 *   0x19F010  creates the abstract-namespace listening socket ("create abstract {}",
 *             "bind {} failed") and rejects peers that fail credential checks
 *   0x19F70C  peer credential / SELinux context validation ("get peercred failed")
 *   0xC3118   "zn-nsdaemon-" - the namespace-daemon side of the socket family
 *
 * No inet_ntop / htons / getaddrinfo exists anywhere in this binary: the address
 * family here is AF_UNIX / AF_LOCAL, which is why there is a server socket at all
 * and still no network capability.
 *
 * Auto-extracted from the Hex-Rays AArch64 decompilation of
 *   bin/arm64-v8a/zygiskd
 * Strings that the binary XOR-decrypts at runtime have been
 * substituted back in as C string literals. Nothing else was edited.
 */

// ===== 0xC3118 sub_C3118 =====
void __fastcall __noreturn sub_C3118(
        unsigned int a1,
        int a2,
        int8x16_t a3,
        int8x16_t a4,
        long double a5,
        long double a6,
        __int64 a7,
        unsigned int a8,
        __int64 a9,
        unsigned int a10,
        char a11,
        int a12)
{
  int v12; // w19
  int v13; // w20
  int v14; // w21
  bool v15; // w22
  int *v16; // x24
  int v17; // w25
  int v18; // w26
  int v19; // w27
  int v20; // w28
  int v21; // w29
  __int64 v22; // x0
  int v23; // w23
  int v24; // w8
  const char *v25; // x0
  unsigned int v26; // w3
  unsigned int v27; // w5
  char v28; // w6
  int v29; // w7
  int8x16_t v30; // q0
  int8x16_t v31; // q1
  long double v32; // q2
  long double v33; // q3
  __int64 v34; // [xsp+8h] [xbp-E8h]
  char revents; // [xsp+3Ch] [xbp-B4h]
  __int64 v38; // [xsp+40h] [xbp-B0h]
  int v39; // [xsp+4Ch] [xbp-A4h]
  int v40; // [xsp+50h] [xbp-A0h]
  int v41; // [xsp+54h] [xbp-9Ch]
  _WORD *v42; // [xsp+58h] [xbp-98h]
  pollfd fds; // [xsp+60h] [xbp-90h] BYREF
  __int64 v44; // [xsp+68h] [xbp-88h] BYREF
  int v45; // [xsp+74h] [xbp-7Ch] BYREF
  char v46; // [xsp+78h] [xbp-78h] BYREF

  v22 = sub_C2CE8((__int64)"zn-nsdaemon-", (__int64)"zn-nsdaemon-", 0xDu, a8, &dword_1E0F54, a10, a11, a12, a3, a4, a5, a6);
  v23 = -1508222266;
  while ( 1 )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        v24 = v23;
        if ( v23 <= -46129774 )
          break;
        if ( v23 <= 746017392 )
        {
          if ( v23 <= 328263519 )
          {
            if ( v23 > 274083972 )
            {
              switch ( v23 )
              {
                case 274083973:
                  v22 = sub_C3B0C(&v45);
                  v23 = 548179786;
                  break;
                case 281607297:
                  v23 = -843408269;
                  break;
                case 291020727:
                  v23 = 1752880492;
                  v42 = (_WORD *)&v44 + 3;
                  break;
              }
            }
            else if ( v23 == -46129773 )
            {
              v39 = v13;
              v23 = 2002212551;
            }
            else if ( v23 == 49034965 )
            {
              v20 = v17;
              v23 = -202842626;
            }
            else
            {
              v23 = 548179786;
            }
          }
          else if ( v23 <= 548179785 )
          {
            if ( v23 == 328263520 )
            {
              v23 = -341797092;
            }
            else if ( v23 == 382727950 )
            {
              v23 = -1649326975;
              WORD2(v44) = 1;
            }
            else
            {
              v23 = 293761548;
            }
          }
          else if ( v23 > 633302084 )
          {
            if ( v23 == 633302085 )
            {
              v22 = open(aI, 0x80000);
              v45 = v22;
              v23 = -976539196;
            }
            else
            {
              v14 = v19;
              v23 = 2134658263;
            }
          }
          else if ( v23 == 548179786 )
          {
            fds = 0;
            v44 = 0;
            v23 = 1000607379;
          }
          else
          {
            v23 = -1174026292;
            v22 = __errno(v22);
            v16 = (int *)v22;
          }
        }
        else if ( v23 > 1707836657 )
        {
          if ( v23 > 2002212550 )
          {
            if ( v23 == 2002212551 )
            {
              if ( v39 )
                v23 = -1749211406;
              else
                v23 = -1777827619;
            }
            else if ( v23 == 2042602515 )
            {
              v23 = -986922808;
              v22 = __errno(v22);
              v38 = v22;
            }
            else
            {
              v13 = v14;
              if ( v14 >= 0 )
                v23 = -46129773;
              else
                v23 = 1352679203;
            }
          }
          else if ( v23 <= 1752880491 )
          {
            if ( v23 != 1709817687 )
              _exit(0);
            v23 = -1673923309;
            v22 = __errno(v22);
            v34 = v22;
          }
          else if ( v23 == 1752880492 )
          {
            v23 = -911332890;
            v41 = *v42 & 9;
          }
          else if ( v12 )
          {
            v23 = 991016792;
          }
          else
          {
            v23 = 105948486;
          }
        }
        else if ( v23 <= 1000607378 )
        {
          if ( v23 == 746017393 )
          {
            v19 = v20;
            v23 = -1004420970;
          }
          else if ( v23 == 876228514 )
          {
            v22 = (__int64)sub_3D158(&byte_5, (__int64)"ns-daemon: exit", 15);
            v23 = 1707836658;
          }
          else if ( v12 == 3 )
          {
            v23 = 548179786;
          }
          else
          {
            v23 = 537330856;
          }
        }
        else if ( v23 > 1076256274 )
        {
          if ( v23 == 1076256275 )
            v23 = 281607297;
          else
            v23 = 2042602515;
        }
        else if ( v23 == 1000607379 )
        {
          fds.events = 10;
          v23 = 382727950;
          fds.fd = v45;
          LODWORD(v44) = a2;
        }
        else
        {
          v22 = sub_C3B0C(&v45);
          v23 = -588424251;
        }
      }
      if ( v23 <= -1027217950 )
        break;
      if ( v23 > -764295716 )
      {
        if ( v23 <= -588424252 )
        {
          if ( v23 == -764295715 )
          {
            v22 = sub_18F804(a1);
            v23 = 1056715210;
          }
          else if ( v23 == -662389788 )
          {
            if ( (revents & 0xA) != 0 )
              v23 = -387536710;
            else
              v23 = -588424251;
          }
          else
          {
            v12 = v21;
            v23 = 1842944139;
          }
        }
        else if ( v23 > -341797093 )
        {
          if ( v23 != -202842626 )
          {
            sub_3CC3C(&byte_6, (__int64)"ns-daemon open mountinfo failed with {}", 39, v34);
            _exit(1);
          }
          v18 = v20;
          v23 = -1311676506;
        }
        else if ( v23 == -588424251 )
        {
          v21 = 0;
          v23 = -590294662;
        }
        else
        {
          v22 = sub_C3B0C(&v45);
          v23 = -1863276458;
        }
      }
      else if ( v23 <= -976539197 )
      {
        if ( v23 == -1027217949 )
        {
          v23 = 876228514;
        }
        else if ( v23 == -1004420970 )
        {
          v23 = 744982115;
        }
        else
        {
          v22 = (__int64)sub_3CC3C(&byte_6, (__int64)"ns-daemon poll failed with {}", 29, v38);
          v23 = -1170201579;
        }
      }
      else if ( v23 > -911332891 )
      {
        if ( v23 == -911332890 )
        {
          if ( v41 )
            v23 = -1295568661;
          else
            v23 = 1076256275;
        }
        else
        {
          v23 = -662389788;
          revents = fds.revents;
        }
      }
      else if ( v23 == -976539196 )
      {
        if ( v45 >= 0 )
          v23 = 274083973;
        else
          v23 = 1709817687;
      }
      else
      {
        v22 = poll(&fds, 2u, -1);
        v17 = v22;
        v23 = 49034965;
      }
    }
    if ( v23 <= -1649326976 )
    {
      if ( v23 > -1777827620 )
      {
        if ( v23 == -1777827619 )
        {
LABEL_3:
          v21 = 3;
          v23 = -590294662;
        }
        else if ( v23 == -1749211406 )
        {
          v23 = 291020727;
        }
        else
        {
          v23 = 328263520;
        }
      }
      else if ( v23 == -2049510544 )
      {
        v23 = -959604553;
      }
      else if ( v23 == -1977930006 )
      {
        if ( v15 )
          v23 = -2049510544;
        else
          v23 = 746017393;
      }
      else
      {
        v23 = -764295715;
      }
    }
    else if ( v23 <= -1311676507 )
    {
      v23 = -2049510544;
      if ( v24 != -1649326975 )
      {
        if ( v24 == -1568890021 )
        {
          v23 = -1977930006;
          v15 = v40 == 4;
        }
        else
        {
          sub_180E38((int)&v46, "zn-nsdaemon-");
          v25 = (const char *)sub_3D408();
          sub_7BA94(v25);
          v22 = sub_C2CE8((__int64)aI, (__int64)aI, 0x15u, v26, &dword_1E0F58, v27, v28, v29, v30, v31, v32, v33);
          v23 = 633302085;
        }
      }
    }
    else if ( v23 > -1174026293 )
    {
      if ( v23 != -1174026292 )
        goto LABEL_3;
      v23 = -1568890021;
      v40 = *v16;
    }
    else if ( v23 == -1311676506 )
    {
      v15 = 0;
      if ( v18 == -1 )
        v23 = 576508759;
      else
        v23 = -1977930006;
    }
    else
    {
      v23 = -1027217949;
    }
  }
}


// ===== 0x19F010 sub_19F010 =====
__int64 __fastcall sub_19F010(__int64 a1, __int64 a2, __int64 a3, __int64 a4)
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

  sub_19F308("get peercred failed with {}", "get peercred failed with {}", 28, a4, 0);
  sub_19F308("get peersec failed with {}", "get peersec failed with {}", 27, v4, 0);
  sub_19F308("read failed with {}", "read failed with {}", 20, v5, 0);
  sub_19F308("read ({} != {}) failed with {}", "read ({} != {}) failed with {}", 31, v6, 0);
  sub_19F308("write failed with {}", "write failed with {}", 21, v7, 0);
  sub_19F308("write ({} != {}) failed with {}", "write ({} != {}) failed with {}", 32, v8, 0);
  sub_19F308("recvmsg failed with {}", "recvmsg failed with {}", 23, v9, 0);
  sub_19F308("sendmsg failed with {}", "sendmsg failed with {}", 23, v10, 0);
  sub_19F308("too big string to read: {}", "too big string to read: {}", 27, v11, 0);
  sub_19F308("too big string to write: {}", "too big string to write: {}", 28, v12, 0);
  sub_19F308("/proc/{}/attr/sockcreate", "/proc/{}/attr/sockcreate", 25, v13, 0);
  sub_19F308("set socket con failed with {}", "set socket con failed with {}", 30, v14, 0);
  sub_19F308("getfd failed with {}", "getfd failed with {}", 21, v15, 0);
  sub_19F308("setfd failed with {}", "setfd failed with {}", 21, v16, 0);
  for ( i = 2113424991; i == 2113424991; i = -1836801447 )
  {
    sub_19F308("too long path {}", "too long path {}", 17, v17, 0);
    sub_19F308("create abstract {} failed with {}", "create abstract {} failed with {}", 34, v19, 0);
    sub_19F308("bind {} failed with {}", "bind {} failed with {}", 23, v20, 0);
    sub_19F308("listen socket failed with {}", "listen socket failed with {}", 29, v21, 0);
    sub_19F308("connect {} failed with {}", "connect {} failed with {}", 26, v22, 0);
    sub_19F308("recv_fd: msg_flags = {}, msg_controllen({}) != {}", "recv_fd: msg_flags = {}, msg_controllen({}) != {}", 50, v23, 0);
    sub_19F308("recv_fd: cmsg == nullptr", "recv_fd: cmsg == nullptr", 25, v24, 0);
  }
  sub_19F308("recv_fd: cmsg_len({}) != {}", "recv_fd: cmsg_len({}) != {}", 28, v17, 0);
  sub_19F308("recv_fd: cmsg_level != SOL_SOCKET", "recv_fd: cmsg_level != SOL_SOCKET", 34, v25, 0);
  return sub_19F308("recv_fd: cmsg_type != SCM_RIGHTS", "recv_fd: cmsg_type != SCM_RIGHTS", 33, v26, 0);
}


// ===== 0x19F70C sub_19F70C =====
__int64 __fastcall sub_19F70C(__int64 a1, void *a2)
{
  char v2; // w20
  __int64 v3; // x23
  int v4; // w24
  int v5; // w26
  __int64 v6; // x0
  __int64 v8; // [xsp+10h] [xbp-1080h]
  int fd; // [xsp+1Ch] [xbp-1074h]
  _BYTE v11[4096]; // [xsp+2Ch] [xbp-1064h] BYREF
  socklen_t v12; // [xsp+102Ch] [xbp-64h] BYREF

  fd = a1;
  v8 = 0;
  v5 = 1351507163;
  while ( 1 )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        while ( 1 )
        {
          while ( v5 > 86687430 )
          {
            if ( v5 > 1200470349 )
            {
              if ( v5 <= 1488780812 )
              {
                if ( v5 == 1200470350 )
                {
                  v12 = 4096;
                  v5 = -765471547;
                }
                else
                {
                  v5 = 1488780813;
                }
              }
              else if ( v5 == 1488780813 )
              {
                v5 = 77831996;
                v12 = 12;
              }
              else if ( v5 == 1604282191 )
              {
                v5 = -258963253;
              }
              else if ( v4 )
              {
                v5 = 271828166;
              }
              else
              {
                v5 = -494726244;
              }
            }
            else if ( v5 <= 271828165 )
            {
              if ( v5 == 86687431 )
              {
                v6 = __errno(a1);
                a1 = (__int64)sub_3CC3C(&byte_6, (__int64)"get peersec failed with {}", 26, v6);
                v5 = -500262740;
              }
              else
              {
                v5 = -290497932;
                a1 = __errno(a1);
                v3 = a1;
              }
            }
            else if ( v5 == 271828166 )
            {
              v5 = -289875814;
            }
            else if ( v5 == 911942844 )
            {
              a1 = (__int64)sub_3CC3C(&byte_6, (__int64)"get peercred failed with {}", 27, v3);
              v5 = -1487451482;
            }
            else
            {
              v11[v8] = 0;
              sub_7BA00();
              v5 = -875698282;
            }
          }
          if ( v5 > -290497933 )
            break;
          if ( v5 <= -765471548 )
          {
            if ( v5 == -1487451482 )
            {
              v2 = 0;
              v5 = -258963253;
            }
            else
            {
              v2 = 1;
              v5 = 1604282191;
            }
          }
          else if ( v5 == -765471547 )
          {
            a1 = getsockopt(fd, 1, 31, v11, &v12);
            v4 = a1;
            v5 = 1794594971;
          }
          else if ( v5 == -500262740 )
          {
            v12 = 0;
            v5 = -494726244;
          }
          else
          {
            v5 = 1005635337;
            v8 = v12;
          }
        }
        if ( v5 > -258963254 )
          break;
        if ( v5 == -290497932 )
        {
          v5 = 911942844;
        }
        else if ( v5 == -289875814 )
        {
          v5 = 86687431;
        }
        else
        {
          v5 = 1200470350;
        }
      }
      if ( v5 != -258963253 )
        break;
      v5 = -226752635;
    }
    if ( v5 != 77831996 )
      break;
    a1 = getsockopt(fd, 1, 17, a2, &v12);
    if ( (_DWORD)a1 )
      v5 = 195602847;
    else
      v5 = -283092343;
  }
  return v2 & 1;
}


