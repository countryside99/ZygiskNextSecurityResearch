/*
 * libpayload.so - the execve() monitor injected into init (PID 1)
 * ================================================================
 * Complete decompilation of all 6 functions in the arm64 build (1536 bytes of .text,
 * ZERO imported symbols - every syscall is issued inline via svc #0).
 *
 * What it does: opens an AF_UNIX socket to the daemon address written into .bss at
 * injection time, sends a notification, then re-issues the original execve/execveat
 * syscall untouched. It is the trigger for process-creation detection, not a
 * replacement for the kernel's exec path.
 *
 * Original function names: my_execve, my_execveat, my_wait4 (exported), plus three
 * static helpers. Addresses are runtime addresses in the loadable segment.
 *
 * Auto-extracted from the Hex-Rays AArch64 decompilation of
 *   lib/arm64-v8a/libpayload.so
 * Strings that the binary XOR-decrypts at runtime have been
 * substituted back in as C string literals. Nothing else was edited.
 */

// ===== 0x43C sub_43C =====
bool __fastcall sub_43C(int a1, int a2)
{
  int *v4; // x1
  size_t v5; // x2
  unsigned __int64 v6; // x0
  int v8; // [xsp+Ch] [xbp-4h] BYREF

  v4 = &v8;
  v5 = 4;
  v8 = a2;
  do
  {
    while ( 1 )
    {
      v6 = linux_eabi_syscall(__NR_write, a1, v4, v5);
      if ( v6 >= 0xFFFFFFFFFFFFF001LL )
        break;
      v5 -= v6;
      if ( v6 )
      {
        v4 = (int *)((char *)v4 + v6);
        if ( v5 )
          continue;
      }
      return v5 == 0;
    }
  }
  while ( (_DWORD)v6 == -4 );
  return 0;
}


// ===== 0x4A4 sub_4A4 =====
bool __fastcall sub_4A4(int a1, char *a2)
{
  size_t v3; // x2
  unsigned __int64 v4; // x0

  v3 = 1;
  do
  {
    while ( 1 )
    {
      v4 = linux_eabi_syscall(__NR_read, a1, a2, v3);
      if ( v4 >= 0xFFFFFFFFFFFFF001LL )
        break;
      v3 -= v4;
      if ( v4 )
      {
        a2 += v4;
        if ( v3 )
          continue;
      }
      return v3 == 0;
    }
  }
  while ( (_DWORD)v4 == -4 );
  return 0;
}


// ===== 0x4F4 my_execve =====
int __fastcall my_execve(const char *a1, char *const *a2, char *const *a3)
{
  sub_52C();
  return linux_eabi_syscall(__NR_execve, a1, a2, a3);
}


// ===== 0x52C sub_52C =====
unsigned __int64 __fastcall sub_52C(unsigned __int64 result, unsigned __int8 **a2)
{
  unsigned __int8 *v2; // x9
  int v4; // w19
  int v5; // w21
  char *v6; // x1
  size_t v7; // x2
  unsigned __int64 v8; // x0
  __pid_t *v9; // x1
  size_t v10; // x2
  unsigned __int64 v11; // x0
  int v12; // w8
  unsigned __int8 *v13; // x10
  int v14; // t1
  int *v15; // x1
  size_t v16; // x2
  size_t v17; // x10
  unsigned __int64 v18; // x0
  unsigned __int64 v19; // x0
  __int64 v20; // x1
  unsigned __int8 *v22; // x9
  int v23; // w8
  unsigned __int8 *v24; // x10
  int v25; // t1
  int *v26; // x1
  size_t v27; // x2
  size_t v28; // x10
  unsigned __int64 v29; // x0
  unsigned __int64 v30; // x0
  unsigned __int8 *v31; // t1
  char v32; // [xsp+Bh] [xbp-35h] BYREF
  char v33[4]; // [xsp+Ch] [xbp-34h] BYREF
  char v34; // [xsp+10h] [xbp-30h] BYREF
  __pid_t v35; // [xsp+14h] [xbp-2Ch] BYREF
  int v36; // [xsp+18h] [xbp-28h] BYREF
  int v37; // [xsp+1Ch] [xbp-24h] BYREF

  if ( result )
  {
    v2 = (unsigned __int8 *)result;
    result = linux_eabi_syscall(__NR_socket, 1, 524289, 0);
    if ( result <= 0xFFFFFFFFFFFFF000LL )
    {
      v4 = result;
      v5 = result;
      if ( (unsigned __int64)linux_eabi_syscall(__NR_connect, result, (const struct sockaddr *)&daemon_addr, dword_8B50) > 0xFFFFFFFFFFFFF000LL )
        return linux_eabi_syscall(__NR_close, v4);
      v6 = &v34;
      v7 = 1;
      v34 = 0;
      while ( 1 )
      {
        while ( 1 )
        {
          v8 = linux_eabi_syscall(__NR_write, v4, v6, v7);
          if ( v8 < 0xFFFFFFFFFFFFF001LL )
            break;
          if ( (_DWORD)v8 != -4 )
            return linux_eabi_syscall(__NR_close, v4);
        }
        v7 -= v8;
        if ( !v8 )
          break;
        v6 += v8;
        if ( !v7 )
          goto LABEL_13;
      }
      if ( v7 )
        return linux_eabi_syscall(__NR_close, v4);
LABEL_13:
      v9 = &v35;
      v10 = 4;
      v35 = linux_eabi_syscall(__NR_getpid);
      while ( 1 )
      {
        while ( 1 )
        {
          v11 = linux_eabi_syscall(__NR_write, v4, v9, v10);
          if ( v11 < 0xFFFFFFFFFFFFF001LL )
            break;
          if ( (_DWORD)v11 != -4 )
            return linux_eabi_syscall(__NR_close, v4);
        }
        v10 -= v11;
        if ( !v11 )
          break;
        v9 = (__pid_t *)((char *)v9 + v11);
        if ( !v10 )
          goto LABEL_20;
      }
      if ( v10 )
        return linux_eabi_syscall(__NR_close, v4);
LABEL_20:
      v12 = -1;
      v13 = v2;
      do
      {
        v14 = *v13++;
        ++v12;
      }
      while ( v14 );
      v15 = &v36;
      v16 = 4;
      v17 = v12 <= 4096 ? (unsigned int)v12 : 0LL;
      v36 = v17;
      while ( 1 )
      {
        while ( 1 )
        {
          v18 = linux_eabi_syscall(__NR_write, v4, v15, v16);
          if ( v18 < 0xFFFFFFFFFFFFF001LL )
            break;
          if ( (_DWORD)v18 != -4 )
            return linux_eabi_syscall(__NR_close, v4);
        }
        v16 -= v18;
        if ( !v18 )
          break;
        v15 = (int *)((char *)v15 + v18);
        if ( !v16 )
          goto LABEL_32;
      }
      if ( v16 )
        return linux_eabi_syscall(__NR_close, v4);
LABEL_32:
      if ( (int)v17 >= 1 )
      {
        do
        {
          while ( 1 )
          {
            v19 = linux_eabi_syscall(__NR_write, v4, v2, v17);
            if ( v19 < 0xFFFFFFFFFFFFF001LL )
              break;
            if ( (_DWORD)v19 != -4 )
              return linux_eabi_syscall(__NR_close, v4);
          }
          v17 -= v19;
          if ( !v19 )
            break;
          v2 += v19;
        }
        while ( v17 );
        if ( v17 )
          return linux_eabi_syscall(__NR_close, v4);
      }
      v33[0] = 0;
      if ( sub_4A4(v5, v33) )
      {
        if ( v33[0] != 1 )
          goto LABEL_73;
        if ( a2 )
        {
          if ( *a2 )
          {
            v20 = 0;
            while ( a2[++v20] )
              ;
          }
          else
          {
            LODWORD(v20) = 0;
          }
          if ( !sub_43C(v5, v20) )
            return linux_eabi_syscall(__NR_close, v4);
          v22 = *a2;
          if ( *a2 )
          {
            while ( 1 )
            {
              v23 = -1;
              v24 = v22;
              do
              {
                v25 = *v24++;
                ++v23;
              }
              while ( v25 );
              v26 = &v37;
              v27 = 4;
              v28 = v23 <= 4096 ? (unsigned int)v23 : 0LL;
              v37 = v28;
              while ( 1 )
              {
                while ( 1 )
                {
                  v29 = linux_eabi_syscall(__NR_write, v4, v26, v27);
                  if ( v29 < 0xFFFFFFFFFFFFF001LL )
                    break;
                  if ( (_DWORD)v29 != -4 )
                    goto LABEL_73;
                }
                v27 -= v29;
                if ( !v29 )
                  break;
                v26 = (int *)((char *)v26 + v29);
                if ( !v27 )
                  goto LABEL_64;
              }
              if ( v27 )
                goto LABEL_73;
LABEL_64:
              if ( (int)v28 >= 1 )
              {
                while ( 1 )
                {
                  while ( 1 )
                  {
                    v30 = linux_eabi_syscall(__NR_write, v4, v22, v28);
                    if ( v30 < 0xFFFFFFFFFFFFF001LL )
                      break;
                    if ( (_DWORD)v30 != -4 )
                      goto LABEL_73;
                  }
                  v28 -= v30;
                  if ( !v30 )
                    break;
                  v22 += v30;
                  if ( !v28 )
                    goto LABEL_72;
                }
                if ( v28 )
                  break;
              }
LABEL_72:
              v31 = a2[1];
              ++a2;
              v22 = v31;
              if ( !v31 )
                goto LABEL_73;
            }
          }
          goto LABEL_73;
        }
        if ( sub_43C(v5, 0) )
LABEL_73:
          sub_4A4(v5, &v32);
      }
      return linux_eabi_syscall(__NR_close, v4);
    }
  }
  return result;
}


// ===== 0x828 my_execveat =====
signed __int64 __fastcall my_execveat(int a1, void *a2, unsigned __int8 **a3, void *a4, int a5)
{
  void *v10; // x5
  void *v11; // x6

  sub_52C((unsigned __int64)a2, a3);
  return linux_eabi_syscall(__NR_execveat, (void *)a1, a2, a3, a4, (void *)a5, v10, v11);
}


// ===== 0x880 my_wait4 =====
signed __int64 __fastcall my_wait4(__pid_t a1, _DWORD *a2, int a3, struct rusage *a4)
{
  signed __int64 result; // x0
  signed __int64 v6; // x21
  unsigned __int64 v7; // x8
  int v8; // w20
  int v9; // w0
  size_t v10; // x2
  char *v11; // x1
  unsigned __int64 v12; // x0
  int *v13; // x1
  size_t v14; // x2
  unsigned __int64 v15; // x0
  int *v16; // x1
  size_t v17; // x2
  unsigned __int64 v18; // x0
  char v19; // [xsp+Fh] [xbp-31h] BYREF
  int v20; // [xsp+10h] [xbp-30h] BYREF
  char v21; // [xsp+14h] [xbp-2Ch] BYREF
  int v22; // [xsp+18h] [xbp-28h] BYREF
  int v23; // [xsp+1Ch] [xbp-24h] BYREF

  v20 = 0;
  result = linux_eabi_syscall(__NR_wait4, a1, (__WAIT_STATUS)&v20, a3, a4);
  if ( (unsigned __int64)(result - 1) <= 0xFFFFFFFFFFFFEFFFLL && ((v20 & 0x7F) == 0 || (((_BYTE)v20 + 1) & 0x7E) != 0) )
  {
    v6 = result;
    v7 = linux_eabi_syscall(__NR_socket, 1, 524289, 0);
    result = v6;
    if ( v7 <= 0xFFFFFFFFFFFFF000LL )
    {
      v8 = v7;
      if ( (unsigned __int64)linux_eabi_syscall(__NR_connect, v7, (const struct sockaddr *)&daemon_addr, dword_8B50) <= 0xFFFFFFFFFFFFF000LL )
      {
        v10 = 1;
        v11 = &v21;
        v21 = 1;
        while ( 1 )
        {
          while ( 1 )
          {
            v12 = linux_eabi_syscall(__NR_write, v7, v11, v10);
            if ( v12 < 0xFFFFFFFFFFFFF001LL )
              break;
            if ( (_DWORD)v12 != -4 )
              goto LABEL_6;
          }
          v10 -= v12;
          if ( !v12 )
            break;
          v11 += v12;
          if ( !v10 )
            goto LABEL_17;
        }
        if ( v10 )
          goto LABEL_6;
LABEL_17:
        v13 = &v22;
        v14 = 4;
        v22 = v6;
        while ( 1 )
        {
          while ( 1 )
          {
            v15 = linux_eabi_syscall(__NR_write, v7, v13, v14);
            if ( v15 < 0xFFFFFFFFFFFFF001LL )
              break;
            if ( (_DWORD)v15 != -4 )
              goto LABEL_6;
          }
          v14 -= v15;
          if ( !v15 )
            break;
          v13 = (int *)((char *)v13 + v15);
          if ( !v14 )
            goto LABEL_24;
        }
        if ( v14 )
          goto LABEL_6;
LABEL_24:
        v16 = &v23;
        v17 = 4;
        v23 = v20;
        while ( 1 )
        {
          while ( 1 )
          {
            v18 = linux_eabi_syscall(__NR_write, v7, v16, v17);
            if ( v18 < 0xFFFFFFFFFFFFF001LL )
              break;
            if ( (_DWORD)v18 != -4 )
              goto LABEL_6;
          }
          v17 -= v18;
          if ( !v18 )
            break;
          v16 = (int *)((char *)v16 + v18);
          if ( !v17 )
            goto LABEL_31;
        }
        if ( v17 )
          goto LABEL_6;
LABEL_31:
        sub_4A4(v7, &v19);
      }
LABEL_6:
      v9 = linux_eabi_syscall(__NR_close, v8);
      result = v6;
    }
  }
  if ( a2 )
    *a2 = v20;
  return result;
}


