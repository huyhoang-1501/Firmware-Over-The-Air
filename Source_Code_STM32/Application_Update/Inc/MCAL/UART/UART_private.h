#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_


#define USART     ((volatile USART_t*)0x40013800)


typedef struct
{
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GTPR;
}USART_t;

#endif /* UART_PRIVATE_H_ */
