/*
 * TWI_MCAL_Interface.h
 *
 *  Created on: Dec 9, 2023
 *      Author: Lenovo
 */

#ifndef MCAL_TWI_DRIVER_TWI_MCAL_INTERFACE_H_
#define MCAL_TWI_DRIVER_TWI_MCAL_INTERFACE_H_

void TWI_InitMaster(void);
void TWI_InitSlave(u8 Add);
void TWI_Start_Cond(void);
void TWI_SendSlaveAdd_Write(u8 Add);
void TWI_SendSlaveAdd_Read(u8 Add);
void TWI_WriteByte(u8 Data);
u8 TWI_RecieveByte();
void TWI_RepeatedStartCond(void);
void TWI_Stop();
u8 TWI_Slave_Read_Byte(void);




#endif /* MCAL_TWI_DRIVER_TWI_MCAL_INTERFACE_H_ */
