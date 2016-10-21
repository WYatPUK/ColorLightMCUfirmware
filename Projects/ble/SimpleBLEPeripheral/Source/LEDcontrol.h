#ifndef LEDCONTROL_H
#define LEDCONTROL_H

//修改完的颜色序列并不直接发送到LED上，而是存到GRBbuffer里，
//待LED_perform_period_task()来完成发送LED
//这样就强制使用10Hz的更新频率

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