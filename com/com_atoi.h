/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __COM_ATOI_H
#define __COM_ATOI_H


#include "com_typedef.h"







//===================================================

// "0-9 a-f  A-F"  --> 0-15
extern u8 hexChar2Byte( u8 hexChar, u8 *pByte );




// "f3" -> 0xF3   "0f" -> 0x0F
extern u8 hexStr2U8( u8 *str, u8 *pByte );

extern u8 hexStrToU8buf( u8  *str, u32 len,  u8 *pU8buf );


// "f3B5" -> 0xF3B5
extern u8 hexStr2U16( u8 *str, u16 *pU16 );


// "f3B5CA00" -> 0xF3B5CA00
extern u8 hexStr2U32( u8 *str, u32 *pU32 );

//===================================================
// 123 -> "123"
extern void dec2str( u32 num, u8 *str );

// 100 -> "64"
extern void decU8toHexStr( u8 num, u8 *str );

// 100 -> "0064"
extern void decU16toHexStr( u16 num, u8 *str );

// 100 -> "00000064"
extern void decU32toHexStr( u32 num, u8 *str );


// "123"->123
extern u32 str2Dec( u8 *str );


// "12.3"->12.3
extern u32 str2float( u8  *str );



#endif

