/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#if 1

#include "com_includes.h"
#include "timer.h"

#include "aes_switch.h"
#include "aes_key12.h"

#include "dbg_uart.h"

#include "dev_state.h"



//=================================================


const char strCmdAesHead[] =      "aes";




const char strCmdAesSwitchGet[]  = "switchget";
#define DEBUG_AES_SWITCH_GET_CMD_LEN  (  9)

const char strCmdAesSwitchSet1[]  = "switchset1";
const char strCmdAesSwitchSet0[]  = "switchset0";
#define DEBUG_AES_SWITCH_SET_CMD_LEN  (10)



const char strCmdAesKeyGet[]     =  "keyget";
#define DEBUG_AES_KEY_GET_CMD_LEN  (6)


const char strCmdAesKeySet[]     =  "keyset";
#define _AES_KEY_SET_HEAD_CMD_LEN  ( 6)
#define DEBUG_AES_KEY_SET_CMD_LEN  ( _AES_KEY_SET_HEAD_CMD_LEN + AES_KEY_12_LEN )








// str = switchget / keyget ...
u8 debugCmdAes( u8 *str,  u8 len )
{
	u8 pKey12[AES_KEY_12_LEN];
	
	if( len == DEBUG_AES_SWITCH_GET_CMD_LEN )
	{
		if( strcmp( ( const char *)str, strCmdAesSwitchGet ) == 0 )
		{
			if( aesSwitchGet() )
				dprintf( "\naes switch on" );
			else
				dprintf( "\naes switch off" );
				
			return TRUE;
		}
	}
	else if( len == DEBUG_AES_SWITCH_SET_CMD_LEN )
	{
		if( strcmp( ( const char *)str, strCmdAesSwitchSet1 ) == 0 )
		{
			aesSwitchSet( 1 );
			dprintf( "\naes switch on" );
			return TRUE;
		}
		else if( strcmp( ( const char *)str, strCmdAesSwitchSet0 ) == 0 )
		{
			aesSwitchSet( 0 );
			dprintf( "\naes switch off" );
			return TRUE;
		}
		
	}
	else if( len == DEBUG_AES_KEY_GET_CMD_LEN )
	{
		if( strcmp( ( const char *)str, strCmdAesKeyGet ) == 0 )
		{
			aesKey12Get( pKey12 );
			dprintfBuf( "\naeskey:", pKey12, AES_KEY_12_LEN, 1);
			return TRUE;
		}
	}
	else if( len == DEBUG_AES_KEY_SET_CMD_LEN )
	{
		if( memcmp( ( const char *)str, strCmdAesKeySet, _AES_KEY_SET_HEAD_CMD_LEN ) == 0 )
		{ 
			if( aesKey12Set( str + _AES_KEY_SET_HEAD_CMD_LEN ) == FALSE )
			{
				dprintf( "\naeskeyset Error" );
			}
			else
			{
				dprintfBuf( "\naeskeyset ok, key=", str + _AES_KEY_SET_HEAD_CMD_LEN , AES_KEY_12_LEN, 1 );
			}
			return TRUE;
		}
	}

		


	return FALSE;


}

#endif


