#ifndef __TIMER2_H__
#define __TIMER2_H__

#include "config.h"                    // 配置头文件
void Timer2_Inter_Init(void);          // 定时器2初始化函数(内部时钟)
void Timer2_Out_Init(void);            // 定时器2初始化函数(外部时钟)
uint16_t Get_Count_Timer2(void);       // 获取定时器2计数值函数
uint16_t Get_Number_Timer2_Exti(void); // 获取定时器2中断次数函数
#endif                                 // __TIMER2_H__
