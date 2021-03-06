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
#include "sn_master_state.h"
#include "zgb_state.h"
#include "cfg.h"
#include "sn.h"
//#include "led.h"

#include "ctrl.h"



#include "dbg_uart.h"




#define FLASH_WRITE_GAP_SEC  ( 60 * 10 )


static void _10msCB( void )
{
#if 1
	#define _10_MS_CNT_MAX  (99) // 10 * 99 = 1000ms
	
	static u8 _10msCnt = _10_MS_CNT_MAX; 
	static u16 _cfgWriteSecCnt = FLASH_WRITE_GAP_SEC;


	if( _10msCnt != 0 )
	{
		_10msCnt--;
	}
	else
	{
		_10msCnt = _10_MS_CNT_MAX;
	}

	if( (_10msCnt & 1 ) == 0 )// 20ms
	{
		//devSleepPoll();
	}



	if( (_10msCnt & 3 ) == 0 )// 40ms
	{
		ctrlStatePoll();
		snPoll(); 
	}

	if( devStateIsReadCtrlInfo() )
	{
		zgbUartTxPoll();
	}
	else
	{
		if( (_10msCnt % 6) == 0 ) // 50ms
		{
			zgbUartTxPoll();
		}
	}

	if( (_10msCnt & 7 ) == 0 )// 80ms
	{
		//configUpdate(); 
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
		modZgbStatePoll();
	}
	else if( _10msCnt == 6 )
	{

	}
	else if( _10msCnt == 9 )
	{
		
	}
	else if( _10msCnt == 12 )
	{
		if( _cfgWriteSecCnt )
		{
			_cfgWriteSecCnt--;
		}
		else
		{
			_cfgWriteSecCnt = FLASH_WRITE_GAP_SEC;
			configUpdate();
		}
	}	
	else if( _10msCnt == 15 )
	{
		if( devStateIsDbg() == TRUE )
		{
			devVbattPoll();
		}
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
#if 1
	// 启动时要发送的数据帧
	#include "f_frame_comm.h"
	
	gstN2S.reboot = 1; 
	// gstN2S.heartbeat = 1; 
#endif

}


static void _writeFlashCB( void )
{
	configUpdate(); // test


}



void devInit( void )
{
	devStateInit();

	devVbattInit();

	//devSleepInit();

	
	timerStart( 10/TIMER_UNIT_MS, TIMER_REPEAT_FOREVER, _10msCB ); 

	
	timerStartSec(1, 1, _devStartCB );
	
	//timerStartSec(10, TIMER_REPEAT_FOREVER, _writeFlashCB );


	#ifdef USE_IWDG
		iwdgInit();
	#endif

}








