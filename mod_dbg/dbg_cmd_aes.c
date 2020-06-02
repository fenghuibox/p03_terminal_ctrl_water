/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#if 0

#include "com_includes.h"
#include "timer.h"

#include "aes_switch.h"
#include "aes_key12.h"

#include "mod_uart_debug.h"

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
	if( len == DEBUG_AES_SWITCH_GET_CMD_LEN )
	{
		if( strcmp( ( const char *)str, strCmdAesSwitchGet ) == 0 )
		{
			if( aesSwitchGet() )
				modUartDebugTx0( "\naes switch on" );
			else
				modUartDebugTx0( "\naes switch off" );
				
			return TRUE;
		}
	}
	else if( len == DEBUG_AES_SWITCH_SET_CMD_LEN )
	{
		if( strcmp( ( const char *)str, strCmdAesSwitchSet1 ) == 0 )
		{
			aesSwitchSet( 1 );
			modUartDebugTx0( "\naes switch on" );
			return TRUE;
		}
		else if( strcmp( ( const char *)str, strCmdAesSwitchSet0 ) == 0 )
		{
			aesSwitchSet( 0 );
			modUartDebugTx0( "\naes switch off" );
			return TRUE;
		}
		
	}
	else if( len == DEBUG_AES_KEY_GET_CMD_LEN )
	{
		if( strcmp( ( const char *)str, strCmdAesKeyGet ) == 0 )
		{
			modUartDebugTx0( "\naeskey:" );
			modUartDebugTxU8buf( _aesKey12Get(), AES_KEY_12_LEN );
			return TRUE;
		}
	}
	else if( len == DEBUG_AES_KEY_SET_CMD_LEN )
	{
		if( memcmp( ( const char *)str, strCmdAesKeySet, _AES_KEY_SET_HEAD_CMD_LEN ) == 0 )
		{ 
			if( aesKey12Set( str + _AES_KEY_SET_HEAD_CMD_LEN ) == FALSE )
			{
				modUartDebugTx0( "\naeskeyset Error" );
			}
			else
			{
				modUartDebugTx0( "\naeskeyset ok, key=" );
				modUartDebugTxU8buf( str + _AES_KEY_SET_HEAD_CMD_LEN , AES_KEY_12_LEN );
			}
			return TRUE;
		}
	}

		


	return FALSE;


}

#endif


