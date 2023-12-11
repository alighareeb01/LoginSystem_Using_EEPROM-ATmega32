/*
 * SPI_MCAL_Priv.h
 *
 *  Created on: Nov 9, 2023
 *      Author: Lenovo
 */

#ifndef MCAL_SPI_DRIVER_SPI_MCAL_PRIVATE_H_
#define MCAL_SPI_DRIVER_SPI_MCAL_PRIVATE_H_


#define SPCR_REG 	*((volatile u8*)(0x2D))
#define SPSR_REG	*((volatile u8*)(0x2E))
#define SPDR_REG	*((volatile u8*)(0x2F))



#define SPI_SPIE_PIN					7
#define SPI_SPE_PIN						6
#define SPI_DORD_PIN					5
#define SPI_MSTR_PIN					4
#define SPI_CPOL_PIN					3
#define SPI_CPHA_PIN					2
#define SPI_SPR1_PIN					1
#define SPI_SPR0_PIN					0

#define SPI_SPI2X_PIN					0
#define SPI_SPIF_PIN					7


/*Date Order*/
#define LSB_ORDER	0
#define MSB_OREDER	1
/*Select master or slave*/
#define Master  0
#define Slave	1
/*clock polarity*/
#define RISING_leads	0
#define FALLING_leads	1
/*CPHA*/

#define Sample_leads	0
#define Setup_leads		1



/* Select Clk Rate */

#define Clk_4								0
#define Clk_16								1
#define Clk_64								2
#define Clk_128								3
#define Clk_2								4
#define Clk_8								5
#define Clk_32								6

#endif /* MCAL_SPI_DRIVER_SPI_MCAL_PRIVATE_H_ */
