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
#include "dri_io_ctrl.h"
#include "dri_rtc.h"

#include "cfg_ctrl.h"
#include "timer.h"
#include "ctrl.h"




typedef struct
{
	u8 state:1;
	u8 ing:1;
	u8 exe:1;
	
	u8 init:1;
	u8 b2:1;
	u8 b3:1;
	u8 b4:1;
	u8 b5:1;
	


}ST_BOOL_CTRL;



static ST_BOOL_CTRL _stCtrl;





u8 ctrlStateGet( void )
{
	return cfgCtrlStateGet();
}



void ctrlOpenStartSecUpdate( void )
{
	u32 ctrlOpenStartSec;
	
	ctrlOpenStartSec = driRtcGetDateTimeSec();

	cfgCtrlOpenStartSet( ctrlOpenStartSec );

}





static void _ctrlFinishTimerCB( void )
{	
	driCtrl12VenL();
	
	driCtrl12VswitchL();
	
	driCtrlFinish();

	
	if( _stCtrl.state == cfgCtrlStateGet() )
	{
		_stCtrl.exe   = 0;

		if( _stCtrl.state )
		{
			ctrlOpenStartSecUpdate();
		}
	}
	else
	{
		_stCtrl.exe   = 1;
	}

	
	_stCtrl.ing = 0;
}


static void _ctrlTimerCB( void )
{
	if( _stCtrl.state )
		driCtrlOpen();
	else
		driCtrlClose();

	cfgCtrlStateSet( _stCtrl.state );
	
	timerStart( 150/TIMER_UNIT_MS, 1, _ctrlFinishTimerCB );
}




static void _enTimerCB( void )
{
	driCtrl12VenH();
	timerStart( 200/TIMER_UNIT_MS, 1, _ctrlTimerCB );
}




static void _ctrl( void )
{
	_stCtrl.ing = 1;
	
	driCtrl12VswitchH();
	timerStart( 2, 1, _enTimerCB );
}




void ctrlOpen( void )
{
	_stCtrl.state = 1;
	_stCtrl.exe   = 1;
	
}


void ctrlClose( void )
{
	_stCtrl.state = 0;
	_stCtrl.exe   = 1;
}




void ctrlStatePoll( void ) // 50 ms
{
	if( _stCtrl.ing )
		return;


	if( _stCtrl.exe == 0 )
		return;


	if( _stCtrl.init )
	{
		_stCtrl.init = 0;
		_ctrl();
		return;
	}


	if( _stCtrl.state == cfgCtrlStateGet() )
	{
		_stCtrl.exe   = 0;
		return;
	}

	_ctrl();
}




void ctrlOpenSecPoll( void ) // 200 ms
{
	u32 ctrlOpenStartSec;
	u32 curSec;
	
	if( cfgCtrlStateGet() == 0 ) 
		return;// 当前是 关 的状态

	
	ctrlOpenStartSec = cfgCtrlOpenStartGet();
	curSec = driRtcGetDateTimeSec();
	

	// 当前是 开 的状态
	if( curSec - ctrlOpenStartSec < cfgCtrlOpenSecGet() )
	{
		return; // 开的时长不够
	}


	// 开的时长够了
	ctrlClose();

	// 马上更新
	ctrlStatePoll();
}











u8 ctrlIsIdle( void )
{
	if( _stCtrl.ing || _stCtrl.exe )
		return FALSE;
	
	if(  _stCtrl.state == cfgCtrlStateGet() )
		return TRUE;

	return FALSE;
}






void ctrlInit( void )
{
	ctrlModeInit();
	ctrlOpenSecInit();

	ctrlCmdCtrlInit();

	_stCtrl.init = 1;

	_stCtrl.ing = 0;
	
	

	if( cfgCtrlStateGet() )
		ctrlOpen();
	else
		ctrlClose();
		
}




