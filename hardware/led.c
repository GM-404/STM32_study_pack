#include "stm32f10x.h" // Device header
#include "led.h"       // LED头文件
/**
 * 函    数：LED初始化,自定义引脚，状态
 * 参    数：status: LED状态 1为高电平，0为低电平
 * 返 回 值：无
 */
void LED_Init(uint16_t status)
{
    /*开启时钟*/
    if (ENABLE_LED_GPIOA_CLOCK) // 如果需要开启GPIOA的时钟
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 开启GPIOA的时钟
    }
    /*GPIO初始化*/
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin   = LED_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure); // 将引脚初始化为推挽输出

    /*设置GPIO初始化后的默认电平*/
    if (status == 1) {
        GPIO_SetBits(GPIOA, LED_PIN); // 设置引脚为高电平
    } else {
        GPIO_ResetBits(GPIOA, LED_PIN); // 设置引脚为低电平
    }
}

void LED1_Turn(void)
{
    if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) == 0) // 获取输出寄存器的状态，如果当前引脚输出低电平
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_1); // 则设置PA1引脚为高电平
    } else                               // 否则，即当前引脚输出高电平
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_1); // 则设置PA1引脚为低电平
    }
}
