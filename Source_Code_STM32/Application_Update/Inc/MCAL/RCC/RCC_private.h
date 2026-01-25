#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_

#define BASE_ADDRESS            0x40021000

#define    RCC_CR     			*((volatile u32*)BASE_ADDRESS)

#define    RCC_CFGR     		*((volatile u32*)BASE_ADDRESS + 0x04)

#define    RCC_CIR     			*((volatile u32*)BASE_ADDRESS +0x08)

#define    RCC_APB2RSTR     	*((volatile u32*)BASE_ADDRESS +0x0C )

#define    RCC_APB1RSTR     	*((volatile u32*)BASE_ADDRESS +0x10 )

#define    RCC_AHBENR     		*((volatile u32*)BASE_ADDRESS +0x14 )

#define    RCC_APB2ENR     		*((volatile u32*)BASE_ADDRESS +0x18 )

#define    RCC_APB1ENR     		*((volatile u32*)BASE_ADDRESS +0x1C )

#define    RCC_BDCR     		*((volatile u32*)BASE_ADDRESS +0x20 )

#define    RCC_CSR				*((volatile u32*)BASE_ADDRESS +0x24 )

#define RCC ((volatile RCC_t *)0x40021000)

typedef struct
{
	volatile u32 CR;
	volatile u32 CFGR;
	volatile u32 CIR;
	volatile u32 APB2RSTR;
	volatile u32 APB1RSTR;
	volatile u32 AHBENR;
	volatile u32 APB2ENR;
	volatile u32 APB1ENR;
	volatile u32 BDCR;
	volatile u32 CSR;

}RCC_t;

/**************************************************/
/*                  REGISTER CR                   */
/**************************************************/
 /*HSI ready bit*/
#define CLK_HSI_RDY_BIT			1

/*HSE ready bit*/
#define CLK_HSE_RDY_BIT			17

/*PLL ready bit*/
#define CLK_PLL_RDY_BIT			25

/**************************************************/
/*first bit in select switch for clock source select to use in register mask*/
#define SYSTEM_CLOCK_SWITCH_BIT     0
/***************************************************/

/****************************************************/
/*Values to set in CFGR Bit to Select Clock Source  */
/*HSI:0b00                                          */
/*HSE:0b01                                          */
/*PLL:0b10                                          */
/****************************************************/
#define HSI_CLK_SELECT			0
#define HSE_CLK_SELECT			1
#define PLL_CLK_SELECT			2
#define CLEARING_VALUE_SW		3
/*Values for local_u8Status Check for clock ready or not*/
#define CLK_RDY         	1
#define CLK_NOT_RDY			0

/*********************************************************/
#define PLL_EN_BIT              24
#define	HSE_EN_BIT				16
#define	HSI_EN_BIT				0

/*****************************/
/*PRESCALER FOR PLL*/
#define PLL_CLEARING_VALUE     		     63
#define PLL_FIRST_BIT          			 16
#define PLL_MULFACTOR_BIT				 18
#define PLL_SOURCE_SELECT_BIT			 16
#define PLL_HSEDIVIDED_BIT 				 17
/***********************************************/
#define BUSES_REG_PRESCALER_CLEARING_VALUE	1023

#define AHB_PRESCALER_FIRST_BIT         4
#define APB1_PRESCALER_FIRST_BIT        8
#define APB2_PRESCALER_FIRST_BIT        11


#define HSI_DIVIDED_BY_2			0

/**************************************************/
/****************************************************************************/
                /*AHB ENABLE REGISTER PERIPHERIALS*/
/***************************************************************************/

#define ETHMACRXEN_BIT 16
#define ETHMACTXEN_BIT 15
#define ETHMACEN_BIT   14
#define OTGFSEN_BIT    12
#define CRCEN_BIT      6
#define FLITFEN_BIT    4
#define SRAMEN_BIT     2
#define DMA2EN_BIT     1
#define DMA1EN_BIT     0


/****************************************************************************/
                /*APB1 ENABLE REGISTER PERIPHERIALS*/
/***************************************************************************/

#define DACEN_BIT      29
#define PWREN_BIT      28
#define BKPEN_BIT      27
#define CAN2EN_BIT     26
#define CAN1EN_BIT     25
#define I2C2EN_BIT     22
#define I2C1EN_BIT     21
#define UART5EN_BIT    20
#define UART4EN_BIT    19
#define USART3EN_BIT   18
#define UART2EN_BIT    17
#define SPI3EN_BIT     15
#define SPI2EN_BIT     14
#define WWDGEN_BIT     11
#define TIM7EN_BIT     5
#define TIM6EN_BIT     4
#define TIM5EN_BIT     3
#define TIM4EN_BIT     2
#define TIM3EN_BIT     1
#define TIM2EN_BIT     0


/****************************************************************************/
                /*APB2 ENABLE REGISTER PERIPHERIALS*/
/***************************************************************************/

#define AFIOEN_BIT     0
#define IOPA_BIT       2
#define IOPB_BIT       3
#define IOPC_BIT       4
#define IOPD_BIT       5
#define SPI1EN_BIT     12
#define USARTEN_BIT    14


#endif /* RCC_PRIVATE_H_ */
