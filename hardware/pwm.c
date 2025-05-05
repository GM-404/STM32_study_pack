#include "stm32f10x.h" // STM32F10x标准外设库头文件
#include "pwm.h"       // PWM头文件

void PWM_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  // 使能TIM2时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 使能GPIOA时钟

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP; // 设置为复用推挽输出模式
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;      // 设置PA0为TIM2_CH1输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure); // 初始化GPIOA

    TIM_InternalClockConfig(TIM2); // 配置TIM2为内部时钟模式

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_ClockDivision     = TIM_CKD_DIV1;       // 设置时钟分频系数
    TIM_TimeBaseStructure.TIM_CounterMode       = TIM_CounterMode_Up; // 设置计数模式为向上计数模式
    TIM_TimeBaseStructure.TIM_Period            = 100 - 1;            // 设置计数周期为100  ARR   分辨率为1%
    TIM_TimeBaseStructure.TIM_Prescaler         = 720 - 1;            // 设置预分频器为7200，计数频率为10KHz PSC
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                  // 设置重复计数器为0
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);                   // 初始化TIM2

    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure);                       // 初始化TIM2通道1的输出比较结构体
    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;        // 设置PWM模式1
    TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High;    // 设置输出极性为高电平有效
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // 使能输出
    TIM_OCInitStructure.TIM_Pulse       = 0;                      // 设置初始占空比为can be a number between 0x0000 and 0xFFFF
    // 以下为高级定时器的配置，TIM3不支持，但保留以备将来使用，
    //  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable; // 禁用输出N状态
    //  TIM_OCInitStructure.TIM_OCIdleState  = TIM_OCIdleState_Reset;  // 设置空闲状态为复位
    //  TIM_OCInitStructure.TIM_OCNPolarity  = TIM_OCNPolarity_High;   // 设置输出N极性为高电平有效
    //  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset; // 设置输出N空闲状态为复位
    TIM_OC1Init(TIM2, &TIM_OCInitStructure); // 初始化TIM2通道1

    TIM_Cmd(TIM2, ENABLE); // 使能TIM3
}

void PWM_Breathe_SetCompare1() // 如果全打开会超时影响定时器效果
{
    // uint16_t i = 0; // 定义变量i
    // for (i = 0; i <= 100; i++) {
    TIM_SetCompare1(TIM2, 50); // 设置占空比 // 依次将定时器的CCR寄存器设置为0~100，PWM占空比逐渐增大，LED逐渐变亮
    //     Delay_ms(10);             // 延时10ms
    // }
    // for (i = 0; i <= 100; i++) {
    //     TIM_SetCompare1(TIM2, 100 - i); // 设置占空比 // 依次将定时器的CCR寄存器设置为100~0，PWM占空比逐渐减小，LED逐渐变暗
    //     Delay_ms(10);                   // 延时10ms
    // }
}