/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/

// sn: Server and node communication	服务器和节点通信

#include "com_includes.h"

#include "timer.h"
#include "dbg_uart.h"




static QURUE_V *_pQVsnRx;






u8 snRxQueueIsFull( u8 len )
{
	if( getUnuseLenQueueV(_pQVsnRx ) - 1 < len )
		return TRUE;

	return FALSE;
}

u8 snRxQueueIsEmpty( void )
{
	return IsEmptyQueueV(_pQVsnRx );
}



void snRxQueueClear( void )
{
	clearQueueV(_pQVsnRx );
}




// 入队
u8 snRxQueueEn( u8 *pData, u8 len )
{
	if( enQueueV(_pQVsnRx, pData, len ) == FALSE )
	{
		dprintf("\r\nSNIX");

		return FALSE;
	}
	else
	{
		//modUartDebugTxStrU32("\r\nGPI:", len );
	}

	return TRUE;
}

// 出队
u8 snRxQueueDe( u8 *pData, u32 *pLen )
{
	if( deQueueV(_pQVsnRx, pData, pLen ) == FALSE )
	{
		dprintf("\r\nsnRxQueueDe x1");

		return FALSE;
	}

	return TRUE;
}





void snRxQueueInit( void )
{
	_pQVsnRx = initQqueueV( 512 );
	if( _pQVsnRx == NULL )
	{
		dprintf("\r\nsnRxQueueInit x1");
		return;
	}
}


