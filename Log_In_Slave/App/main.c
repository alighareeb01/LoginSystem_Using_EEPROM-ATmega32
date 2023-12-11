/*
 * main.c
 *
 *  Created on: Oct 3, 2023
 *      Author: Lenovo
 */

#include <util/delay.h>.
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include "../MCAL/DIO-DRIVER/DIO_MCAL_Interface.h"
#include "../MCAL/GIE-DRIVER/GIE_MCAL_Interface.h"
#include "../MCAL/EXTI-DRIVER/EXTI_MCAL_Interface.h"
#include "../MCAL/ADC-DRIVER/ADC_MCAL_Interface.h"
#include "../MCAL/TMR-DRIVER/TMR_MCAL_Interface.h"
#include "../MCAL/USART-DRIVER/USART_MCAL_Interface.h"
#include "../MCAL/SPI-DRIVER/SPI_MCAL_Interface.h"
#include "../MCAL/TWI-DRIVER/TWI_MCAL_Interface.h"

#include "../HAL/LCD-DRIVER/LCD_HAL_Interface.h"
#include "../HAL/SEGMENT_DRIVER/SEG_HAL_Interface.h"
#include "../HAL/KPD_DRIVER/KPD_HAL_Interface.h"
#include "../HAL/LM_SENSOR-DIRVER/LM_HAL_Interface.h"
#include "../HAL/STEPPER_MOTOR-DRIVER/STEP_HAL_Interface.h"
#include "../HAL/EEPROM-DRIVER/EEPROM_HAL_Interface.h"
#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
void Stop_Cooler(void);
void Stop_Heater(void);
void Stop_Both(void);
int main(void) {

	SPI_Init();
	DIO_SetPinDirection(DIO_PORTB,DIO_PIN3,DIO_OUTPUT);
	DIO_SetPinDirection(DIO_PORTD,DIO_PIN7,DIO_OUTPUT);
	DIO_SetPinDirection(DIO_PORTA,DIO_PIN0,DIO_OUTPUT);
	DIO_SetPinDirection(DIO_PORTA,DIO_PIN1,DIO_OUTPUT);
	DIO_SetPinDirection(DIO_PORTC, DIO_PIN0, DIO_OUTPUT);
	DIO_SetPinDirection(DIO_PORTC, DIO_PIN1, DIO_OUTPUT);
	DIO_SetPinDirection(DIO_PORTC, DIO_PIN2, DIO_OUTPUT);
	DIO_SetPinDirection(DIO_PORTC, DIO_PIN3, DIO_OUTPUT);
	u8 data;
	LCD_Init();
	f32 Temp;
	while (1) {
		data = SPI_Transieve('q');
		if (data == '1') {
			Stop_Cooler();
			TMR0_FastPWM(Non_Inverted,100);
		} else if (data == '2') {
			Stop_Heater();
			TMR2_PhasePWM(Inverted,100);
		} else if (data == '3') {
			DIO_SetPinValue(DIO_PORTA,DIO_PIN0,DIO_HIGH);
			DIO_SetPinValue(DIO_PORTA,DIO_PIN1,DIO_HIGH);

		} else if (data == '4') {
			DIO_SetPortValue(DIO_PORTA,0x00);
		} else if (data =='d'){
			Stop_Both();
			DIO_SetPinValue(DIO_PORTA, DIO_PIN0, DIO_LOW);
			DIO_SetPinValue(DIO_PORTA, DIO_PIN1, DIO_LOW);

		}
	}
}
void Stop_Cooler(void)
{
	DIO_SetPinDirection(DIO_PORTD,DIO_PIN7,DIO_INPUT);
				DIO_SetPinDirection(DIO_PORTB,DIO_PIN3,DIO_OUTPUT);
}
void Stop_Heater(void)
{
	DIO_SetPinDirection(DIO_PORTD,DIO_PIN7,DIO_OUTPUT);
				DIO_SetPinDirection(DIO_PORTB,DIO_PIN3,DIO_INPUT);
}
void Stop_Both(void)
{	DIO_SetPinDirection(DIO_PORTD,DIO_PIN7,DIO_OUTPUT);
DIO_SetPinDirection(DIO_PORTD,DIO_PIN7,DIO_INPUT);


}
