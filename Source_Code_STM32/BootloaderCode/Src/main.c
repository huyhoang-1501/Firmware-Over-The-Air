#include "../Inc/LIB/BIT_MATH.h"
#include "../Inc/LIB/STD_TYPES.h"
#include "../Inc/MCAL/RCC/RCC_interface.h"
#include "../Inc/MCAL/GPIO/GPIO_interface.h"
#include "../Inc/MCAL/SYSTICK/STK_interface.h"
#include "../Inc/MCAL/USART/USART_interface.h"
#include "../Inc/MCAL/FPEC/FPEC_interface.h"
#include "../Inc/Parse_Interface.h"

volatile u8  u8RecBuffer[100]   ;
volatile u8  u8RecCounter    = 0;
volatile u8  u8TimeOutFlag   = 0;
volatile u16 u16TimerCounter = 0;
volatile u8  u8BLWriteReq    = 1;
typedef void (*Function_t)(void);
Function_t addr_to_call = 0;
/*Bootloader to jump to bank1*/
void JUMP_TO_BANK1(void)
{
#define SCB_VTOR   *((volatile u32*)0xE000ED08)

	SCB_VTOR = 0x08001000;

	addr_to_call = *(Function_t*)(0x08001004);
	addr_to_call();
}

void JUMP_TO_BANK2(void)
{
#define SCB_VTOR   *((volatile u32*)0xE000ED08)

	SCB_VTOR = 0x08008800;

	addr_to_call = *(Function_t*)(0x08008804);
	addr_to_call();
}



void main(void)
{
	u8 Local_u8RecStatus;
	u8 Local_CheckResult;
	u8 x=0;

	/*Initialize RCC */
	RCC_voidInitSysClock();

	/*Initialize Peripherals CLK  */
	RCC_voidEnableClock(RCC_APB2,USART1EN); /* USART1 */
	RCC_voidEnableClock(RCC_APB2,IOPAEN);   /* PortA  */
	RCC_voidEnableClock(RCC_AHB,FLITFEN);   /* FPEC   */


	MGPIO_VidSetPinDirection(GPIOA,PIN9,OUTPUT_SPEED_2MHZ_AFPP);   /* TX AFPP           */
	MGPIO_VidSetPinDirection(GPIOA,PIN10,INPUT_FLOATING);          /* RC Input Floating */
	MGPIO_VidSetPinDirection(GPIOA,PIN1,OUTPUT_SPEED_2MHZ_PP);     /* OUTPUT PUSH PULL  */
	MGPIO_VidSetPinValue(GPIOA,PIN1,HIGH);

	/*Initialize USART*/
	MUSART1_voidInit();

	/*Initialize SYSTICK*/
	MSTK_voidInit();

	/*If Nothing received for 15 sec jump to bank 1*/
	MSTK_voidSetIntervalSingle(15000000,JUMP_TO_BANK1);

	while(u8TimeOutFlag == 0)
	{

		Local_u8RecStatus = MUSART1_u8Receive( &(u8RecBuffer[u8RecCounter]) );
		if (Local_u8RecStatus == 1)
		{
			MSTK_voidStopInterval();

			if(u8RecBuffer[u8RecCounter] == '\n')
			{


				Local_CheckResult = BootLoader_CheckSum(u8RecBuffer , (u8RecCounter-1));
				if (Local_CheckResult == 1 )
			{
					x=1;
				if (u8BLWriteReq == 1)
				{
					FPEC_voidEraseBank1();
					u8BLWriteReq = 0;
				}

				/* Parse */
				Parser_voidParseRecord(u8RecBuffer);
				MUSART1_voidTransmit("o");
				u8RecCounter = 0;

			}
				else
				{
					MGPIO_VidSetPinValue(GPIOA,PIN1,LOW);
					x=2;
				}
			}

			else
			{
				u8RecCounter ++ ;
			}

			if (x==1)
				{
					MSTK_voidSetIntervalSingle(10000000,JUMP_TO_BANK1);

				}
				//problem in transmission
			else if (x==2)
				{
					MSTK_voidSetIntervalSingle(100,JUMP_TO_BANK2);

				}
		}

		else
		{

		}
	}
}
