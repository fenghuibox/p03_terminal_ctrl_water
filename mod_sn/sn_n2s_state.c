/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/

 // sn: Server and node communication    服务器和节点通信
// n2s: node to server                   节点发送给服务器

#include "com_includes.h"

#include "dbg_uart.h"

#include "sn_n2s_state.h"







static EN_TXT_FRAME_EXE_STATE _enExeState;







u8 txtFrameExeStateIsIdle( void )
{
	if( _enExeState == TXT_FRAME_EXE_STATE_IDLE )
		return TRUE;

	return FALSE;

}



u8 txtFrameExeStateIsUnpack( void )
{
	if( _enExeState == TXT_FRAME_EXE_STATE_UNPACK )
		return TRUE;

	return FALSE;

}



u8 txtFrameExeStateIsExe( void )
{
	if( _enExeState == TXT_FRAME_EXE_STATE_EXE )
		return TRUE;

	return FALSE;

}



u8 txtFrameExeStateIsWaitRspResport( void )
{
	if( _enExeState == TXT_FRAME_EXE_STATE_WAIT_RSP_REPORT )
		return TRUE;

	return FALSE;

}



static void _setTxtFrameExeState( EN_TXT_FRAME_EXE_STATE s )
{
	if( _enExeState == s )
		return;


	_enExeState = s;
	

	if(    s == TXT_FRAME_EXE_STATE_EXE 
		|| s == TXT_FRAME_EXE_STATE_IDLE
		|| s == TXT_FRAME_EXE_STATE_UNPACK )
	{
		gB1.txtFrameExeOKhaveRspReport = 0;
	}
	
}





void txtFrameExeStateOnEvent( EN_TXT_FRAME_EXE_EVENT event )
{
	switch( _enExeState )
	{
	case TXT_FRAME_EXE_STATE_IDLE:
		if( TXT_FRAME_EXE_EVENT_RX_TXT == event )
		{
			_setTxtFrameExeState( TXT_FRAME_EXE_STATE_UNPACK );
		}
		break;

	case TXT_FRAME_EXE_STATE_UNPACK:
		if( TXT_FRAME_EXE_EVENT_UNPACK_NG == event )
		{
			_setTxtFrameExeState( TXT_FRAME_EXE_STATE_IDLE );
		}
		else if( TXT_FRAME_EXE_EVENT_UNPACK_OK == event )
		{
			_setTxtFrameExeState( TXT_FRAME_EXE_STATE_EXE );
		}
		break;

	case TXT_FRAME_EXE_STATE_EXE:
		if( TXT_FRAME_EXE_EVENT_EXE_NG == event )
		{
			_setTxtFrameExeState( TXT_FRAME_EXE_STATE_IDLE );
		}
		else if( TXT_FRAME_EXE_EVENT_EXE_OK == event )
		{
			if( gB1.txtFrameExeOKhaveRspReport )
				_setTxtFrameExeState( TXT_FRAME_EXE_STATE_WAIT_RSP_REPORT );
			else
				_setTxtFrameExeState( TXT_FRAME_EXE_STATE_IDLE );
		}
		break;

	case TXT_FRAME_EXE_STATE_WAIT_RSP_REPORT:
		if( TXT_FRAME_EXE_EVENT_RSP_REPORT == event || TXT_FRAME_EXE_EVENT_WAIT_RSP_TIMEOUT == event )
		{
			_setTxtFrameExeState( TXT_FRAME_EXE_STATE_IDLE );
		}
		else if( TXT_FRAME_EXE_EVENT_RX_TXT == event )
		{
			_setTxtFrameExeState( TXT_FRAME_EXE_STATE_UNPACK );
		}
		break;
		
	case TXT_FRAME_EXE_STATE_NOT_DEF:
		if( TXT_FRAME_EXE_EVENT_INIT )
		{
			_setTxtFrameExeState( TXT_FRAME_EXE_STATE_IDLE );
		}
		break;

		

	}

}


void snN2sStateInit( void )
{
	_enExeState = TXT_FRAME_EXE_STATE_NOT_DEF;

	txtFrameExeStateOnEvent( TXT_FRAME_EXE_EVENT_INIT );
}



