/*Include Standard libraries*/

#include "../Inc/LIB/bit_math.h"
#include "../Inc/LIB/std_types.h"

/*Include header files of RCC */

#include "../Inc/MCAL/RCC/RCC_interface.h"
#include "../Inc/MCAL/RCC/RCC_private.h"
#include "../Inc/MCAL/RCC/RCC_configuration.h"

/************************************************************************************/
/*Function:MRCC_Init                                                                */
/*Argument:void                                                                     */
/*return:void                                                                       */
/*Desc:Initialization of RCC with pre-configured configurations                     */
/************************************************************************************/

void MRCC_Init(void)
{
	u8 local_u8ClkStatus=CLK_NOT_RDY;

	#if(CLK_SELECTED == HSE_CLK_SELECT)

		MRCC_voidSetClkStatus(HSE_CLK_SELECT,CLK_ON);
		local_u8ClkStatus=MRCC_CheckReady(HSE_RDY);
		if(local_u8ClkStatus!=CLK_NOT_RDY)
		{
		MRCC_voidSetClkSource(HSE_CLK_SELECT);
		MRCC_voidSetClkStatus(HSI_CLK_SELECT,CLK_OFF);
		MRCC_voidSetClkStatus(PLL_CLK_SELECT,CLK_OFF);

		MRCC_SetBusesPreScalers(AHB_PRESCALER,APB2_PRESCALER,APB1_PRESCALER);
		}
	#elif(CLK_SELECTED == HSI_CLK_SELECT)

		MRCC_voidSetClkStatus(HSI_CLK_SELECT,CLK_ON);
		local_u8ClkStatus=MRCC_CheckReady(HSI_RDY);
		if(local_u8ClkStatus != CLK_NOT_RDY)
		{
		MRCC_voidSetClkSource(HSI_CLK_SELECT);
		MRCC_voidSetClkStatus(HSE_CLK_SELECT,CLK_OFF);
		MRCC_voidSetClkStatus(PLL_CLK_SELECT,CLK_OFF);
		MRCC_SetBusesPreScalers(AHB_PRESCALER,APB2_PRESCALER,APB1_PRESCALER);
		}
	#elif(CLK_SELECTED == PLL_CLK_SELECT)
		#if(PLL_SOURCE_SELECT == HSI_CLK_SELECT )

		MRCC_voidSetClkStatus(HSI_CLK_SELECT,CLK_ON);
		local_u8ClkStatus=MRCC_CheckReady(HSI_RDY);
		if(local_u8ClkStatus != CLK_NOT_RDY)
		{
		MRCC_voidSetClkSource(HSI_CLK_SELECT);
		MRCC_voidSetClkStatus(HSE_CLK_SELECT,CLK_OFF);
		MRCC_voidSetClkStatus(PLL_CLK_SELECT,CLK_OFF);
		MRCC_SetPLLConfiguration(PLL_MUL_FACTOR,PLL_SOURCE_HSI_DIVIDED_BY_2,HSI_DIVIDED_BY_2);
		MRCC_SetBusesPreScalers(AHB_PRESCALER,APB2_PRESCALER,APB1_PRESCALER);
		MRCC_voidSetClkStatus(PLL_CLK_SELECT,CLK_ON);
		local_u8ClkStatus=MRCC_CheckReady(PLL_RDY);
		if(local_u8ClkStatus!=CLK_NOT_RDY)
		{
		MRCC_voidSetClkSource(PLL_CLK_SELECT);
		}
		}
		#elif(PLL_SOURCE_SELECT == HSE_CLK_SELECT)

			MRCC_voidSetClkStatus(HSE_CLK_SELECT,CLK_ON);
			local_u8ClkStatus=MRCC_CheckReady(HSE_RDY);

		if(local_u8ClkStatus!=CLK_NOT_RDY)
		{
			MRCC_voidSetClkSource(HSE_CLK_SELECT);
			MRCC_voidSetClkStatus(HSI_CLK_SELECT,CLK_OFF);
			MRCC_voidSetClkStatus(PLL_CLK_SELECT,CLK_OFF);
			MRCC_SetPLLConfiguration(PLL_MUL_FACTOR,PLL_SOURCE_HSE,HSE_DIVIDED);
			MRCC_SetBusesPreScalers(AHB_PRESCALER,APB2_PRESCALER,APB1_PRESCALER);
			MRCC_voidSetClkStatus(PLL_CLK_SELECT,CLK_ON);
			local_u8ClkStatus=MRCC_CheckReady(PLL_RDY);
			if(local_u8ClkStatus!=CLK_NOT_RDY)
			{
				MRCC_voidSetClkSource(PLL_CLK_SELECT);
			}
		}
		#endif
	#endif
}



/************************************************************************************/
/*Function:MRCC_u8CheckReady                                                        */
/*Argument:copy_u8CLK                                                               */
/*return:Status of clock                                                            */
/*Desc:Synch Non-blocking function Check on status of clock is ready to use or not  */
/*options: HSI_RDY  HSE_RDY  PLL_RDY                                                */
/************************************************************************************/

u8 MRCC_CheckReady(u8 copy_u8CLK)
{
	u8 local_u8Status=CLK_RDY;
	u32 local_u32Timeout=0;

	if(copy_u8CLK == HSI_RDY || copy_u8CLK== HSE_RDY || copy_u8CLK== PLL_RDY) //input validation
	{

		while(GET_BIT(RCC->CR,copy_u8CLK) ==  CLK_NOT_RDY)
		{
			local_u32Timeout++;						//time to break from function if CLK is still not ready
		if(local_u32Timeout == CLK_RDY_TIMEOUT)
		{
			local_u8Status=CLK_NOT_RDY;
			break;
		}
		}
	}
	else
		{
			local_u8Status=CLK_NOT_RDY;
		}
	return 	local_u8Status;
	}

/**************************************************************/
/*Function:MRCC_voidSetClkSource                              */
/*Argumet:copy_u8ClkSource                                    */
/*return:void                                                 */
/*Desc:Function Select which clock to be used as system clock */
/*options: HSI_CLK_SELECT , HSE_CLK_SELECT , PLL_CLK_SELECT   */
/**************************************************************/
void MRCC_voidSetClkSource(u8 copy_u8ClkSource)
{
	if(copy_u8ClkSource==HSE_CLK_SELECT || copy_u8ClkSource==HSI_CLK_SELECT || copy_u8ClkSource==PLL_CLK_SELECT )
	{
		RCC->CFGR &= ~(CLEARING_VALUE_SW<<SYSTEM_CLOCK_SWITCH_BIT); //Register clear System clock switch bits
		RCC->CFGR |= (copy_u8ClkSource<<SYSTEM_CLOCK_SWITCH_BIT);			//Register set clock selected
	}
	else
	{

	}
}
/***************************************************************/
/*Function:MRCC_voidSetClkStatus                               */
/*Arguments:copy_u8ClkSource, copy_u8Status                    */
/*return:void                                                  */
/*Desc:Function to set clock on                                */
/*options: copy_u8ClkSource:(HSI_CLK,HSE_CLK,PLL_CLK)          */
/*options: copy_u8Status(CLK_ENABLE,CLOCK_DISABLE)             */
/***************************************************************/

void MRCC_voidSetClkStatus(u8 copy_u8ClkSource,u8 copy_u8Status)
{
	if((copy_u8ClkSource==HSE_CLK_SELECT || copy_u8ClkSource==HSI_CLK_SELECT ||
		copy_u8ClkSource==PLL_CLK_SELECT) && (copy_u8Status==CLK_ON || copy_u8Status==CLK_OFF) )
	{
		switch(copy_u8ClkSource)
		{
			case HSI_CLK_SELECT:
				switch(copy_u8Status)
				{ case CLK_ON:
					SET_BIT(RCC->CR,HSI_EN_BIT);
					break;
				  case CLK_OFF:
					CLEAR_BIT(RCC->CR,HSI_EN_BIT);
					break;
				}
			break;

			case HSE_CLK_SELECT:
				switch(copy_u8Status)
				{
				case CLK_ON:
					SET_BIT(RCC->CR,HSE_EN_BIT);
						break;
    		    case CLK_OFF:
					CLEAR_BIT(RCC->CR,HSE_EN_BIT);
				}

			break;

			case PLL_CLK_SELECT:

				switch(copy_u8Status)
								{
				case CLK_ON:
				SET_BIT(RCC->CR,PLL_EN_BIT);
							break;
			    case CLK_OFF:
				CLEAR_BIT(RCC->CR,PLL_EN_BIT);
								}
							break;
		}
	}
	else
	{

	}


}

/*******************************************************************************/
/*Function:MRCC_voidSetClkStatus                                               */
/*Arguments:copy_u8AHBPrescaler, copy_u8APB2Prescaler ,copy_u8APB1Prescaler    */
/*return:void                                                                  */
/*Desc:Function to set clock on                                                */
/*options: copy_u8ClkSource:(HSI_CLK,HSE_CLK,PLL_CLK)                          */
/*options: copy_u8Status(CLK_ENABLE,CLOCK_DISABLE)                             */
/*******************************************************************************/


void MRCC_SetBusesPreScalers(u8 copy_u8AHBPrescaler,u8 copy_u8APB2Prescaler,u8 copy_u8APB1Prescaler)
{
	if((copy_u8AHBPrescaler>=0 && copy_u8AHBPrescaler<=15) && (copy_u8APB2Prescaler>=0 && copy_u8APB2Prescaler<=7)
			&& (copy_u8APB1Prescaler>=0 && copy_u8APB1Prescaler<=7))
	{
	RCC->CFGR &= ~(BUSES_REG_PRESCALER_CLEARING_VALUE<<AHB_PRESCALER_FIRST_BIT);

	RCC->CFGR |= ((copy_u8AHBPrescaler<<AHB_PRESCALER_FIRST_BIT)|

				(copy_u8APB1Prescaler<<APB1_PRESCALER_FIRST_BIT)|

				(copy_u8APB2Prescaler<<APB2_PRESCALER_FIRST_BIT));
	}
	else
	{

	}

}

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



void MRCC_SetPLLConfiguration(u8 copy_u8PLLMulFactor,u8 copy_u8PLLSource,u8 copy_u8HSEDivided)
{
	RCC->CFGR &= ~(PLL_CLEARING_VALUE<<PLL_FIRST_BIT);
	RCC->CFGR |=( (copy_u8PLLSource<<PLL_SOURCE_SELECT_BIT)
			  | (copy_u8PLLMulFactor<<PLL_MULFACTOR_BIT)
	          | (copy_u8HSEDivided<<PLL_HSEDIVIDED_BIT));
}




/**********************************************************************************************/
/*Function:MRCC_voidSetPeripheralClock                                                        */
/*Arguments:copy_u8Bus, copy_u8Peripheral , copy_u8Status                                     */
/*Return:void                                                                                 */
/*Desc:This Function enables or disables Clock for selected peripheral                        */
/*options: copy_u8Bus: BUS_AHB , BUS_APB1 , BUS_APB2                                          */
/*options: copy_u8Peripheral                                                                  */
/*options: copy_u8Status: CLK_ON , CLK_OFF                                                    */
/**********************************************************************************************/
void MRCC_voidSetPeripheralClock(u8 copy_u8Bus, u8 copy_u8Peripheral, u8 copy_u8Status)
{
	switch(copy_u8Bus)
	{
	case BUS_AHB:
		switch(copy_u8Status)
		{
		case CLK_ON:
			SET_BIT(RCC->AHBENR,copy_u8Peripheral);
			break;

		case CLK_OFF:
			CLEAR_BIT(RCC->AHBENR,copy_u8Peripheral);
			break;
		}
		break;
	case BUS_APB1:
		switch(copy_u8Status)
				{
				case CLK_ON:
					SET_BIT(RCC->APB1ENR,copy_u8Peripheral);
					break;

				case CLK_OFF:
					CLEAR_BIT(RCC->APB1ENR,copy_u8Peripheral);
					break;
				}
		break;
	case BUS_APB2:
		switch(copy_u8Status)
				{
				case CLK_ON:
					SET_BIT(RCC->APB2ENR,copy_u8Peripheral);
					break;

				case CLK_OFF:
					CLEAR_BIT(RCC->APB2ENR,copy_u8Peripheral);
					break;
				}
		break;
	}
}
