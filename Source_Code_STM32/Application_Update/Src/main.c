/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------
#include "../Inc/LIB/bit_math.h"
#include "../Inc/LIB/std_types.h"

#include "../Inc/MCAL/SCB/SCB_interface.h"
#include "../Inc/MCAL/SCB/SCB_configuration.h"
#include "../Inc/MCAL/SCB/SCB_private.h"

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

#include "../Inc/MCAL/SYSTICK/SYSTICK_interface.h"
#include "../Inc/MCAL/SYSTICK/SYSTICK_private.h"
#include "../Inc/MCAL/SYSTICK/SYSTICK_configuration.h"
#include <stdio.h>
#include <stdlib.h>
#include "../system/include/diag/Trace.h"

// ----------------------------------------------------------------------------
//
// Standalone STM32F1 empty sample (trace via ITM).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the ITM output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int main(int argc, char* argv[])
{
	/*Initialization for RCC clock*/
	MRCC_Init();
	/*Enable GPIOA Clock*/
	MRCC_voidSetPeripheralClock(BUS_APB2,IOPA,CLK_ON);
	/*Enable UART Clock*/
	MRCC_voidSetPeripheralClock(BUS_APB2,USARTEN,CLK_ON);

	/*Pin 10 is configured as Rx for usart1*/

	MGPIO_voidSetPinDirection(GPIO_PORTA,GPIO_PIN10,GPIO_PIN_INPUT,GPIO_INPUT_FLOATING);

	/*Pin 9 is configured as Tx for usart1*/
	MGPIO_voidSetPinDirection(GPIO_PORTA,GPIO_PIN9,GPIO_PIN_OUTPUT_10MHZ,GPIO_OUTPUT_AF_PUSHPULL);

	/*Configuration for pin 0 for input pullup for switch1*/
	MGPIO_voidSetPinDirection(GPIO_PORTA,GPIO_PIN0,GPIO_PIN_INPUT,GPIO_INPUT_PULLUP);
	/*Configuration for pin 1,2,4 for output pushpull*/
	MGPIO_voidSetPinDirection(GPIO_PORTA,GPIO_PIN1,GPIO_PIN_OUTPUT_10MHZ,GPIO_OUTPUT_PUSHPULL);

	MGPIO_voidSetPinDirection(GPIO_PORTA,GPIO_PIN2,GPIO_PIN_OUTPUT_2MHZ,GPIO_OUTPUT_PUSHPULL);

	MGPIO_voidSetPinDirection(GPIO_PORTA,GPIO_PIN7,GPIO_PIN_OUTPUT_2MHZ,GPIO_OUTPUT_PUSHPULL);
	/*Setting value for pin 1 low and pin 2 High*/
	MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN1,GPIO_LOW);

	MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN2,GPIO_HIGH);

	MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN7,GPIO_HIGH);

	/*Intialization for UART*/

	MUSART_voidInit();
	/*Intialization for Systick Timer*/
	SYSTICK_ErrorstatusConfiguration();
	/*Switch1 is variable simulates an input to be sent to Raspberry pi as checking for updtae*/
	/*To start or wait for it's value to be 0*/
	volatile u8 switch1=0;
	/*This variable if set and switch1 is off system will reset to jumpp to bootloader section*/
	volatile u8 ResetReqToUpdate=0;

	volatile u8 local_u8counter=0;
	u8 RecBuffer[10]={0};
	u8 local_recieve=0;

  // At this stage the system clock should have already been configured
  // at high speed.

  // Infinite loop
  while (1)
    {
	  MGPIO_voidGetPinValue(GPIO_PORTA,GPIO_PIN0,&switch1);

	 	  local_recieve=MUSART_u8Recieve(&(RecBuffer[local_u8counter]));
	 	  if(local_recieve==1)
	 	  {		local_u8counter++;
	 	  }
	 	  if(RecBuffer[0]=='N' && RecBuffer[1]=='E' && RecBuffer[2]=='W' && local_u8counter<=3 )
	 		  {
	 		  	  SYSTICK_voidSetBusyWait(900);
	 		  	MUSART_voidSendString("Switch 1\n");
	 			  SYSTICK_voidSetBusyWait(100);
	 			  MUSART_voidTransmit((switch1+48));

	 		  }

	 	  if( (RecBuffer[3] =='1') )
	 		  {
	 			  ResetReqToUpdate=1;
	 		  }
	 	  if(RecBuffer[3]=='B')
	 		  {
	 		  local_u8counter=0;
	 		  /*Clearing Recieve uart array*/
	 			  RecBuffer[0]='0';
	 			  RecBuffer[1]='0';
	 			  RecBuffer[2]='0';
	 			  RecBuffer[3]='0';
	 		  }
	 		  if(local_u8counter>=9)
	 		  {/*Reseting Counter of actual saved array*/
	 			  local_u8counter=0;
	 		  }

	 	  if(switch1==0 && ResetReqToUpdate== 1)
	 	  {
	 		  //Reset micro controller to jump to bootloader
	 		  Reset_system();

	 	  }
    }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
