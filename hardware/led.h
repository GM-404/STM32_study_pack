/*
 * 说明： 该模块本质为初始化一个引脚，控制其输出高低电平
 *        该模块可以用于LED灯的控制，也可以用于其他GPIO的控制
 * 使用时先再config.h中定义好引脚和打开模块开关
 * 然后在led.h中打开使能GPIOA时钟的宏定义
 */
#ifndef __LED_H__
#define __LED_H__

#include "stm32f10x.h"             // Device header
#include "config.h"                // 配置头文件
#define ENABLE_LED_GPIOA_CLOCK (1) // 使能LED模块GPIOA时钟,如果需要开启GPIOA的时钟置1

/**
 * 函    数：LED初始化,自定义引脚，状态
 *           LED_PIN: LED引脚，见config.h
 *       status: LED状态 1为高电平，0为低电平
 * 返 回 值：无
 *
 */
void LED_Init(uint16_t status); // GPIO初始化

/**
 * 函    数：LED翻转
 * 参    数：无
 * 返 回 值：无
 */
void LED1_Turn(void); // LED1翻转
#endif                /* __LED_H__ */
