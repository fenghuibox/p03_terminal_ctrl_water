/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/

// sg: Server and gateway communication  服务器和网关通信

#if 0


#include "com_includes.h"

#include "timer.h"
#include "dbg_uart.h"

typedef enum 
{
	//SG_TX_STATE_NOT_DEF = 0;
	SG_TX_STATE_IDLE = 0, // 空闲态
	SG_TX_STATE_READY,    // 就绪态
	SG_TX_STATE_TX       // 已发送态
	
}EN_SG_TX_STATE; // 
	
	



typedef struct // 位置不能变
{
	u8 msCnt;   // 发送计时   100 ms 每次, 最大值 25600ms
	U8 txCnt;   // 发送次数
	U8 sid;    // 帧sid
	EN_SG_TX_STATE state; // 状态 0:空闲
	U8 len; 
	u8 pBuf[255];
	
}ST_SG_TX;


#define TX_ARR_LEN  (10)


static ST_SG_TX _sgTxArr[TX_ARR_LEN] = {0};



int sgTxIdleIndexGet( void )
{
	int i = TX_ARR_LEN - 1;

	for( ; i != 0; i-- )
	{
		if( SG_TX_STATE_IDLE == _sgTxArr[i].state )
			return i;
	}
	
	if( SG_TX_STATE_IDLE == _sgTxArr[0].state )
		return 0;

	return -1;
		
}





void sgTxAdd( u8 index, u8 sid, u8 *pBuf, u8 len )
{
	_sgTxArr[index].sid   = sid;
	_sgTxArr[index].state = SG_TX_STATE_READY;
	_sgTxArr[index].len   = len;
	memcpy( _sgTxArr[index].pBuf, pBuf, len );
}





void sgTxArrInit( void )
{
	int i = 0;

	for( ; i < TX_ARR_LEN; i++ )
	{
		 _sgTxArr[i].state = SG_TX_STATE_IDLE;
	}
}

#endif


