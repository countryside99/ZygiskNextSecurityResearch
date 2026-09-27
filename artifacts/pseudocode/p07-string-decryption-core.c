/*
 * zygiskd - the string decryption entry points
 * =============================================
 * These two 49-line wrappers are what every call of the form
 *
 *     sub_3D158(&byte_6, (__int64)&unk_1DB512, 13);
 *
 * ends up in. The plain[i] = enc[i] ^ key[i % 32] core sits in sub_5FCE4 ->
 * sub_40E48. In the dumps below every &unk_XXXXXX operand has been replaced with the
 * actual plaintext, so the calls read as string literals.
 *
 * See 04-string-crypto-method.md for the key tables and the full method.
 *
 * Auto-extracted from the Hex-Rays AArch64 decompilation of
 *   bin/arm64-v8a/zygiskd
 * Strings that the binary XOR-decrypts at runtime have been
 * substituted back in as C string literals. Nothing else was edited.
 */

// ===== 0x3CC3C sub_3CC3C =====
_BYTE *__fastcall sub_3CC3C(_BYTE *result, __int64 a2, __int64 a3, __int64 a4)
{
  unsigned int v7; // w22
  int i; // w8
  _BYTE v9[1024]; // [xsp+10h] [xbp-460h] BYREF

  v7 = (unsigned int)result;
  for ( i = 1023163238; ; i = -802685012 )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        while ( i <= -802685013 )
        {
          if ( i > -1138233942 )
          {
            i = -488953075;
          }
          else if ( i == -2039192464 )
          {
            result = (_BYTE *)sub_191B28(v7, v9);
            i = 1954853132;
          }
          else
          {
            i = -794324651;
          }
        }
        if ( i > -488953076 )
          break;
        if ( i == -802685012 )
          i = -1781723169;
        else
          i = -1138233941;
      }
      if ( i != -488953075 )
        break;
      result = (_BYTE *)sub_5EE40(v9, a2, a2, a3, a4);
      *result = 0;
      i = -2039192464;
    }
    if ( i != 1023163238 )
      break;
  }
  return result;
}


// ===== 0x3D158 sub_3D158 =====
_BYTE *__fastcall sub_3D158(_BYTE *result, __int64 a2, __int64 a3)
{
  unsigned int v5; // w21
  int i; // w9
  _BYTE v7[1024]; // [xsp-400h] [xbp-430h] BYREF

  v5 = (unsigned int)result;
  for ( i = 1078696302; ; i = -1283271264 )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        while ( i > 1078696301 )
        {
          if ( i > 1499420930 )
          {
            i = -154311009;
          }
          else if ( i == 1078696302 )
          {
            i = -1440074395;
          }
          else
          {
            result = (_BYTE *)sub_191B28(v5, v7);
            i = -287150771;
          }
        }
        if ( i > -1283271265 )
          break;
        if ( i == -1791584066 )
          i = 1562662868;
        else
          i = -1791584066;
      }
      if ( i != -1283271264 )
        break;
      i = 1222823289;
    }
    if ( i != -154311009 )
      break;
    result = (_BYTE *)sub_5FCE4(v7, a2, a2, a3);
    *result = 0;
  }
  return result;
}


