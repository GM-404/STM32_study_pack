#ifndef __MOTOR_H
#define __MOTOR_H

#include "config.h"    // 配置头文件
#include "stm32f10x.h" // STM32F10x头文件

void Motor_Init(void);
void Motor_SetSpeed(int8_t Speed);

#endif
