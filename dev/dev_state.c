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
#include "timer.h"
#include "dbg_uart.h"

//#include "dri_includes.h"
//#include "mod_includes.h"



#include "dev_state.h"
#include "cfg_base.h"



#define DEV_POLL_GAP_MS  (50)

#define IDLE_POLL_CNT   DEV_WAIT_SEC_IDLE * (1000 / DEV_POLL_GAP_MS )
#define CFG_POLL_CNT    DEV_WAIT_SEC_CFG  * (1000 / DEV_POLL_GAP_MS )
#define WORK_POLL_CNT   DEV_WAIT_SEC_WORK * (1000 / DEV_POLL_GAP_MS )



#define ZIGBEE_ERR_POLL_CNT      DEV_WAIT_SEC_ERR_HINT * (1000 / DEV_POLL_GAP_MS ) // ��ǰ״̬�µȴ���ʱ��
#define ZIGBEE_ERR_POLL_GAP      (1000/DEV_POLL_GAP_MS) // ÿ1.0����һ��״̬


#define MASTER_ERR_POLL_CNT    DEV_WAIT_SEC_ERR_HINT * (1000 / DEV_POLL_GAP_MS ) // ��ǰ״̬�µȴ���ʱ��
#define MASTER_ERR_POLL_GAP   (2000/DEV_POLL_GAP_MS)// ÿ2����һ��״̬

//=====================================================
static EN_DEV_STATE _devS;

static u32 _devErrBit;

static u32 _pollCnt;


//====================================================
static void _devStateSet( EN_DEV_STATE s );
//====================================================
static void _sToZigbeeErr( void );
static void _sToMasterErr( void );


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


u8 devStateIsIdle( void )
{
	return _devS == DEV_STATE_IDLE ? 1 : 0;
}


u8 devStateIsWork( void )
{
	return _devS == DEV_STATE_WORK ? 1 : 0;
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


static u8 devHaveWork( void )
{
	
	#if 0//fenghuiw
	
	#include "sg_ch.h"
	#include "zgb_uart.h"
	#include "g4_uart.h"
	#include "ipad_uart.h"
	
	if( modUartZigbeeIsIdle() == FALSE )
		return TRUE;

	
	if(  sgChIsIpad() )
	{
		if( ipadUartIsIdle() == FALSE )
			return TRUE;
	}
	else
	{
		if( modUart4gIsIdle() == FALSE )
			return TRUE;
	}
	
	return FALSE;
	
	#else
	
	return FALSE;
	#endif
}


static void _sToIdle( void ); // dev state to idle

static void _devIdlePoll( void )
{
	//if( _devS != DEV_STATE_IDLE )
	//	return;

	if( cfgWorkStateIsNormal() == FALSE )
	{
		_devStateSet( DEV_STATE_CFG );
		return;
	}

	// work state is normal
	if( devHaveWork() == TRUE  )
	{
		_devStateSet( DEV_STATE_WORK );
		return;
	}

	if( _pollCnt )
	{
		_pollCnt--;
	}
	else
	{
		#if 0 // fenghuiw
		// ����ʱ�䵽
		// to sleep/ close / idle ? fenghuiwait

		_sToIdle();

		#include "sg_g2s.h"

		g2sHeartbeat();
		#endif
	}
		
}

static void _devWorkPoll( void )
{
	if( cfgWorkStateIsNormal() == FALSE )
	{
		_devStateSet( DEV_STATE_CFG );
		return;
	}
		
	if( devHaveWork() == FALSE )
	{
		if( _pollCnt )
		{
			_pollCnt--;
			return;
		}
		else
		{
			// ���� �� ���� �Ĺ���ʱ�� ��
			// to sleep fenghuiwait
			_devStateSet( DEV_STATE_IDLE );
		}
		
		return;
	}
		
}


static void _devCfgPoll( void )
{
	if( cfgWorkStateIsNormal() == TRUE )
	{
		_devStateSet( DEV_STATE_IDLE );
		return;
	}
	

	if( _pollCnt )
	{
		_pollCnt--;
	}
	else
	{
		#if 0
		// ����ʱ�䵽
		// to idle

		if( modCfgWorkSecGet() ==  CFG_IDLE_SEC_MAX )
		{
			_devStateSet( DEV_STATE_IDLE );
		}
		else
		{
			// to sleep ?
		}
		#endif
	}
		
}


static void _devZigbeeErrPoll( void )
{
#if 1
	//#include "zgb_cmd.h"

	
	if( (_pollCnt % ZIGBEE_ERR_POLL_GAP) == 0 )
	{
		//zcmdWorkStateGet(); fenhuiw
	}


	if( _pollCnt )
	{
		_pollCnt--;
	}
	else
	{
		// �������̬ʱ�䵽
		_sToZigbeeErr();
	}

#endif
}






static void _devMasterErrPoll( void )
{
#if 1
	//#include "sg_master_state.h"

	
	if( (_pollCnt % MASTER_ERR_POLL_GAP) == 0 )
	{
		//modMasterStatePoll(); fenghuiw
	}


	if( _pollCnt )
	{
		_pollCnt--;
	}
	else
	{
		// ��������̬ʱ�䵽
		_sToMasterErr();
	}
#endif	
}



static void _devTimerPollCB( void ) // dev state to init
{
	
	if ( _devS == DEV_STATE_WORK  )
	{
		_devWorkPoll();
	}
	else if( _devS == DEV_STATE_IDLE  )
	{
		_devIdlePoll();
	}
	else if ( _devS == DEV_STATE_CFG  )
	{
		_devCfgPoll();
	}
	else if ( _devS == DEV_STATE_ERR_HINT_ZIGBEE )
	{
		_devZigbeeErrPoll();
	}	
	else if ( _devS == DEV_STATE_ERR_HINT_MASTER )
	{
		_devMasterErrPoll();
	}	


	

}



static void _sToInit( void ) // dev state to init
{
	_devS      = DEV_STATE_INIT;

	timerStart( DEV_POLL_GAP_MS/TIMER_UNIT_MS, TIMER_REPEAT_FOREVER, _devTimerPollCB);
}






//====================================================
static void _sToIdle( void ) // dev state to idle
{	
#if 0
	#define CFG_IDLE_SEC_MAX  (0xFFFFFFFF)

	//motorIdle();
	u32 sec;

	sec = cfgWorkSecGet();

	if( sec == 0 )
	{
		_pollCnt = 2;
	}
	else if( sec ==  CFG_IDLE_SEC_MAX )
	{
		_pollCnt =	IDLE_POLL_CNT;		
	}
	else
	{
		_pollCnt =  sec * (1000 / DEV_POLL_GAP_MS );
	}
#else

	_pollCnt =	IDLE_POLL_CNT;// fenghuiw


#endif

	
}





//====================================================
static void _sToWork( void )
{
	//motorWork();

	_pollCnt =  WORK_POLL_CNT;
	
}

//====================================================
static void _sToCfg( void )
{
	_pollCnt =  CFG_POLL_CNT;
}


//====================================================
static void _sToZigbeeUartPassDebug( void )
{
	_pollCnt =  CFG_POLL_CNT;
}

//====================================================
static void _sToZigbeeErr( void )
{
	_pollCnt =  ZIGBEE_ERR_POLL_CNT;
}


//====================================================
static void _sToMasterErr( void )
{
	_pollCnt =  MASTER_ERR_POLL_CNT;
}

//====================================================



static void _devStateSet( EN_DEV_STATE s )
{	
	dprintf( "\r\nDS%d-%d", _devS,s );

	if( _devS == s ) // newwait
	{
		if( s == DEV_STATE_IDLE )
		{
			_sToIdle();
		}
		return;
	}


	switch( s )
	{
	case DEV_STATE_WORK:
		_sToWork();
		break;

	case DEV_STATE_INIT:
		_sToInit();
		break;
		
	case DEV_STATE_IDLE:
		_sToIdle();
		break;
		
	case DEV_STATE_CFG:
		_sToCfg();
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



static void _devOnEvent( EN_DEV_EVENT e, void *data)
{	
	switch( _devS )
	{
	case DEV_STATE_CFG:
		if( DEV_EVENT_WORK_START == e )
		{
			_devStateSet( DEV_STATE_IDLE );
		}
		break;

	case DEV_STATE_WORK:
		if( DEV_EVENT_CFG_START == e )
		{
			_devStateSet( DEV_STATE_CFG );
		}

		break;

		
	case DEV_STATE_IDLE:
		if( DEV_EVENT_WORK_START == e )
		{
			_devStateSet( DEV_STATE_WORK );
		}
		else if ( DEV_EVENT_CFG_START== e )
		{
			_devStateSet( DEV_STATE_CFG );
		}
		else if ( DEV_EVENT_IDLE_END == e )
		{
			_devStateSet( DEV_STATE_IDLE ); // fenghuiwait
		}
		break;

		
	case DEV_STATE_INIT:	
		if( DEV_EVENT_INIT_END == e )
		{
			_devStateSet( DEV_STATE_IDLE );
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
		_devStateSet(  DEV_STATE_IDLE );
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
���ж������ʱ�������˳����  zigbee --> 4G --> master
*/
static void _onErr( EN_DEV_STATE s, u32 errBit)
{
	valBitSet1( &_devErrBit, errBit);

	if( devStateIsUartPass() )
		return;
	
	
	if( _devS > DEV_STATE_ERR ) // ��ǰ�Ǵ���̬
	{
		if( errBit == DEV_ERR_BIT_ZIGBEE ) // zigbee���� ���۵�ǰ��ʲô���󣬶��ȱ�����ͼ��� zigbee����
		{
			if( _devS > DEV_STATE_ERR_HINT_ZIGBEE ) // zigbee���������ǰ�Ĵ��󼶱����zigbee, ���л���zigbee
			{
				_devStateSet( s );
			}
		}
		else  if( errBit == DEV_ERR_BIT_MASTER )
		{			
			if( _devS > DEV_STATE_ERR_HINT_MASTER )// Master���������ǰ�Ĵ��󼶱����Master, ���л���Master
			{
				_devStateSet( s );
			}
		}
	}
	else 
	{
		_devStateSet( s ); // ��ǰ������̬��ֱ���л�������
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
	else if( e == DEV_EVENT_UART_PASS_START ) // ����̬��Ҫ��Ӧ 
	{
		_devStateSet( DEV_STATE_UART_PASS );
	}
	else if( e == DEV_EVENT_UART_PASS_END ) // ����̬��Ҫ��Ӧ 
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
			_devStateSet( DEV_STATE_IDLE );
		}
	}
	



	if( _devS > DEV_STATE_ERR ) // ��ǰ״̬��ERR̬
	{
		if(  e == DEV_EVENT_CMD_REBOOT )
		{
			// _reboot();
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








