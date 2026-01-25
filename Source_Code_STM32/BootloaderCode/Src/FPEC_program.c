#include "../Inc/LIB/BIT_MATH.h"
#include "../Inc/LIB/STD_TYPES.h"

#include "../Inc/MCAL/FPEC/FPEC_config.h"
#include "../Inc/MCAL/FPEC/FPEC_interface.h"
#include "../Inc/MCAL/FPEC/FPEC_private.h"



void FPEC_voidEraseBank1 (void)
{
	u8 i;
	
	for (i=4;i<34;i++)
	{
		FPEC_voidFlashPageErase(i);
	}
}

void FPEC_voidEraseBank2(void)
{
	u8 i;

	for (i=34;i<64;i++)
	{
		FPEC_voidFlashPageErase(i);
	}
}

void FPEC_voidFlashPageErase(u8 Copy_u8PageNumber)
{
	/* Wait Busy Flag */
	while (GET_BIT(FPEC->SR,BUSYWAIT_BIT) == 1);

	/* Check if FPEC is locked or not */
	if ( GET_BIT(FPEC->CR,LOCK_BIT) == 1)
	{
		FPEC -> KEYR = KEY1 ;
		FPEC -> KEYR = KEY2 ;
	}
	
	/* Page Erase Operation */
	SET_BIT(FPEC->CR,PAGE_EARSE_BIT);

	/* Write Page address */
	FPEC->AR = (u32)(Copy_u8PageNumber * 1024) + 0x08000000 ;

	/* Start operation */
	SET_BIT(FPEC->CR,START_BIT);

	/* Wait Busy Flag */
	while (GET_BIT(FPEC->SR,BUSYWAIT_BIT) == 1);

	/* EOP */
	SET_BIT(FPEC->SR,EOP_BIT);
	CLR_BIT(FPEC->CR,PAGE_EARSE_BIT);
}

void FPEC_voidFlashWrite(u32 Copy_u32Address, u16* Copy_u16Data, u8 Copy_u8Length)
{
	u8 i;
	volatile u16 Temp;

	while (GET_BIT(FPEC->SR,BUSYWAIT_BIT) == 1);

	/* Check if FPEC is locked or not */
	if ( /* FPEC_CR->BitAccess.LOCK == 1 */ GET_BIT(FPEC->CR,LOCK_BIT) == 1 )
	{
		FPEC -> KEYR = KEY1 ;
		FPEC -> KEYR = KEY2 ;
	}
	
	
	for (i = 0; i< Copy_u8Length; i++)
	{
		/* Write Flash Programming */
		SET_BIT(FPEC->CR,PROGGRAMMING_BIT);

		/* Half word operation */
		Temp = Copy_u16Data[i];
		*((volatile u16*)Copy_u32Address) = Copy_u16Data[i];
		Copy_u32Address += 2 ;

		/* Wait Busy Flag */
		while (GET_BIT(FPEC->SR,BUSYWAIT_BIT) == 1);
	
		/* EOP */
		SET_BIT(FPEC->SR,EOP_BIT);
		CLR_BIT(FPEC->CR,PROGGRAMMING_BIT);
	}

}
