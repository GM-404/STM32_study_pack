#ifndef __LED_H__
#define __LED_H__
// #include "study_config.h"  //总开关文件，待添加
#include "stm32f10x.h"                    // Device header
#define ENABLE_LED_GPIOA_CLOCK (1)        // 使能LED模块GPIOA时钟,如果需要开启GPIOA的时钟置1
#define LED_PIN                GPIO_Pin_1 // 在这里定义LED的引脚
/**
 * 函    数：LED初始化,自定义引脚，状态
 * 参    数：LED_PIN: LED引脚，见上文
 *       status: LED状态 1为高电平，0为低电平
 * 返 回 值：无
 */
void LED_Init(uint16_t status); // GPIO初始化

/**
 * 函    数：LED翻转
 * 参    数：无
 * 返 回 值：无
 */
void LED1_Turn(void); // LED1翻转
#endif                /* __LED_H__ */
