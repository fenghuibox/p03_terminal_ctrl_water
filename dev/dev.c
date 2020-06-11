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
#include "timer.h"
//#include "mod_includes.h"


#include "dev.h"

//#include "zgb_state.h"
#include "cfg.h"
#include "sn.h"
//#include "led.h"

#include "ctrl.h"



#include "dbg_uart.h"







static void _10msCB( void )
{
#if 1
	#define _10_MS_CNT_MAX  (49) // 10 * 50 = 500ms
	
	static u8 _10msCnt = _10_MS_CNT_MAX; 


	

	if( _10msCnt != 0 )
	{
		_10msCnt--;
	}
	else
	{
		_10msCnt = _10_MS_CNT_MAX;
	}

	if( (_10msCnt & 3 ) == 0 )// 40ms
	{
		ctrlStatePoll();
		snPoll(); 
	}

	if( (_10msCnt % 5) == 0 ) // 50ms
	{
		zgbUartTxPoll();
	}

	if( (_10msCnt & 7 ) == 0 )// 80ms
	{
		configUpdate();
	}

	if( (_10msCnt & 15 ) == 0  )// 160 ms
	{
		ctrlOpenSecPoll(); 
	}


	//--------- 1 sec -------------------
	if( _10msCnt == 0 )
	{
	
	}
	else if( _10msCnt == 3 )
	{
		//modZgbStatePoll();
	}
	else if( _10msCnt == 6 )
	{

	}
	else if( _10msCnt == 9 )
	{
		
	}
	else if( _10msCnt == 12 )
	{
		//configUpdate();
	}	
	else if( _10msCnt == 15 )
	{

	}	



#else
	static u8 _10msCnt = 19;

	if( _10msCnt != 0 )
	{
		_10msCnt--;
	}
	else
	{
		_10msCnt = 19;
	}


	g4Poll(); // 4G 
	sgPoll(); // 50ms

	ledPoll();// 50ms

	//--------- 1 sec -------------------
	if( _10msCnt == 0 )
	{

	}
	else if( _10msCnt == 3 )
	{
		modZgbStatePoll();
	}
	else if( _10msCnt == 6 )
	{

	}
	else if( _10msCnt == 9 )
	{
		modVbattCB();
	}
	else if( _10msCnt == 12 )
	{
		configUpdate();
	}	
	else if( _10msCnt == 15 )
	{
	
	}	

#endif
	
}





static void _devStartCB( void )
{
#if 1// fenghuiw
	// 启动时要发送的数据帧
	#include "f_frame_comm.h"
	
	//gstN2S.reboot = 1; 
	gstN2S.heartbeat = 1; 
#endif

}





void devInit( void )
{
	devStateInit();

	devVbattInit();

	//devSleepInit();

	
	timerStart( 10/TIMER_UNIT_MS, TIMER_REPEAT_FOREVER, _10msCB ); 

	
	timerStartSec(1, 1, _devStartCB );


	#ifdef USE_IWDG
		iwdgInit();
	#endif

}








