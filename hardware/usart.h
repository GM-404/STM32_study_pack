// USART(Universal synchronous asynchronous receiver transmitter)通用同步异步接收传输器，uart为异步
// 没有做复位端口，发送端口PA9,接收端口PA10
#ifndef _USART_H
#define _USART_H

#include "stm32f10x.h"
#include "config.h"
#include <stdio.h>  //重写printf
#include <stdarg.h> //封装sprintf
// // 变量在.c文件中定义
// uint8_t Usart1_Rx_Data; // 串口1接收数据缓存
// uint8_t Usart1_Rx_Flag; // 串口1接受标志位

void Usart1_Init(void);                                  // 串口1初始化
void Usart1_SendByte(uint8_t data);                      // 发送一个字节
void Usart1_SendArray(uint8_t *Array, uint16_t Length);  // 发送数组
void Usart1_SendString(char *String);                    // 发送字符串
void Usart1_SendNumber(uint32_t Number, uint8_t Length); // 发送数字
// 重定向
uint32_t Usart1_pow(uint32_t scale, uint8_t index); // 返回scale 的 index次方
int fputc(int ch, FILE *f);                         // 重定向fputc,也就是在串口中使用printf
void Usart1_Printf(char *format, ...);
// 接收需要的函数封装
void USART1_IRQHandler(void);    // 中断函数
uint8_t Usart1_GetRxFlag(void);  // 获取接收标志位，1表示接收到数据，0表示没有接收到数据
uint8_t Usart1_GetRxFData(void); // 获取接收到的数据
#endif

// 使用说明
//  while (1) {
//      if (Usart1_GetRxFlag() == 1) {
//          Rx_data = Usart1_GetRxFData();
//          Usart1_SendByte(Rx_data); // 将接收到的数据发送回去
//          OLED_ShowHexNum(1, 1, Rx_data, 2);
//      }
//  }
