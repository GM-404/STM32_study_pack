#ifndef _ADC_H
#define _ADC_H
#include "config.h"
#include "stm32f10x.h"
void Adc_Init(void);
uint16_t Get_Adc_Value(uint8_t ADC_Channel);
#endif
