#ifndef _CONFIG_H_
#define _CONFIG_H_
/**
 * @brief STM32F103C8系列单片机配置文件
 *
 * @return 无
 */
/*参数设置-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --*/

// 包含头文件
#include "led.h"    // LED头文件
#include "key.h"    // 按键头文件
#include "Delay.h"  // 延时头文件
#include "OLED.h"   // OLED头文件
#include "exti.h"   // EXTI头文件
#include "timer2.h" // 定时器2头文件
#include "timer3.h" // 定时器3头文件
#include "pwm.h"    // PWM头文件
#include "motor.h"  // 电机头文件
// 模块总开关
#define LED_MODULE          (1) // LED模块开关
#define KEY_MODULE          (1) // 按键模块开关
#define OLED_MODULE         (1) // OLED模块开关
#define EXTI_15_10_MODULE   (1) // EXTI模块开关

#define TIMER2_MODULE       (0)                    // 定时器2模块开关
#define TIMER2_INTER_MODULE (0)                    // 定时器2内部时钟模式开关
#define TIMER2_EXT_MODULE   (~TIMER2_INTER_MODULE) // 定时器2外部时钟模式开关

#define TIMER3_MODULE       (1) // 定时器3模块开关
#define TIMER3_INTER_MODULE (1) // 定时器3内部时钟模式开关
// 定时器3外部时钟模式暂时不可用
#define TIMER3_EXT_MODULE   0 // (~TIMER3_INTER_MODULE) // 定时器3外部时钟模式开关

#define PWM_MODULE          (1) // PWM模块开关，同时初始化定时器的PA0,PA1,PA2,PA3引脚
#define PWM_PWM_MODULE_AFIO (0) // timer2引脚映射到AFIO的引脚定义 0为默认引脚PA0，1为重映射引脚PA15
#define MOTOR_MODULE        (0) // 电机模块开关
// 引脚定义
#define LED_PIN GPIO_Pin_3 // 在这里定义LED的引脚  GPIOA
#define KEY_PIN GPIO_Pin_0 // 按键引脚定义 GPIOB
// define OLED_PIN引脚在对应的.c文件中定义,默认PB8(SCL),PB9(SDA)
#define EXTI_15_10_MODULE_PIN  GPIO_Pin_13      // EXTI引脚定义 GPIOB 13
#define EXTI_15_10_MODULE_AFIO GPIO_PinSource13 // EXTI引脚映射到AFIO的引脚定义 与上面对应
#define EXTI_15_10_MODULE_LINE EXTI_Line13      // EXTI线定义 EXTI14,与EXTI_15_10_MODULE_PIN对应

#define TIMER2_MODULE_PIN      GPIO_Pin_0      // 定时器2引脚定义,在使能外部时钟时使用,PA0
#define TIMER2_MODULE_AFIO_PIN GPIO_PinSource0 // 定时器2引脚映射到AFIO的引脚定义 与上面对应

// #define TIMER3_MODULE_PIN      GPIO_Pin_6      // 定时器3引脚定义,在使能外部时钟时使用,PA6
// #define TIMER3_MODULE_AFIO_PIN GPIO_PinSource6 // 定时器3引脚映射到AFIO的引脚定义 与上面对应

#if (PWM_PWM_MODULE_AFIO)          // 如果PWM模块引脚映射为0，则使用默认引脚
#define PWM_MODULE_PIN GPIO_Pin_15 // 定时器2引脚映射到AFIO的引脚定义 与上面对应
#else
#define PWM_MODULE_PIN GPIO_Pin_0 // 定时器2引脚映射到AFIO的引脚定义 与上面对应
#endif
#define PWM_MODULE_Channel2_PIN GPIO_Pin_1 // 定时器2通道2引脚(舵机)
#define PWM_MODULE_Channel3_PIN GPIO_Pin_2 // 定时器2通道3引脚(直流电机)
#define PWM_MODULE_Channel4_PIN GPIO_Pin_3 // 定时器2通道4引脚（待定）

#define PWM_MOTOR_MODULE_PIN1   GPIO_Pin_4 // 直流电机引脚定义 GPIOA 4
#define PWM_MOTOR_MODULE_PIN2   GPIO_Pin_5 // 直流电机引脚定义 GPIOA 5

//  初始化模块
void Module_Init_Config(void); // 配置函数

#endif // _CONFIG_H_
