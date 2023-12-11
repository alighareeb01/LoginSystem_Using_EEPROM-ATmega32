/*
 * Login.c
 *
 *  Created on: Dec 10, 2023
 *      Author: Lenovo
 */

#include "../LIB/STD_TYPES.h"
#include <util/delay.h>

#include "../HAL/EEPROM-DRIVER/EEPROM_HAL_Interface.h"
#include "../HAL/LCD-DRIVER/LCD_HAL_Interface.h"
#include "../HAL/KPD_DRIVER/KPD_HAL_Interface.h"

#include "Login.h"

#define State 1
u8 pass1, pass2, pass3, pass4;
void Get_Pass(void) {

	u8 i = 0, key;
	u8 DigitCount = 0;
	u8 Password[4];
	while (1) {
		LCD_SetPosition(0, 0);
		LCD_SendString((u8*) "Intialize Pass : ");
		while (1) {
			key = KPD_GetKey();
			if (key != 255) {
				if (key == '=') {
					break;
				}
				if (key >= '0' && key <= '9') {
					if (DigitCount < 4) {
						LCD_SetPosition(1, i);
						LCD_SendChar(key);
						_delay_ms(50);
						LCD_SetPosition(1, i);
						LCD_SendChar('*');
						i++;
						Password[DigitCount++] = key;
					}
				}

			}
		}
//
		//saving to memory
		Write_Pass_To_Memory(Password);
		_delay_ms(50);
		LCD_ClearDisplay();
		break;
//		}
	}
}
//u8 Login(void) {
//	u8 Password[4];
//	u8 DigitCount = 0;
//	u8 i = 0, key, log_flag = 0, pass_falg = 1;
//	while (i < 3) {
//		while (1) {
//			LCD_SetPosition(0, 0);
//			LCD_SendString((u8*) "Log in  : ");
//			key = KPD_GetKey();
//			if (key != 255) {
//				if (key == '=')
//					{
//					break;
//					}
//				else if (key >= '0' && key <= '9') {
//					if(DigitCount < 4)
//					{
//						LCD_SetPosition(1, i);
//						LCD_SendChar(key);
//						_delay_ms(50);
//						LCD_SetPosition(1, i);
//						LCD_SendChar('*');
//						i++;
//						Password[DigitCount++] = key;
//					}
//				}
//			}
//		}
//		if(DigitCount != 4)
//		{
//			DigitCount = 0;
//			LCD_ClearDisplay();
//			LCD_SetPosition(0,0);
//			LCD_SendString((u8*)"Wrong");
//			_delay_ms(1000);
//		}
//		else
//		{
//			Retrieve_Pass_From_EEP();
//			pass_falg = Check_Matching(Password);
//			if (pass_falg) {
//				log_flag = 1;
//				DigitCount = 0;
//				pass_falg = 0;
//				LCD_ClearDisplay();
//				LCD_SendString((u8*)"Pass Right");
//				break;
//			} else {
//				log_flag = 0;
//				DigitCount = 0;
//				LCD_ClearDisplay();
//				LCD_SendString((u8*)"Wrong x");
//			}
//
//		}
//	}
//	return log_flag;
//}
u8 Login(void) {
	u8 Password[4];
	u8 DigitCount = 0;
	u8 i = 0, key, log_flag = 0, pass_flag = 1;
	u8 left_trials = 3;
	while (left_trials != 0) {
		i = 0;
		DigitCount = 0;
		while (1) {
			LCD_SetPosition(0, 0);
			LCD_SendString((u8*) "Log in  : ");
			key = KPD_GetKey();
			if (key != 255) {
				if (key == '=') {
					break;
				} else if (key >= '0' && key <= '9') {
					LCD_SetPosition(1, i);
					LCD_SendChar(key);
					_delay_ms(50);
					LCD_SetPosition(1, i);
					LCD_SendChar('*');
					i++;
					Password[DigitCount++] = key;
				}
			}
		}
		Retrieve_Pass_From_EEP();
		pass_flag = Check_Matching(Password);
		if (DigitCount == 4) {
			if (pass_flag) {
				log_flag = 1;
				break;
			} else {
				log_flag = 0;
				left_trials--;
				i = 0;
				DigitCount = 0;
				LCD_ClearDisplay();
				LCD_SendString((u8*) "Wrong pass");
				LCD_SetPosition(1, 0);
				LCD_SendString((u8*) "trials = ");
				LCD_SetPosition(1, 7);
				LCD_SendNumber(left_trials);
				_delay_ms(700);
				LCD_ClearDisplay();
			}
		} else {
			log_flag = 0;
			left_trials--;
			i = 0;
			DigitCount = 0;
			LCD_ClearDisplay();
			LCD_SendString((u8*) "must be 4 number");
			LCD_SetPosition(1, 0);
			LCD_SendString((u8*) "trials = ");
			LCD_SetPosition(1, 8);
			LCD_SendNumber(left_trials);
			_delay_ms(700);
			LCD_ClearDisplay();
		}
	}

	return log_flag;
}

void Retrieve_Pass_From_EEP(void) {
	pass1 = EEPROM_ReadByte(3, 0);
	pass2 = EEPROM_ReadByte(25, 0);
	pass3 = EEPROM_ReadByte(100, 0);
	pass4 = EEPROM_ReadByte(125, 0);
}
void Write_Pass_To_Memory(u8 *pass) {

	EEPROM_WriteByte(pass[0], 3, 0);
	EEPROM_WriteByte(pass[1], 25, 0);
	EEPROM_WriteByte(pass[2], 100, 0);
	EEPROM_WriteByte(pass[3], 125, 0);
}
u8 Check_Matching(u8 *pass) {
	u8 correct = 1;
	if (pass[0] != pass1)
		correct = 0;
	if (pass[1] != pass2)
		correct = 0;
	if (pass[2] != pass3)
		correct = 0;
	if (pass[3] != pass4)
		correct = 0;
	return correct;
}

