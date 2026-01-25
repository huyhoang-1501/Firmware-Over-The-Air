#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

/****************************************************************************/
/*Function Name:MUSART_voidInit											 	*/
/*Function Desc:Intialization for UART with Pre-configured Configurations	*/
/*Arguments:void															*/
/*Return:void																*/
/****************************************************************************/
void MUSART_voidInit(void);

/****************************************************************************/
/*Function Name:MUSART_voidTransmit											*/
/*Function Desc:Sends one character using uart								*/
/*Arguments:copy_data to be sent											*/
/*Return:void																*/
/****************************************************************************/



void MUSART_voidTransmit(u8 copy_data);

/****************************************************************************/
/*Function Name:MUSART_voidSendString										*/
/*Function Desc:Sends String using uart										*/
/*Arguments:*copy_Strinptr address to the string to be sent					*/
/*Return:void																*/
/****************************************************************************/

void MUSART_voidSendString(u8 *copy_Strinptr);

/****************************************************************************/
/*Function Name:MUSART_u8Recieve											*/
/*Function Desc:Recieve data using uart										*/
/*Arguments:*Copy_u8Data address of buffer to save data in					*/
/*Return:received(1) or didn't recieve (0)									*/
/****************************************************************************/


u8 MUSART_u8Recieve(u8 *Copy_u8Data);

/*Control Register 1*/
#define  RECIEVE_ENABLE			2

#define	TRANSMIT_ENABLE			3

#define	PARITY_SELECTION		9

#define	PARITY_CONTROL_ENABLE	10

#define	WORD_LENGTH_CONTROL		12

#define	UART_ENABLE				13

/*Control Register 2*/

#define	STOP_BIT_1			12

#define STOP_BIT_2			13
/*Status Register*/

#define	TRANSMISSION_COMPLETE		6

#define	RECIEVE_NOT_EMPTY			5


#endif /* UART_INTERFACE_H_ */
