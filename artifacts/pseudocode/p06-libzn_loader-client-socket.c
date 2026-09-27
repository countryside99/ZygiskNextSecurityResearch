/*
 * libzn_loader.so - the client side of the local channel
 * =======================================================
 *   0x4FAA8  socketpair + sendmsg (fd handover)
 *   0x5CC58  abstract-namespace bind + peercred check ("create abstract {}",
 *            "get peercred failed")
 *   0x60568  socket() + connect() - both with w0 = 1 (AF_UNIX)
 *   0x5E2A4  recvmsg with MSG_CMSG_CLOEXEC / MSG_TRUNC
 *   0x4F210  unshare / PutCleanNs
 *
 * Capstone + pyelftools audit of this binary found 150,892 instructions, 0 raw svc
 * instructions, 0 bind/listen/accept, 0 sendto/recvfrom.
 *
 * Auto-extracted from the Hex-Rays AArch64 decompilation of
 *   lib/arm64-v8a/libzn_loader.so
 * Strings that the binary XOR-decrypts at runtime have been
 * substituted back in as C string literals. Nothing else was edited.
 */

// ===== 0x4F210 sub_4F210 =====
__int64 sub_4F210()
{
  int i; // w8

  sub_4F598("zn_zygote_{}", "zn_zygote_{}", 13);
  sub_4F598("connect daemon failed with {}", "connect daemon failed with {}", 30);
  sub_4F598("GetUidFlags failed", "GetUidFlags failed", 19);
  sub_4F598("ReadModules failed", "ReadModules failed", 19);
  sub_4F598("ConnectCompanion failed", "ConnectCompanion failed", 24);
  sub_4F598("GetModuleDir failed", "GetModuleDir failed", 20);
  sub_4F598("Start failed", "Start failed", 13);
  sub_4F598("Stop failed", "Stop failed", 12);
  sub_4F598("Exit failed", "Exit failed", 12);
  sub_4F598("SetDenylistPolicy failed", "SetDenylistPolicy failed", 25);
  sub_4F598("GetDenylist failed", "GetDenylist failed", 19);
  sub_4F598("SetEnforceDenylist failed", "SetEnforceDenylist failed", 26);
  sub_4F598("SetMemoryType failed", "SetMemoryType failed", 21);
  for ( i = 1085741316; i == 1085741316; i = 59464119 )
  {
    sub_4F598("GetMemoryType failed", "GetMemoryType failed", 21);
    sub_4F598("SetLinker failed", "SetLinker failed", 17);
    sub_4F598("GetLinker failed", "GetLinker failed", 17);
    sub_4F598("PutCleanNs failed", "PutCleanNs failed", 18);
    sub_4F598("GetCleanNs failed", "GetCleanNs failed", 18);
    sub_4F598("release unshare file lock failed with {}", "release unshare file lock failed with {}", 41);
    sub_4F598("get unshare lock fd failed", "get unshare lock fd failed", 27);
    sub_4F598("acquire unshare file lock failed with {}", "acquire unshare file lock failed with {}", 41);
    sub_4F598("DisableZygisk failed", "DisableZygisk failed", 21);
    sub_4F598("DumpZnModules failed", "DumpZnModules failed", 21);
    sub_4F598("GetRootImpl failed", "GetRootImpl failed", 19);
    sub_4F598("SetHookMode failed", "SetHookMode failed", 19);
    sub_4F598("ZygiskHookReport failed", "ZygiskHookReport failed", 24);
    sub_4F598("ZygiskJniNotFoundReport failed", "ZygiskJniNotFoundReport failed", 31);
    sub_4F598("ReportModuleIssue failed", "ReportModuleIssue failed", 25);
    sub_4F598("zn_global_{}", "zn_global_{}", 13);
    sub_4F598("create pipe failed with {}", "create pipe failed with {}", 27);
  }
  sub_4F598("sendmsg failed with {}", "sendmsg failed with {}", 23);
  sub_4F598("remote WriteProc failed", "remote WriteProc failed", 24);
  sub_4F598("WriteProc failed", "WriteProc failed", 17);
  sub_4F598("remote RequestExecMemHelperFd failed", "remote RequestExecMemHelperFd failed", 37);
  sub_4F598("RequestExecMemHelperFd failed", "RequestExecMemHelperFd failed", 30);
  return sub_4F598("ZnServiceRequestCompanion failed", "ZnServiceRequestCompanion failed", 33);
}


// ===== 0x4FAA8 sub_4FAA8 =====
__int64 __fastcall sub_4FAA8(__int64 a1)
{
  __int64 v1; // x20
  __int64 v2; // x21
  unsigned int v3; // w22
  int v4; // w23
  unsigned int v5; // w24
  int v6; // w25
  unsigned int v7; // w26
  _DWORD *msg_control; // x29
  unsigned int v9; // w19
  int v10; // w28
  int v11; // w8
  int v12; // w9
  int v13; // w0
  msghdr message; // [xsp+8h] [xbp-D8h] BYREF
  _QWORD v16[2]; // [xsp+40h] [xbp-A0h] BYREF
  char v17; // [xsp+50h] [xbp-90h] BYREF
  char v18; // [xsp+54h] [xbp-8Ch] BYREF
  int fd; // [xsp+6Ch] [xbp-74h] BYREF
  unsigned int v20; // [xsp+70h] [xbp-70h] BYREF
  int v21; // [xsp+74h] [xbp-6Ch] BYREF
  int fds[2]; // [xsp+78h] [xbp-68h] BYREF

  v9 = a1;
  v10 = -879918778;
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
              v11 = v10;
              if ( v10 <= 547402660 )
                break;
              if ( v10 > 1393715125 )
              {
                if ( v10 <= 1935983870 )
                {
                  if ( v10 <= 1630030967 )
                  {
                    if ( v10 == 1393715126 )
                    {
                      if ( v6 >= 0 )
                        v10 = -521242859;
                      else
                        v10 = -1692990735;
                    }
                    else
                    {
                      a1 = socketpair(1, 1, 0, fds);
                      v6 = a1;
                      v10 = 1393715126;
                    }
                  }
                  else if ( v10 == 1630030968 )
                  {
                    a1 = (__int64)sub_44CE0((int *)&v20);
                    v10 = 404269616;
                  }
                  else if ( v10 == 1641782875 )
                  {
                    v10 = -159020675;
                    a1 = __errno(a1);
                    v1 = a1;
                  }
                  else
                  {
                    v10 = -11783688;
                  }
                }
                else if ( v10 > 2081049698 )
                {
                  if ( v10 == 2081049699 )
                  {
                    a1 = sub_4F998((int *)&v20);
                    v5 = a1;
                    v10 = -636116294;
                  }
                  else if ( v10 == 2101968849 )
                  {
                    v10 = 216466938;
                  }
                  else
                  {
                    v10 = -1972338063;
                    a1 = __errno(a1);
                    v2 = a1;
                  }
                }
                else if ( v10 == 1935983871 )
                {
                  v10 = -1008561643;
                }
                else if ( v10 == 1939490945 )
                {
                  v7 = -1;
                  v10 = 736475115;
                }
                else
                {
                  v10 = -2092422854;
                }
              }
              else if ( v10 <= 798127696 )
              {
                if ( v10 <= 690774495 )
                {
                  if ( v10 == 547402661 )
                  {
                    message.msg_control = &v18;
                    v10 = -865921465;
                    message.msg_controllen = 24;
                  }
                  else
                  {
                    a1 = sub_60568(a1, dword_B0AB4);
                    v4 = a1;
                    v10 = 798127697;
                  }
                }
                else if ( v10 == 690774496 )
                {
                  v17 = 0;
                  v10 = -336968918;
                }
                else
                {
                  v10 = -488080688;
                  if ( v11 != 736475115 )
                    v10 = -1656216950;
                }
              }
              else if ( v10 > 1221278600 )
              {
                v10 = -488080688;
                if ( v11 != 1221278601 )
                {
                  if ( v11 == 1330501982 )
                  {
                    v10 = 2072687014;
                  }
                  else
                  {
                    sub_42DC4(&v21, fds[0]);
                    a1 = (__int64)sub_42DC4(&v20, fds[1]);
                    v10 = 620447536;
                  }
                }
              }
              else if ( v10 == 798127697 )
              {
                sub_42DC4(&fd, v4);
                a1 = sub_4E4B8(&fd);
                if ( (a1 & 1) != 0 )
                  v10 = 690774496;
                else
                  v10 = 842122917;
              }
              else if ( v10 == 842122917 )
              {
                v7 = -1;
                v10 = 1695354396;
              }
              else
              {
                v3 = v20;
                v10 = 2101968849;
              }
            }
            if ( v10 <= -636116295 )
              break;
            if ( v10 <= -11783689 )
            {
              if ( v10 <= -488080689 )
              {
                if ( v10 == -636116294 )
                {
                  v7 = v5;
                  v10 = 1221278601;
                }
                else
                {
                  v10 = 1353495279;
                }
              }
              else if ( v10 == -488080688 )
              {
                v10 = 1330501982;
              }
              else if ( v10 == -336968918 )
              {
                v16[0] = &v17;
                v16[1] = 1;
                v10 = 547402661;
                message.msg_name = 0;
                message.msg_namelen = 0;
                message.msg_iov = (struct iovec *)v16;
                message.msg_iovlen = 1;
              }
              else
              {
                v10 = -1620827105;
              }
            }
            else if ( v10 > 320272002 )
            {
              if ( v10 == 320272003 )
              {
                v10 = 1641782875;
              }
              else if ( v10 == 404269616 )
              {
                v10 = 40577391;
              }
              else
              {
                a1 = sub_4E3A8((__int64)&v21);
                v10 = 965436914;
              }
            }
            else if ( v10 == -11783688 )
            {
              a1 = (__int64)sub_44CE0(&fd);
              v10 = 1630030968;
            }
            else if ( v10 == 40577391 )
            {
              a1 = (__int64)sub_44CE0(&v21);
              v10 = 1935983871;
            }
            else
            {
              a1 = sub_5E91C(v3, v9);
              if ( (a1 & 1) != 0 )
                v10 = 2081049699;
              else
                v10 = 1939490945;
            }
          }
          if ( v10 > -1370786224 )
            break;
          if ( v10 <= -1692990736 )
          {
            if ( v10 == -2092422854 )
            {
              v10 = -11783688;
            }
            else
            {
              sub_3D2E8(a1, (__int64)"create pipe failed with {}", 26, v2);
              v7 = -1;
              v10 = -1370786223;
            }
          }
          else if ( v10 == -1692990735 )
          {
            v10 = 2124192264;
          }
          else if ( v10 == -1656216950 )
          {
            msg_control = message.msg_control;
            v10 = -1073230896;
          }
          else
          {
            sub_3D2E8(a1, (__int64)"sendmsg failed with {}", 22, v1);
            v7 = -1;
            v10 = -488080688;
          }
        }
        if ( v10 <= -904509838 )
          break;
        if ( v10 == -904509837 )
        {
          msg_control = 0;
          v10 = -1073230896;
        }
        else if ( v10 == -879918778 )
        {
          v10 = 1543233934;
        }
        else
        {
          message.msg_flags = 0;
          if ( message.msg_controllen <= 0xF )
            v10 = -904509837;
          else
            v10 = 748871923;
        }
      }
      v10 = 1935983871;
    }
    while ( v11 == -1370786223 );
    if ( v11 != -1073230896 )
      break;
    v12 = v21;
    v13 = fd;
    *(_QWORD *)msg_control = 20;
    msg_control[4] = v12;
    *((_QWORD *)msg_control + 1) = 0x100000001LL;
    a1 = sendmsg(v13, &message, 0);
    if ( a1 >= 0 )
      v10 = 476881499;
    else
      v10 = 320272003;
  }
  return v7;
}


// ===== 0x5CC58 sub_5CC58 =====
__int64 __fastcall sub_5CC58(__int64 a1, __int64 a2, __int64 a3, __int64 a4)
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

  sub_5CF50("get peercred failed with {}", "get peercred failed with {}", 28, a4, 0);
  sub_5CF50("get peersec failed with {}", "get peersec failed with {}", 27, v4, 0);
  sub_5CF50("read failed with {}", "read failed with {}", 20, v5, 0);
  sub_5CF50("read ({} != {}) failed with {}", "read ({} != {}) failed with {}", 31, v6, 0);
  sub_5CF50("write failed with {}", "write failed with {}", 21, v7, 0);
  sub_5CF50("write ({} != {}) failed with {}", "write ({} != {}) failed with {}", 32, v8, 0);
  sub_5CF50("recvmsg failed with {}", "recvmsg failed with {}", 23, v9, 0);
  sub_5CF50("sendmsg failed with {}", "sendmsg failed with {}", 23, v10, 0);
  sub_5CF50("too big string to read: {}", "too big string to read: {}", 27, v11, 0);
  sub_5CF50("too big string to write: {}", "too big string to write: {}", 28, v12, 0);
  sub_5CF50("/proc/{}/attr/sockcreate", "/proc/{}/attr/sockcreate", 25, v13, 0);
  sub_5CF50("set socket con failed with {}", "set socket con failed with {}", 30, v14, 0);
  sub_5CF50("getfd failed with {}", "getfd failed with {}", 21, v15, 0);
  sub_5CF50("setfd failed with {}", "setfd failed with {}", 21, v16, 0);
  for ( i = 2113424991; i == 2113424991; i = -1836801447 )
  {
    sub_5CF50("too long path {}", "too long path {}", 17, v17, 0);
    sub_5CF50("create abstract {} failed with {}", "create abstract {} failed with {}", 34, v19, 0);
    sub_5CF50("bind {} failed with {}", "bind {} failed with {}", 23, v20, 0);
    sub_5CF50("listen socket failed with {}", "listen socket failed with {}", 29, v21, 0);
    sub_5CF50("connect {} failed with {}", "connect {} failed with {}", 26, v22, 0);
    sub_5CF50("recv_fd: msg_flags = {}, msg_controllen({}) != {}", "recv_fd: msg_flags = {}, msg_controllen({}) != {}", 50, v23, 0);
    sub_5CF50("recv_fd: cmsg == nullptr", "recv_fd: cmsg == nullptr", 25, v24, 0);
  }
  sub_5CF50("recv_fd: cmsg_len({}) != {}", "recv_fd: cmsg_len({}) != {}", 28, v17, 0);
  sub_5CF50("recv_fd: cmsg_level != SOL_SOCKET", "recv_fd: cmsg_level != SOL_SOCKET", 34, v25, 0);
  return sub_5CF50("recv_fd: cmsg_type != SCM_RIGHTS", "recv_fd: cmsg_type != SCM_RIGHTS", 33, v26, 0);
}


// ===== 0x5E2A4 sub_5E2A4 =====
__int64 __fastcall sub_5E2A4(ssize_t a1, struct msghdr *a2)
{
  __int64 v2; // x23
  int v3; // w24
  int v4; // w29
  int i; // w21
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
              sub_3D2E8(a1, (__int64)"recvmsg failed with {}", 22, v2);
              i = 1737364685;
            }
            else
            {
              i = -1946650499;
            }
          }
          else if ( i == 1605448829 )
          {
            i = 489285618;
            a1 = __errno(a1);
            v2 = a1;
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


// ===== 0x60568 sub_60568 =====
__int64 __fastcall sub_60568(__int64 a1, socklen_t len)
{
  int v2; // w20
  int v3; // w21
  unsigned int v4; // w22
  __int64 v5; // x23
  unsigned int v6; // w24
  int v7; // w25
  int v9; // w26
  int v10; // w8
  int v11; // w0
  __int64 v12; // x0
  char *v14; // [xsp+0h] [xbp-60h] BYREF
  char *v15; // [xsp+8h] [xbp-58h] BYREF
  int v16; // [xsp+1Ch] [xbp-44h] BYREF

  v9 = -79931857;
  while ( 1 )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        while ( 1 )
        {
          v10 = v9;
          if ( v9 > 383358050 )
            break;
          if ( v9 > -629916684 )
          {
            if ( v9 <= -359408080 )
            {
              if ( v9 == -629916683 )
              {
                a1 = sub_4F998(&v16);
                v4 = a1;
                v9 = -1113166745;
              }
              else if ( v9 == -489394403 )
              {
                if ( v3 == -1 )
                  v9 = 999775070;
                else
                  v9 = -629916683;
              }
              else
              {
                a1 = sub_60A68(a1, "connect {} failed with {}", 25, &v14, v5);
                v6 = -1;
                v9 = 1746620697;
              }
            }
            else if ( v9 > -69566077 )
            {
              v9 = 1746620697;
            }
            else
            {
              v9 = 1746620697;
              if ( v10 != -359408079 )
                v9 = -1150880957;
            }
          }
          else if ( v9 <= -1113166746 )
          {
            if ( v9 == -2055660667 )
            {
              v15 = (char *)&xmmword_B0ABA + 1;
              v12 = __errno(a1);
              a1 = sub_60A68(v12, "create abstract {} failed with {}", 33, &v15, v12);
              v6 = -1;
              v9 = -359408079;
            }
            else if ( v9 == -1271697257 )
            {
              v14 = (char *)&xmmword_B0ABA + 1;
              v9 = -480549577;
              a1 = __errno(a1);
              v5 = a1;
            }
            else
            {
              v9 = 1607122760;
            }
          }
          else if ( v9 > -905860735 )
          {
            v9 = -1043215453;
          }
          else if ( v9 == -1113166745 )
          {
            v6 = v4;
            v9 = 45004095;
          }
          else
          {
            v2 = v16;
            v9 = 1035628720;
          }
        }
        if ( v9 > 1458210494 )
          break;
        if ( v9 <= 999775069 )
        {
          if ( v9 == 383358051 )
          {
            v9 = -2055660667;
          }
          else if ( v9 == 406862807 )
          {
            v11 = socket(1, 524290, 0);
            a1 = (__int64)sub_42DC4(&v16, v11);
            v9 = 1171334202;
          }
          else if ( v7 == -1 )
          {
            v9 = 1742365970;
          }
          else
          {
            v9 = -905860734;
          }
        }
        else if ( v9 > 1035628719 )
        {
          if ( v9 == 1035628720 )
          {
            a1 = connect(v2, (const struct sockaddr *)&word_B0AB8, len);
            v3 = a1;
            v9 = -489394403;
          }
          else
          {
            v7 = v16;
            v9 = 571095899;
          }
        }
        else if ( v9 == 999775070 )
        {
          v9 = 1013651174;
        }
        else
        {
          v9 = -1271697257;
        }
      }
      if ( v9 > 1746620696 )
        break;
      if ( v9 == 1458210495 )
      {
        v9 = 2033777490;
      }
      else
      {
        v9 = 1973739916;
        if ( v10 != 1607122760 )
          v9 = 383358051;
      }
    }
    if ( v9 > 2033777489 )
      break;
    if ( v9 == 1746620697 )
    {
      a1 = (__int64)sub_44CE0(&v16);
      v9 = 1458210495;
    }
    else
    {
      v9 = 406862807;
    }
  }
  return v6;
}


