#include "usart.h"

uint8_t RxCounter;      // 串口1接收数据计数
uint8_t RxBuffer[25];   // 串口1接收数据缓存
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
/**
 * 函    数：串口发送一个字节
 * 参    数：Byte 要发送的一个字节
 * 返 回 值：无
 */
void Usart1_SendByte(uint8_t data)
{
    USART_SendData(USART1, data);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}
/**
 * 函    数：串口发送一个数组
 * 参    数：Array 要发送数组的首地址
 * 参    数：Length 要发送数组的长度
 * 返 回 值：无
 */
void Usart1_SendArray(uint8_t *Array, uint16_t Length)
{
    uint16_t i;
    for (i = 0; i < Length; i++) {
        Usart1_SendByte(Array[i]);
    }
}
/**
 * 函    数：串口发送一个字符串
 * 参    数：String 要发送字符串的首地址
 * 返 回 值：无
 */
void Usart1_SendString(char *String)
{
    uint8_t i;
    for (i = 0; String[i] != '\0'; i++) {
        Usart1_SendByte(String[i]);
    }
}

// 重定向fputc,也就是在串口中使用printf
/**
 * 函    数：使用printf需要重定向的底层函数
 * 参    数：保持原始格式即可，无需变动
 * 返 回 值：保持原始格式即可，无需变动
 */
int fputc(int ch, FILE *f)
{
    (void)f; // 告诉编译器 f 参数有意不使用
    Usart1_SendByte(ch);
    return ch;
}
/**
 * 函    数：自己封装的prinf函数
 * 参    数：format 格式化字符串
 * 参    数：... 可变的参数列表
 * 返 回 值：无
 */
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
/**
 * 函    数：USART1中断函数
 * 参    数：无
 * 返 回 值：无
 * 注意事项：此函数为中断函数，无需调用，中断触发后自动执行
 *           函数名为预留的指定名称，可以从启动文件复制
 *           请确保函数名正确，不能有任何差异，否则中断函数将不能进入
 */
void USART1_IRQHandler(void)
{
    if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
        RxBuffer[RxCounter++] = USART_ReceiveData(USART1);
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
    if (USART_GetITStatus(USART1, USART_IT_IDLE) != RESET) {
        USART1->SR;
        USART1->DR;
        Usart1_Rx_Flag = 1; // 表示接收到数据
    }
}

// 以下仅为本分支所需函数
void Usart2_Proc(void)
{
    if (Usart1_Rx_Flag == 1) { // 如果接收到了数据
        Usart1_Rx_Flag = 0;    // 先置零再说

        Usart1_SendByte(RxBuffer[0]); // 成功接收
        Usart1_SendByte(0XFF);        // 成功接收
        RxCounter = 0;
    }
}
