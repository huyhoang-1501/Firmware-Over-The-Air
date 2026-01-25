#include "../Inc/LIB/STD_TYPES.h"
#include "../Inc/LIB/BIT_MATH.h"
#include "../Inc/MCAL/FPEC/FPEC_interface.h"
#include "../Inc/Parse_Interface.h"




/* Array to Receive Hex File in */
u16 Data[100] = {0};


u32 Address= 0x08000000;

u8 AsciToHex(u8 Copy_u8Asci)
{
	u8 Result;
	if ( (Copy_u8Asci >= 48) && (Copy_u8Asci <= 57) )
	{
		Result = Copy_u8Asci - 48;
	}

	else
	{
		Result = Copy_u8Asci - 55;
	}

	return Result;
}


void ParseData(u8* Copy_u8BufData)
{
	u8 DigitLow,DigitHigh,CC,i;
	u8 DataDigit0,DataDigit1,DataDigit2,DataDigit3;
	u8 DataCounter = 0;

	/* Get Character Count */
	DigitHigh = AsciToHex (Copy_u8BufData[1]);
	DigitLow  = AsciToHex (Copy_u8BufData[2]);
	CC        = (DigitHigh<<4) | DigitLow ;

	/* Get Address */
	DataDigit0 = AsciToHex (Copy_u8BufData[3]);
	DataDigit1 = AsciToHex (Copy_u8BufData[4]);
	DataDigit2 = AsciToHex (Copy_u8BufData[5]);
	DataDigit3 = AsciToHex (Copy_u8BufData[6]);

	/* Clear Low Part of Address */
	Address = Address & 0xFFFF0000;
	Address = Address | (DataDigit3) | (DataDigit2 << 4) | (DataDigit1 << 8) | (DataDigit0<<12);

	for (i=0;i<CC/2; i++)
	{
		DataDigit0 = AsciToHex (Copy_u8BufData[4*i+9 ]);
		DataDigit1 = AsciToHex (Copy_u8BufData[4*i+10]);
		DataDigit2 = AsciToHex (Copy_u8BufData[4*i+11]);
		DataDigit3 = AsciToHex (Copy_u8BufData[4*i+12]);

		Data[DataCounter] = (DataDigit3 << 8) | (DataDigit2 << 12) | (DataDigit1) | (DataDigit0<<4);
		DataCounter++;
	}

	FPEC_voidFlashWrite(Address,Data,CC/2);
}

void ParseUpperAddress(u8* Copy_u8BufData)
{
	u8 DataDigit0,DataDigit1,DataDigit2,DataDigit3;

	/* Get Address */
	DataDigit0 = AsciToHex (Copy_u8BufData[3]);
	DataDigit1 = AsciToHex (Copy_u8BufData[4]);
	DataDigit2 = AsciToHex (Copy_u8BufData[5]);
	DataDigit3 = AsciToHex (Copy_u8BufData[6]);

	/* Clear Low Part of Address */
	Address = Address & (u32)0x0000FFFF;
	Address = Address | (u32)((u32)(DataDigit3 << 28) | (u32)(DataDigit2 << 24) | (u32)(DataDigit1 << 20) | (u32)(DataDigit0 << 16));
}

void Parser_voidParseRecord(u8* Copy_u8BufData)
{
	switch (Copy_u8BufData[8])
	{
	case '0': ParseData(Copy_u8BufData); break;
	case '4': ParseUpperAddress(Copy_u8BufData); break;
	}
}



/*Function to Check Checksum error*/
u8 BootLoader_CheckSum (u8 *arr , u8 Count)
{
	u8 CHECKSUM  = 0,SECOND_VAR=0,FIRST_VAR=0,COM_CHECKSUM=0 ;
	u8 LocalCheckResult=0;
	u8 i = 0 ;
	u16 D2igits = 0x00 ;

	for ( i = 1 ; i < Count - 2  ; i+=2 )
	{
	    int VAR2 = AsciToHex(arr[i+1] );
	    int VAR1 = AsciToHex(arr[i]) ;
	    //Store 2 hex digits
	    D2igits = VAR2 | (VAR1 << 4 );
	    CHECKSUM+=D2igits;

	}
	    //	1's Complement
		CHECKSUM = ~ CHECKSUM ;
		// 2's Complement
	    CHECKSUM += 1;

	     SECOND_VAR = AsciToHex(arr[Count-1]);
	     FIRST_VAR = AsciToHex(arr[Count-2]) ;

	   COM_CHECKSUM = SECOND_VAR | (FIRST_VAR  << 4 );

	    if (COM_CHECKSUM == CHECKSUM)
	    {

	    	LocalCheckResult= 1 ;
	    }
	    else
	    {
	    	LocalCheckResult= 0 ;

	    }

return LocalCheckResult;
}
