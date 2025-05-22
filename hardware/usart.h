// USART(Universal synchronous asynchronous receiver transmitter)通用同步异步接收传输器，uart为异步
// 没有做复位端口，发送端口PA9,接收端口PA10
// 串口收数据包的文本模式待补充
#ifndef _USART_H
#define _USART_H

#include "stm32f10x.h"
#include "config.h"
#include <stdio.h>  //重写printf
#include <stdarg.h> //封装sprintf
                    // // 变量在.c文件中定义

extern uint8_t RxCounter;      // 串口1接收数据计数
extern uint8_t RxBuffer[25];   // 串口1接收数据缓存
extern uint8_t Usart1_Rx_Flag; // 串口1接受标志位

//________________________________________________________________________________________________________
void Usart1_Init(void);               // 串口1初始化
void Usart1_SendByte(uint8_t data);   // 发送一个字节
void Usart1_SendString(char *String); // 发送字符串
int fputc(int ch, FILE *f);           // 重定向fputc,也就是在串口中使用printf
void Usart1_Printf(char *format, ...);
// 接收需要的函数封装
void USART1_IRQHandler(void); // 中断函数

#endif

// 使用说明
//  while (1) {
//      if (Usart1_GetRxFlag() == 1) {
//          Rx_data = Usart1_GetRxFData();
//          Usart1_SendByte(Rx_data); // 将接收到的数据发送回去
//          OLED_ShowHexNum(1, 1, Rx_data, 2);
//      }
//  }
// 仅与本分支有关的函数
void Usart2_Proc(void);
// uint8_t StringCheck(void);  // 检查字符串函数
// void RxbufferToEmpty(void); // 字符串数组清零函数
