
#ifndef PARSE_INTERFACE_H_
#define PARSE_INTERFACE_H_



/*******************************************************************/
/*                                                                 */
/* Description : This Function Check on Record type                */
/*				if it is upper address or data                     */
/* Return    : Void                                                */
/* Arguments : Saved Record in Array                               */
/*                                                                 */
/*******************************************************************/
void Parser_voidParseRecord(u8* Copy_u8BufData) ;


/*******************************************************************/
/*                                                                 */
/* Description : This Fuction Gets Upper Address                   */
/* Return    : Void                                                */
/* Arguments : Saved Record in Array                               */
/*                                                                 */
/*******************************************************************/
void ParseUpperAddress(u8* Copy_u8BufData) ;


/*******************************************************************/
/*                                                                 */
/* Description : This Fuction analyise recieced record :           */
/* 				CC & Lower Address & Record Type & Data            */
/* Return    : Void                                                */
/* Arguments : Saved Record in Array                               */
/*                                                                 */
/*******************************************************************/
void ParseData(u8* Copy_u8BufData) ;


/*******************************************************************/
/*                                                                 */
/* Description : This Fuction Convert from Asci  TO HE             */
/* Return    : u8 (HEX Result)                                                 */
/* Arguments : Array Elements (IN ASCII)                          */
/*                                                                 */
/*******************************************************************/
u8 AsciToHex(u8 Copy_u8Asci) ;


/*******************************************************************/
/*                                                                 */
/* Description : This Function Calculate CheckSum                  */
/* Return    : u8 (1 OR 0) According to Checksum  Result           */
/* Arguments :  Record Stored in Array and ArrayLength             */
/*                                                                 */
/*******************************************************************/
u8 BootLoader_CheckSum (u8 *arr , u8 Count);


#endif /* PARSE_INTERFACE_H_ */
