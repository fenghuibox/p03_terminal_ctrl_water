
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

#include "uart_pack.h"
#include "timer.h"









void uartPackInit( UART_PACK *pstUartPack,  UART_PACK_PARA *pstUartPackPara)
{	
	pstUartPack->pRxQ = queueInit( pstUartPackPara->rxQLen, NULL );
	if( pstUartPack->pRxQ == NULL )
	{
		comMallocEr();
		return;
	}

	pstUartPack->pTxQ = queueInit( pstUartPackPara->txQLen, NULL );
	if( pstUartPack->pTxQ == NULL )
	{
		comMallocEr();
		return;
	}

	pstUartPack->pRxQV = initQqueueV( pstUartPackPara->rxQVLen );
	if( pstUartPack->pRxQV == NULL )
	{
		comMallocEr();
		return;
	}

	pstUartPack->pTxQV = initQqueueV( pstUartPackPara->txQVLen );
	if( pstUartPack->pTxQV == NULL )
	{
		comMallocEr();
		return;
	}	

	pstUartPack->b.txFinish = TRUE;
	pstUartPack->b.rxFinish = TRUE;
	pstUartPack->b.callTxFinishFun = FALSE;

	pstUartPack->rxGapCnt = pstUartPackPara->rxGapMsCnt;
	pstUartPack->txGapCnt = pstUartPackPara->txGapMsCnt;

	pstUartPack->rxCnt = 0;
	pstUartPack->txCnt = 0;

	pstUartPack->rxFunCB    = pstUartPackPara->rxFunCB;
	pstUartPack->txFinishCB = pstUartPackPara->txFinishFunCB;
	

	//pstUartPack->timerId = timerStart( 2/TIMER_UNIT_MS,  TIMER_REPEAT_FOREVER,  testDbgUartTxPollCB );

	
	
}



#endif


 
