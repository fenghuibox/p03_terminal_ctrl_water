/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/

// sg: Server and gateway communication  ������������ͨ��

#if 0


#include "com_includes.h"

#include "timer.h"
#include "dbg_uart.h"

typedef enum 
{
	//SG_TX_STATE_NOT_DEF = 0;
	SG_TX_STATE_IDLE = 0, // ����̬
	SG_TX_STATE_READY,    // ����̬
	SG_TX_STATE_TX       // �ѷ���̬
	
}EN_SG_TX_STATE; // 
	
	



typedef struct // λ�ò��ܱ�
{
	u8 msCnt;   // ���ͼ�ʱ   100 ms ÿ��, ���ֵ 25600ms
	U8 txCnt;   // ���ʹ���
	U8 sid;    // ֡sid
	EN_SG_TX_STATE state; // ״̬ 0:����
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


