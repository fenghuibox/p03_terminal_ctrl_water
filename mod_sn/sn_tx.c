/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
#if 0
// sg: Server and gateway communication  ������������ͨ��

#include "com_includes.h"

#include "timer.h"
#include "dbg_uart.h"




static QURUE_V *_pQVsgRx;






u8 sgRxQueueIsFull( u8 len )
{
	if( getUnuseLenQueueV(_pQVsgRx ) - 1 < len )
		return TRUE;

	return FALSE;
}

u8 sgRxQueueIsEmpty( void )
{
	return IsEmptyQueueV(_pQVsgRx );
}



void sgRxQueueClear( void )
{
	clearQueueV(_pQVsgRx );
}




// ���
u8 sgRxQueueEn( u8 *pData, u8 len )
{
	if( enQueueV(_pQVsgRx, pData, len ) == FALSE )
	{
		dprintf("\r\nSGIX");

		return FALSE;
	}
	else
	{
		//modUartDebugTxStrU32("\r\nGPI:", len );
	}

	return TRUE;
}

// ����
u8 sgRxQueueDe( u8 *pData, u32 *pLen )
{
	if( deQueueV(_pQVsgRx, pData, pLen ) == FALSE )
	{
		dprintf("\r\nsgRxQueueDe x1");

		return FALSE;
	}

	return TRUE;
}





void sgRxQueueInit( void )
{
	_pQVsgRx = initQqueueV( 2048 );
	if( _pQVsgRx == NULL )
	{
		dprintf("\r\nsgRxQueueInit x1");
		return;
	}
}

#endif


