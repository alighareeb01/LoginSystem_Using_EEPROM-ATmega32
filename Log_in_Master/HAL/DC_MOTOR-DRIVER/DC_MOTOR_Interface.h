/*
 * DC_MOTOR_Interface.h
 *
 *  Created on: Nov 5, 2023
 *      Author: Lenovo
 */

#ifndef HAL_DC_MOTOR_DRIVER_DC_MOTOR_INTERFACE_H_
#define HAL_DC_MOTOR_DRIVER_DC_MOTOR_INTERFACE_H_

#define SPEED_ZERO 		0
#define SPEED_quar		25
#define SPEED_Half 		50
#define SPEED_HalfQau	75
#define SPEED_FULL		100


#define MOTOR_PORT	DIO_PORTB
#define MOTOR_PIN0	DIO_PIN0
#define MOTOR_PIN1	DIO_PIN1

typedef enum{
	Stop,CW,ACW
}DC_MOTOTR_STATE;
/*
 * Set two pins of motor as output
 *
 */
void DC_Init(void);
/*
 * rotate motor or stop
 */
void DC_Rotate(DC_MOTOTR_STATE state, u8 Speed);
#endif /* HAL_DC_MOTOR_DRIVER_DC_MOTOR_INTERFACE_H_ */
