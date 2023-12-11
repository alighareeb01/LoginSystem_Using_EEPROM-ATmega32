/*
 * TWI_MCAL_Private.h
 *
 *  Created on: Dec 9, 2023
 *      Author: Lenovo
 */

#ifndef MCAL_TWI_DRIVER_TWI_MCAL_PRIVATE_H_
#define MCAL_TWI_DRIVER_TWI_MCAL_PRIVATE_H_

#define TWBR_REG  *((volatile u8*)0x20)
#define TWSR_REG  *((volatile u8*)0x21)
#define TWAR_REG  *((volatile u8*)0x22)
#define TWDR_REG  *((volatile u8*)0x23)
#define TWCR_REG  *((volatile u8*)0x56)


#define START_COND_ACK					0x08
#define REPEATED_START_COND_ACK			0x10
#define SLAVE_WRITE_ACK					0x18
#define SLAVE_READ_ACK					0x40
#define WRITE_BYTE_ACK					0x28
#define READ_BYTE_ACK					0x50
#define READ_BYTE_NACK					0X51
#define SLAVE_Data_Rec 					0x80



#endif /* MCAL_TWI_DRIVER_TWI_MCAL_PRIVATE_H_ */
