/*
 * EEPROM_HAL_Interface.h
 *
 *  Created on: Dec 10, 2023
 *      Author: Lenovo
 */

#ifndef HAL_EEPROM_DRIVER_EEPROM_HAL_INTERFACE_H_
#define HAL_EEPROM_DRIVER_EEPROM_HAL_INTERFACE_H_

void EEPROM_Init(void);
void EEPROM_WriteByte(u8 Data, u16 Add,u8 CHIP_SELECTOR);
u8 EEPROM_ReadByte(u16 Add,u8 CHIP_SELECTOR);


#endif /* HAL_EEPROM_DRIVER_EEPROM_HAL_INTERFACE_H_ */
