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
#include "dbg_uart.h"

//#include "dri_includes.h"
//#include "mod_includes.h"



#include "dev_state.h"
#include "cfg_base.h"

#include "sn_n2s.h"
#include "sn_ch.h"
#include "f_txt_frame_dpara_ctrl.h"




#define DEV_POLL_GAP_MS            (50)

#define HEARTBEAT_POLL_CNT          DEV_WAIT_SEC_HEARTBEAT * (1000 / DEV_POLL_GAP_MS )

#define IDLE_POLL_CNT              DEV_WAIT_SEC_IDLE * (1000 / DEV_POLL_GAP_MS )

#define POWER_ON_POLL_CNT          DEV_WAIT_SEC_POWER_ON * (1000 / DEV_POLL_GAP_MS )

#define READ_CTRL_INFO_POLL_CNT    DEV_WAIT_SEC_READ_CTRL_INFO * (1000 / DEV_POLL_GAP_MS )

//#define DEBUG_POLL_CNT             DEV_WAIT_SEC_DEBUG * (1000 / DEV_POLL_GAP_MS )


#define UART_PASS_POLL_CNT         DEV_WAIT_SEC_UART_PASS * (1000 / DEV_POLL_GAP_MS )



#define ZIGBEE_ERR_POLL_CNT       DEV_WAIT_SEC_ERR_HINT * (1000 / DEV_POLL_GAP_MS ) // 当前状态下等待的时间
#define ZIGBEE_ERR_POLL_GAP       (1000/DEV_POLL_GAP_MS) // 每1.0秒检查一下状态


#define MASTER_ERR_POLL_CNT      DEV_WAIT_SEC_ERR_HINT * (1000 / DEV_POLL_GAP_MS ) // 当前状态下等待的时间
#define MASTER_ERR_POLL_GAP      (2000/DEV_POLL_GAP_MS)// 每2秒检查一下状态

//=====================================================
static EN_DEV_STATE _devS;

static u32 _devErrBit;

static u32 _pollCnt;

static u32 _dbgHeartbeatCnt;

//====================================================
static void _devStateSet( EN_DEV_STATE s );
//====================================================
static void _sToZigbeeErr( void );
static void _sToMasterErr( void );
static void _onReadCtrlInfoEnd( void );




void devHeartbeatUpdate( void )
{
	_dbgHeartbeatCnt = HEARTBEAT_POLL_CNT;
}

//====================================================
u8 devErrIsHaveZigbee( void )
{
	if( _devErrBit & DEV_ERR_BIT_ZIGBEE )
		return TRUE;

	return FALSE;
}


u8 devErrIsHaveMaster( void )
{
	if( _devErrBit & DEV_ERR_BIT_MASTER )
		return TRUE;

	return FALSE;
}




EN_DEV_STATE devStateGet( void )
{
	return _devS;
}


//================================================
u8 devStateIsNormal( void )
{
	return _devS < DEV_STATE_ERR ? 1 : 0;
}


u8 devStateIsDbg( void )
{
	return _devS == DEV_STATE_DBG? 1 : 0;
}


//================================================
u8 devStateIsReadCtrlInfo( void )
{
	return _devS == DEV_STATE_READ_CTRL_INFO? 1 : 0;
}


//================================================
u8 devStateIsUartPass( void )
{
	return _devS == DEV_STATE_UART_PASS? 1 : 0;
}



//================================================


u8 devStateIsNg( void )
{
	return _devS > DEV_STATE_ERR ? 1 : 0;
}

u8 devStateIsZigbeeErr( void )
{
	return _devS == DEV_STATE_ERR_HINT_ZIGBEE? 1 : 0;
}


u8 devStateIsMasterErr( void )
{
	return _devS == DEV_STATE_ERR_HINT_MASTER? 1 : 0;
}



//====== poll ==============================================

static u8 _isLeaveDbg( void )
{
	if( snChIs485() || gB1.isDebug || ctrlPackRxIsDbg() ) // 485时不休眠 ,转为DEBUG态
		return FALSE;

	return TRUE;
}



//====== poll ==============================================



static void _devReadCtrlInfoPoll( void )
{	
	if( _pollCnt )
	{
		_pollCnt--;
		return;
	}
	else
	{
		dprintf( "readCtrlInfoEnd" );
		//_devStateSet( DEV_STATE_SLEEP );  //  使用指令超时处理

		//_onReadCtrlInfoEnd();
	}
	
	return;
		
}





static void _devDebugPoll( void )
{	
	if( _dbgHeartbeatCnt )
	{
		_dbgHeartbeatCnt--;
	}
	else
	{
		//n2sHeartbeat();
		n2sCtrlPackGet();
		devHeartbeatUpdate();
	}
	
		
	if( _pollCnt )
	{
		_pollCnt--;
		return;
	}
	else
	{
		if( _isLeaveDbg() == TRUE )
			devOnEvent( DEV_EVENT_DBG_END, NULL );  // 
	}
	
	return;
		
}

static void _devUartPassPoll( void )
{
	if( _pollCnt )
	{
		_pollCnt--;
	}
	else
	{
		// 时间到
		devOnEvent( DEV_EVENT_UARTPASS_TIMEOUT , NULL );
	}
}


static void _devZigbeeErrPoll( void )
{
	#include "zgb_cmd.h"
	
	if( ( _pollCnt % ZIGBEE_ERR_POLL_GAP) == 0 )
	{
		zcmdWorkStateGet(); // fenhuiw
	}


	if( _pollCnt )
	{
		_pollCnt--;
	}
	else
	{
		// 网络错误态时间到
		devOnEvent( DEV_EVENT_ERR_TIMEOUT , NULL );
	}
}






static void _devMasterErrPoll( void )
{
	#include "sn_master_state.h"

	if( (_pollCnt % MASTER_ERR_POLL_GAP) == 0 )
	{
		modMasterStatePoll(); //fenghuiw
	}

	if( _pollCnt )
	{
		_pollCnt--;
	}
	else
	{
		// 主机错误态时间到
		devOnEvent( DEV_EVENT_ERR_TIMEOUT , NULL );
	}


}






static void _devTimerPollCB( void ) // dev state to init
{
	if ( _devS == DEV_STATE_READ_CTRL_INFO  )
	{
		_devReadCtrlInfoPoll();
	}
	else if ( _devS == DEV_STATE_DBG)
	{
		_devDebugPoll();
	}
	else if ( _devS == DEV_STATE_ERR_HINT_ZIGBEE )
	{
		_devZigbeeErrPoll();
	}	
	else if ( _devS == DEV_STATE_ERR_HINT_MASTER )
	{
		_devMasterErrPoll();
	}	
	else if ( _devS == DEV_STATE_UART_PASS )
	{
		_devUartPassPoll();
	}	
	


	

}



static void _sToInit( void ) // dev state to init
{
	_devS      = DEV_STATE_INIT;

	timerStart( DEV_POLL_GAP_MS/TIMER_UNIT_MS, TIMER_REPEAT_FOREVER, _devTimerPollCB );
}




//====================================================
static void _sToPowerOn( void )
{
	_pollCnt =  POWER_ON_POLL_CNT;
}


//====================================================
static void _sToSleep( void )
{	
	#include "dev_sleep.h"
	#include "sn_n2s.h"

	U32 sleepSec;
	
	gB1.sleep = 1;

	//dprintf("toSleep");
	//n2sPrint();

	sleepSec = cfgSleepSecGet();

	//dprintf( "sleepSec=%d", sleepSec );

	if( gN2sServerNgCnt == 0 )
	{
		if( sleepSec < N2S_SERVER_NG_SLEEP_SEC )
			sleepSec = N2S_SERVER_NG_SLEEP_SEC;
	}

	devSleepSecSet( sleepSec );
}

//====================================================

static void _txCtrlPack( void )
{	
	//------send ctrl_pack_get---
	if( gB1.ctrlPackTx == 0 )
	{
		gB1.ctrlPackTx = 1;
		gB1.ctrlPackFinish = 0;
		
		n2sCtrlPackGet();
		return;
	}
	else
	{
		dprintf("gB1.ctrlPackTx=1 err");
	}
}


static void _sToReadCtrlInfo( void )
{
	#include "zgb_state.h"
	
	gB1.isDebug = 0;

	gB1.ctrlPackTx = gB1.ctrlPackFinish = 0; // fenghuiw
		
	if( modZgbStateIsOk() )
	{
		_txCtrlPack();
		_pollCnt =  READ_CTRL_INFO_POLL_CNT;

		//dprintf("_sToReadCtrlInfo ok");
	}
	else
	{
		_pollCnt =  0;
		gB1.ctrlPackFinish = 1;

		//dprintf("_sToReadCtrlInfo ng");
	}
}


//====================================================
static void _sToDebug( void )
{	
	u32 debugSec;

	debugSec = cfgWorkSecGet();

	
	//dprintf( "gB1.isPowerOn=%d", gB1.isPowerOn);
	
	if( gB1.isPowerOn )
	{
		gB1.isPowerOn = 0;

		if( debugSec < DEV_WAIT_SEC_POWER_ON )
			debugSec = DEV_WAIT_SEC_POWER_ON;
	}


	if( debugSec < DEV_WAIT_SEC_DEBUG_MIN )
		debugSec = DEV_WAIT_SEC_DEBUG_MIN;


	debugSec = 30; // fenghuiw
	
	_pollCnt = debugSec * (1000 / DEV_POLL_GAP_MS );

	dprintf( "debugSec=%d", debugSec );
	
}



//====================================================
static void _sToZigbeeUartPassDebug( void )
{
	_pollCnt =  UART_PASS_POLL_CNT;
}

//====================================================
static void _sToZigbeeErr( void )
{ 
	// 错误时不重新记时
	//_pollCnt =  ZIGBEE_ERR_POLL_CNT;
	
}


//====================================================
static void _sToMasterErr( void )
{
	// 错误时不重新记时
	//_pollCnt =  MASTER_ERR_POLL_CNT;
}

//====================================================



static void _devStateSet( EN_DEV_STATE s )
{	
	dprintf( "\r\nDS%d-%d", _devS,s );

	if( _devS == s ) // newwait
	{
		return;
	}


	switch( s )
	{
	case DEV_STATE_READ_CTRL_INFO:
		_sToReadCtrlInfo();
		break;	

	case DEV_STATE_DBG:
		_sToDebug();
		break;

	case DEV_STATE_SLEEP:
		_sToSleep();
		break;


	case DEV_STATE_INIT:
		_sToInit();
		break;

	case DEV_STATE_UART_PASS:
		_sToZigbeeUartPassDebug();
		break;			

	case DEV_STATE_ERR_HINT_ZIGBEE:
		_sToZigbeeErr();
		break;

	case DEV_STATE_ERR_HINT_MASTER:
		_sToMasterErr();
		break;
		
	default:
		dprintf("\r\n****** _devStateSet Err ****");
		return;

		
	}


	
	_devS = s;

}






//=====================================================

/*
static void _printSleepSec( void )
{
	dprintf( "sleepSec=%d", cfgSleepSecGet() );
}
*/


static void _onReadCtrlInfoEnd( void )
{
	//gB1.ctrlPackTx = gB1.ctrlPackFinish = 0; // 打开后会影响到休眠
	
	if( snChIs485() || gB1.isDebug || ctrlPackRxIsDbg() ) // 485时不休眠 ,转为DEBUG态
	{
		_devStateSet( DEV_STATE_DBG );
	}
	else
	{
		_devStateSet( DEV_STATE_SLEEP );
	}
}


static void _devOnEvent( EN_DEV_EVENT e, void *data)
{	
	
	switch( _devS )
	{
	case DEV_STATE_DBG:	
		if( DEV_EVENT_DBG_END == e )
		{
			//dprintf( "sleepSec=%d", cfgSleepSecGet() );
			//dprintf( "debugEnd");

			
			_devStateSet( DEV_STATE_READ_CTRL_INFO );
		}
		break;
			
	case DEV_STATE_READ_CTRL_INFO:	
		if( DEV_EVENT_READ_CTRL_INFO_END == e )
		{
			_onReadCtrlInfoEnd();
		}
		break;

	case DEV_STATE_SLEEP:	
		if( DEV_EVENT_SLEEP_END == e )
		{
			_devStateSet( DEV_STATE_READ_CTRL_INFO );
		}
		break;

	case DEV_STATE_UART_PASS:	
		if( DEV_EVENT_UARTPASS_TIMEOUT == e )
		{
			_devStateSet( DEV_STATE_DBG );
		}
		break;		
		
		
	case DEV_STATE_INIT:	
		if( DEV_EVENT_INIT_END == e )
		{
			_devStateSet( DEV_STATE_DBG );
		}
		break;

	case DEV_STATE_NOT_DEF:	
		if( DEV_EVENT_INIT_START == e )
		{
			_devStateSet( DEV_STATE_INIT );
		}
		break;	
		
	default:
		dprintf("\r\n****** _devOnEvent Err ****");
		return;

	}

	
}



//-----on err to ok------------------------------------------------------------------
static void _onErrToOk( u32 errBit )
{
	valBitSet0( &_devErrBit, errBit);

	if( devStateIsUartPass() )
		return;
	
	if( _devErrBit == 0 )
	{
		_devStateSet(  DEV_STATE_DBG );
		return;
	}
	else
	{
		dprintf("_onErrToOk_devErrBit=%08X", _devErrBit );

		if( _devErrBit & DEV_ERR_BIT_ZIGBEE )
		{
			_devStateSet( DEV_STATE_ERR_HINT_ZIGBEE );
		}
		else  if( _devErrBit & DEV_ERR_BIT_MASTER )
		{
			_devStateSet( DEV_STATE_ERR_HINT_MASTER );
		}
		else
		{
			dprintf( " onErrToOk_X1" );
		}
	}
}



static void _onErrToOkEvent( EN_DEV_EVENT e, void *data)
{
	dprintf("_onErrToOk_e=%d", e );
	
	switch( e )
	{
	case DEV_EVENT_ZIGBEE_STATE_TO_OK: // 
		_onErrToOk( DEV_ERR_BIT_ZIGBEE );	
		break;

	case DEV_EVENT_MASTER_STATE_TO_OK: // 
		_onErrToOk( DEV_ERR_BIT_MASTER );	
		break;		
		
	default:
		dprintf("\r\n****** _onErrToOkEvent Err ****");
		return;
	}
}

//-----on err------------------------------------------------------------------

/*
当有多个错误时，报告的顺序是  zigbee --> 4G --> master
*/
static void _onErr( EN_DEV_STATE s, u32 errBit)
{
	valBitSet1( &_devErrBit, errBit);

	if( devStateIsUartPass() )
		return;
	
	if( devStateIsDbg() == FALSE ) // 只有 DEBUG 时才响应
		return;
	
	
	if( _devS > DEV_STATE_ERR ) // 当前是错误态
	{
		if( errBit == DEV_ERR_BIT_ZIGBEE ) // zigbee错误， 无论当前是什么错误，都先报告最低级的 zigbee错误
		{
			if( _devS > DEV_STATE_ERR_HINT_ZIGBEE ) // zigbee错误，如果当前的错误级别高于zigbee, 就切换到zigbee
			{
				_devStateSet( s );
			}
		}
		else  if( errBit == DEV_ERR_BIT_MASTER )
		{			
			if( _devS > DEV_STATE_ERR_HINT_MASTER )// Master错误，如果当前的错误级别高于Master, 就切换到Master
			{
				_devStateSet( s );
			}
		}
	}
	else 
	{
		_devStateSet( s ); // 当前是正常态，直接切换到错误
	}
}


static void _onErrHintEvent( EN_DEV_EVENT e, void *data)
{
	dprintf("_onErrHintEvent_e=%d", e );
	
	switch( e )
	{
	case DEV_EVENT_ERR_HINT_ZIGBEE_STATE_NG: // 
		_onErr(DEV_STATE_ERR_HINT_ZIGBEE, DEV_ERR_BIT_ZIGBEE);	
		break;
				
	case DEV_EVENT_ERR_HINT_MASTER_STATE_NG: // 
		_onErr(DEV_STATE_ERR_HINT_MASTER, DEV_ERR_BIT_MASTER );	
		break;	
		
	default:
		dprintf("\r\n****** _onErrHintEvent Err ****");
		return;
	}
}



void devOnEvent( EN_DEV_EVENT e, void *data)
{
	//uartSend2("e", e, 0 );
	
	if( e > DEV_EVENT_ERR_TO_OK )
	{
		_onErrToOkEvent( e,data);
		return;
	}
	else if( e > DEV_EVENT_ERR_STOP )
	{
		//_onErrStopEvent( e,data);
		return;
	}
	else if( e > DEV_EVENT_ERR_REBOOT )
	{
		//_onErrRebootEvent( e,data);
		return;
	}
	else if( e > DEV_EVENT_ERR_HINT )
	{
		_onErrHintEvent( e,data);
		return;
	}
	else if( e > DEV_EVENT_WARNING )
	{
		//_onWarningEvent( e,data);
		return;
	}
	else if( e == DEV_EVENT_UART_PASS_START ) // 任意态都要响应 
	{
		_devStateSet( DEV_STATE_UART_PASS );
	}
	else if( e == DEV_EVENT_UART_PASS_END ) // 任意态都要响应 
	{
		if( devErrIsHaveZigbee() )
		{
			_devStateSet( DEV_STATE_ERR_HINT_ZIGBEE );
		}
		else if ( devErrIsHaveMaster() )
		{
			_devStateSet( DEV_STATE_ERR_HINT_MASTER );
		}
		else
		{
			_devStateSet( DEV_STATE_DBG );
		}
	}
	

	if( _devS > DEV_STATE_ERR ) // 当前状态是ERR态
	{
		if(  e == DEV_EVENT_CMD_REBOOT )
		{
			// _reboot();
		}
		else if (  e == DEV_EVENT_ERR_TIMEOUT  )
		{
			gB1.ctrlPackFinish = 1;
			_devStateSet( DEV_STATE_SLEEP );
		}

		return;
	}
	
	_devOnEvent( e, data);
}















void devStateInit( void )
{
	_devErrBit = 0;
	
	_devStateSet(  DEV_STATE_NOT_DEF );


	devOnEvent(DEV_EVENT_INIT_START, NULL );
	devOnEvent(DEV_EVENT_INIT_END, NULL );
}








