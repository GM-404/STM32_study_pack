#include "config.h"
#include "OLED.h"             // OLED头文件
void Module_Init_Config(void) // 配置函数
{
    if (LED_MODULE) { // LED模块开关
        LED_Init(1);  // LED初始化 1为高电平，0为低电平
    }
    if (KEY_MODULE) { // 按键模块开关
        KEY_Init();   // 按键初始化
    }
    if (OLED_MODULE) { // OLED模块开关
        OLED_Init();   // OLED初始化
    }
    if (EXTI_15_10_MODULE) { // EXTI模块开关
        EXTI_15_10_Init();   // EXTI初始化
    }
    OLED_ShowString(1, 1, "LED MOUDLE:"); // OLED显示字符串函数
    OLED_ShowString(2, 1, "KEY MOUDLE:"); // OLED显示字符串函数
    OLED_ShowNum(1, 13, LED_MODULE, 1);   // OLED显示数字函数
    OLED_ShowNum(2, 13, KEY_MODULE, 1);   // OLED显示数字函数
}
