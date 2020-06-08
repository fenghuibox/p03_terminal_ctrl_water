
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
//#include "dbg.h"
#include "dbg_uart.h"


#include "dev_state.h"

//--------------------------------

#include "zgb_cmd.h"
#include "zgb_unpack.h"
#include "zgb_rx_pass.h"
#include "zgb_g2n.h"


#include "f_txt_frame.h"

//




//#include "zgb_uart.h"
//#include "dev_state.h"


#define ZGB_Q_LEN  (256)
#define ZGB_QV_LEN (1024)

//=================================================

static UART_PACK  _stUartPackZgb;


//==========================================================================

static void _txData( void )
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
					_txData();
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



u8 zgbUartIsIdle( void )
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




void zgbUartTx( u8 *pBuf, u32 len )
{
	enQueueV( _stUartPackZgb.pTxQV, pBuf, len );
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
	#define ZGB_TX_GAP_MS     (4)
	#define ZGB_RX_GAP_MS     (4)
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
	dprintfBuf("zrx:", str, len, 1 );
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


