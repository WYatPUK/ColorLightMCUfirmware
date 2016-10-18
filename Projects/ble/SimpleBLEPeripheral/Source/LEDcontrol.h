#include "LEDTool.h"

#define LEDp P1_2
static char GRBbuffer[300];
static bool Blink_Open = false;

static void Code(unsigned char a){
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

static void SetGRBAll(char *All, int num)
{
  int i=0;
  for (;i<num;i++)
  {
    Code(All[i]);
  }
}

static void LED_perfrom_period_task()
{
  
}

static void ExcuteSetUnitCmd(uint8 *String,uint8 N)
{
  //already confirm at "IsSetUnitCmd" function
  GRBbuffer[0] = HexToChar(String[5], String[6]);
  GRBbuffer[1] = HexToChar(String[7], String[8]);
  GRBbuffer[2] = HexToChar(String[9], String[10]);
  SetGRBAll(GRBbuffer, 3);
}
static void ExcuteSetNSameCmd(uint8 *String,uint8 N)
{
  char i= String[14] - '0';
  char Num = i;
  char G = HexToChar(String[6], String[7]);
  char R = HexToChar(String[8], String[9]);
  char B = HexToChar(String[10], String[11]);
  while (i--)
  {
    GRBbuffer[3*i] = G;
    GRBbuffer[3*i + 1] = R;
    GRBbuffer[3*i + 2] = B;
  }
  SetGRBAll(GRBbuffer, 3*Num);
}
static void ExcutePushNCmd(uint8 *String,uint8 N)
{
  char i= String[14] - '0';
  char Num = i;
  while (--i)
  {
    GRBbuffer[3*i] = GRBbuffer[3*i-3];
    GRBbuffer[3*i + 1] = GRBbuffer[3*i-2];
    GRBbuffer[3*i + 2] = GRBbuffer[3*i-1];
  }
  GRBbuffer[0] = HexToChar(String[6], String[7]);
  GRBbuffer[1] = HexToChar(String[8], String[9]);
  GRBbuffer[2] = HexToChar(String[10], String[11]);
  SetGRBAll(GRBbuffer, 3*Num);
}
static void HandleGRBCmd(uint8 *String, uint8 N)
{
  if (IsSetUnitCmd(String, N))
  {
    ExcuteSetUnitCmd(String, N);
  }
  else if (IsSetNSameCmd(String, N))
  {
    ExcuteSetNSameCmd(String, N);
  }
  else if (IsPushNCmd(String, N))
  {
    ExcutePushNCmd(String, N);
  }
}