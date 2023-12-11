/*
 * SPI_MCAL_Prog.c
 *
 *  Created on: Nov 9, 2023
 *      Author: Lenovo
 */

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include <avr/interrupt.h>
#include "SPI_MCAL_Interface.h"
#include "SPI_MCAL_Config.h"
#include "SPI_MCAL_Private.h""
#include "../DIO-DRIVER/DIO_MCAL_Interface.h"


static void(*SPI_pf)(void) = STD_TYPES_NULL;
void SPI_SetCAllBack(void (*pf)(void))
{
	SPI_pf = pf;
}
ISR(SPI_STC_vect)
{
	SPI_pf();
}

void SPI_Init(void)
{
	#if UC_MODE == Master
	/*Pin Direction*/
	DIO_SetPinDirection(DIO_PORTB,DIO_PIN4,DIO_OUTPUT);
	DIO_SetPinDirection(DIO_PORTB,DIO_PIN5,DIO_OUTPUT);
	DIO_SetPinDirection(DIO_PORTB,DIO_PIN6,DIO_INPUT);
	DIO_SetPinDirection(DIO_PORTB,DIO_PIN7,DIO_OUTPUT);
	DIO_SetPinValue(DIO_PORTB,DIO_PIN4,DIO_HIGH);
	//order
	#if DATA_ORDER == MSB_OREDER
		CLR_BIT(SPCR_REG,SPI_DORD_PIN);
	#elif DATA_ORDER == LSB_ORDER
		SET_BIT(SPCR_REG,SPI_DORD_PIN);
	#endif
		//select master
		SET_BIT(SPCR_REG,SPI_MSTR_PIN);
		//clk
#if Clk_Rate_Mode == Clk_4
			CLR_BIT(SPCR_REG, SPI_SPR0_PIN);
			CLR_BIT(SPCR_REG, SPI_SPR1_PIN);
			CLR_BIT(SPSR_REG, SPI_SPI2X_PIN);
		#elif Clk_Rate_Mode == Clk_16
			SET_BIT(SPCR_REG, SPI_SPR0_PIN);
			CLR_BIT(SPCR_REG, SPI_SPR1_PIN);
			CLR_BIT(SPSR_REG, SPI_SPI2X_PIN);
		#elif Clk_Rate_Mode == Clk_64
			CLR_BIT(SPCR_REG, SPI_SPR0_PIN);
			SET_BIT(SPCR_REG, SPI_SPR1_PIN);
			CLR_BIT(SPSR_REG, SPI_SPI2X_PIN);
		#elif Clk_Rate_Mode == Clk_128
			SET_BIT(SPCR_REG, SPI_SPR0_PIN);
			SET_BIT(SPCR_REG, SPI_SPR1_PIN);
			CLR_BIT(SPSR_REG, SPI_SPI2X_PIN);
		#elif Clk_Rate_Mode == Clk_2
			CLR_BIT(SPCR_REG, SPI_SPR0_PIN);
			CLR_BIT(SPCR_REG, SPI_SPR1_PIN);
			SET_BIT(SPSR_REG, SPI_SPI2X_PIN);
		#elif Clk_Rate_Mode == Clk_8
			SET_BIT(SPCR_REG, SPI_SPR0_PIN);
			CLR_BIT(SPCR_REG, SPI_SPR1_PIN);
			SET_BIT(SPSR_REG, SPI_SPI2X_PIN);
		#elif Clk_Rate_Mode == Clk_32
			CLR_BIT(SPCR_REG, SPI_SPR0_PIN);
			SET_BIT(SPCR_REG, SPI_SPR1_PIN);
			SET_BIT(SPSR_REG, SPI_SPI2X_PIN);
		#endif
			//polarity
		#if CLK_Polarity == FALLING_leads
			SET_BIT(SPCR_REG,1);
		#elif CLK_Polarity == RISING_leads
			CLR_BIT(SPCR_REG,1);
		#endif
			//phase
		#if CPHA == Setup_leads
			SET_BIT(SPCR_REG,2);
		#elif CPHA = Sample_leads
			CLR_BIT(SPCR_REG,2);
		#endif
#elif UC_MODE == Slave
			DIO_SetPinDirection(DIO_PORTB,DIO_PIN4,DIO_INPUT);
			DIO_SetPinDirection(DIO_PORTB,DIO_PIN5,DIO_INPUT);
			DIO_SetPinDirection(DIO_PORTB,DIO_PIN6,DIO_OUTPUT);
			DIO_SetPinDirection(DIO_PORTB,DIO_PIN7,DIO_INPUT);
			DIO_SetPinValue(DIO_PORTB,DIO_PIN4,DIO_HIGH);
			//select slave
			CLR_BIT(SPCR_REG, SPI_MSTR_PIN);
			//order
		#if DATA_ORDER == MSB_OREDER
		CLR_BIT(SPCR_REG,SPI_DORD_PIN);
		#elif DATA_ORDER == LSB_ORDER
		SET_BIT(SPCR_REG,SPI_DORD_PIN);
		#endif
		//polarity
			#if CLK_Polarity == FALLING_leads
				SET_BIT(SPCR_REG,1);
			#elif CLK_Polarity == RISING_leads
				CLR_BIT(SPCR_REG,1);
			#endif
				//phase
			#if CPHA == Setup_leads
				SET_BIT(SPCR_REG,2);
			#elif CPHA = Sample_leads
				CLR_BIT(SPCR_REG,2);
			#endif
#endif
				//enable SPI
				SET_BIT(SPCR_REG,6);
}

u8 SPI_Transieve(u8 data)
{
	//send data
	SPDR_REG = data;
	while((GET_BIT(SPSR_REG,7)) == 0);
	return SPDR_REG;
}


void SPI_EnableINT(void)
{
	SET_BIT(SPCR_REG,7);
}


