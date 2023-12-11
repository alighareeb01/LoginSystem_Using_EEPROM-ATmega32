/*
 * SPI_MCAL_Interface.h
 *
 *  Created on: Nov 9, 2023
 *      Author: Lenovo
 */

#ifndef MCAL_SPI_DRIVER_SPI_MCAL_INTERFACE_H_
#define MCAL_SPI_DRIVER_SPI_MCAL_INTERFACE_H_

void SPI_Init(void);

u8 SPI_Transieve(u8 data);

void SPI_SetCAllBack(void (*pf)(void));

void SPI_EnableINT(void);
#endif /* MCAL_SPI_DRIVER_SPI_MCAL_INTERFACE_H_ */
