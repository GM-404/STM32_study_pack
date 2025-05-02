#ifndef _CONFIG_H_
#define _CONFIG_H_
/**
 * @brief STM32F103C8系列单片机配置文件
 *
 * @return 无
 */
/*参数设置-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --*/

// 包含头文件
#include "led.h"   // LED头文件
#include "Delay.h" // 延时头文件

// 需要初始化的模块
void Module_Init_Config(void); // 配置函数

#endif // _CONFIG_H_
