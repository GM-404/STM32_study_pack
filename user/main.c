#include "stm32f10x.h"
#include "config.h" // 配置头文件

int main(void)
{
    Module_Init_Config(); // 配置函数
    while (1) {

        if (Get_key_value()) { // 按键扫描函数
            LED1_Turn();       // LED翻转函数
        }
    }
}
