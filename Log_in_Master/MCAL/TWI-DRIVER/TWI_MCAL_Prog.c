/*
 * TWI_MCAL_Prog.c
 *
 *  Created on: Dec 9, 2023
 *      Author: Lenovo
 */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "TWI_MCAL_Config.h"
#include "TWI_MCAL_Interface.h"
#include "TWI_MCAL_Private.h"
void TWI_InitMaster(void)
{
	//400kHz
	TWBR_REG = 2;
	CLR_BIT(TWSR_REG,0);
	CLR_BIT(TWSR_REG,1);
	//enable ack
	SET_BIT(TWCR_REG,6);
	//enable
	SET_BIT(TWCR_REG,2);
}
void TWI_InitSlave(u8 Add)
{
	TWAR_REG = (Add << 1);
	//enable ack
	SET_BIT(TWCR_REG,6);
	//enable
	SET_BIT(TWCR_REG,2);
}
void TWI_Start_Cond(void)
{
	SET_BIT(TWCR_REG,7);
	SET_BIT(TWCR_REG,5);
	while(!(GET_BIT(TWCR_REG,7)));
	while((TWSR_REG&0xf8)!=START_COND_ACK);
}
void TWI_SendSlaveAdd_Write(u8 Add)
{
	TWDR_REG = (Add << 1);
	//write
	CLR_BIT(TWDR_REG,0);
	//clr TWSTA
	CLR_BIT(TWCR_REG,5);
	//clr flag
	SET_BIT(TWCR_REG,7);
	while(!(GET_BIT(TWCR_REG,7)));
	while((TWSR_REG&0xf8)!=SLAVE_WRITE_ACK);
}
void TWI_SendSlaveAdd_Read(u8 Add)
{
	TWDR_REG = (Add << 1);
	//Read
	SET_BIT(TWDR_REG,0);
	CLR_BIT(TWCR_REG,5);
	SET_BIT(TWCR_REG,7);
	while(!(GET_BIT(TWCR_REG,7)));
	while((TWSR_REG&0xf8)!=SLAVE_READ_ACK);
}
void TWI_WriteByte(u8 Data)
{
	TWDR_REG = Data;
	SET_BIT(TWCR_REG,7);
	while(!(GET_BIT(TWCR_REG,7)));
	while((TWSR_REG&0xf8)!=WRITE_BYTE_ACK);
}
u8 TWI_RecieveByte()
{
	SET_BIT(TWCR_REG,7);
	while(!(GET_BIT(TWCR_REG,7)));
	while((TWSR_REG&0xf8)!=READ_BYTE_ACK);
	return TWDR_REG;
}
void TWI_RepeatedStartCond(void)
{
	SET_BIT(TWCR_REG,5);
	SET_BIT(TWCR_REG,7);
	while(!(GET_BIT(TWCR_REG,7)));
	while((TWSR_REG&0xf8)!=REPEATED_START_COND_ACK);
}
void TWI_Stop()
{
	SET_BIT(TWCR_REG,4);
	SET_BIT(TWCR_REG,7);
}
u8 TWI_Slave_Read_Byte(void)
{
	SET_BIT(TWCR_REG,7);
	SET_BIT(TWCR_REG,6);
	SET_BIT(TWCR_REG,2);
	while(!(GET_BIT(TWCR_REG,7)));
	while((TWSR_REG&0xf8)!=SLAVE_Data_Rec);
	return TWDR_REG;
}


