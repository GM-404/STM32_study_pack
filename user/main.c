#include "stm32f10x.h"
#include "config.h" // 配置头文件

uint16_t Number_Timer2_Exti; // 计数器变量
uint16_t Number_Timer3_Exti; // 计数器变量
int main(void)
{
    Module_Init_Config();                 // 配置函数
    OLED_ShowString(1, 1, "EXTI COUNT:"); // OLED显示字符串函数
    // OLED_ShowString(2, 1, "KEY MOUDLE:"); // OLED显示字符串函数
    // OLED_ShowNum(1, 13, LED_MODULE, 1);   // OLED显示数字函数
    // OLED_ShowNum(2, 13, KEY_MODULE, 1);   // OLED显示数字函数

    while (1) {
        OLED_ShowNum(1, 13, Get_EXTI_Count(), 3); // OLED不断刷新显示Get_EXTI_Count的返回值，可以替换成CountSensor_Get(1, 5); // OLED不断刷新显示CountSensor_Get的返回值
        if (Get_key_value()) {                    // 按键扫描函数
            LED1_Turn();                          // LED翻转函数
        }
        OLED_ShowNum(3, 1, Get_Count_Timer2(), 5);       // 显示计数器变化量
        OLED_ShowNum(4, 1, Get_Number_Timer2_Exti(), 5); // 显示计数器变化量
        OLED_ShowNum(3, 7, Get_Count_Timer3(), 5);       // 显示计数器变化量
        OLED_ShowNum(4, 7, Get_Number_Timer3_Exti(), 5); // 显示计数器变化量
        PWM_Breathe_SetCompare1();
    }
}
