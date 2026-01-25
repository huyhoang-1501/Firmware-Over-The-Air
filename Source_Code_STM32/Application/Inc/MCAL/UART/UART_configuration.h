#ifndef UART_CONFIGURATION_H_
#define UART_CONFIGURATION_H_


#define F_CPU 8000000
#define USART1_BAUD_RATE   (u32)9600


/*Configuration for data length*/
#define WORD_LENGTH			EIGHT_DATA_BITS

#define NINE_DATA_BITS		0

#define EIGHT_DATA_BITS		1

/*Configuration for Parity*/
#define PARITY_CONTROL   DISABLE

#define DISABLE      0
#define ENABLE       1
#define PARITY_TYPE		  EVEN

#define EVEN		0

#define ODD			1

/*Configuration for stop bits*/
#define STOP_BITS		ONE_STOP_BIT

#define ONE_STOP_BIT				0

#define HALF_STOP_BIT				1

#define TWO_STOP_BIT				2

#define ONE_AND_HALF_STOP_BIT		3

/*Configuration for transmission mode*/
#define TRANSMISSION_MODE       FULL_DUPLEX

#define HALF_DUPLEX				0
#define FULL_DUPLEX				1
#endif /* UART_CONFIGURATION_H_ */
