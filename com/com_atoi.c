/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#include "com_typedef.h"
#include "com_char.h"








//===================================================

// "0-9 a-f  A-F"  --> 0-15
u8 hexChar2Byte( u8  hexChar, u8 *pByte )
{
	u8  ch;

	ch = hexChar;
	
	if( isNumber( ch) )
	{
		*pByte = ch - '0';      // 0 -- 9
	}
	else if ( isHexUpper( ch ) )
	{
		*pByte = ch - 'A' + 10; // A -- Z
	}
	else if ( isHexLower( ch ) )
	{
		*pByte = ch - 'a' + 10; // a -- z
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}




// "f3" -> 0xF3   "0f" -> 0x0F
u8 hexStr2U8( u8  *str, u8 *pU8 )
{
	u8 n1, n2;

	if( hexChar2Byte(*str, &n1) == FALSE )
		return FALSE;
	
	if( hexChar2Byte( *(str+1), &n2) == FALSE )
		return FALSE;
	
	*pU8 = n1 * 16 + n2;

	return TRUE;
	
}


u8 hexStrToU8buf( u8  *str, u32 len,  u8 *pU8buf )
{
	u32 i;

	if( len < 2 )
		return FALSE;

	for( i = 0; i < len/2; i++ )
	{
		if( hexStr2U8( str + i*2, pU8buf + i) == FALSE )
			return FALSE;
	}

	return TRUE;
}



// "f3B5" -> 0xF3B5
u8 hexStr2U16( u8  *str, u16 *pU16 )
{
	u32 sum;
	u8 n;
	u8  *pCh;
	u8 i;

	sum = 0;
	
	i = 4;
	
	for( pCh = str;  *pCh && (i != 0);  pCh++, i-- )
	{
		if( hexChar2Byte(*pCh, &n) == FALSE )
			return FALSE;

		 sum = sum * 16 + n;
	}

	*pU16 = sum;


	return TRUE;
	
}


// "f3B5CA00" -> 0xF3B5CA00
u8 hexStr2U32( u8  *str, u32 *pU32 )
{
	u32 sum;
	u8 n;
	u8  *pCh;
	u8 i;

	sum = 0;
	
	i = 8;
	
	for( pCh = str; *pCh && (i != 0);   pCh++, i-- )
	{
		if( hexChar2Byte(*pCh, &n) == FALSE )
			return FALSE;

		 sum = sum * 16 + n;
	}

	*pU32 = sum;


	return TRUE;

	
}



//===================================================



// 123 -> "123"
void dec2str( u32 num, u8  *str )
{
    sprintf((char *)str, "%d" , (int) num);
}

// 100 -> "64"
void decU8toHexStr( u8 num, u8  *str )
{
    sprintf((char *)str, "%02X" , num);
}





// 100 -> "0064"
void decU16toHexStr( u16 num, u8  *str )
{
    sprintf((char *)str, "%04X" , num);
}


// 100 -> "00000064"
void decU32toHexStr( u32 num, u8  *str )
{
    sprintf((char *)str, "%08X" , (int)  num);
}



// "123"->123
u32 str2Dec( u8  *str )
{
	return atol((const char *)str);
}

// "12.3"->12.3
u32 str2float( u8  *str )
{
	return atof((const char *)str);
}




//BCD码转十进制函数，输入BCD，返回十进制
u8 BCD2decimal( u8 bcd )
{
	u8 Decimal;
	
	Decimal = bcd >> 4;

	Decimal = Decimal * 10 + ( bcd &= 0x0F );
	
	return Decimal ;
}


