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

#include "zgb_state.h"

#include "zgb_cmd.h"

#include "dev_state.h"



static EN_ZIGBEE_WORK_STATE _zigbeeState;



u8 modZgbStateIsOk( void )
{
	if( _zigbeeState == ZIGBEE_WORK_STATE_IDLE || _zigbeeState == ZIGBEE_WORK_STATE_ALLOW_JOIN )
	{
		return TRUE;
	}

	return FALSE;
}






static void _modZigbeeStateSet( EN_ZIGBEE_WORK_STATE s )
{
	if( _zigbeeState == s )
		return;

	dprintf( "\r\nZS%d-%d", _zigbeeState,s );


	if( s == ZIGBEE_WORK_STATE_IDLE || s == ZIGBEE_WORK_STATE_ALLOW_JOIN )
	{
		devOnEvent( DEV_EVENT_ZIGBEE_STATE_TO_OK, NULL );
		zcmdDevInfoGet();
	}
	else
	{
		devOnEvent( DEV_EVENT_ERR_HINT_ZIGBEE_STATE_NG, NULL );
	}

	_zigbeeState = s;
	
}


/*
EN_ZIGBEE_WORK_STATE modZigbeeStateGet( void )
{
	return zigbeeWorkStateGet();
}
*/

void modZgbStatePoll( void )
{
	EN_ZIGBEE_WORK_STATE s;

	if( zigbeeWorkStateGet( &s ) == FALSE )
	{
		_modZigbeeStateSet( ZIGBEE_WORK_STATE_NOT_DEF );
		
		if( devStateIsZigbeeErr() == FALSE )
		{
			devOnEvent( DEV_EVENT_ERR_HINT_ZIGBEE_STATE_NG, NULL );
		}
	}
	else
	{
		_modZigbeeStateSet( s );

		if( devStateIsZigbeeErr() )
		{
			zcmdWorkStateGet();
			return;
		}
	}
}





void zgbStateInit( void )
{
	_zigbeeState = ZIGBEE_WORK_STATE_NOT_DEF;
	
	//timerStartSec( 2, TIMER_REPEAT_FOREVER, modZgbStatePoll );
}





