
#include "usart.h"
// 变量
uint8_t Usart1_Rx_Data;                                      // 串口1接收数据缓存
uint8_t Usart1_Rx_Flag;                                      // 串口1接受标志位
uint8_t Usart1_Tx_Data_Packet[Usart1_Tx_Data_Packet_Length]; // 串口1发送数据包
uint8_t Usart1_Rx_Data_Packet[Usart1_Rx_Data_Packet_Length]; // 串口1接收数据包
uint8_t Usart1_Rx_Data_Packet_Flag;                          // 串口1接收数据包标志位
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
/**
 * 函    数：次方函数（内部使用）
 * 返 回 值：返回值scale 的 index次方
 */
uint32_t Usart1_pow(uint32_t scale, uint8_t index) // 返回scale 的 index次方
{
    uint32_t Result = 1;
    while (index--) {
        Result *= scale;
    }
    return Result;
}
/**
 * 函    数：串口发送数字
 * 参    数：Number 要发送的数字，范围：0~4294967295
 * 参    数：Length 要发送数字的长度，范围：0~10
 * 返 回 值：无
 */
void Usart1_SendNumber(uint32_t Number, uint8_t Length)
{
    uint8_t i;
    for (i = 0; i < Length; i++) {
        Usart1_SendByte(Number / Usart1_pow(10, Length - i - 1) % 10 + '0'); // 加0是偏移量
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
    static uint8_t Usart1_Rx_Packet_static     = 0; // 定义接收状态机标志位
    static uint8_t Usart1_Rx_Data_Packet_Index = 0; // 定义接收数据包数据接收到第几个了
    if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
        Usart1_Rx_Data = USART_ReceiveData(USART1);
        Usart1_Rx_Flag = 1; // 表示接收到数据
        if (Usart1_Rx_Packet_static == 0) {
            if (Usart1_Rx_Data == 0xFF) { // 接收状态机状态0，判断接收到的数据是否为帧头
                Usart1_Rx_Packet_static     = 1;
                Usart1_Rx_Data_Packet_Index = 0; // 重置接收数据包数据接收到第几个了,也即是为接收数据做准备
            }
        } else if (Usart1_Rx_Packet_static == 1) {
            Usart1_Rx_Data_Packet[Usart1_Rx_Data_Packet_Index] = Usart1_Rx_Data;
            Usart1_Rx_Data_Packet_Index++;
            if (Usart1_Rx_Data_Packet_Index == Usart1_Rx_Data_Packet_Length) { // 判断接收到的数据是否够了，够了就进入状态2等待判断帧尾
                Usart1_Rx_Packet_static = 2;
            }
        } else if (Usart1_Rx_Packet_static == 2) { // 接收状态机状态2，判断接收到的数据是否为帧尾
            if (Usart1_Rx_Data == 0xFE) {
                Usart1_Rx_Packet_static    = 0; // 回到等待帧头的位置
                Usart1_Rx_Data_Packet_Flag = 1; // 表示接收到数据包
            }
        }
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

// 使用前请按照如下格式声明如下
//  Usart1_Tx_Data_Packet[0] = 0x01;
//          Usart1_Tx_Data_Packet[1] = 0x02;
//          Usart1_Tx_Data_Packet[2] = 0x03;
//          Usart1_Tx_Data_Packet[3] = 0x04;
//          Usart1_SendPacket();
void Usart1_SendPacket(void)
{
    Usart1_SendByte(0xFF); // 帧头
    Usart1_SendArray(Usart1_Tx_Data_Packet, Usart1_Tx_Data_Packet_Length);
    Usart1_SendByte(0xFE); // 帧尾
}
