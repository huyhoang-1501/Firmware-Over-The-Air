/*
 * GPIO.c
 *
 *  Created on: Feb 15, 2022
 *      Author: Ahmed
 */


/*Include Standard libraries*/

#include "../Inc/LIB/bit_math.h"
#include "../Inc/LIB/std_types.h"

/*Include header files of RCC */

#include "../Inc/MCAL/RCC/RCC_interface.h"
#include "../Inc/MCAL/RCC/RCC_private.h"
#include "../Inc/MCAL/RCC/RCC_configuration.h"

/*Include header files of GPIO*/
#include "../Inc/MCAL/GPIO/GPIO_private.h"
#include "../Inc/MCAL/GPIO/GPIO_interface.h"
#include "../Inc/MCAL/GPIO/GPIO_configuration.h"


void MGPIO_voidSetPinDirection(u8 copy_u8PortNumber,u8 copy_u8PinNumber,u8 copy_u8Mode,u8 copy_u8CNF)
{
	u8 local_MODE_PIN=0;
	u8 local_CNF_PIN=0;
if((copy_u8PinNumber < GPIO_PIN8)  && (copy_u8PinNumber >= GPIO_PIN0))
{
	local_MODE_PIN=copy_u8PinNumber*CONSTANT_MODE_VALUE;
	local_CNF_PIN=local_MODE_PIN+CONSTANT_CNF_VALUE;

	}
else if(copy_u8PinNumber > GPIO_PIN7 && copy_u8PinNumber <= GPIO_PIN15)
{
	local_MODE_PIN=(copy_u8PinNumber-CONSTANT_PIN_CRH)*CONSTANT_MODE_VALUE;
	local_CNF_PIN=local_MODE_PIN+CONSTANT_CNF_VALUE;

	}

		switch(copy_u8PortNumber)
	{

		case GPIO_PORTA:
			if (copy_u8PinNumber < GPIO_PIN8 && copy_u8PinNumber >= GPIO_PIN0 )
			{
				GPIOA->CRL &=~(CONSTANT_CLEARING_VALUE_GPIO<<local_MODE_PIN);
				GPIOA->CRL |=(copy_u8Mode<<local_MODE_PIN);
				GPIOA->CRL |=(copy_u8CNF<<local_CNF_PIN);
				if(copy_u8CNF== GPIO_INPUT_PULLUP)
				{
				GPIOA->CRL |=(copy_u8CNF<<local_CNF_PIN);
				SET_BIT(GPIOA->ODR,copy_u8PinNumber);
				}
				else if(copy_u8CNF== GPIO_INPUT_PULLDOWN)
				{
					GPIOA->CRL |=(GPIO_INPUT_PULLUP_DOWN<<local_CNF_PIN);
				}
			}
			else if(copy_u8PinNumber > GPIO_PIN7 && copy_u8PinNumber <= GPIO_PIN15)
			{
				GPIOA->CRH &=~(CONSTANT_CLEARING_VALUE_GPIO<<local_MODE_PIN);
				GPIOA->CRH |=(copy_u8Mode<<local_MODE_PIN);
				GPIOA->CRH |=(copy_u8CNF<<local_CNF_PIN);
				if(copy_u8CNF== GPIO_INPUT_PULLUP)
				{
					GPIOA->CRH |=(copy_u8CNF<<local_CNF_PIN);
					SET_BIT(GPIOA->ODR,copy_u8PinNumber);
					}
			else if(copy_u8CNF== GPIO_INPUT_PULLDOWN)
					{
						GPIOA->CRH |=(GPIO_INPUT_PULLUP_DOWN<<local_CNF_PIN);
					}

			}
			break;
		case GPIO_PORTB:
			if (copy_u8PinNumber < GPIO_PIN8 && copy_u8PinNumber >= GPIO_PIN0 )
			{
				GPIOB->CRL &=~(CONSTANT_CLEARING_VALUE_GPIO<<local_MODE_PIN);
				GPIOB->CRL |=(copy_u8Mode<<local_MODE_PIN);
				GPIOB->CRL |=(copy_u8CNF<<local_CNF_PIN);
				if(copy_u8CNF== GPIO_INPUT_PULLUP)
				{
					GPIOB->CRL |=(copy_u8CNF<<local_CNF_PIN);
					SET_BIT(GPIOB->ODR,copy_u8PinNumber);
				}
				else if(copy_u8CNF== GPIO_INPUT_PULLDOWN)
					{
						GPIOB->CRL |=(GPIO_INPUT_PULLUP_DOWN<<local_CNF_PIN);
					}
				}
		else if(copy_u8PinNumber > GPIO_PIN7 && copy_u8PinNumber <= GPIO_PIN15)
			{
				GPIOB->CRH &=~(CONSTANT_CLEARING_VALUE_GPIO<<local_MODE_PIN);
				GPIOB->CRH |=(copy_u8Mode<<local_MODE_PIN);
				GPIOB->CRH |=(copy_u8CNF<<local_CNF_PIN);
				if(copy_u8CNF== GPIO_INPUT_PULLUP)
				{
				GPIOB->CRH |=(copy_u8CNF<<local_CNF_PIN);
				SET_BIT(GPIOB->ODR,copy_u8PinNumber);
				}
					else if(copy_u8CNF== GPIO_INPUT_PULLDOWN)
				{
					GPIOB->CRH |=(GPIO_INPUT_PULLUP_DOWN<<local_CNF_PIN);
				}

			}
			break;
		case GPIO_PORTC:
			if (copy_u8PinNumber >= GPIO_PIN13 && copy_u8PinNumber <= GPIO_PIN15)
			{
				GPIOC->CRH &=~(CONSTANT_CLEARING_VALUE_GPIO<<local_MODE_PIN);
				GPIOC->CRH |=(copy_u8Mode<<local_MODE_PIN);
				GPIOC->CRH |=(copy_u8CNF<<local_CNF_PIN);
				if(copy_u8CNF== GPIO_INPUT_PULLUP)
					{
					GPIOC->CRH |=(copy_u8CNF<<local_CNF_PIN);
					SET_BIT(GPIOC->ODR,copy_u8PinNumber);
					}
				else if(copy_u8CNF== GPIO_INPUT_PULLDOWN)
					{
						GPIOC->CRH |=(GPIO_INPUT_PULLUP_DOWN<<local_CNF_PIN);
					}
				}



			break;
		}
		}
Errorstatus MGPIO_voidSetPinValue(u8 copy_u8PortNumber,u8 copy_u8PinNumber,u8 copy_u8Value)
{
	Errorstatus local_ErrorStatus=NOT_OK;
	switch(copy_u8PortNumber)
	{
	case GPIO_PORTA:
		switch(copy_u8Value)
		{
		case GPIO_HIGH:
			//SET_BIT(GPIOA->ODR,copy_u8PinNumber);
			GPIOA->BSRR|=(1<<copy_u8PinNumber);
			local_ErrorStatus=OK;
			break;
		case GPIO_LOW:
			//CLEAR_BIT(GPIOA->ODR,copy_u8PinNumber);
			GPIOA->BRR|=(1<<copy_u8PinNumber);
			local_ErrorStatus=OK;
			break;
		default:
			local_ErrorStatus=OUT_OF_RANGE;
		}
		break;
	case GPIO_PORTB:
		switch(copy_u8Value)
				{
				case GPIO_HIGH:
					//SET_BIT(GPIOB->ODR,copy_u8PinNumber);
					GPIOB->BSRR|=(1<<copy_u8PinNumber);
					local_ErrorStatus=OK;
					break;
				case GPIO_LOW:
					//CLEAR_BIT(GPIOB->ODR,copy_u8PinNumber);
					GPIOB->BRR|=(1<<copy_u8PinNumber);
					local_ErrorStatus=OK;
					break;
				default:
					local_ErrorStatus=OUT_OF_RANGE;
				}


		break;
	case GPIO_PORTC:
		if(copy_u8PinNumber>= GPIO_PIN13)
		{
		switch(copy_u8Value)
				{
				case GPIO_HIGH:
					//SET_BIT(GPIOC->ODR,copy_u8PinNumber);
					GPIOC->BSRR|=(1<<copy_u8PinNumber);
					local_ErrorStatus=OK;
					break;
				case GPIO_LOW:
					//CLEAR_BIT(GPIOC->ODR,copy_u8PinNumber);
					GPIOC->BRR|=(1<<copy_u8PinNumber);
					local_ErrorStatus=OK;
					break;
				default:
					local_ErrorStatus=OUT_OF_RANGE;
				}
		}
		else
		{

		}
			break;
	default:
		local_ErrorStatus=OUT_OF_RANGE;
	}
return	local_ErrorStatus;
}

Errorstatus MGPIO_voidGetPinValue(u8 copy_u8PortNumber,u8 copy_u8PinNumber,u8 *copy_u8PtrValue)
{
	Errorstatus local_ErrorStatus=OK;
	switch(copy_u8PortNumber)
	{
	case GPIO_PORTA:
		*copy_u8PtrValue=GET_BIT(GPIOA->IDR,copy_u8PinNumber);
		    break;
	case GPIO_PORTB:
		*copy_u8PtrValue=GET_BIT(GPIOB->IDR,copy_u8PinNumber);
			break;
	case GPIO_PORTC:
		if(copy_u8PinNumber >= GPIO_PIN13 && copy_u8PinNumber <= GPIO_PIN15 )
		{
		*copy_u8PtrValue=GET_BIT(GPIOC->IDR,copy_u8PinNumber);

		}
		else
		{

		}
		break;
	default:
		local_ErrorStatus=OUT_OF_RANGE;
	}
	return local_ErrorStatus;
}

void MGPIO_voidLockPin(u8 copy_u8PortNumber,u8 copy_u8PinNumber)
{
	u32 local_u32LockValue=0;
		switch(copy_u8PortNumber)
		{
		case GPIO_PORTA:
			local_u32LockValue=((1<<16)|(1UL<<copy_u8PinNumber));
			GPIOA->LCKR=local_u32LockValue;
			GPIOA->LCKR=(1UL<<copy_u8PinNumber);
			GPIOA->LCKR=local_u32LockValue;
			local_u32LockValue=GPIOA->LCKR;

			break;

	case GPIO_PORTB:
		local_u32LockValue=((1<<16)|(1<<copy_u8PinNumber));
		GPIOB->LCKR=local_u32LockValue;
		GPIOB->LCKR=(1<<copy_u8PinNumber);
		GPIOB->LCKR=local_u32LockValue;
		local_u32LockValue=GPIOB->LCKR;

		break;
	case GPIO_PORTC:
		local_u32LockValue=((1<<16)|(1<<copy_u8PinNumber));
		GPIOC->LCKR=local_u32LockValue;
		GPIOC->LCKR=(1<<copy_u8PinNumber);
		GPIOC->LCKR=local_u32LockValue;
		local_u32LockValue=GPIOC->LCKR;

		break;
	}
}
