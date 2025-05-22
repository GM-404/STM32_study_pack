#include "stm32f10x.h"
#include "config.h" // 配置头文件

uint16_t Number_Timer2_Exti; // 计数器变量
uint16_t Number_Timer3_Exti; // 计数器变量

uint16_t lighrt          = 0; // 灯光亮度变量
uint8_t Key4_Value       = 0; // 判断按键值按下了几次
uint8_t all_number       = 8; // 总车位
uint8_t CNBR_Number      = 0; // CNBR类车数量
uint8_t VNBR_Number      = 0; // VNBR类车数量
uint8_t IDLE_Number      = 0; // 空闲车位
static int32_t CNBR_Rate = 3; // CNBR类车费率
static int32_t VNBR_Rate = 2; // VNBR类车费率

int main(void)
{
    uint8_t LCD_Mode = 0;           // 默认显示车位显示页面，0为费率设置页面
    Module_Init_Config();           // 配置函数
    OLED_ShowString(1, 7, "Data");  // OLED显示字符串函数
    OLED_ShowString(2, 1, "CNBR:"); // CNBR类车数量
    OLED_ShowString(3, 1, "VNBR:"); // VNBR类车数量
    OLED_ShowString(4, 1, "IDLE:"); // 空闲车位
    OLED_ShowNum(2, 11, (uint32_t)CNBR_Number, 1);
    OLED_ShowNum(3, 11, (uint32_t)VNBR_Number, 1);
    OLED_ShowNum(4, 11, (uint32_t)IDLE_Number, 1);
    while (1) {
        IDLE_Number = all_number - CNBR_Number - VNBR_Number; // 空闲车位
        // 通信功能
        Usart2_Proc();

        if (Get_key0_value()) // 界面切换
        {
            if (LCD_Mode == 1) {
                OLED_Clear();
                OLED_ShowString(1, 7, "Data");  // OLED显示字符串函数
                OLED_ShowString(2, 1, "CNBR:"); // CNBR类车数量
                OLED_ShowString(3, 1, "VNBR:"); // VNBR类车数量
                OLED_ShowString(4, 1, "IDLE:"); // 空闲车位
                OLED_ShowNum(2, 11, (uint32_t)CNBR_Number, 1);
                OLED_ShowNum(3, 11, (uint32_t)VNBR_Number, 1);
                OLED_ShowNum(4, 11, (uint32_t)IDLE_Number, 1);
                LCD_Mode = 0;
            } else {
                OLED_Clear();
                OLED_ShowString(1, 7, "Para");  // OLED显示字符串函数
                OLED_ShowString(2, 1, "CNBR:"); // CNBR类车费率
                OLED_ShowString(3, 1, "VNBR:"); // VNBR类车费率
                OLED_ShowNum(2, 11, (uint32_t)CNBR_Rate, 1);
                OLED_ShowNum(3, 11, (uint32_t)VNBR_Rate, 1);
                LCD_Mode = 1;
            }
        }
        // 判断是否有车位
        if (IDLE_Number == 0) {             // 车位满了
            GPIO_ResetBits(GPIOA, LED_PIN); // 则设置引脚PA4为低电平
        } else {
            GPIO_SetBits(GPIOA, LED_PIN); // 设置引脚PA4为高电平
        }
        // 判断加钱
        if (Get_key1_value()) // 判断加钱按键
        {
            if (LCD_Mode == 1) { // 判断是否在费率设置界面
                CNBR_Rate += 1;
                VNBR_Rate += 1;
                if (CNBR_Rate > 5) { CNBR_Rate = 0; }
                if (VNBR_Rate > 5) { VNBR_Rate = 0; }
                OLED_ShowNum(2, 11, (uint32_t)CNBR_Rate, 1);
                OLED_ShowNum(3, 11, (uint32_t)VNBR_Rate, 1);
            }
        }
        if (Get_key10_value()) // 在费率设置界面判断减钱按键
        {
            if (LCD_Mode == 1) { // 判断是否在费率设置界面
                CNBR_Rate -= 1;
                VNBR_Rate -= 1;
                if (CNBR_Rate < 0) { CNBR_Rate = 5; }
                if (VNBR_Rate < 0) { VNBR_Rate = 5; }
                OLED_ShowNum(2, 11, (uint32_t)CNBR_Rate, 1);
                OLED_ShowNum(3, 11, (uint32_t)VNBR_Rate, 1);
            }
        }
        if (Get_key11_value()) // 判断控制按键
        {
            Key4_Value++;
            if (Key4_Value == 1) {
                lighrt = 20;
                PWM_Breathe_SetCompare1(lighrt); // 设置亮度为50,这里是PA15端口
            } else if (Key4_Value == 2) {
                lighrt = 0;
                PWM_Breathe_SetCompare1(lighrt);
                Key4_Value = 0;
            }
        }
    }
}
