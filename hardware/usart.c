
#include "usart.h"
// 变量
uint8_t Usart1_Rx_Data; // 串口1接收数据缓存
uint8_t Usart1_Rx_Flag; // 串口1接受标志位
void Usart1_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    /*GPIO初始化*/
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin   = Usart1_Tx;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure); // 将TX初始化为复用推挽输出

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin   = Usart1_Rx;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure); // 将引脚初始化为复用推挽输出

    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate            = 115200;                         // 波特率
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 无硬件流控
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;            // 8位数据长度
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;               // 1个停止位
    USART_InitStructure.USART_Parity              = USART_Parity_No;                // 无奇偶校验
    USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;  // 使能发送和接收
    USART_Init(USART1, &USART_InitStructure);
    // 使用中断的方式接收
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel                   = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART1, ENABLE);
}
void Usart1_SendByte(uint8_t data)
{
    USART_SendData(USART1, data);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}
void Usart1_SendArray(uint8_t *Array, uint16_t Length)
{
    uint16_t i;
    for (i = 0; i < Length; i++) {
        Usart1_SendByte(Array[i]);
    }
}
void Usart1_SendString(char *String)
{
    uint8_t i;
    for (i = 0; String[i] != '\0'; i++) {
        Usart1_SendByte(String[i]);
    }
}
uint32_t Usart1_pow(uint32_t scale, uint8_t index) // 返回scale 的 index次方
{
    uint32_t Result = 1;
    while (index--) {
        Result *= scale;
    }
    return Result;
}
void Usart1_SendNumber(uint32_t Number, uint8_t Length)
{
    uint8_t i;
    for (i = 0; i < Length; i++) {
        Usart1_SendByte(Number / Usart1_pow(10, Length - i - 1) % 10 + '0'); // 加0是偏移量
    }
}
// 重定向fputc,也就是在串口中使用printf
int fputc(int ch, FILE *f)
{
    (void)f; // 告诉编译器 f 参数有意不使用
    Usart1_SendByte(ch);
    return ch;
}
void Usart1_Printf(char *format, ...)
{
    char String[100];
    va_list arg;
    va_start(arg, format);
    vsprintf(String, format, arg);
    va_end(arg);
    Usart1_SendString(String);
}
// USART1中断
void USART1_IRQHandler(void)
{
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
        Usart1_Rx_Data = USART_ReceiveData(USART1);
        Usart1_Rx_Flag = 1;
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}
uint8_t Usart1_GetRxFData(void)
{
    return Usart1_Rx_Data;
}
uint8_t Usart1_GetRxFlag(void)
{
    if (Usart1_Rx_Flag == 1) {
        Usart1_Rx_Flag = 0;
        return 1;
    }
    return 0;
}
