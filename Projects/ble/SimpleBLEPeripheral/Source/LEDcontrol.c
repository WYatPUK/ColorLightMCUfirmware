#include "OnBoard.h"
#include "gatt.h"
#include "simpleBLE.h"
#include "LEDcontrol.h"
#include "LEDTool.h"

static char GRBbuffer[60];
static char *GRBstatue;
static char *GRBTel = GRBbuffer + 3;

uint8 GRB_count = 0;

void SetColor_at(int num, uint8 *String, char *buffer)
{
  buffer[3*num] = HexToChar(String[0], String[1]);
  buffer[3*num+1] = HexToChar(String[2], String[3]);
  buffer[3*num+2] = HexToChar(String[4], String[5]);
}
char TelNum[11] = {'0','0','0','0','0','0','0','0','0','0','0'};

//״̬����
#define LED_Mode_NULL 0x00
#define LED_Mode_Tel 0x41
#define LED_Mode_Msg 0x42
#define LED_Mode_WeChat 0x43 //Ĭ�Ϲ��˵�����
#ifdef QQenabled
#define LED_Mode_QQ 0x44
#endif
//Ч������
#define LED_Mode_Blink_Slow 0x71
#define LED_Mode_Blink_Fast 0x72
#define LED_Mode_Breath_Slow 0x73
#define LED_Mode_Breath_Fast 0x74
#define LED_Mode_Blink_Mani 0x75 //�������ǿ����ֻ��������ʵ�
#define LED_Mode_Breath_Mani 0x76 //�����ֵ�ʱ��high����������
#define LED_Mode_Disco 0x77
//
char Ringing_Mode = LED_Mode_Breath_Slow;
char LED_Mode;

/*
  ֻ����������͵ײ�API���Ըı��ǿ����ɫ
  �½�������ȫ��Ҫ�ŵ�GRBbuffer��ر�ģ�GRBstatueָ���0λ��GRBTelָ���3λ
    ��Ӧstatueָʾ�ƺͺ�����ʾ��

  ���ȼ�������
    1���Ƿ���������
      ���ӣ���һ�����ȼ�
      δ���ӣ���˸���10�룬Ȼ��Ϩ��
    2���Ƿ��е绰��������
      û�У���һ�����ȼ�
      �У���ʾ���룬Ĭ��Ч��ΪLED_Mode_Breath_Slow���ɵ���Ringing_Mode
    3���Ƿ��ж���
      û�У���һ�����ȼ�
      �У���ʾ���룬statusָʾ
    4���Ƿ���Ⱦ����
      û�У���һ�����ȼ�
      �У���������blink��breath
*/
void LED_perfrom_period_task() // ���Գɹ�
{
  GRB_count++;
  GRB_count%=127;
  if (!simpleBLE_IfConnected())
  {
    
  } else if (LED_Mode == LED_Mode_Tel)
  {
  } else if (LED_Mode == LED_Mode_Msg)
  {
  }
  SetColor_at(0, "ffffff", GRBstatue);
  SetGRBAll(GRBbuffer, 5);
}

void ExcuteSetUnitCmd(uint8 *String,uint8 N)
{
  //already confirm at "IsSetUnitCmd" function
  SetColor_at(0, String + 5, GRBbuffer);
  SetGRBAll(GRBbuffer, 1);
}
void ExcuteSetNSameCmd(uint8 *String,uint8 N)
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
  SetGRBAll(GRBbuffer, Num);
}
void ExcutePushNCmd(uint8 *String,uint8 N)
{
  char i= String[14] - '0';
  char Num = i;
  while (--i)
  {
    GRBbuffer[3*i] = GRBbuffer[3*i-3];
    GRBbuffer[3*i + 1] = GRBbuffer[3*i-2];
    GRBbuffer[3*i + 2] = GRBbuffer[3*i-1];
  }
  SetColor_at(0, String + 6, GRBbuffer);
  SetGRBAll(GRBbuffer, Num);
}
void ExcuteTelCmd(uint8 *String,uint8 N)
{
  int i;
  for (i=0; i<11; i++)
  {
    TelNum[i] = String[i+4];
    SetColor_at(i, get_tel_ptr(CharToDec(TelNum[i])), GRBTel);
  }
  LED_Mode = LED_Mode_Tel;
}
void ExcuteTelDownCmd()
{
  LED_Mode = LED_Mode_NULL;
}
void ExcuteSetE(uint8 *String, uint8 N)
{
  uint8 *Status = String + 5;
  uint8 Len = N - 5;
  if (Len == 4 && IsMatchString("NULL", Status, Len))
  {
    LED_Mode = LED_Mode_NULL;
  } else if (Len == 3 && IsMatchString("Tel", Status, Len))
  {
    LED_Mode = LED_Mode_Tel;
  } else if (Len == 10 && IsMatchString("Blink_Slow", Status, 10))
  {
    LED_Mode = LED_Mode_Blink_Slow;
  } else if (Len == 10 && IsMatchString("Blink_Fast", Status, Len))
  {
    LED_Mode = LED_Mode_Blink_Fast;
  } else if (Len == 11 && IsMatchString("Breath_Slow", Status, Len))
  {
    LED_Mode = LED_Mode_Breath_Slow;
  } else if (Len == 11 && IsMatchString("Breath_Fast", Status, Len))
  {
    LED_Mode = LED_Mode_Breath_Fast;
  }
}
void HandleGRBCmd(uint8 *String, uint8 N)
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
  else if (IsTel(String, N))
  {
    ExcuteTelCmd(String, N);
  }
  else if (IsTelDown(String, N))
  {
    ExcuteTelDownCmd();
  }
  else if (IsSetEffect(String, N))
  {
    ExcuteSetE(String, N);
  }
}