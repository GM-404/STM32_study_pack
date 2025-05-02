#include "stm32f10x.h " // STM32F10x头文件

#include "key.h" // 按键头文件
#include "Delay.h"

void KEY_Init(void) // 按键初始化
{

    if (ENABLE_KEY_GPIOB_CLOCK) {                             // 如果需要开启GPIOB的时钟
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // 使能GPIOB时钟
    }
    GPIO_InitTypeDef GPIO_InitStructure;              // GPIO初始化结构体
    GPIO_InitStructure.GPIO_Pin   = KEY_PIN;          // PA0引脚
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;    // 上拉输入模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 50MHz速度
    GPIO_Init(GPIOB, &GPIO_InitStructure);            // 初始化GPIOA
}
/*
 *@brief 按键扫描函数
 *@ return 1 : 按键按下 1 : 按键未按下 0
 */
uint8_t Get_key_value(void) // 按键扫描函数
{
    uint8_t key_value = 0;                            // 按键值
    if (GPIO_ReadInputDataBit(GPIOB, KEY_PIN) == 0) { // 如果按键按下
        // Delay_ms(10);                                           // 延时10ms去抖动
        if (GPIO_ReadInputDataBit(GPIOB, KEY_PIN) == 0) {       // 如果按键仍然按下
            while (GPIO_ReadInputDataBit(GPIOB, KEY_PIN) == 0); // 等待按键释放
            key_value = 1;                                      // 返回
        } else {
            key_value = 0;
        }
    }
    return key_value; // 返回按键值
}