#include "stm32f10x.h" // Device header
#include "timer2.h"
#include "Delay.h"

extern uint16_t Number_Timer2_Exti; // 计数器变量
void Timer2_Inter_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // 使能TIM2时钟

    TIM_InternalClockConfig(TIM2); // 配置TIM2为内部时钟模式

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_ClockDivision     = TIM_CKD_DIV1;       // 设置时钟分频系数
    TIM_TimeBaseStructure.TIM_CounterMode       = TIM_CounterMode_Up; // 设置计数模式为向上计数模式
    TIM_TimeBaseStructure.TIM_Period            = 10000 - 1;          // 设置计数周期为1000
    TIM_TimeBaseStructure.TIM_Prescaler         = 7200 - 1;           // 设置预分频器为7200，计数频率为10KHz
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                  // 设置重复计数器为0
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);                   // 初始化TIM2

    TIM_ClearFlag(TIM2, TIM_FLAG_Update);      // 清除TIM2更新标志位,避免刚初始化完就终端
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // 使能TIM2更新中断

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // Set NVIC priority group to 2
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel                   = TIM2_IRQn; // Select EXTI15_10_IRQn
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM2, ENABLE); // 使能TIM2
}
void Timer2_Out_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  // 使能TIM2时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 使能GPIOA时钟

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU; // 设置为上拉输入模式
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;    // 设置PA0为TIM2_CH1输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure); // 初始化GPIOA

    TIM_ETRClockMode1Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0X00);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_ClockDivision     = TIM_CKD_DIV1;       // 设置时钟分频系数
    TIM_TimeBaseStructure.TIM_CounterMode       = TIM_CounterMode_Up; // 设置计数模式为向上计数模式
    TIM_TimeBaseStructure.TIM_Period            = 10 - 1;             // 设置计数周期为10
    TIM_TimeBaseStructure.TIM_Prescaler         = 1 - 1;              // 设置预分频器为0，计数频率为10KHz
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                  // 设置重复计数器为0
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);                   // 初始化TIM2

    TIM_ClearFlag(TIM2, TIM_FLAG_Update);      // 清除TIM2更新标志位,避免刚初始化完就终端
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // 使能TIM2更新中断

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // Set NVIC priority group to 2
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel                   = TIM2_IRQn; // Select EXTI15_10_IRQn
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM2, ENABLE); // 使能TIM2
}
uint16_t Get_Count_Timer2(void)
{
    return TIM_GetCounter(TIM2); // 返回当前计数器值
}
uint16_t Get_Number_Timer2_Exti(void)
{
    return Number_Timer2_Exti; // 返回当前计数器值
}
void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // 清除TIM2更新中断标志位
        Number_Timer2_Exti++;                       // 在这里添加定时器中断处理代码
    }
    // 例如：LED闪烁、数据采集等操作
}