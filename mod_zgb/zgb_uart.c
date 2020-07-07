
#if 1
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
#include "dri_uart_zgb.h"

#include "uart_pack.h"
#include "zgb_uart.h"

#include "timer.h"

#include "dbg.h"
//#include "dbg_uart.h"


#include "dev_state.h"

//--------------------------------

#include "zgb_cmd.h"

#include "f_txt_frame.h"

//

#include "zgb_uart.h"
#include "dev_state.h"

#include "sn_n2s.h"

#define ZGB_UART_PRINT 


#define ZGB_Q_LEN  (256)
#define ZGB_QV_LEN (1024)

//=================================================

static UART_PACK  _stUartPackZgb;


//==========================================================================

static void _zgbTxData( void )
{
	QUEUE_ElemType  elem;
	
	if( queueDe( _stUartPackZgb.pTxQ, &elem) == EN_QUEUE_RST_OK )
	{	
		Uart_SendDataIt( ZGB_UART_HANDLE, elem );
		

		_stUartPackZgb.b.txFinish = FALSE;
	}
}


static void _zgbIRQHandler( void )
{
	U8 tempData;

	if(Uart_GetStatus(ZGB_UART_HANDLE, UartTC))
	{
		Uart_ClrStatus(ZGB_UART_HANDLE, UartTC);   ///<清发送中断请求
		
		if( queueIsEmpty( _stUartPackZgb.pTxQ ) == TRUE )
		{
			_stUartPackZgb.b.txFinish        = TRUE;
			_stUartPackZgb.b.callTxFinishFun = TRUE;
			
			_stUartPackZgb.txCnt    = _stUartPackZgb.txGapCnt;
			
			return;
		}

		_stUartPackZgb.b.txFinish = FALSE;

		if( queueDe( _stUartPackZgb.pTxQ, &tempData) == EN_QUEUE_RST_OK )
		{	
			//Uart_SendDataIt( ZGB_UART_HANDLE, tempData );
			ZGB_UART_HANDLE->SBUF_f.DATA = tempData; 
		}
		
	}

	if(Uart_GetStatus(ZGB_UART_HANDLE, UartRC))    ///接收数据
	{
		Uart_ClrStatus(ZGB_UART_HANDLE, UartRC);   ///<清接收中断请求
		
		//tempData = Uart_ReceiveData(ZGB_UART_HANDLE);  ///读取数据
		tempData = ZGB_UART_HANDLE->SBUF_f.DATA;  ///读取数据

		queueEn( _stUartPackZgb.pRxQ, tempData );
		
		_stUartPackZgb.rxCnt = _stUartPackZgb.rxGapCnt;

		_stUartPackZgb.b.rxFinish = FALSE;

	}

}




static u8 _pZgbBuf[ZGB_Q_LEN];
static u32 _zgbLen;



static void _zgbUartPollCB( void )
{
	int i;
	u8 *pTempU8;
	

	// ===  TX  ===
	if( _stUartPackZgb.b.txFinish == TRUE )
	{
		if( _stUartPackZgb.txCnt != 0 )
			_stUartPackZgb.txCnt--;
	
		// 间隔时间到
		if( _stUartPackZgb.txCnt == 0 )
		{
			if( IsEmptyQueueV( _stUartPackZgb.pTxQV ) == FALSE ) // 有数据项要发送
			{
				if( deQueueV( _stUartPackZgb.pTxQV, _pZgbBuf, &_zgbLen ) == TRUE )
				{
					for( i = 0, pTempU8 = _pZgbBuf; i < _zgbLen; i++, pTempU8++ )
					{
						queueEn( _stUartPackZgb.pTxQ, *pTempU8 );
					}
					_zgbTxData();
				}
			}
		}
	}

	// ===  txFinishCB ===
	if( _stUartPackZgb.b.callTxFinishFun )
	{
		_stUartPackZgb.b.callTxFinishFun = FALSE;

		if( _stUartPackZgb.txFinishCB )
			_stUartPackZgb.txFinishCB();
	}


	//=====================================================================
	
	// ===  RX  ===
	if( _stUartPackZgb.b.rxFinish == FALSE )
	{
		if( _stUartPackZgb.rxCnt != 0 )
			_stUartPackZgb.rxCnt--;

		// 间隔时间到
		if( _stUartPackZgb.rxCnt == 0 )
		{
			for( i = 0, pTempU8 = _pZgbBuf; i < ZGB_Q_LEN; i++, pTempU8++ )
			{
				if( queueDe( _stUartPackZgb.pRxQ, pTempU8 ) == EN_QUEUE_RST_ERR_DE_EMPTY)
					break;
			}

			enQueueV( _stUartPackZgb.pRxQV, _pZgbBuf, i );

			 _stUartPackZgb.b.rxFinish = TRUE;
		}
	}


	// ===	rxFunCB	===
	if( IsEmptyQueueV( _stUartPackZgb.pRxQV )  )
		return;

	deQueueV( _stUartPackZgb.pRxQV, _pZgbBuf, &_zgbLen );

	if( _stUartPackZgb.rxFunCB )
	{
		_stUartPackZgb.rxFunCB( _pZgbBuf, _zgbLen );
	}
	
}



static u8 _zgbUartIsIdle( void )
{
	if( _stUartPackZgb.b.txFinish == TRUE )
	{
		if( IsEmptyQueueV( _stUartPackZgb.pTxQV )  )
		{
			if( _stUartPackZgb.b.rxFinish == TRUE  )
			{
				if( IsEmptyQueueV( _stUartPackZgb.pRxQV )  )
					return TRUE;
			}

			//return TRUE;
		}
	}

	return FALSE;
}




int zgbUartTx( u8 *pBuf, u16 len )
{
	#ifdef ZGB_UART_PRINT
		//dprintfBuf("ztx:", pBuf, len, 1 );
		//dprintf("zt%d", len);

		if( len > 23 )
			dprintfBuf("\nzt", pBuf + 20, len - 21, 1 );
		
	#endif

	
	return enQueueV( _stUartPackZgb.pTxQV, pBuf, len );
}



static void _zgbUartRxCB( u8 *str,	u8 len );

static void _zgbUartRx( u8 *pBuf, u32 len )
{
	_zgbUartRxCB( pBuf, len );
}


static void _zgbUartTxFinish( void )
{
	//dprintf( "\r\n tx finish" );
}



void zgbUartInit( void )
{
	#define ZGB_TX_GAP_MS     (10)
	#define ZGB_RX_GAP_MS     (10)
	#define ZGB_TIMER_GAP_MS  (2)

	UART_PACK_PARA stPara;

	
	stPara.rxQLen     = ZGB_Q_LEN;
	stPara.txQLen     = ZGB_Q_LEN;
	stPara.rxQVLen    = ZGB_QV_LEN;
	stPara.txQVLen    = ZGB_QV_LEN;
	stPara.rxGapMsCnt = ZGB_RX_GAP_MS/ZGB_TIMER_GAP_MS;
	stPara.txGapMsCnt = ZGB_TX_GAP_MS/ZGB_TIMER_GAP_MS;

	stPara.rxFunCB    = _zgbUartRx;
	stPara.txFinishFunCB = _zgbUartTxFinish;

	
	uartPackInit( &_stUartPackZgb, &stPara );
	

	_stUartPackZgb.timerId = timerStart( ZGB_TIMER_GAP_MS/TIMER_UNIT_MS,  TIMER_REPEAT_FOREVER,  _zgbUartPollCB );


	driUartZgbIrqCBset( _zgbIRQHandler );



	

}






static void _zgbUartRxCB( u8 *str,  u8 len )
{
	#ifdef ZGB_UART_PRINT
		//dprintfBuf("zr", str, len, 1 );
		//dprintf("zr%d", len);

	u8 pTemp[12];
	u32 val1, val2;

	if( len > 31  )
	{
		/*
		正常/调试	 1Byte |  0:正常  1：调试
		休眠时间	 4Byte |  单位：秒	(5的倍数)  (5 -- 600)
		命令控制	 1Byte |  0:关	1：开
		开启时长	 4Byte |  单位：秒	(最小60，偏差 5 )
		是否重启记时 1Byte |  0:否	1：重启记时
		*/
		memcpy(pTemp, str + 20, 11 );

		
		memcpy(&val1, pTemp + 1, 4 );
		memcpy(&val2, pTemp + 6, 4 );
		
		u32Image( (u8 *)&val1 );
		u32Image( (u8 *)&val2 );
		
		dprintf("%ds%dc%do%dr%d", pTemp[0], val1, pTemp[5], val2, pTemp[10] );
		
		//dprintfBuf("\nzr", str+20, len-21, 1 );
	}
	
	#endif

	if( len > 7 )
	{
		gN2sServerNgCnt = N2S_SERVER_NG_CNT;
	}

	
	// ---------- 透传态 --------------------
	if( devStateIsUartPass() )
	{
		if( debugPassIsZigbee() )
		{
			debugUartTxPass(str, len);// 透传
		}
		
		return;
	}
	
	// ---------- 正常态 --------------------
	// 第 1 层数据流
	if( zcmdRx(str, len ) == TRUE ) 
	{
		//modUartDebugTx0("zuart zcmd rx ok");
		return;
	}



	#include "sn_rx.h"
	snRx( str, len );
}




u8 zgbUartTxPoll( void ) // >50 ms
{
	if( devStateIsUartPass() )
		return TRUE;

	if( gB1.zgbWakeupFinish == 0 )
		return FALSE;


	//---- zigbee cmd ---------------
	if( zcmdTxCB() )
		return TRUE;

	//--- rf out --------------------
	return n2sCB();	// fenghuiwait 时间可能被 zcmdTxCB() 截获
}





u8 zgbUartIsIdle( void )
{

#if 1

	if( _zgbUartIsIdle() == FALSE )
		return FALSE;

	if( queueIsEmpty( _stUartPackZgb.pTxQ ) == FALSE )
		return FALSE;
	
	if( queueIsEmpty( _stUartPackZgb.pRxQ ) == FALSE )
		return FALSE;

	return TRUE;
	
#else

	if( IsEmptyQueueV( _stUartPackZgb.pTxQV ) == FALSE )
		return FALSE;

	if( queueIsEmpty( _stUartPackZgb.pTxQ ) == FALSE )
		return FALSE;

	if( IsEmptyQueueV( _stUartPackZgb.pRxQV ) == FALSE )
		return FALSE;

	if( queueIsEmpty( _stUartPackZgb.pRxQ ) == FALSE )
		return FALSE;

	return TRUE;
	
#endif
	
}






#ifdef TEST_MOD_ZGB_UART


static void _testZcmdDevInfoGet( void )
{
	const u8 pCmd[5] = {0xAB, 0xBC, 0xCD, 0xD1, 0xAA};

	zgbUartTx((u8 *)pCmd, 5 );
}



static void testModZgbTimerCB( void )
{
	#define TYPE_CNT (5)
	
	static u8 _cnt = 0;
	
	if( _cnt % TYPE_CNT == 0 )
		_testZcmdDevInfoGet();
	else if( _cnt % TYPE_CNT == 1 )
		_cnt = 0xFF;
	else if( _cnt % TYPE_CNT == 2 )
		;
	else if( _cnt % TYPE_CNT == 3 )
		;
	else if( _cnt % TYPE_CNT == 4 )
	{
		;
	}

	_cnt++;

	
}



void testModZgbUart( void )
{
	timerStartSec( 5,  TIMER_REPEAT_FOREVER,  testModZgbTimerCB );

}

/*  测试结果
[2020-04-30 10:47:53.620]# RECV ASCII>
pStr = string
[2020-04-30 10:47:54.628]# RECV ASCII>
ia = -123456
[2020-04-30 10:47:55.636]# RECV ASCII>
fa = 12.345679
[2020-04-30 10:47:56.643]# RECV ASCII>
u32a = 12345678 
[2020-04-30 10:47:57.653]# RECV ASCII>
pBuf =  00 01 FE C0 18 00 FF 1C
*/

#endif


#endif


