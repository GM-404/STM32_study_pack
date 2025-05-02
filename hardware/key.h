#ifndef _KEY_H_
#define _KEY_H_
#include "config.h"                // 配置头文件
#define ENABLE_KEY_GPIOB_CLOCK (1) // 使能KEY模块GPIOB时钟,如果需要开启GPIOB的时钟置1

void KEY_Init(void);         // 按键初始化函数
uint8_t Get_key_value(void); // 按键扫描函数

#endif // _KEY_H_
