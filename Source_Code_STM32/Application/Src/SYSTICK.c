/*Include Standard libraries*/
#include "../Inc/LIB/bit_math.h"
#include "../Inc/LIB/std_types.h"
#include "../Inc/MCAL/SYSTICK/SYSTICK_interface.h"
#include "../Inc/MCAL/SYSTICK/SYSTICK_private.h"
#include "../Inc/MCAL/SYSTICK/SYSTICK_configuration.h"

static void(*pf)(void)=NULL;

static u8 SYSTICK_u8ModeOfInterval;

Errorstatus SYSTICK_ErrorstatusConfiguration(void)
{
	u8 local_ErrorStatus=NOT_OK;
#if (INT_EN==ENABLE)
	SET_BIT(SYSTICK->CTRL,INTEN_BIT);
#else
	CLEAR_BIT(SYSTICK->CTRL,INTEN_BIT);
#endif
#if (SYSTICK_SELECT==ENABLE)
	SET_BIT(SYSTICK->CTRL,SYSTICKEN_BIT);
#else
	CLEAR_BIT(SYSTICK->CTRL,SYSTICKEN_BIT);
#endif
	#if(CLK_SOUCRE == AHB)
	SET_BIT(SYSTICK->CTRL,CLK_SOURCE_BIT);
	local_ErrorStatus=OK;
	#else
	CLEAR_BIT(SYSTICK->CTRL,CLK_SOURCE_BIT);
	local_ErrorStatus=OK;
	#endif

return local_ErrorStatus;
}

Errorstatus SYSTICK_ErrorstatusEnable(void)
{
	u8 local_ErrorStatus=NOT_OK;
	SET_BIT(SYSTICK->CTRL,SYSTICKEN_BIT);
	local_ErrorStatus=OK;
	return local_ErrorStatus;
	}


Errorstatus SYSTICK_ErrorstatusDisable(void)
{
	u8 local_ErrorStatus=NOT_OK;
	CLEAR_BIT(SYSTICK->CTRL,SYSTICKEN_BIT);
	local_ErrorStatus=OK;
	return local_ErrorStatus;
}

Errorstatus SYSTICK_ErrorstatusPreLoadSet(u32 copy_u32PreLoadValue)
{
	u8 local_ErrorStatus=NOT_OK;
#if (PRELOAD_SELECT==IMMEDIATE)

	SYSTICK->LOAD=copy_u32PreLoadValue;
	SYSTICK->VAL=CLEARING_REGISTER_VAL;
	local_ErrorStatus=OK;
#else

	SYSTICK->LOAD=copy_u32PreLoadValue;
	local_ErrorStatus=OK;
#endif

return local_ErrorStatus;

}

void SYSTICK_voidSetBusyWait(u32 copy_u32TickNumber)
{

	SYSTICK->LOAD=copy_u32TickNumber;
	SYSTICK->VAL=CLEARING_REGISTER_VAL;
	SET_BIT(SYSTICK->CTRL,SYSTICKEN_BIT);

	while((GET_BIT(SYSTICK->CTRL,UNDER_FLOW_FLAG)==0));

	CLEAR_BIT(SYSTICK->CTRL,SYSTICKEN_BIT);
	SYSTICK->LOAD=0;
	SYSTICK->VAL=CLEARING_REGISTER_VAL;


	}

void SYSTICK_voidDelay_ms(u32 Time_MilliSecond)
{

	u32 local_NumberOfTicks;
	CLEAR_BIT(SYSTICK->CTRL,CLK_SOURCE_BIT);

	local_NumberOfTicks=Time_MilliSecond*(1000);
	SYSTICK->LOAD=local_NumberOfTicks;
	SYSTICK->VAL=CLEARING_REGISTER_VAL;
	SET_BIT(SYSTICK->CTRL,SYSTICKEN_BIT);

	while((GET_BIT(SYSTICK->CTRL,UNDER_FLOW_FLAG)==0));

	CLEAR_BIT(SYSTICK->CTRL,SYSTICKEN_BIT);
	SYSTICK->LOAD=0;
	SYSTICK->VAL=CLEARING_REGISTER_VAL;


}

void SYSTICK_voidSetIntervalSingle(u32 copy_u32TickNumber,void(*Ptr)(void))
{
	CLEAR_BIT(SYSTICK->CTRL,SYSTICKEN_BIT);

	SYSTICK->VAL=CLEARING_REGISTER_VAL;

	SYSTICK->LOAD=copy_u32TickNumber;



	SET_BIT(SYSTICK->CTRL,SYSTICKEN_BIT);

	SYSTICK_SetCallBackFunction(Ptr);

	SYSTICK_u8ModeOfInterval=SYSTICK_SINGLE_INTERVAL;

	SET_BIT(SYSTICK->CTRL,INTEN_BIT);



}

void SYSTICK_voidSetIntervalPeriodic(u32 copy_u32TickNumber,void(*Copy_Ptr)(void))
{

	CLEAR_BIT(SYSTICK->CTRL,SYSTICKEN_BIT);

	SYSTICK->VAL=CLEARING_REGISTER_VAL;

	SYSTICK->LOAD=copy_u32TickNumber;



	SET_BIT(SYSTICK->CTRL,SYSTICKEN_BIT);

	SYSTICK_SetCallBackFunction(Copy_Ptr);

	SYSTICK_u8ModeOfInterval=SYSTICK_PERIODIC_INTERVAL;

	SET_BIT(SYSTICK->CTRL,INTEN_BIT);



}


void SYSTICK_SetCallBackFunction(u32 *copy_Ptrfunc)
{
	pf=copy_Ptrfunc;
}

void SysTick_Handler(void)
{
	u8 Local_u8Temp;
if (SYSTICK_u8ModeOfInterval == SYSTICK_SINGLE_INTERVAL)
{
	CLEAR_BIT(SYSTICK->CTRL,SYSTICKEN_BIT);

	CLEAR_BIT(SYSTICK->CTRL,INTEN_BIT);

	SYSTICK->VAL=CLEARING_REGISTER_VAL;

	SYSTICK->LOAD=0;

}
	pf();

/*Clear interrupt Flag*/
Local_u8Temp=GET_BIT(SYSTICK->CTRL,UNDER_FLOW_FLAG);

}

u32 SYSTICK_voidGetRemainingTime(void)
{
	u32 local_u32RemainingTime;

	local_u32RemainingTime=SYSTICK->VAL;

	return local_u32RemainingTime;
}


u32 SYSTICK_voidGetElapsedTime(void)
{
	u32 local_u32ElapsedTime;

	local_u32ElapsedTime=SYSTICK->LOAD - SYSTICK->VAL;

	return local_u32ElapsedTime;
}

/*To stop Function of Periodic interval*/

void SYSTICK_voidStopInterval(void)
{
	CLEAR_BIT(SYSTICK->CTRL,INTEN_BIT);

	CLEAR_BIT(SYSTICK->CTRL,SYSTICKEN_BIT);

	SYSTICK->VAL=CLEARING_REGISTER_VAL;

	SYSTICK->LOAD=0;


}


