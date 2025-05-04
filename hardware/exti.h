/*
 * @brief 此为中断头文件初始化，在config.h中打开开关后，会自动初始化
   由于10~15号引脚的外部中断线是共用的，所以在此文件中定义了EXTI15_10_Init函数
   该函数会初始化10~15号引脚的外部中断线，目前配置是只针对其中一个引脚，后续需要可以在
   config.h中定义其他引脚的外部中断线
 * @version 0.1
 * */
#ifndef __EXTI_H
#define __EXTI_H
#include "stm32f10x.h"                     // STM32F10x头文件
#include "config.h"                        // 配置头文件
#define ENABLE_EXTI_15_10_MODULE_CLOCK (1) // 使能EXTI15_10模块时钟，如果需要开启EXTI15_10的时钟置1
void EXTI_15_10_Init();
uint16_t Get_EXTI_Count(void);   // 获取EXTI中断次数
void EXTI15_10_IRQHandler(void); // EXTI15_10中断服务函数
#endif
