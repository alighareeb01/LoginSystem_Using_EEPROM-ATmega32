/*
 * DC_MOTOR_Prog.c
 *
 *  Created on: Nov 5, 2023
 *      Author: Lenovo
 */
#include "../../LIB/Bit_Math.h"
#include "../../LIB/Std_Types.h"
#include "../../MCAL/DIO-DRIVER/DIO_MCAL_Interface.h"
#include "../../MCAL/TMR-DRIVER/TMR_MCAL_Interface.h"
#include "DC_MOTOR_Config.h"
#include "DC_MOTOR_Interface.h"
#include "DC_MOTOR_Private.h"
#include <avr/delay.h>

void DC_Init(void)
{
	DIO_SetPinDirection(MOTOR_PORT,MOTOR_PIN0,DIO_OUTPUT);
	DIO_SetPinDirection(MOTOR_PORT,MOTOR_PIN1,DIO_OUTPUT);
	DIO_SetPinValue(MOTOR_PORT,MOTOR_PIN0,DIO_LOW);
	DIO_SetPinValue(MOTOR_PORT,MOTOR_PIN0,DIO_HIGH);
}
void DC_Rotate(DC_MOTOTR_STATE state, u8 Speed)
{
	if(state == Stop)
	{
			DIO_SetPinValue(MOTOR_PORT,MOTOR_PIN0,DIO_LOW);
			DIO_SetPinValue(MOTOR_PORT,MOTOR_PIN1,DIO_LOW);
	}
	else if(state == CW)
	{
			DIO_SetPinValue(MOTOR_PORT,MOTOR_PIN0,DIO_HIGH);
			DIO_SetPinValue(MOTOR_PORT,MOTOR_PIN1,DIO_LOW);
	}
	else if(state == ACW)
	{
			DIO_SetPinValue(MOTOR_PORT,MOTOR_PIN0,DIO_LOW);
			DIO_SetPinValue(MOTOR_PORT,MOTOR_PIN1,DIO_HIGH);
	}
	else
	{
		DIO_SetPinValue(MOTOR_PORT,MOTOR_PIN0,DIO_LOW);
					DIO_SetPinValue(MOTOR_PORT,MOTOR_PIN1,DIO_LOW);
	}
	TMR0_FastPWM(Inverted,Speed);
}
