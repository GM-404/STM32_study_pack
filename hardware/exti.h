#ifndef __EXTI_H
#define __EXTI_H
#include "stm32f10x.h"                     // STM32F10x头文件
#include "config.h"                        // 配置头文件
#define ENABLE_EXTI_15_10_MODULE_CLOCK (1) // 使能EXTI15_10模块时钟，如果需要开启EXTI15_10的时钟置1
void EXTI_15_10_Init();
uint16_t Get_EXTI_Count(void);   // 获取EXTI中断次数
void EXTI15_10_IRQHandler(void); // EXTI15_10中断服务函数
#endif
