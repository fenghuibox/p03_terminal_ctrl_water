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



//===================================================

u8 isOperator( u8  ch )
{
	if ( ch == '+' || ch == '-' || ch == '*' || ch == '/')
		return TRUE;

	return FALSE;
}

u8 isFloat( u8  ch )
{
	if ( ch >= '0' && ch <= '9')
		return TRUE;
	
	if ( ch == '.')
		return TRUE;

	return FALSE;
}


u8 isNumber( u8  ch )
{
	if ( ch >= '0' && ch <= '9')
		return TRUE;

	return FALSE;
}

u8 isLower( u8  ch )
{
	if ( ch >= 'a' && ch <= 'z')
		return TRUE;

	return FALSE;
}

u8 isHexLower( u8  ch )
{
	if ( ch >= 'a' && ch <= 'f')
		return TRUE;

	return FALSE;
}



u8 isUpper( u8  ch )
{
	if ( ch >= 'A' && ch <= 'Z')
		return TRUE;

	return FALSE;
}


u8 isHexUpper( u8  ch )
{
	if ( ch >= 'A' && ch <= 'f')
		return TRUE;

	return FALSE;
}


u8 isHex( u8  ch )
{
	if( isNumber(ch) || isHexLower(ch) || isHexUpper(ch) )
		return TRUE;

	return FALSE;
}

u8 isPwd( u8 ch )
{
	if( isNumber(ch) || isLower(ch) || isUpper(ch) )
		return TRUE;

	return FALSE;
}


//===================================================
u8  toLower( u8  ch )  
{  
    if ( isUpper( ch ) )  
    {  
        return ch - 'A' + 'a';  
    }  

	return ch;  
}  


u8  toUpper( u8  ch )  
{  
    if ( isLower( ch ) )  
    {  
        return ch - 'a' + 'A';  
    }  

	 return ch;  
}  



