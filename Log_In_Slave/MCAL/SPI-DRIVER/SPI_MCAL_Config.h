/*
 * SPI_MCAL_Config.h
 *
 *  Created on: Nov 9, 2023
 *      Author: Lenovo
 */

#ifndef MCAL_SPI_DRIVER_SPI_MCAL_CONFIG_H_
#define MCAL_SPI_DRIVER_SPI_MCAL_CONFIG_H_

/*DATA_ORDER
 * 			LSB_ORDER
 * 			MSB_OREDER
 */
#define DATA_ORDER	MSB_OREDER
/*
 * UC_MODE :
 * 			Master
 * 			Slave
 */
#define UC_MODE	Slave

/*clock polarity
 * 				RISING_leads
 * 				FALLING_leads
 */
#define CLK_Polarity	FALLING_leads
/*CPHA
 * 		Sample_leads
 * 		Setup_leads
 */
#define CPHA Setup_leads



/*
Clk_4
Clk_16
Clk_64
Clk_128
Clk_2
Clk_8
Clk_32
*/
#define Clk_Rate_Mode						Clk_64



#endif /* MCAL_SPI_DRIVER_SPI_MCAL_CONFIG_H_ */
