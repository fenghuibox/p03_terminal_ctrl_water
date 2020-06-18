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

#include "sn_master_state.h"

#include "sn_n2s.h"
#include "dev_state.h"





static EN_MASTER_STATE _masterState;




void modMasterStateSet( EN_MASTER_STATE s )
{
	if( devStateIsDbg() == FALSE ) // 只有 DEBUG 时才响应
		return;

	if( _masterState == s )
		return;

	_masterState = s;

	if( s == MASTER_STATE_OK )
	{
		if( devErrIsHaveMaster()  )
		{
			devOnEvent( DEV_EVENT_MASTER_STATE_TO_OK, NULL );
		}
	}
	else
	{
		if( devErrIsHaveMaster() == FALSE )
		{
			devOnEvent( DEV_EVENT_ERR_HINT_MASTER_STATE_NG, NULL );
		}
	}
}



EN_MASTER_STATE modMasterStateGet( void )
{
	return _masterState;
}


void modMasterStatePoll( void ) //
{	
	#include "f_frame_comm.h"

	
	if( devStateIsDbg() == FALSE ) // 只有 DEBUG 时才响应
		return;

	if( devStateIsMasterErr() )
	{
		if( n2sIsHave() == TRUE )
			return;

		gstN2S.heartbeat = 1;
		
	}

	
}






void snMasterStateInit( void )
{
	_masterState = MASTER_STATE_NOT_DEF;
}





