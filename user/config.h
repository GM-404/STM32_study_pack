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
#include "key.h"   // 按键头文件
#include "Delay.h" // 延时头文件
#include "OLED.h"  // OLED头文件
#include "exti.h"  // EXTI头文件

// 模块总开关
#define LED_MODULE        (1) // LED模块开关
#define KEY_MODULE        (1) // 按键模块开关
#define OLED_MODULE       (1) // OLED模块开关
#define EXTI_15_10_MODULE (1) // EXTI模块开关

// 引脚定义
#define LED_PIN GPIO_Pin_1 // 在这里定义LED的引脚  GPIOA
#define KEY_PIN GPIO_Pin_0 // 按键引脚定义 GPIOB
// define OLED_PIN引脚在对应的.c文件中定义,默认PB8,PB9
#define EXTI_15_10_MODULE_PIN  GPIO_Pin_13      // EXTI引脚定义 GPIOB
#define EXTI_15_10_MODULE_AFIO GPIO_PinSource13 // EXTI引脚映射到AFIO的引脚定义 与上面对应
#define EXTI_15_10_MODULE_LINE EXTI_Line13      // EXTI线定义 EXTI14,与EXTI_15_10_MODULE_PIN对应

//  初始化模块
void Module_Init_Config(void); // 配置函数

#endif // _CONFIG_H_
