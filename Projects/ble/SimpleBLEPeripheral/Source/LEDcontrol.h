#ifndef LEDCONTROL_H
#define LEDCONTROL_H

//�޸������ɫ���в���ֱ�ӷ��͵�LED�ϣ����Ǵ浽GRBbuffer�
//��LED_perform_period_task()����ɷ���LED
//������ǿ��ʹ��10Hz�ĸ���Ƶ��

#ifdef __cplusplus
extern "C"
{
#endif

  extern void LED_perfrom_period_task();
  
  extern void HandleGRBCmd(uint8 *String, uint8 N);

#ifdef __cplusplus
}
#endif

#endif