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



#define SG_TX_CMD_POLL_GAP_MS                     (100)     //
#define SG_TX_CMD_REDO_CNT                          (3)     // �ط�����
#define SG_TX_CMD_REDO_GAP_MS                    (2800)     // �ط��������
#define SG_TX_CMD_REDO_GAP_CNT        ( SG_TX_CMD_REDO_GAP_MS / SG_TX_CMD_POLL_GAP_MS )   // �ط���������Ӧ�Ĵ���





typedef enum 
{
	//SG_TX_CMD_STATE_NOT_DEF = 0;
	SG_TX_CMD_STATE_IDLE = 0, // ����̬
	SG_TX_CMD_STATE_READY,    // ����̬
	SG_TX_CMD_STATE_TX       // �ѷ���̬
	
}EN_SG_TX_CMD_STATE; // 
	
	
#define TX_CMD_ARR_LEN  (10)




typedef struct // λ�ò��ܱ�
{
	u8 msCnt;   // ���ͼ�ʱ   100 ms ÿ��, ���ֵ 25600ms
	U8 txCnt;   // ���ʹ���
	EN_SG_TX_CMD_STATE state; // ״̬ 0:����
	U8 len; 
	u8 pBuf[256];
	
}ST_SG_TX_CMD;


#define TX_CMD_ARR_LEN  (10)


static ST_SG_TX_CMD _sgTxCmdArr[TX_CMD_ARR_LEN] = {0};



int sgTxCmdIdleIndexGet( void )
{
	int i = TX_CMD_ARR_LEN - 1;

	for( ; i != 0; i-- )
	{
		if( SG_TX_CMD_STATE_IDLE == _sgTxCmdArr[i].state )
			return i;
	}
	
	if( SG_TX_CMD_STATE_IDLE == _sgTxCmdArr[0].state )
		return 0;

	return -1;
		
}





void sgTxCmdAdd( u8 index, u8 *pBuf, u8 len )
{
	_sgTxCmdArr[index].msCnt = SG_TX_CMD_REDO_GAP_CNT;
	_sgTxCmdArr[index].txCnt = SG_TX_CMD_REDO_CNT;
	_sgTxCmdArr[index].state = SG_TX_CMD_STATE_READY;
	_sgTxCmdArr[index].len   = len;
	memcpy( _sgTxCmdArr[index].pBuf, pBuf, len );
}


void sgTxCmdPoll( void ) // 100ms
{
	int i = 0;

	for( ; i < TX_CMD_ARR_LEN; i++ )
	{
		if( _sgTxCmdArr[i].state == SG_TX_CMD_STATE_TX )
		{
			comU8Dec( &_sgTxCmdArr[i].msCnt );
			
			if( _sgTxCmdArr[i].msCnt == 0 )
			{
				
			}
		}
		
	}
}







void sgTxCmdArrInit( void )
{
	int i = 0;

	for( ; i < TX_CMD_ARR_LEN; i++ )
	{
		 _sgTxCmdArr[i].state = SG_TX_CMD_STATE_IDLE;
	}
}


#endif


