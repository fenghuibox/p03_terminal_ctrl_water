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
//#include "sg.h"
//#include "led.h"



#include "dbg_uart.h"







static void _50msCB( void )
{
#if 1
	static u8 _50msCnt = 19;

	if( _50msCnt != 0 )
	{
		_50msCnt--;
	}
	else
	{
		_50msCnt = 19;
	}


	//sgPoll(); // 50ms
	//ledPoll();// 50ms

	//--------- 1 sec -------------------
	if( _50msCnt == 0 )
	{

	}
	else if( _50msCnt == 3 )
	{
		//modZgbStatePoll();
	}
	else if( _50msCnt == 6 )
	{

	}
	else if( _50msCnt == 9 )
	{
	
	}
	else if( _50msCnt == 12 )
	{
		configUpdate();
	}	
	else if( _50msCnt == 15 )
	{

	}	



#else
	static u8 _50msCnt = 19;

	if( _50msCnt != 0 )
	{
		_50msCnt--;
	}
	else
	{
		_50msCnt = 19;
	}


	g4Poll(); // 4G 
	sgPoll(); // 50ms

	ledPoll();// 50ms

	//--------- 1 sec -------------------
	if( _50msCnt == 0 )
	{

	}
	else if( _50msCnt == 3 )
	{
		modZgbStatePoll();
	}
	else if( _50msCnt == 6 )
	{

	}
	else if( _50msCnt == 9 )
	{
		modVbattCB();
	}
	else if( _50msCnt == 12 )
	{
		configUpdate();
	}	
	else if( _50msCnt == 15 )
	{
	
	}	

#endif
	
}





static void _devStartCB( void )
{
#if 0// fenghuiw
	// 启动时要发送的数据帧
	#include "f_frame_comm.h"
	
	gstG2S.reboot = 1; 
#endif

}





void devInit( void )
{
	devStateInit();

	devVbattInit();

	//devSleepInit();

	
	timerStart( 50/TIMER_UNIT_MS, TIMER_REPEAT_FOREVER, _50msCB ); 

	
	timerStartSec(1, 1, _devStartCB );


	#ifdef USE_IWDG
		iwdgInit();
	#endif

}








