// USART(Universal synchronous asynchronous receiver transmitter)通用同步异步接收传输器，uart为异步
// 没有做复位端口，发送端口PA9,接收端口PA10
#ifndef _USART_H
#define _USART_H

#include "stm32f10x.h"
#include "config.h"
#include <stdio.h>  //重写printf
#include <stdarg.h> //封装sprintf
void Usart1_Init(void);
void Usart1_SendByte(uint8_t data);
void Usart1_SendArray(uint8_t *Array, uint16_t Length);
void Usart1_SendString(char *String);
void Usart1_SendNumber(uint32_t Number, uint8_t Length);
uint32_t Usart1_pow(uint32_t scale, uint8_t index); // 返回scale 的 index次方
int fputc(int ch, FILE *f);                         // 重定向fputc,也就是在串口中使用printf
void Usart1_Printf(char *format, ...);
#endif
