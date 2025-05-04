/*
说明：使用时同样先在config.h中打开模块开关，然后在config.c中配置引脚和时钟
      可以使用定时器2的内部时钟和外部时钟，需要在config.h中打开开关
      由于定时器2的复用引脚是PA0，所以在config.h中定义了TIMER2_MODULE_PIN引脚
    计数默认是向上计数，1s间隔

*/
#ifndef __TIMER2_H__
#define __TIMER2_H__

#include "config.h"                    // 配置头文件
void Timer2_Inter_Init(void);          // 定时器2初始化函数(内部时钟)
void Timer2_Out_Init(void);            // 定时器2初始化函数(外部时钟)
uint16_t Get_Count_Timer2(void);       // 获取定时器2计数值函数
uint16_t Get_Number_Timer2_Exti(void); // 获取定时器2中断次数函数
#endif                                 // __TIMER2_H__
