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

#include <avr/io.h>

#include "Login.h"

int main(void) {
	DIO_SetPinDirection(DIO_PORTC, DIO_PIN2, DIO_OUTPUT);
	DIO_SetPinDirection(DIO_PORTB, DIO_PIN3, DIO_OUTPUT);
	u8 state;
	u8 flag_Log = 0;
	u8 val;
	u8 key;
	f32 Temp;
	LCD_Init();
	KPD_Init();
	EEPROM_Init();
	Get_Pass();
	state = Login();
	ADC_Init();
	SPI_Init();

	while (1) {
		if (state) {
			while (1) {
				LCD_ClearDisplay();
				LCD_SendString((u8*) "Logged Successfully");
				_delay_ms(1000);
				LCD_ClearDisplay();
				LCD_SendString((u8*) "Opening door");
				TMR0_FastPWM(Non_Inverted, 100);
				_delay_ms(2000);
				DIO_SetPinDirection(DIO_PORTB, DIO_PIN3, DIO_INPUT);
				_delay_ms(2000);
				flag_Log = 1;
				break;
			}
		} else {
			LCD_ClearDisplay();
			LCD_SendString((u8*) "Blocked");
			DIO_SetPinValue(DIO_PORTC, DIO_PIN2, DIO_HIGH);
			flag_Log = 0;
			_delay_ms(10000);
			LCD_ClearDisplay();
			break;
		}
		if (flag_Log) {
			while (1) {
				_delay_ms(100);
				LCD_ClearDisplay();
				LCD_SetPosition(0, 0);
				LCD_SendString((u8*) "1-cool");
				LCD_SetPosition(0, 6);
				LCD_SendString((u8*) "2-heat");
				LCD_SetPosition(1, 0);
				LCD_SendString((u8*) "3-On");
				LCD_SetPosition(1, 6);
				LCD_SendString((u8*) "4-Off");
				while (1) {
					key = KPD_GetKey();
					if (key != 255) {
						DIO_SetPinValue(DIO_PORTB, DIO_PIN4, DIO_LOW);
						if (key >= '0' && key <= '9') {
							LCD_ClearDisplay();
							val = val * 10 + (key - '0');
							LCD_SendChar(key);
						} else if (key == '=') {
							break;
						}
					}
					switch (val) {
					case 1 :
						SPI_Transieve('1');
						break;
					case 2 :
						SPI_Transieve('2');
						break;
					case 3: //light on
						SPI_Transieve('3');
						break;
					case 4://light off
						SPI_Transieve('4');
						break;
					case 5:
					case 6:
					case 7:
					case 8:
					case 9:
						SPI_Transieve('d');
						break;
					}
					val = 0;
				}

			}
		}
	}
}
