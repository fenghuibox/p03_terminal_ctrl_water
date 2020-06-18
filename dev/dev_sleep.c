/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#if 1
#include "com_includes.h"

#include "dri_includes.h"

#include "dev_state.h"
#include "dev_sleep.h"

#include "dbg_uart.h"
#include "zgb_io.h"

#include "sn_ch.h"
#include "ctrl.h"
#include "cfg.h"
#include "zgb_uart.h"
#include "sn_rx.h"
#include "sn_n2s.h"








static void _toSleep( void )
{
	// --- to sleep ------
	
	driToSleep();


	// --- wakeup ----------	
	gB1.sleep  = 0;
		
	gB1.ctrlPackTx = gB1.ctrlPackFinish = 0;
	//gB1.battTx     = gB1.battTxFinish   = 0;
	gB1.zgbSleepTx = gB1.zgbSleepFinish = 0;
	
	driOnWakeup();

	modIoZgbWakeup();

	
	dprintf("w"); // wakeup
	
	devOnEvent( DEV_EVENT_SLEEP_END, NULL );
	
}



void devSleep( void )
{
	if( ctrlIsIdle() == FALSE )
	{
		//dprintf("\r\nctrl is busy");
		return;
	}
	
	if( cfgIsIdle() == FALSE )
	{
		//dprintf("\r\ncfg is busy");
		return;
	}
	
	if( zgbUartIsIdle() == FALSE )
	{
		//dprintf("\r\nzgbUart is busy");
		return;
	}

	if( snIsIdle() == FALSE )
	{
		//dprintf("\r\nsn is busy");
		return;
	}

	//------send ctrl_pack_get--------------------
	if( gB1.ctrlPackFinish == 0 )
	{
		return;
	}


	#if 0

	//----- batt low report ---------------------
	if( gB1.battIsLow )
	{
		if( gB1.battTx == 0 )
		{
			gB1.battTx = 1;
			gB1.battTxFinish = 0;
			
			n2sBattRpt();
			return;
		}
		
		if( gB1.battTxFinish == 0 )
		{
			return;
		}
	}
	#endif


	//----- zgb to sleep ---------------------
	if( gB1.zgbSleepTx == 0 )
	{
		gB1.zgbSleepTx = 1;
		gB1.zgbSleepFinish = 0;
		
		modIoZgbSleep();
		return;
	}

	if( gB1.zgbSleepFinish == 0 )
	{
		return;
	}

	_toSleep();

}




#if 0

void devSleepPoll( void ) // 20ms / times
{
	//u32 sleepSec;
	u32 cfgWorkSec;


	if( snChIs485() )
		return;

	//sleepSec = cfgSleepSecGet();

	if( cfgSleepSecGet() == 0 ) // 不要休眠
	{
		_workSecCnt = 0;
		return;
	}


	// 要休眠

	cfgWorkSec = cfgWorkSecGet();

	if( cfgWorkSec == 0 )
	{
		// 马上休眠
		gB1.sleep = 1;
	}
	else
	{
		_workSecCnt++;

		if( _workSecCnt * DEV_SLEEP_POLL_GAP_MS   >=  cfgWorkSec * 1000 )
		{
			gB1.sleep = 1;
		}
	}
}
#endif


void devSleepInit( void )
{
	//_workSecCnt = 0;
	
}










#endif




