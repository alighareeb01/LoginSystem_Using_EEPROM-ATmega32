/*
 * Login.h
 *
 *  Created on: Dec 10, 2023
 *      Author: Lenovo
 */

#ifndef APP_LOGIN_H_
#define APP_LOGIN_H_


void Get_Pass(void);
u8 Login(void);
void Retrieve_Pass_From_EEP(void);
void Write_Pass_To_Memory(u8 *pass);
u8 Check_Matching(u8 *pass);


#endif /* APP_LOGIN_H_ */
