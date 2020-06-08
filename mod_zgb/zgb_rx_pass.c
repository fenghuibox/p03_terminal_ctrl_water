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
#include "dbg_uart.h"
#include "zgb_rx_pass.h"




// zigbee rx --> 4g


static QURUE_V *_pQVrx;






u8 modUartZgbPassRxIsFull( u8 len )
{
	if( getUnuseLenQueueV(_pQVrx ) - 1 < len )
		return TRUE;

	return FALSE;
}

u8 modUartZgbPassRxIsEmpty( void )
{
	return IsEmptyQueueV(_pQVrx );
}


void modUartZgbPassRxClear( void )
{
	clearQueueV(_pQVrx );
}



// 入队
u8 modUartZgbPassRxEn( u8 *pData, u8 len )
{
	if( enQueueV(_pQVrx, pData, len ) == FALSE )
	{
		dprintf("\r\nZPIX");

		return FALSE;
	}
	else
	{
		//modUartDebugTxStrU32("\r\nZPI:", len );
		
		//modUartDebugTx0("\r\nZNOK:");
		//modUartDebugTxU8buf( pData, len );
		//modUartDebugTxU8buf( pData, len );
	}

	return TRUE;
}

// 出队
u8 modUartZgbPassRxDe( u8 *pData, u32 *pLen )
{
	if( deQueueV(_pQVrx, pData, pLen ) == FALSE )
	{
		dprintf("\r\nZRDeX");

		return FALSE;
	}

	return TRUE;
}





void zgbPassRxInit( void )
{
	_pQVrx = initQqueueV( 2048 );
	if( _pQVrx == NULL )
	{
		dprintf("\r\nmodUartZgbPassRxInit x1");
		return;
	}

}


/*

//static u8 _pNodeData[240];

u8 modUartZgbPassTo4g( void )
{
	#include "g4_cmd.h" 

	ST_4G_CMD_QMT_PUBEX_BUF *pBuf;
	
	if( IsEmptyQueueV(_pQVrx ) )
		return FALSE;

	
	pBuf = g4cmdQmtPubexPass(); 
	if( pBuf == NULL )
		return FALSE;
	
	modUartZgbPassRxDe( pBuf->pBuf, &pBuf->len );

	return TRUE;
	
}

*/
