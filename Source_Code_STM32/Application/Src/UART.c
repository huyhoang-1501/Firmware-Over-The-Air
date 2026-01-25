#ifndef UART_C_
#define UART_C_


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

#include "../Inc/MCAL/UART/UART_private.h"
#include "../Inc/MCAL/UART/UART_interface.h"
#include "../Inc/MCAL/UART/UART_configuration.h"

void MUSART_voidInit(void)
{
u32 LOC_u32Mantissa=(F_CPU)/(16*USART1_BAUD_RATE);

u32 LOC_u32fraction=( ( (F_CPU*100) / (16*USART1_BAUD_RATE ) ) % 100 )*16 ;

#if(WORD_LENGTH == EIGHT_DATA_BITS)

	CLEAR_BIT(USART->CR1,WORD_LENGTH_CONTROL);


#elif(WORD_LENGTH == NINE_DATA_BITS)

	SET_BIT(USART->CR1,WORD_LENGTH_CONTROL);

#endif

#if(PARITY_CONTROL== ENABLE)
	SET_BIT(USART->CR1,PARITY_CONTROL_ENABLE);
	#if(PARITY_TYPE==ODD)
	SET_BIT(USART->CR1,PARITY_SELECTION);
	#elif(PARITY_TYPE==EVEN)
	CLEAR_BIT(USART->CR1,PARITY_SELECTION);
	#endif
#elif(PARITY== DISABLE)
	CLEAR_BIT(USART->CR1,PARITY_CONTROL_ENABLE);
	#endif

#if(STOP_BITS==ONE_STOP_BIT)

 CLEAR_BIT(USART->CR2,STOP_BIT_1);
 CLEAR_BIT(USART->CR2,STOP_BIT_2);
#elif(STOP_BITS==HALF_STOP_BIT)

 USART->CR2 &=~ (3<<STOP_BIT_1);
 USART->CR2 |= (1<<STOP_BIT_1);

#elif(STOP_BITS==TWO_STOP_BIT)

 USART->CR2 &=~ (3<<STOP_BIT_1);
 USART->CR2 |= (2<<STOP_BIT_1);

#elif(STOP_BITS==ONE_AND_HALF_STOP_BIT)

 USART->CR2 &=~ (3<<STOP_BIT_1);
  USART->CR2 |= (2<<STOP_BIT_1);

#endif

  /*ENABLE TRANSMITTER*/
 SET_BIT(USART->CR1,TRANSMIT_ENABLE);

 /*ENABLE RECIEVER*/
 SET_BIT(USART->CR1,RECIEVE_ENABLE);

USART->BRR=(LOC_u32Mantissa<<4)|(LOC_u32fraction/100);

	/*Enable USART*/
 SET_BIT(USART->CR1,UART_ENABLE);
}

void MUSART_voidTransmit(u8 copy_data)
{
	/*Set data to DR register*/
	USART->DR=copy_data;

	/*Wait until TC flag is set*/
	while((GET_BIT(USART->SR,TRANSMISSION_COMPLETE)) != 1);

	/*Clear transmission flag*/
	CLEAR_BIT(USART->SR,TRANSMISSION_COMPLETE);
}



void MUSART_voidSendString(u8 *copy_Strinptr)
{
	u8 local_data=0;
	local_data=*copy_Strinptr;

	while( *copy_Strinptr != '\0')
	{
		local_data=*copy_Strinptr;
		USART->DR=local_data;

		/*Wait until TC flag is set*/
		while(GET_BIT(USART->SR,TRANSMISSION_COMPLETE)!=1);

		/*Clear transmission flag*/
		CLEAR_BIT(USART->SR,TRANSMISSION_COMPLETE);

		copy_Strinptr++;
	}
}

u8 MUSART_u8Recieve(u8 *Copy_u8Data)
{
	u8 local_recieve_data=1;

	/*Check on RXNE*/
	if( (GET_BIT(USART->SR,RECIEVE_NOT_EMPTY)) == 1)
	/*Read DAta from register*/
	{
		*Copy_u8Data=USART->DR;
	}

	else
	{
		local_recieve_data=0;
	}

	return local_recieve_data;
}

#endif /* UART_C_ */
