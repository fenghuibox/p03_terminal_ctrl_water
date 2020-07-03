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

#include "dri_io_ch.h"

#include "dbg_uart.h"

 // 服务器和节点通信通道
 // Server and node communication channel


#if 1

// 可用通道定义：
typedef enum
{
	SN_CH_NOT_DEF = 0x00,
	SN_CH_ZGB     = 0x01,
	SN_CH_485     = 0x02,
	SN_CH_ROLA    = 0x04,
}EN_SN_CH;







static EN_SN_CH _ch; 

#define SN_CH_STATE_ZGB    (1)
#define SN_CH_STATE_485    (0)
#define SN_CH_STATE_DEF    (SN_CH_STATE_ZGB)



u8 snChIsZgb( void )
{
	if( _ch == SN_CH_ZGB )
		return TRUE;

	return FALSE;
}

u8 snChIs485( void )
{
	if( _ch == SN_CH_485 )
		return TRUE;

	return FALSE;
}





static void _chSet( u8 ch )
{
	#include "sn_n2s.h"
	#include "zgb_cmd.h"
	//#include "m485_uart.h"

	if( ch == SN_CH_STATE_ZGB )
	{
		snN2sTxCBset( zgbUartTx );
		_ch = SN_CH_ZGB;
		dprintf("ch=zgb");
	}
	else
	{
		//snN2sTxCBset( m485UartTx );
		_ch = SN_CH_485;
		dprintf("ch=485");
	}

}


//------------------------------------



void snChInit( void )
{
	#define _CHECK_CH_CNT  (3)

	int i, k;
	
	u8 _chArr[_CHECK_CH_CNT];
	u8 _chIndex;	
	u8 chState;
	
	//== 1 init==========================
	_ch      = SN_CH_NOT_DEF;
	_chIndex = 0;
	chState  = 0;


	for( i = 0; i < _CHECK_CH_CNT; i++ )
	{
		_chArr[i] = i;
	}



	for( k = 0; _ch == SN_CH_NOT_DEF && k < 200; k++ )
	{
		comDelayMs(1);
		
		chState = driIoChRead();
		
		//== 2 去抖动===========================
		_chArr[_chIndex++] = chState;
		if(_chIndex == _CHECK_CH_CNT )
			_chIndex = 0;
		
		for( i = 0; i < _CHECK_CH_CNT - 1; i++ )
		{
			if( _chArr[i] != _chArr[i+1] )
				continue;
		}

		//== 3 set ===============
		_chSet( chState );
		return;
	}



	//== 4 DEF =============
	_chSet( SN_CH_STATE_DEF );

}


#else

u8 snChIsZgb( void )
{
	return TRUE;
}


void snChInit( void )
{

}

#endif




