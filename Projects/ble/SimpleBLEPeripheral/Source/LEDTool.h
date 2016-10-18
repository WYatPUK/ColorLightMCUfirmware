static bool IsHexNum(char x)
{
  if ((x>='0' && x<='9') || (x>='a' && x<='f') || (x>='A' && x<='F')) return true;
  return false;
}
static char HexToChar(char H, char L)
{
  char A = 0;
  if (H>='0' && H<='9') A |= (H - '0')<<4;
  else if (H>='a' && H<='f') A |= (H - 'a' + 10)<<4;
  else if (H>='A' && H<='F') A |= (H - 'A' + 10)<<4;
  if (L>='0' && L<='9') A |= (L - '0');
  else if (L>='a' && L<='f') A |= (L - 'a' + 10);
  else if (L>='A' && L<='F') A |= (L - 'A' + 10);
  return A;
}
static bool IsSetUnitCmd(uint8 *String,uint8 N)
{
  if (N!=11) return false;
  if (String[0]!='U' || String[1]!='n' || String[2]!='i' || String[3]!='t' || String[4]!=':') return false;
  if (!IsHexNum(String[5]) || !IsHexNum(String[6]) || !IsHexNum(String[7]) || !IsHexNum(String[8]) || !IsHexNum(String[9]) || !IsHexNum(String[10])) return false;
  return true;
}
static bool IsSetNSameCmd(uint8 *String,uint8 N)
{
  if (N!=15) return false;
  if (String[0]!='N' || String[1]!='S' || String[2]!='a' || String[3]!='m' || String[4]!='e' || String[5]!=':') return false;
  if (!IsHexNum(String[6]) || !IsHexNum(String[7]) || !IsHexNum(String[8]) || !IsHexNum(String[9]) || !IsHexNum(String[10]) || !IsHexNum(String[11])) return false;
  if (String[12]!='o' || String[13]!='f') return false;
  if (!IsHexNum(String[14])) return false;
  return true;
}
static bool IsPushNCmd(uint8 *String,uint8 N)
{
  if (N!=15) return false;
  if (String[0]!='P' || String[1]!='u' || String[2]!='s' || String[3]!='h' || String[4]!='N' || String[5]!=':') return false;
  if (!IsHexNum(String[6]) || !IsHexNum(String[7]) || !IsHexNum(String[8]) || !IsHexNum(String[9]) || !IsHexNum(String[10]) || !IsHexNum(String[11])) return false;
  if (String[12]!='o' || String[13]!='f') return false;
  if (!IsHexNum(String[14])) return false;
  return true;
}