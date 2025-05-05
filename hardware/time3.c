#include "stm32f10x.h" // Device header
#include "timer3.h"
#include "Delay.h"

extern uint16_t Number_Timer3_Exti; // 计数器变量
void Timer3_Inter_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); // 使能TIM3时钟

    TIM_InternalClockConfig(TIM3); // 配置TIM3为内部时钟模式

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_ClockDivision     = TIM_CKD_DIV1;       // 设置时钟分频系数
    TIM_TimeBaseStructure.TIM_CounterMode       = TIM_CounterMode_Up; // 设置计数模式为向上计数模式
    TIM_TimeBaseStructure.TIM_Period            = 10000 - 1;          // 设置计数周期为1000
    TIM_TimeBaseStructure.TIM_Prescaler         = 7200 - 1;           // 设置预分频器为7200，计数频率为10KHz
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                  // 设置重复计数器为0
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);                   // 初始化TIM3

    TIM_ClearFlag(TIM3, TIM_FLAG_Update);      // 清除TIM3更新标志位,避免刚初始化完就终端
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); // 使能TIM3更新中断

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // Set NVIC priority group to 2
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel                   = TIM3_IRQn; // Select EXTI15_10_IRQn
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM3, ENABLE); // 使能TIM2
}
void Timer3_Out_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  // 使能TIM3时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 使能GPIOA时钟

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU; // 设置为上拉输入模式
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6;    // 设置PA6为TIM3_CH1输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure); // 初始化GPIOA

    TIM_ETRClockMode1Config(TIM3, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0X00);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_ClockDivision     = TIM_CKD_DIV1;       // 设置时钟分频系数
    TIM_TimeBaseStructure.TIM_CounterMode       = TIM_CounterMode_Up; // 设置计数模式为向上计数模式
    TIM_TimeBaseStructure.TIM_Period            = 10 - 1;             // 设置计数周期为10
    TIM_TimeBaseStructure.TIM_Prescaler         = 1 - 1;              // 设置预分频器为0，计数频率为10KHz
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                  // 设置重复计数器为0
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);                   // 初始化TIM3

    TIM_ClearFlag(TIM3, TIM_FLAG_Update);      // 清除TIM3更新标志位,避免刚初始化完就终端
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); // 使能TIM3更新中断

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // Set NVIC priority group to 2
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel                   = TIM3_IRQn; // Select EXTI15_10_IRQn
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM3, ENABLE); // 使能TIM2
}
uint16_t Get_Count_Timer3(void)
{
    return TIM_GetCounter(TIM3); // 返回当前计数器值
}
uint16_t Get_Number_Timer3_Exti(void)
{
    return Number_Timer3_Exti; // 返回当前计数器值
}
void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update); // 清除TIM3更新中断标志位
        Number_Timer3_Exti++;                       // 在这里添加定时器中断处理代码
    }
    // 例如：LED闪烁、数据采集等操作
}