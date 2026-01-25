/*
 * GPIO_interface.h
 *
 *  Created on: Feb 15, 2022
 *      Author: nourhan
 */

#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_



void MGPIO_voidSetPinDirection(u8 copy_u8PortNumber,u8 copy_u8PinNumber,u8 copy_u8Mode,u8 copy_u8CNF);

Errorstatus MGPIO_voidSetPinValue(u8 copy_u8PortNumber,u8 copy_u8PinNumber,u8 copy_u8Value);

Errorstatus MGPIO_voidGetPinValue(u8 copy_u8PortNumber,u8 copy_u8PinNumber,u8 *copy_u8PtrValue);

void MGPIO_voidLockPin(u8 copy_u8PortNumber,u8 copy_u8PinNumber);

#define GPIO_PORTA			0
#define GPIO_PORTB			1
#define GPIO_PORTC			2

#define GPIO_PIN0			0
#define GPIO_PIN1			1
#define GPIO_PIN2			2
#define GPIO_PIN3			3
#define GPIO_PIN4			4
#define GPIO_PIN5			5
#define GPIO_PIN6			6
#define GPIO_PIN7			7
#define GPIO_PIN8			8
#define GPIO_PIN9			9
#define GPIO_PIN10			10
#define GPIO_PIN11			11
#define GPIO_PIN12			12
#define GPIO_PIN13			13
#define GPIO_PIN14			14
#define GPIO_PIN15			15

#define GPIO_PIN_INPUT				0
#define GPIO_PIN_OUTPUT_10MHZ		1
#define GPIO_PIN_OUTPUT_2MHZ		2
#define GPIO_PIN_OUTPUT_50MHZ		3

#define GPIO_INPUT_ANALOG			0
#define GPIO_INPUT_FLOATING			1
#define GPIO_INPUT_PULLUP			2
#define	GPIO_INPUT_PULLUP_DOWN		2
#define GPIO_INPUT_PULLDOWN			3

#define GPIO_OUTPUT_PUSHPULL		0
#define GPIO_OUTPUT_OPENDRAIN		1
#define GPIO_OUTPUT_AF_PUSHPULL		2
#define GPIO_OUTPUT_AF_OPENDRAIN	3

#define GPIO_HIGH					1
#define GPIO_LOW					0
#endif /* GPIO_INTERFACE_H_ */
