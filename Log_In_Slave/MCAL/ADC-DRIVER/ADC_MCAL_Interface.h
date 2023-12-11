/*
 * ADC_MCAL_Interface.h
 *
 *  Created on: Oct 13, 2023
 *      Author: Lenovo
 */

#ifndef MCAL_ADC_DRIVER_ADC_MCAL_INTERFACE_H_
#define MCAL_ADC_DRIVER_ADC_MCAL_INTERFACE_H_



void ADC_Init(void);
u16 ADC_GetResult(u8 Channel);
u16 ADC_GetValueINT(u8 ADCCHANNEL, void(*ADC_pf)(u16));

#define ADC_CHannel0	0
#define ADC_CHannel1	1
#define ADC_CHannel2	2
#define ADC_CHannel3	3
#define ADC_CHannel4	4
#define ADC_CHannel5	5
#define ADC_CHannel6	6
#define ADC_CHannel7	7

#define PRESCALAR_2 	0b00000001
#define PRESCALAR_4 	0b00000010
#define PRESCALAR_8 	0b00000011
#define PRESCALAR_16 	0b00000100
#define PRESCALAR_32	0b00000101
#define PRESCALAR_64 	0b00000110
#define PRESCALAR_128 	0b00000111




#endif /* MCAL_ADC_DRIVER_ADC_MCAL_INTERFACE_H_ */
