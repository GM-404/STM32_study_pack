#include "usart.h"
// 变量
uint8_t Usart1_Rx_Data;                                          // 串口1接收数据缓存
uint8_t Usart1_Rx_Flag;                                          // 串口1接受标志位
uint8_t Usart1_Tx_Data_Packet[Usart1_Tx_Data_Packet_Length];     // 串口1发送数据包
uint8_t Usart1_Rx_Data_Packet[Usart1_Rx_Data_Packet_Length];     // 串口1接收数据包
uint8_t Usart1_Rx_Data_Packet_Flag;                              // 串口1接收数据包标志位
uint8_t Usart1_Rx_Data_Packet_String_Flag;                       // 串口1接收文本包标志位
char Usart1_Tx_Data_Packet_String[Usart1_Tx_Char_Packet_Length]; // 串口1发送文本格式包
char Usart1_Rx_Data_Packet_String[Usart1_Rx_Char_Packet_Length]; // 串口1接收文本格式包
uint8_t year_temp  = 0;                                          // 年份
uint8_t month_temp = 0;                                          // 月份
uint8_t day_temp   = 0;                                          // 天数
uint8_t hour_temp  = 0;                                          // 小时
uint8_t min_temp   = 0;                                          // 分钟
uint8_t car_id[5];
uint8_t car_type[5];
uint8_t locate;
uint32_t CarStopTime;
uint32_t Money;
extern uint8_t IDLE_Number; // 空闲车位
extern uint8_t CNBR_Number; // CNBR类车数量
extern uint8_t VNBR_Number; // VNBR类车数量
typedef struct
{
    uint8_t cartype[5]; // 车辆类型
    uint8_t carid[5];   // 车俩编号
    uint8_t yearin;
    uint8_t monthin;
    uint8_t dayin;
    uint8_t hourin;
    uint8_t minin;
    uint8_t secin;
    uint8_t state;
} StorageSystem; // 信息储存系统
StorageSystem car[8] = {0};

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
    USART_InitStructure.USART_BaudRate            = Usart1_BaudRate;                // 波特率
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
// 中断函数数据包格式
#if (!Usart1_MDOE)
void USART1_IRQHandler(void)
{
    static uint8_t Usart1_Rx_Packet_static     = 0; // 定义接收状态机标志位
    static uint8_t Usart1_Rx_Data_Packet_Index = 0; // 定义接收数据包数据接收到第几个了
    if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
        Usart1_Rx_Data = USART_ReceiveData(USART1);
        if (Usart1_Rx_Packet_static == 0 && Usart1_Rx_Data_Packet_Flag == 0) {
            if (Usart1_Rx_Data == 0xFF) { // 接收状态机状态0，判断接收到的数据是否为帧头
                Usart1_Rx_Packet_static     = 1;
                Usart1_Rx_Data_Packet_Index = 0; // 重置接收数据包数据接收到第几个了,也即是为接收数据做准备
            }
        } else if (Usart1_Rx_Packet_static == 1 && Usart1_Rx_Data_Packet_Flag == 0) {
            Usart1_Rx_Data_Packet[Usart1_Rx_Data_Packet_Index] = Usart1_Rx_Data;
            Usart1_Rx_Data_Packet_Index++;
            if (Usart1_Rx_Data_Packet_Index == Usart1_Rx_Data_Packet_Length) { // 判断接收到的数据是否够了，够了就进入状态2等待判断帧尾
                Usart1_Rx_Packet_static = 2;
            }
        } else if (Usart1_Rx_Packet_static == 2 && Usart1_Rx_Data_Packet_Flag == 0) { // 接收状态机状态2，判断接收到的数据是否为帧尾
            if (Usart1_Rx_Data == 0xFE) {
                Usart1_Rx_Packet_static    = 0; // 回到等待帧头的位置
                Usart1_Rx_Data_Packet_Flag = 1; // 表示接收到数据包
            }
        }
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}
#endif
#if (Usart1_MDOE)
// 目前无帧头，帧尾用空格替代
void USART1_IRQHandler(void)
{
    static uint8_t Usart1_Rx_Data_Packet_String_Index = 0; // 定义接收数据包数据接收到第几个了
    if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
        Usart1_Rx_Data                                                   = USART_ReceiveData(USART1);
        Usart1_Rx_Data_Packet_String[Usart1_Rx_Data_Packet_String_Index] = Usart1_Rx_Data;
        Usart1_Rx_Data_Packet_String_Index++;
    }
    if (Usart1_Rx_Data == ' ') {
        Usart1_Rx_Data_Packet_String[Usart1_Rx_Data_Packet_String_Index] = '\0'; // 表示字符串接收结束,给该字符串添加结束符
        Usart1_Rx_Data_Packet_String_Flag                                = 1;    // 表示接收到文本包
        Usart1_Rx_Data_Packet_String_Index                               = 0;    // 重置接收数据包
    }
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}
#endif

uint8_t Usart1_Get_Rx_Flag(void) // 返回接收一个字符标志位
{
    if (Usart1_Rx_Flag == 1) {
        // 一些操作放这里面，可以有效避免覆盖问题，或者后面手动将标志位清零
        Usart1_Rx_Flag = 0;
        return 1;
    }
    return 0;
}
uint8_t Usart1_Get_Rx_Data_Packet_Flag(void) // 返回接收到数据包标志位
{
    if (Usart1_Rx_Data_Packet_Flag == 1) {
        // 一些操作放这里面，可以有效避免覆盖问题，或者后面手动将标志位清零
        Usart1_Rx_Data_Packet_Flag = 0;
        return 1;
    }
    return 0;
}
uint8_t Usart1_Get_Rx_String_Packet_Flag(void) // 返回接收文本包标志位
{
    if (Usart1_Rx_Data_Packet_String_Flag == 1) {
        // 一些操作放这里面，可以有效避免覆盖问题，或者后面手动将标志位清零
        Usart1_Rx_Data_Packet_String_Flag = 0;
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
uint8_t StringCheck(void)
{
    uint8_t i = 0;
    if ((Usart1_Rx_Data_Packet_String[0] == 'C' || Usart1_Rx_Data_Packet_String[0] == 'V') && Usart1_Rx_Data_Packet_String[1] == 'N' && Usart1_Rx_Data_Packet_String[2] == 'B' && Usart1_Rx_Data_Packet_String[3] == 'R') {
        for (i = 10; i < 22; i++) { // 检测字符串是否合法
            if (Usart1_Rx_Data_Packet_String[i] > '9' || Usart1_Rx_Data_Packet_String[i] < '0') {
                printf("Error\r\n");
            }
        }
        year_temp  = (Usart1_Rx_Data_Packet_String[12] - '0') * 10 + (Usart1_Rx_Data_Packet_String[13] - '0');
        month_temp = (Usart1_Rx_Data_Packet_String[14] - '0') * 10 + (Usart1_Rx_Data_Packet_String[15] - '0');
        day_temp   = (Usart1_Rx_Data_Packet_String[16] - '0') * 10 + (Usart1_Rx_Data_Packet_String[17] - '0');
        hour_temp  = (Usart1_Rx_Data_Packet_String[18] - '0') * 10 + (Usart1_Rx_Data_Packet_String[19] - '0');
        min_temp   = (Usart1_Rx_Data_Packet_String[20] - '0') * 10 + (Usart1_Rx_Data_Packet_String[21] - '0');

        printf("Year:%u\r\n", year_temp);
        printf("Month:%d\r\n", month_temp);
        printf("Day:%d\r\n", day_temp);
        printf("Hour:%d\r\n", hour_temp);
        printf("Min:%d\r\n", min_temp);
        return 1;
    }

    return 0;
}
/*判断车辆是入库还是出库，入库返回0，出库返回1，其他返回2
先看入库
判断一辆车入库还是出库，得看现存的车牌号有没有这个车，同时还有一种情况是，
没有车位了，所以先判断一下有没有车位*/
uint8_t JudgeTheCar_In_or_Out(void)
{
    substr(car_id, Usart1_Rx_Data_Packet_String, 5, 4);   // 将车辆的编号信息提取到car_id
    substr(car_type, Usart1_Rx_Data_Packet_String, 0, 4); // 将车辆的类型信息提取到car_type}
    locate = isExist(car_id);                             // 查询这辆车是否在车库从存在,返回车库位置，不然返回0xFF
    if (locate != 0xFF)                                   // 这辆车在车库中存在
    {
        if (strcmp((const char *)car_type, (const char *)car[locate].cartype)) // 如果车辆的id和车辆的类型不同，则表示信息错误
        {
            printf("车辆id和车辆类型不匹配\r\n");
            return 2; // 报错
        } else {
            printf("查询成功，可以出库\r\n");
            return 1; // 出库
        }
    } else {                    // 这辆车在车库中不存在
        if (IDLE_Number == 0) { // 看有没有车位，没有就返回2
            printf("车库已满,无法入库\r\n");
            return 2;
        } else {
            printf("查询成功，可以入库\r\n");
            return 0;
        } // 入库
    }
}

// 提取车辆信息
void substr(uint8_t *d_str, uint8_t *s_str, uint8_t locate, uint8_t length)
{
    uint8_t i = 0;
    for (i = 0; i < length; i++) {
        d_str[i] = s_str[locate + i];
    }
    d_str[length] = '\0';
}
// 检测车辆是否已经存在
uint8_t isExist(uint8_t *str)
{
    uint8_t i = 0;
    for (i = 0; i < 8; i++) {
        if (strcmp((const char *)str, (const char *)car[i].carid) == 0) {
            return i;
        }
    }
    return 0xFF;
}
// 入库函数
void InCar(void)
{
    uint8_t i = 0;
    printf("即将入库的车辆car_id:%s\r\n", car_id);
    for (i = 0; i < 8; i++) {
        if (car[i].state == 0) {      // 找到第i个空闲车位
            if (car_type[0] == 'C') { // 如果是C类型
                CNBR_Number++;        // CNBR类车数量加1
                printf("C类型车入库%d车位成功\r\n", i + 1);
            } else if (car_type[0] == 'V') { // 如果是M类型
                VNBR_Number++;               // VNBR类车数量加1
                printf("V类型车入库%d车位成功\r\n", i + 1);
            }
            memcpy(car[i].carid, car_id, 5);
            memcpy(car[i].cartype, car_type, 5);
            car[i].yearin  = year_temp;
            car[i].monthin = month_temp;
            car[i].dayin   = day_temp;
            car[i].hourin  = hour_temp;
            car[i].minin   = min_temp;
            car[i].state   = 1;
            IDLE_Number--; // 车位减1
            break;
        }
    }
}
void OutStorage(void)
{
    printf("即将出库的车辆car_id:%s\r\n", car_id);
    uint8_t i = 0;
    for (i = 0; i < 8; i++) {
        if (strcmp((const char *)car[i].carid, (const char *)car_id) == 0) {
            if (car[i].state == 1) {
                if (car[i].cartype[0] == 'C') {
                    CNBR_Number--; // CNBR类车数量减1
                    printf("C类型车出库%d车位成功\r\n", i + 1);
                } else if (car[i].cartype[0] == 'V') {
                    VNBR_Number--; // VNBR类车数量减1
                    printf("V类型车出库%d车位成功\r\n", i + 1);
                }
                car[i].state      = 0;
                car[i].carid[0]   = 0;
                car[i].cartype[0] = 0;
                car[i].yearin     = 0;
                car[i].monthin    = 0;
                car[i].dayin      = 0;
                car[i].hourin     = 0;
                car[i].minin      = 0;
                IDLE_Number++; // 车位加1
            }
        }
    }
}
// 计算车费函数
void CalculateFee(void)
{
    // 待添加
}