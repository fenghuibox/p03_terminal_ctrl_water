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

#include "dri.h"

#include "timer.h"

#include "dbg_uart.h"

#include "dbg_cmd_uart_pass.h"

//#include "dev_state.h"


const char strCmdUartPassHead[]  =  "uartpass";




const char strCmdUartZigbeeOn[]  = "zigbee1"; // 7
//const char strCmdUartZigbeeOff[] = "zigbee0";


const char strCmdUartOff[] = "0";


#define UART_PASS_CMD_LEN_OFF     ( 1 )
#define UART_PASS_CMD_LEN_4G     ( 3 )
#define UART_PASS_CMD_LEN_IPAD   ( 5 )
#define UART_PASS_CMD_LEN_ZGB    ( 7 )
#define UART_PASS_CMD_LEN_485    ( 8 )



static EN_DEBUG_UART_PASS_PORT _passPort;


static void _passPortSet( EN_DEBUG_UART_PASS_PORT pport )
{
	if( pport == _passPort )
		return;

	if( _passPort == DEBUG_UART_PASS_ZIGBEE)
	{
		dprintf( "passPort=zigbee" );	
	}
	
	_passPort = pport;
	

}


u8 debugPassIsZigbee( void )
{
	return (_passPort == DEBUG_UART_PASS_ZIGBEE)? 1:0;
}


//str = zigbee1 / 4g1 ......
u8 debugCmdUartPass( u8 *str,  u8 len  )
{
	#if 0 // fenghuiw
	if( len == UART_PASS_CMD_LEN_OFF )
	{
		if(   *str == '0' )
		{
			//devOnEvent( DEV_EVENT_UART_PASS_END, NULL );
			driSoftReset();
			return TRUE;
		}
	}
	else if( len == UART_PASS_CMD_LEN_ZGB )
	{
		if( strcmp( ( const char *)str, strCmdUartZigbeeOn ) == 0 )
		{
			devOnEvent( DEV_EVENT_UART_PASS_START, NULL);
			_passPortSet( DEBUG_UART_PASS_ZIGBEE );
			return TRUE;
		}
	}
	#endif

	

	return FALSE;

}



void debugCmdUartPassInit( void )
{
	_passPort = DEBUG_UART_PASS_NOT_DEF;
}


