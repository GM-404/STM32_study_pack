#include "config.h"

void Module_Init_Config(void) // 配置函数
{
    if (OLED_MODULE) { // OLED模块开关
        OLED_Init();   // OLED初始化
    }
    if (LED_MODULE) { // LED模块开关
        LED_Init(1);  // LED初始化 1为高电平，0为低电平
    }
    if (KEY_MODULE) { // 按键模块开关
        KEY_Init();   // 按键初始化
    }
    if (EXTI_15_10_MODULE) { // EXTI模块开关
        EXTI_15_10_Init();   // EXTI初始化
    }
    if (TIMER2_MODULE) {                // 定时器2模块开关
        if (TIMER2_INTER_MODULE) {      // 定时器2内部时钟模式开关
            Timer2_Inter_Init();        // 定时器2初始化
        } else if (TIMER2_EXT_MODULE) { // 定时器2外部时钟模式开关
            Timer2_Out_Init();          // 定时器2初始化
        }
    }
    if (TIMER3_MODULE) {                // 定时器3模块开关
        if (TIMER3_INTER_MODULE) {      // 定时器3内部时钟模式开关
            Timer3_Inter_Init();        // 定时器3初始化
        } else if (TIMER3_EXT_MODULE) { // 定时器3外部时钟模式开关
            Timer3_Out_Init();          // 定时器3初始化
        }
    }
    if (PWM_MODULE) { // PWM模块开关
        PWM_Init();   // PWM初始化
    }
    if (MOTOR_MODULE) { // 直流电机模块开关
        Motor_Init();   // 直流电机初始化
    }
}
