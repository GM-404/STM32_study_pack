/*
说明:该模块实际作用为PWM的初始化，作用为用引脚控制PWM的占空比
*/

#ifndef __PWM_H
#define __PWM_H
#include "config.h"             // 配置头文件
#include "stm32f10x.h"          // STM32F10x头文件
void PWM_Init(void);            // PWM初始化函数
void PWM_Breathe_SetCompare1(); // 设置PWM1的占空比函数

#endif /* __PWM_H */