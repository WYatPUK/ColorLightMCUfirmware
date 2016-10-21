#define LEDp P1_2

uint8 brown[] = "30ff00";
uint8 red[] = "00ff00";
uint8 orange[] = "88ff00";
uint8 yellow[] = "ffff00";
uint8 green[] = "ff0000";
uint8 blue[] = "0000ff";
uint8 purple[] = "0099ff";
uint8 grey[] = "444444";
uint8 white[] = "ffffff";
uint8 black[] = "000000";

bool IsHexNum(char x)
{
  if ((x>='0' && x<='9') || (x>='a' && x<='f') || (x>='A' && x<='F')) return true;
  return false;
}
bool IsDecNum(char x)
{
  if (x>='0' && x<='9') return true;
  return false;
}
int CharToDec(char x)
{
  return (x - '0');
}
char HexToChar(char H, char L)
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
bool IsMatchString(uint8 *StringA, uint8 *StringB, uint8 N)
{
  for (int i=0; i<N; i++)
  {
    if (StringA[i] != StringB[i]) return false;
  }
  return true;
}
bool IsMatchHex(uint8 *String, uint8 N)
{
  for (int i=0; i<N; i++)
  {
    if (!IsHexNum(String[i])) return false;
  }
  return true;
}
bool IsMatchDec(uint8 *String, uint8 N)
{
  for (int i=0; i<N; i++)
  {
    if (!IsDecNum(String[i])) return false;
  }
  return true;
}
bool IsSetUnitCmd(uint8 *String,uint8 N)
{
  if (N!=11) return false;
  if (!IsMatchString("Unit:", String, 5)) return false;
  if (!IsMatchHex(String + 5, 6)) return false;
  return true;
}
bool IsSetNSameCmd(uint8 *String,uint8 N)
{
  if (N!=15) return false;
  if (!IsMatchString("NSame:", String, 6)) return false;
  if (!IsMatchHex(String + 6, 6)) return false;
  if (!IsMatchString("of", String + 12, 2)) return false;
  if (!IsHexNum(String[14])) return false;
  return true;
}
bool IsPushNCmd(uint8 *String,uint8 N)
{
  if (N!=15) return false;
  if (!IsMatchString("PushN:", String, 6)) return false;
  if (!IsMatchHex(String + 6, 6)) return false;
  if (!IsMatchString("of", String + 12, 2)) return false;
  if (!IsHexNum(String[14])) return false;
  return true;
}
bool IsTel(uint8 *String, uint8 N)
{
  if (N!=15) return false;
  if (!IsMatchString("Tel:", String, 4)) return false;
  if (!IsMatchDec(String + 4, 11)) return false;
  return true;
}
bool IsTelDown(uint8 *String, uint8 N)
{
  if (N!=7) return false;
  if (!IsMatchString("TelDown", String, 7)) return false;
  return true;
}

bool IsSetEffect(uint8 *String, uint8 N)
{
  if (N<=5) return false;
  if (!IsMatchString("SetE:", String, 5)) return false;
  return true;
}
void Code(const unsigned char a){
  LEDp = 1;
  asm("NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n");
  LEDp = a >> 7;
  asm("NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n");
  LEDp = 0;
  asm("NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n");
  
  LEDp = 1;
  asm("NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n");
  LEDp = a >> 6;
  asm("NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n");
  LEDp = 0;
  asm("NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n");
  
  LEDp = 1;
  asm("NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n");
  LEDp = a >> 5;
  asm("NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n");
  LEDp = 0;
  asm("NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n");
  
  LEDp = 1;
  asm("NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n");
  LEDp = a >> 4;
  asm("NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n");
  LEDp = 0;
  asm("NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n");
  
  LEDp = 1;
  asm("NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n");
  LEDp = a >> 3;
  asm("NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n");
  LEDp = 0;
  asm("NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n");
  
  LEDp = 1;
  asm("NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n");
  LEDp = a >> 2;
  asm("NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n");
  LEDp = 0;
  asm("NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n");
  
  LEDp = 1;
  asm("NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n");
  LEDp = a >> 1;
  asm("NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n");
  LEDp = 0;
  asm("NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n");
  
  LEDp = 1;
  asm("NOP\n NOP\n NOP\n NOP\n NOP\n");
  LEDp = a >> 0;
  asm("NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n");
  LEDp = 0;
  asm("NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n NOP\n");
  
}

void SetGRBAll(char *All, int num)
{
  int i=0;
  num *= 3;
  for (;i<num;i++)
  {
    Code(All[i]);
  }
}

uint8* get_tel_ptr(int num)
{
  switch (num)
  {
  case 0:
    return brown;
  case 1:
    return red;
  case 2:
    return orange;
  case 3:
    return yellow;
  case 4:
    return green;
  case 5:
    return blue;
  case 6:
    return purple;
  case 7:
    return grey;
  case 8:
    return white;
  case 9:
    return black;
  }
  return black;
}
