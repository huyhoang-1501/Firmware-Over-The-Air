#ifndef FPEC_INTERFACE
#define FPEC_INTERFACE

/*******************************************************************/
/*                                                                 */
/* Description : This Fuction Erase Whole Bank1 Area in the memory */
/* Return void , Take No Arguments                                 */
/*                                                                 */
/*******************************************************************/
void FPEC_voidEraseBank1 (void);

void FPEC_voidEraseBank2(void) ;


/*******************************************************************/
/*                                                                 */
/* Description : This Fuction Erase Only one page in Memory        */
/* Return    : Void                                                */
/* Arguments : Page Number (0 ~ 63)                                */
/*                                                                 */
/*******************************************************************/
void FPEC_voidFlashPageErase(u8 Copy_u8PageNumber);



/**********************************************************************************/
/*                                                                                */
/* Description : This Function Flash Line by Line from Hex File to Memory         */
/* Return    : Void                                                               */
/* Arguments : Address received from Hex file line ,                              */
/* 			   Data ,  CC/2                                                       */
/*                                                                                */
/**********************************************************************************/
void FPEC_voidFlashWrite(u32 Copy_u32Address, u16* Copy_u16Data, u8 Copy_u8Length);



/*BITS DEFINE */
    /*SR*/
#define BUSYWAIT_BIT     0
#define EOP_BIT          5

    /*CR*/
#define PROGGRAMMING_BIT 0
#define PAGE_EARSE_BIT   1
#define START_BIT        6
#define LOCK_BIT         7


/*LOCK SEUUENCE */
#define KEY1   0x45670123
#define KEY2   0xCDEF89AB



#endif
