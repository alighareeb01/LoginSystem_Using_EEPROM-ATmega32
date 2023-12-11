/*
 * EEPROM_HAL_Prog.c
 *
 *  Created on: Dec 10, 2023
 *      Author: Lenovo
 */
#include "../../LIB/Bit_Math.h"
#include "../../LIB/Std_Types.h"
#define F_CPU 8000000UL
#include <util/delay.h>
#include "../../MCAL/DIO-DRIVER/DIO_MCAL_Interface.h"
#include "EEPROM_HAL_Config.h"
#include "EEPROM_HAL_Interface.h"
#include "EEPROM_HAL_Private.h"
#include "../../MCAL/TWI-DRIVER/TWI_MCAL_Interface.h"

void EEPROM_Init(void)
{
	TWI_InitMaster();
}
void EEPROM_WriteByte(u8 Data, u16 Add,u8 CHIP_SELECTOR)
{
	u8 LocalAdd = (FIXED_ADD) | (CHIP_SELECTOR << 2) | ((u8)Add >>8);
	TWI_Start_Cond();
	TWI_SendSlaveAdd_Write(LocalAdd);
	TWI_WriteByte((u8)Add);
	TWI_WriteByte(Data);
	TWI_Stop();
	_delay_ms(10);
}


u8 EEPROM_ReadByte(u16 Add, u8 CHIP_SELECTOR)
{
    u8 RetData;
    u8 LocalAdd = (FIXED_ADD) | (CHIP_SELECTOR << 2) | ((u8)Add >>8); // Use shift by 1 instead of 2
    TWI_Start_Cond();
    TWI_SendSlaveAdd_Write(LocalAdd);
    TWI_WriteByte((u8)Add);
    TWI_RepeatedStartCond();
    TWI_SendSlaveAdd_Read(LocalAdd);
    RetData = TWI_RecieveByte();
    TWI_Stop();

//    return (RetData +'0');
    return RetData;
}

