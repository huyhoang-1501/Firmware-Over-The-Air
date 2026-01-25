/*
 * RCC_interface.h
 *
 *  Created on: Feb 14, 2022
 *      Author: nourhan
 */

#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_



/************************************************************************************/
/*Function:MRCC_Init                                                                */
/*Argument:void                                                                     */
/*return:void                                                                       */
/*Desc:Initialization of RCC with pre-configured configurations                     */
/************************************************************************************/

void MRCC_Init(void);




/************************************************************************************/
/*Function:MRCC_u8CheckReady                                                        */
/*Argument:copy_u8CLK                                                               */
/*return:Status of clock (CLK_RDY,CLK_NOT_RDY)                                      */
/*Desc:Synch Non-blocking function Check on status of clock is ready to use or not  */
/*options: HSI_RDY  HSE_RDY  PLL_RDY                                                */
/************************************************************************************/

u8 MRCC_CheckReady(u8 copy_u8CLK);

/**************************************************************/
/*Function:MRCC_voidSetClkSource                              */
/*Argumet:copy_u8ClkSource                                    */
/*return:void                                                 */
/*Desc:Function Select which clock to be used as system clock */
/*options: HSI_CLK_SELECT , HSE_CLK_SELECT , PLL_CLK_SELECT   */
/**************************************************************/

void MRCC_voidSetClkSource(u8 copy_u8ClkSource);

/***************************************************************/
/*Function:MRCC_voidSetClkStatus                               */
/*Arguments:copy_u8ClkSource, copy_u8Status                    */
/*return:void                                                  */
/*Desc:Function to set clock on                                */
/*options: copy_u8ClkSource:(HSI_CLK,HSE_CLK,PLL_CLK)          */
/*options: copy_u8Status(CLK_ENABLE,CLOCK_DISABLE)             */
/***************************************************************/

void MRCC_voidSetClkStatus(u8 copy_u8ClkSource,u8 copy_u8Status);

/*******************************************************************************/
/*Function:MRCC_voidSetClkStatus                                               */
/*Arguments:copy_u8AHBPrescaler, copy_u8APB2Prescaler ,copy_u8APB1Prescaler    */
/*return:void                                                                  */
/*Desc:Function to set clock on                                                */
/*options: copy_u8ClkSource:(HSI_CLK,HSE_CLK,PLL_CLK)                          */
/*options: copy_u8Status(CLK_ENABLE,CLOCK_DISABLE)                             */
/*******************************************************************************/

void MRCC_SetBusesPreScalers(u8 copy_u8AHBPrescaler,u8 copy_u8APB2Prescaler,u8 copy_u8APB1Prescaler);


/****************************************************************************************************/
/*Function:MRCC_SetPLLConfiguration                                                                 */
/*Arguments:copy_u8PLLMulFactor, copy_u8PLLSource ,copy_u8HSEDivided                                */
/*return:void                                                                                       */
/*Desc:Function to set PLL Configurations                                                           */
/*options: copy_u8PLLMulFactor:PLL_MUL_BY_2, PLL_MUL_BY_3 ,PLL_MUL_BY_4 ,PLL_MUL_BY_5               */
/* PLL_MUL_BY_6, PLL_MUL_BY_7 , PLL_MUL_BY_8 , PLL_MUL_BY_9 , PLL_MUL_BY_10 , PLL_MUL_BY_11         */
/* PLL_MUL_BY_12 , PLL_MUL_BY_13 , PLL_MUL_BY_14 , PLL_MUL_BY_15 , PLL_MUL_BY_16                    */
/*options: copy_u8PLLSource:PLL_SOURCE_HSI_DIVIDED_BY_2 , PLL_SOURCE_HSE                            */
/*options: copy_u8HSEDivided: This argument is effective in case of copy_u8PLLSource=PLL_SOURCE_HSE */
/*option: HSE_DIVIDED_BY_2 , HSE_DIVIDED_BY_1                                                       */
/****************************************************************************************************/



void MRCC_SetPLLConfiguration(u8 copy_u8PLLMulFactor,u8 copy_u8PLLSource,u8 copy_u8HSEDivided);

/**********************************************************************************************/
/*Function:MRCC_voidSetPeripheralClock                                                        */
/*Arguments:copy_u8Bus, copy_u8Peripheral , copy_u8Status                                     */
/*Return:void                                                                                 */
/*Desc:This Function enables or disables Clock for selected peripheral                        */
/*options: copy_u8Bus: BUS_AHB , BUS_APB1 , BUS_APB2                                          */
/*options: copy_u8Peripheral                                                                  */
/*options: copy_u8Status: PERIPHERL_CLK_ON , PERIPHERL_CLK_OFF                                */
/**********************************************************************************************/
void MRCC_voidSetPeripheralClock(u8 copy_u8Bus, u8 copy_u8Peripheral, u8 copy_u8Status);



#define HSI_RDY			CLK_HSI_RDY_BIT

#define HSE_RDY			CLK_HSE_RDY_BIT

#define PLL_RDY			CLK_PLL_RDY_BIT

/*****************************************************************************/
/*AHB PRESCALER OPTIONS */
#define AHB_PRESCALER_DIVIDED_BY_1				0
#define AHB_PRESCALER_DIVIDED_BY_2				8
#define AHB_PRESCALER_DIVIDED_BY_4				9
#define AHB_PRESCALER_DIVIDED_BY_8				10
#define AHB_PRESCALER_DIVIDED_BY_16				11
#define AHB_PRESCALER_DIVIDED_BY_64				12
#define AHB_PRESCALER_DIVIDED_BY_128			13
#define AHB_PRESCALER_DIVIDED_BY_256			14
#define AHB_PRESCALER_DIVIDED_BY_512			15

/*****************************************************************************/
/*APB1 PRESCALER OPTIONS*/
#define APB1_PRESCALER_DIVIDED_BY_1        		0
#define APB1_PRESCALER_DIVIDED_BY_2		   		4
#define APB1_PRESCALER_DIVIDED_BY_4	 	   		5
#define APB1_PRESCALER_DIVIDED_BY_8        		6
#define APB1_PRESCALER_DIVIDED_BY_16       		7

/****************************************************************************/
/*APB2 PRESCALER OPTIONS*/
#define APB2_PRESCALER_DIVIDED_BY_1        		0
#define APB2_PRESCALER_DIVIDED_BY_2        		4
#define APB2_PRESCALER_DIVIDED_BY_4        		5
#define APB2_PRESCALER_DIVIDED_BY_8        		6
#define APB2_PRESCALER_DIVIDED_BY_16       		7
/***************************************************************************/
/*PLL MULTIPLICATION FACTOR Macros for PLL_u8MulFactor*/

#define PLL_MUL_BY_2							0
#define PLL_MUL_BY_3							1
#define PLL_MUL_BY_4							2
#define PLL_MUL_BY_5							3
#define PLL_MUL_BY_6							4
#define PLL_MUL_BY_7							5
#define PLL_MUL_BY_8							6
#define PLL_MUL_BY_9							7
#define PLL_MUL_BY_10							8
#define PLL_MUL_BY_11							9
#define PLL_MUL_BY_12							10
#define PLL_MUL_BY_13							11
#define PLL_MUL_BY_14							12
#define PLL_MUL_BY_15							13
#define PLL_MUL_BY_16							14
#define PLL_MUL_BY_16							15

/****************************************************************************/
/*PLL Source Argument Macros for PLL_u8ClkSource */
#define PLL_SOURCE_HSE							1
#define PLL_SOURCE_HSI_DIVIDED_BY_2				0

/****************************************************************************/
/*PLL DIVIDED by macros for HSE copy_u8HSEDivided*/
#define HSE_DIVIDED_BY_1						0
#define HSE_DIVIDED_BY_2						1
/*****************************************************************************/
/*Bus Name Macros for argument copy_u8Bus*/
#define BUS_AHB									0

#define BUS_APB1								1

#define BUS_APB2								2
/*****************************************************************************/
/*Macros for argument peripheral status copy_u8Status */

#define CLK_OFF						0

#define CLK_ON						1
/****************************************************************************/
                /*AHB ENABLE REGISTER PERIPHERIALS*/
/***************************************************************************/

#define ETHMACRXEN     ETHMACRXEN_BIT
#define ETHMACTXEN 	   ETHMACTXEN_BIT
#define ETHMACEN       ETHMACEN_BIT
#define OTGFSEN		   OTGFSEN_BIT
#define CRCEN      	   CRCEN_BIT
#define FLITFEN        FLITFEN_BIT
#define SRAMEN     	   SRAMEN_BIT
#define DMA2EN     	   DMA2EN_BIT
#define DMA1EN     	   DMA1EN_BIT


/****************************************************************************/
                /*APB1 ENABLE REGISTER PERIPHERIALS*/
/***************************************************************************/

#define DACEN      DACEN_BIT
#define PWREN      PWREN_BIT
#define BKPEN      BKPEN_BIT
#define CAN2EN     CAN2EN_BIT
#define CAN1EN     CAN1EN_BIT
#define I2C2EN     I2C2EN_BIT
#define I2C1EN     I2C1EN_BIT
#define UART5EN    UART5EN_BIT
#define UART4EN    UART4EN_BIT
#define USART3EN   USART3EN_BIT
#define UART2EN    UART2EN_BIT
#define SPI3EN     SPI3EN_BIT
#define SPI2EN     SPI2EN_BIT
#define WWDGEN     WWDGEN_BIT
#define TIM7EN     TIM7EN_BIT
#define TIM6EN     TIM6EN_BIT
#define TIM5EN     TIM5EN_BIT
#define TIM4EN     TIM4EN_BIT
#define TIM3EN     TIM3EN_BIT
#define TIM2EN     TIM2EN_BIT


/****************************************************************************/
                /*APB2 ENABLE REGISTER PERIPHERIALS*/
/***************************************************************************/

#define AFIOEN     AFIOEN_BIT
#define IOPA       IOPA_BIT
#define IOPB       IOPB_BIT
#define IOPC       IOPC_BIT
#define IOPD       IOPD_BIT
#define SPI1EN     SPI1EN_BIT
#define USARTEN    USARTEN_BIT





#endif /* RCC_INTERFACE_H_ */
