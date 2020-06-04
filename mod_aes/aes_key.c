/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 


#include "com_includes.h"

#include "dbg_uart.h"

#include "aes_key4.h"
#include "aes_key12.h"
#include "aes_key.h"




u8 aesKeySet( u8 *pKey ) 
{
	return aesKey12Set( pKey );
}


void aesKeyGet2(  u8 frameLen, u8 frameVer, u8 frameAct, u8 frameCheck, u8 *pOutKey )
{
	aesKey12Get( pOutKey );
	aesKey4Get2( frameLen, frameVer, frameAct, frameCheck, pOutKey + AES_KEY_12_LEN );

	
}


void aesKeyGet(  u8 *pFrame, u8 *pOutKey )
{
	
	aesKey12Get( pOutKey );
	aesKey4Get( pFrame, pOutKey + AES_KEY_12_LEN );
	
	comSwapU8( pOutKey + 8,  pOutKey + 12 );

	//dprintfBuf( "key:", pOutKey, 16, 1 );
}




void aesKeyInit( void )
{
	
}


