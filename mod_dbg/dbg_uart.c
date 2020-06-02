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
#include "dri_uart_debug.h"

#include "timer.h"
#include "uart_pack.h"

#include "dbg_uart.h"

//#include "zgb_uart.h"
//#include "dev_state.h"


#define DBG_Q_LEN  (128)
#define DBG_QV_LEN (256)

//=================================================

static UART_PACK  _stUartPackDbg;


//==========================================================================

static void _txData( void )
{
	QUEUE_ElemType  elem;
	
	if( queueDe( _stUartPackDbg.pTxQ, &elem) == EN_QUEUE_RST_OK )
	{	
		LPUart_SendDataIt( DBG_UART_HANDLE, elem );

		_stUartPackDbg.b.txFinish = FALSE;
	}
}


static void _dbgIRQHandler( void )
{
	U8 tempData;

	if(LPUart_GetStatus(DBG_UART_HANDLE, LPUartTC))
	{
		LPUart_ClrStatus(DBG_UART_HANDLE, LPUartTC);   ///<清发送中断请求
		
		if( queueIsEmpty( _stUartPackDbg.pTxQ ) == TRUE )
		{
			_stUartPackDbg.b.txFinish        = TRUE;
			_stUartPackDbg.b.callTxFinishFun = TRUE;
			
			_stUartPackDbg.txCnt    = _stUartPackDbg.txGapCnt;
			
			return;
		}

		_stUartPackDbg.b.txFinish = FALSE;

		if( queueDe( _stUartPackDbg.pTxQ, &tempData) == EN_QUEUE_RST_OK )
		{	
			//LPUart_SendDataIt( DBG_UART_HANDLE, tempData );
			DBG_UART_HANDLE->SBUF_f.DATA = tempData; 
		}
		
	}

	if(LPUart_GetStatus(DBG_UART_HANDLE, LPUartRC))    ///接收数据
	{
		LPUart_ClrStatus(DBG_UART_HANDLE, LPUartRC);   ///<清接收中断请求
		
		//tempData = LPUart_ReceiveData(DBG_UART_HANDLE);  ///读取数据
		tempData = DBG_UART_HANDLE->SBUF_f.DATA;  ///读取数据

		queueEn( _stUartPackDbg.pRxQ, tempData );
		
		_stUartPackDbg.rxCnt = _stUartPackDbg.rxGapCnt;

		_stUartPackDbg.b.rxFinish = FALSE;

	}

}




static u8 _pDbgBuf[DBG_Q_LEN];
static u32 _dbgLen;



static void _dbgUartPollCB( void )
{
	int i;
	u8 *pTempU8;
	

	// ===  TX  ===
	if( _stUartPackDbg.b.txFinish == TRUE )
	{
		if( _stUartPackDbg.txCnt != 0 )
			_stUartPackDbg.txCnt--;
	
		// 间隔时间到
		if( _stUartPackDbg.txCnt == 0 )
		{
			if( IsEmptyQueueV( _stUartPackDbg.pTxQV ) == FALSE ) // 有数据项要发送
			{
				if( deQueueV( _stUartPackDbg.pTxQV, _pDbgBuf, &_dbgLen ) == TRUE )
				{
					for( i = 0, pTempU8 = _pDbgBuf; i < _dbgLen; i++, pTempU8++ )
					{
						queueEn( _stUartPackDbg.pTxQ, *pTempU8 );
					}
					_txData();
				}
			}
		}
	}

	// ===  txFinishCB ===
	if( _stUartPackDbg.b.callTxFinishFun )
	{
		_stUartPackDbg.b.callTxFinishFun = FALSE;

		if( _stUartPackDbg.txFinishCB )
			_stUartPackDbg.txFinishCB();
	}


	//=====================================================================
	
	// ===  RX  ===
	if( _stUartPackDbg.b.rxFinish == FALSE )
	{
		if( _stUartPackDbg.rxCnt != 0 )
			_stUartPackDbg.rxCnt--;

		// 间隔时间到
		if( _stUartPackDbg.rxCnt == 0 )
		{
			for( i = 0, pTempU8 = _pDbgBuf; i < DBG_Q_LEN; i++, pTempU8++ )
			{
				if( queueDe( _stUartPackDbg.pRxQ, pTempU8 ) == EN_QUEUE_RST_ERR_DE_EMPTY)
					break;
			}

			enQueueV( _stUartPackDbg.pRxQV, _pDbgBuf, i );

			 _stUartPackDbg.b.rxFinish = TRUE;
		}
	}


	// ===	rxFunCB	===
	if( IsEmptyQueueV( _stUartPackDbg.pRxQV )  )
		return;

	deQueueV( _stUartPackDbg.pRxQV, _pDbgBuf, &_dbgLen );

	if( _stUartPackDbg.rxFunCB )
	{
		_stUartPackDbg.rxFunCB( _pDbgBuf, _dbgLen );
	}
	
}



void dbgUartTx( u8 *pBuf, u32 len )
{
	enQueueV( _stUartPackDbg.pTxQV, pBuf, len );
}

static void _dbgUartRxCB( u8 *str,	u8 len );

static void _dbgUartRx( u8 *pBuf, u32 len )
{
	_dbgUartRxCB( pBuf, len );
}


static void _dbgUartTxFinish( void )
{
	//dprintf( "\r\n tx finish" );
}



void dbgUartInit( void )
{
	#define DBG_TX_GAP_MS     (4)
	#define DBG_RX_GAP_MS     (4)
	#define DBG_TIMER_GAP_MS  (2)

	UART_PACK_PARA stPara;

	
	stPara.rxQLen     = DBG_Q_LEN;
	stPara.txQLen     = DBG_Q_LEN;
	stPara.rxQVLen    = DBG_QV_LEN;
	stPara.txQVLen    = DBG_QV_LEN;
	stPara.rxGapMsCnt = DBG_RX_GAP_MS/DBG_TIMER_GAP_MS;
	stPara.txGapMsCnt = DBG_TX_GAP_MS/DBG_TIMER_GAP_MS;

	stPara.rxFunCB    = _dbgUartRx;
	stPara.txFinishFunCB = _dbgUartTxFinish;

	
	uartPackInit( &_stUartPackDbg, &stPara );
	

	_stUartPackDbg.timerId = timerStart( DBG_TIMER_GAP_MS/TIMER_UNIT_MS,  TIMER_REPEAT_FOREVER,  _dbgUartPollCB );


	driUartDebugIrqCBset( _dbgIRQHandler );

}



//==================================================
//==================================================

void dprintf(const char *pFormat, ...)
{
	#define PRINT_LEN_MAX  (DBG_Q_LEN)
	
	char pBuf[PRINT_LEN_MAX] = {0};
	
	u32 formatLen;
	
	va_list args;



	//- start ----- 透传时不打印任何信息 ----------------------
	#if 0// fenghuiw
	if( devStateIsUartPass() ) 
		return;
	#endif
	//-- end ---------------------------------------------------


	
	va_start (args, pFormat);
	
	formatLen = vsnprintf (pBuf, PRINT_LEN_MAX, pFormat, args);

	if( formatLen > 0)
	{
		dbgUartTx(  (u8 *)pBuf, formatLen );
	}
	else
	{
		dbgUartTx(  (u8 *)"myPrintf NG", 11 );
	}
	
	va_end (args);

}





void dprintfBuf( char *pStr, u8 *pBuf, u32 len, u8 print0D0A )
{
	u32 i;
	
	if(pStr)
		dprintf(pStr);
	

	for( i = 0; i < len; i++ )
	{
		dprintf( " %02X", pBuf[i]);
	}


	if( print0D0A )
		dprintf("\r\n");
}



void debugUartTxPass( u8 *str,  u8 len ) 
{	
	enQueueV( _stUartPackDbg.pTxQV, str, len);
}




static void _dbgUartRxCB( u8 *str,  u8 len )
{
	
	#include "dbg_cmd.h"
	
	//dprintf( (const char *)str );
	
	#if 0 // fenghuiw //-----------------------------------
		if( debugCmd( str, len ) == TRUE )
			return;
		
		if( devStateIsUartPass() )
		{
			if( debugPassIsZigbee() )
			{
				modUartZigbeeTx(str, len); // 透传
			}

		}
		else
		{
			dprintf("debugRx unkown Str:%s\r\n", str);
			dprintfBuf("debugRx unkown Hex:", str, len, 1);
		}

	#else//-----------------------------------

		if( debugCmd( str, len ) == TRUE )
			return;
		

		dbgUartTx(str, len);


	#endif//-----------------------------------
	
}





#ifdef TEST_MOD_DBG_UART


static void testModDebugTimerCB( void )
{
	#define TYPE_CNT (5)
	
	static u8 _cnt = 0;
	
	char pStr[] = "string";

	int ia = -123456;

	float fa = 12.3456789;

	u32 u32a = 0x12345678;

	u8 pBuf[] = {0, 1,0xFE, 0xC0, 0x18, 0x00, 0xff, 0x1c};
	
	if( _cnt % TYPE_CNT == 0 )
		dprintf( "pStr = %s", pStr);
	else if( _cnt % TYPE_CNT == 1 )
		dprintf( "ia = %d", ia);
	else if( _cnt % TYPE_CNT == 2 )
		dprintf( "fa = %f", fa);
	else if( _cnt % TYPE_CNT == 3 )
		dprintf( "u32a = %x ", u32a);
	else if( _cnt % TYPE_CNT == 4 )
	{
		dprintfBuf("pBuf = ", pBuf, sizeof(pBuf)/sizeof(u8), 0);
	}

	_cnt++;

	
}



void testModDbgUart( void )
{
	timerStartSec( 1,  TIMER_REPEAT_FOREVER,  testModDebugTimerCB );

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

