/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/

// g2n: gateway to node 

#include "com_includes.h"

#include "dbg_uart.h"

#include "zgb_g2n_state.h"

#include "zgb_uart.h"
#include "zgb_g2n.h"


static EN_UART_ZGB_G2N_STATE _g2nState;



#define UART_ZGB_G2N_STATE_TX_TIMEOUT_MS           ( 1000 )
#define UART_ZGB_G2N_STATE_TX_TIMEOUT_CNT          ( UART_ZGB_G2N_STATE_TX_TIMEOUT_MS / MOD_UART_ZGB_TX_GAP_MS)

#define UART_ZGB_G2N_STATE_WAIT_RX_TXT_TIMEOUT_MS  ( 1000 )
#define UART_ZGB_G2N_STATE_WAIT_RX_TXT_TIMEOUT_CNT ( UART_ZGB_G2N_STATE_WAIT_RX_TXT_TIMEOUT_MS / MOD_UART_ZGB_TX_GAP_MS)

U8 _g2nTimeOutCnt;


u8 modUartZgbG2NstateIsCanTx( void ) // 当前的状态可以发送数据吗
{
	if( _g2nState == UART_ZGB_G2N_STATE_IDLE || _g2nState == UART_ZGB_G2N_STATE_TX_ACK )
		return TRUE;

	return FALSE;
}


u8 modUartZgbG2NstateIsTxAck( void )
{
	if( _g2nState == UART_ZGB_G2N_STATE_TX_ACK )
		return TRUE;

	return FALSE;
}


u8 modUartZgbG2NstateIsIdle( void )
{
	if( _g2nState == UART_ZGB_G2N_STATE_IDLE )
		return TRUE;

	return FALSE;
}


static void _uartZgbG2NstateSet( EN_UART_ZGB_G2N_STATE s )
{
	if( _g2nState == s )
		return;

	if( s == UART_ZGB_G2N_STATE_TX_TXT )
	{
		_g2nTimeOutCnt = UART_ZGB_G2N_STATE_TX_TIMEOUT_CNT;
	}
	else if ( s == UART_ZGB_G2N_STATE_WAIT_RX_TXT )
	{
		_g2nTimeOutCnt = UART_ZGB_G2N_STATE_WAIT_RX_TXT_TIMEOUT_CNT;
	}

	_g2nState = s;
}


void modUartZgbG2NstateOnEvent( EN_UART_ZGB_G2N_EVENT e )
{
	switch( _g2nState )
	{
	case UART_ZGB_G2N_STATE_IDLE:
		if(  UART_ZGB_G2N_E_TX_TXT == e )
		{
			_uartZgbG2NstateSet( UART_ZGB_G2N_STATE_TX_TXT );
		}
		break;

	case UART_ZGB_G2N_STATE_TX_TXT:
		if(  UART_ZGB_G2N_E_TX_TXT_TIMEOUT == e  )
		{
			_uartZgbG2NstateSet( UART_ZGB_G2N_STATE_IDLE );
		}
		else if(  UART_ZGB_G2N_E_RX_ACK == e  )
		{
			_uartZgbG2NstateSet( UART_ZGB_G2N_STATE_WAIT_RX_TXT );
		}
		break;

		
	case UART_ZGB_G2N_STATE_WAIT_RX_TXT:
		if(  UART_ZGB_G2N_E_RX_TXT == e  )
		{
			_uartZgbG2NstateSet( UART_ZGB_G2N_STATE_TX_ACK );
		}
		else if(  UART_ZGB_G2N_E_RX_TXT_TIMEOUT == e  )
		{
			_uartZgbG2NstateSet( UART_ZGB_G2N_STATE_IDLE );
		}
		break;	

	case UART_ZGB_G2N_STATE_TX_ACK:
		if(  UART_ZGB_G2N_E_TX_ACK == e )
		{
			_uartZgbG2NstateSet( UART_ZGB_G2N_STATE_IDLE );
		}
		break;

		
	}
}


void modUartZgbG2NstatePollCB( void ) // 已经忽略了第一层处理的时间
{

	if( _g2nState == UART_ZGB_G2N_STATE_TX_TXT )
	{
		if( _g2nTimeOutCnt > 0 )
			_g2nTimeOutCnt--;

		if( _g2nTimeOutCnt == 0 )
		{
			modUartZgbG2NupdateIndex();
			modUartZgbG2NstateOnEvent( UART_ZGB_G2N_E_TX_TXT_TIMEOUT );
		}
	}
	else if( _g2nState == UART_ZGB_G2N_STATE_WAIT_RX_TXT )
	{
		if( _g2nTimeOutCnt > 0 )
			_g2nTimeOutCnt--;

		if( _g2nTimeOutCnt == 0 )
		{
			modUartZgbG2NupdateIndex();
			modUartZgbG2NstateOnEvent( UART_ZGB_G2N_E_RX_TXT_TIMEOUT );
		}
	}

}


void zgbG2NstateInit( void )
{
	_g2nState = UART_ZGB_G2N_STATE_IDLE;
}



