#include "stm32f10x.h"
#include "config.h" // 配置头文件

int main(void)
{
    Module_Init_Config(); // 配置函数
    while (1) {
        OLED_ShowNum(3, 7, Get_EXTI_Count(), 5); // OLED不断刷新显示Get_EXTI_Count的返回值，可以替换成CountSensor_Get(1, 5); // OLED不断刷新显示CountSensor_Get的返回值
        if (Get_key_value()) {                   // 按键扫描函数
            LED1_Turn();                         // LED翻转函数
        }
    }
}
