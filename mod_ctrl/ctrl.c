/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 



#include "com_includes.h"
#include "dri_io_ctrl.h"
#include "dri_rtc.h"

#include "cfg_ctrl.h"
#include "timer.h"
#include "ctrl.h"

#include "dbg_uart.h"
#include "dev_state.h"


typedef struct
{
	u8 state:1;// ˮ����ǰ��״̬
	
	u8 ing:1;  // ��ǰ���ڿ����� 
	
	u8 exe:1;  // �Ƿ�Ҫִ�п���
	
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

	//dprintf(" open start sec=%d ", ctrlOpenStartSec );

	cfgCtrlOpenStartSet( ctrlOpenStartSec );

}





static void _ctrlFinishTimerCB( void )
{	
	#if 1

	driCtrl12VenL();
	
	driCtrl12VswitchL();
	
	driCtrlFinish();

	
	if( _stCtrl.state == cfgCtrlStateGet() )
	{
		_stCtrl.exe   = 0;

		if( _stCtrl.state )
		{
			//dprintf(" opensecUpdate ");
			ctrlOpenStartSecUpdate();
		}
	}
	else
	{
		_stCtrl.exe   = 1;
	}

	
	_stCtrl.ing = 0;
	
	//dprintf(" exe=%d", _stCtrl.exe);

	
	dprintf("CtrlF");

	#else

	dprintf(" ctrlFinish ");
	
	#endif
}


static void _ctrlTimerCB( void )
{
	if( _stCtrl.state )
	{
		//dprintf("Ctrl1");
		driCtrlOpen();
	}
	else
	{
		//dprintf("Ctrl0");
		driCtrlClose();
	}

	cfgCtrlStateSet( _stCtrl.state );
	
	timerStart( 150/TIMER_UNIT_MS, 1, _ctrlFinishTimerCB );

	//timerStartSec( 1, 1, _ctrlFinishTimerCB );


	
}




static void _enTimerCB( void )
{
	//dprintf(" 12VenH ");

	driCtrl12VenH();
	//timerStart( 200/TIMER_UNIT_MS, 1, _ctrlTimerCB );
	timerStartSec( 1, 1, _ctrlTimerCB );
	
}




static void _ctrl( void )
{
	
	dprintf("12Vs");

	_stCtrl.ing = 1;
	
	driCtrl12VswitchH();
	timerStart( 100/TIMER_UNIT_MS, 1, _enTimerCB ); // 6M����


	
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
		 _stCtrl.ing  = 0;
		return;
	}

	_ctrl();
}




void ctrlOpenSecPoll( void ) // 200 ms
{

	u32 ctrlOpenStartSec;
	u32 curSec;
	

	if( _stCtrl.ing || _stCtrl.exe )
		return;

	if( devStateIsDbg() )// ����̬ʱ���Զ���
	{
		return;
	}

	
	if( cfgCtrlStateGet() == 0 ) 
		return;// ��ǰ�� �� ��״̬

	
	ctrlOpenStartSec = cfgCtrlOpenStartGet();
	curSec = driRtcGetDateTimeSec();
	

	// ��ǰ�� �� ��״̬
	if( curSec - ctrlOpenStartSec < cfgCtrlOpenSecGet() )
	{
		return; // ����ʱ������
	}

	//dprintf("close:c_sec=%d s_sec=%d o_sec=%d", curSec, ctrlOpenStartSec, cfgCtrlOpenSecGet() );
	dprintf("close");

	// ����ʱ������
	ctrlClose();
	gB1.ctrlOpenTimeoutClose = 1;

	// ���ϸ���
	ctrlStatePoll();
}



u8 ctrlOpenSecIsTimeout( void )
{
	u32 ctrlOpenStartSec;
	u32 curSec;
	

	if( _stCtrl.ing || _stCtrl.exe )
		return FALSE;

	
	if( cfgCtrlStateGet() == 0 ) 
		return FALSE;// ��ǰ�� �� ��״̬

	
	ctrlOpenStartSec = cfgCtrlOpenStartGet();
	curSec = driRtcGetDateTimeSec();
	

	// ��ǰ�� �� ��״̬
	if( curSec - ctrlOpenStartSec < cfgCtrlOpenSecGet() )
	{
		return FALSE; // ����ʱ������
	}

	return TRUE;
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
	
	
	#if 0 // fenghuiw
	if( cfgCtrlStateGet() )
		ctrlOpen();
	else
		ctrlClose();

	#endif
		
}




