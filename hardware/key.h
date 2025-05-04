/*
说明：该模块实际作用为GPIO的输入初始化，作用为用引脚感知输出的高低电平
      该模块可以用于按键的控制，也可以用于其他GPIO的控制
      使用时先再config.h中定义好引脚和打开模块开关
      然后在key.h中打开使能GPIOB时钟的宏定义
*/
#ifndef _KEY_H_
#define _KEY_H_
#include "config.h"                // 配置头文件
#define ENABLE_KEY_GPIOB_CLOCK (1) // 使能KEY模块GPIOB时钟,如果需要开启GPIOB的时钟置1

/*
 *@brief 按键初始化函数
 *@note 默认上拉输入模式，50MHz速度
 *@ return 无
 */
void KEY_Init(void); // 按键初始化函数

/*
 *@brief 得到按键值函数
 *@ return uint8_t key_value = 1 : 按键按下:
 *         uint8_t key_value = 0 : 按键未按下
 */
uint8_t Get_key_value(void); // 按键扫描函数

#endif // _KEY_H_
