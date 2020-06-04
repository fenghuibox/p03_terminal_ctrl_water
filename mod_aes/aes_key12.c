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


#include "cfg_aes.h"
#include "aes_key12.h"



u8 aesKey12Set( u8 *pKey ) 
{
	cfgAesKeySet( pKey );
	
	return TRUE;

}


void aesKey12Get( u8 *pKey )
{
	cfgAesKeyGet( pKey );
}



u8 aesKey12isEqu( u8 *pKey )
{
	u8 pKey12[AES_KEY_12_LEN] = {0};

	cfgAesKeyGet( pKey12 );
	
	if( memcmp( pKey, pKey12, AES_KEY_12_LEN ) == 0 )
		return TRUE;

	return FALSE;
}



void aesKey12Def( void )
{	
	cfgAesKeyDef();
}






