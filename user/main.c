#include "stm32f10x.h"
#include "config.h" // 配置头文件

uint16_t Number_Timer2_Exti; // 计数器变量
uint16_t Number_Timer3_Exti; // 计数器变量
// uint16_t lighrt = 0;         // 灯光亮度变量
// float angle     = 0;         // 舵机角度变量
// int16_t speed   = -100;      // 直流电机速度变量
// uint32_t Rx_data; // 接收数据
// uint16_t AD1_Value = 0;      // AD值
int main(void)
{
    Module_Init_Config(); // 配置函数
    while (1) {
        if (Usart1_Get_Rx_String_Packet_Flag()) // 如果接收到文本包
        {
            OLED_ShowString(4, 1, Usart1_Rx_Data_Packet_String); // 显示接收的数据包
            if (strcmp(Usart1_Rx_Data_Packet_String, "GM") == 0) {
                printf("OK\r\n");
                Usart1_SendByte(Usart1_Rx_Data_Packet_String[1]); // 发送字符
                Usart1_SendString(Usart1_Rx_Data_Packet_String);  // 发送字符串
            } else {
            }
        }
        if (Usart1_Get_Rx_Data_Packet_Flag()) {
            OLED_ShowHexNum(1, 1, Usart1_Rx_Data_Packet[0], 4);
        }
    }
}

// uint8_t Array[] = {20, 01, 05, 03, 00};
// // Usart1_SendByte(0x01);
// // Usart1_SendArray(Array, 5);
// // Usart1_SendString("hello world \r\n"); // 发送字符串
// // Usart1_SendNumber(100, 3);             // 发送数字
// printf("高明 \r\n");
// printf("Num = %d \r\n", 100);
// char String[100];
// sprintf(String, "Num = %d \r\n", 666);
// Usart1_SendString(String);

// Module_Init_Config();                // 配置函数
// OLED_ShowString(1, 1, "PWM1_Duty:"); // OLED显示字符串函数
// OLED_ShowString(2, 1, "PWM2_Duty:"); // OLED显示字符串函数
// OLED_ShowString(3, 1, "AD1_Value:"); // OLED显示字符串函数
// while (1) {
//     if (Get_key_value()) // 按键扫描函数
//     {
//         lighrt += 20; // 灯光亮度加20
//         if (lighrt > 100) { lighrt = 0; }
//         PWM_Breathe_SetCompare1(lighrt);      // 设置通道1
//         PWM_Enjine_SetCompare2(100 - lighrt); // 设置通道2
//         OLED_ShowNum(1, 11, lighrt, 3);
//         OLED_ShowNum(2, 11, 100 - lighrt, 3);
//     }
//     AD1_Value = Get_Adc_Value(ADC_Channel_3); // 获取AD值
//     OLED_ShowNum(3, 11, AD1_Value, 4);
// }
