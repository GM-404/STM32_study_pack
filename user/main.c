#include "stm32f10x.h"
#include "config.h" // 配置头文件

uint16_t Number_Timer2_Exti; // 计数器变量
uint16_t Number_Timer3_Exti; // 计数器变量
uint16_t lighrt = 0;         // 灯光亮度变量
float angle     = 0;         // 舵机角度变量
int16_t speed   = -100;      // 直流电机速度变量
uint8_t Rx_data;             // 接收数据
int main(void)
{
    Module_Init_Config();              // 配置函数
    OLED_ShowString(1, 1, "Rx_Data:"); // OLED显示字符串函数
    Usart1_SendByte(0x11);
    while (1) {
        if (Usart1_GetRxFlag() == 1) {
            Rx_data = Usart1_GetRxFData();
            Usart1_SendByte(Rx_data); // 将接收到的数据发送回去
            OLED_ShowHexNum(1, 9, Rx_data, 2);
        }
    }
}
// OLED_ShowString(1, 1, "Light:"); // OLED显示字符串函数
// OLED_ShowString(2, 1, "angle:"); // OLED显示字符串函数
// OLED_ShowString(3, 1, "Speed:"); // 显示字符串Speed:
// OLED_ShowString(2, 1, "KEY MOUDLE:"); // OLED显示字符串函数
// OLED_ShowNum(1, 13, LED_MODULE, 1);   // OLED显示数字函数
// OLED_ShowNum(2, 13, KEY_MODULE, 1);   // OLED显示数字函数

// while (1) {
//     // OLED_ShowNum(1, 13, Get_EXTI_Count(), 3); // OLED不断刷新显示Get_EXTI_Count的返回值，可以替换成CountSensor_Get(1, 5); // OLED不断刷新显示CountSensor_Get的返回值
//     if (Get_key_value()) { // 按键扫描函数
//         // LED1_Turn();       // LED翻转函数
//         angle += 30;       // 舵机角度加10度
//         lighrt += 20;      // 灯光亮度加20
//         speed += 20;       // 直流电机速度加10
//         if (angle > 180) { // 舵机角度大于180度时，重新开始
//             angle = 0;
//         }
//         if (lighrt > 100) { // 灯光亮度大于1000时，重新开始
//             lighrt = 0;
//         }
//         if (speed > 100) { // 直流电机速度大于100时，重新开始
//             speed = -100;
//         }
//     }
// PWM_Breathe_SetCompare1(lighrt);    // 设置PWM1的占空比函数
// PWM_Enjine_SetCompare2(angle);      // 设置PWM1的占空比函数(舵机)
// Motor_SetSpeed(speed);              // 设置PWM1的占空比函数(直流电机)
// OLED_ShowNum(2, 7, angle, 3);       // OLED显示数字函数
// OLED_ShowNum(1, 7, lighrt, 3);      // OLED显示数字函数
// OLED_ShowSignedNum(3, 7, speed, 3); // OLED显示数字函数
// OLED_ShowNum(3, 1, Get_Count_Timer2(), 5);       // 显示计数器变化量
// OLED_ShowNum(4, 1, Get_Number_Timer2_Exti(), 5); // 显示计数器变化量
// OLED_ShowNum(3, 7, Get_Count_Timer3(), 5);       // 显示计数器变化量
// OLED_ShowNum(4, 7, Get_Number_Timer3_Exti(), 5); // 显示计数器变化量

// Usart1_SendByte(0x41);
// uint8_t Array[] = {0x42, 0x43, 0x44};
// Usart1_SendArray(Array, 3);
// Usart1_SendString("hello,world\r\n");

// Usart1_SendNumber(12345, 5);
// Usart1_SendString("\r\n");
// printf("Number = %d\r\n", 666);
// Usart1_Printf("Number = %d\r\n", 686);
// Usart1_Printf("你好，加以测试\r\n");