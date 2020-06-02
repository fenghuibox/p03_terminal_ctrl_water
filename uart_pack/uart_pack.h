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

#ifndef __UART_PACK_H__
#define __UART_PACK_H__

#include "com_includes.h"



typedef struct
{	
	u8 txFinish:1; // 
	u8 callTxFinishFun:1;
	u8 rxFinish:1; // 

}ST_UART_PACK_BOOL;



typedef struct __UART_PACK
{
	ST_QUEUE *pRxQ;
	ST_QUEUE *pTxQ;

	QURUE_V *pRxQV;
	QURUE_V *pTxQV;	

	FunUartPackRxCB       rxFunCB;
	FunUartPackTxFinishCB txFinishCB;

	//u8 txFinish;
	//u8 rxFinish;

	ST_UART_PACK_BOOL b;

	u8 timerId;
		
	U8 rxGapCnt;
	U8 txGapCnt;

	U8 rxCnt;
	U8 txCnt;
	
}UART_PACK;



typedef struct __UART_PACK_PARA
{
	u16 rxQLen;
	u16 txQLen;
	u16 rxQVLen;
	u16 txQVLen;
	U8 rxGapMsCnt;
	U8 txGapMsCnt;
	FunUartPackRxCB rxFunCB;
	 FunUartPackTxFinishCB txFinishFunCB;
}UART_PACK_PARA;


extern void uartPackInit( UART_PACK *pstUartPack, UART_PACK_PARA *pstUartPackPara);

#endif


#endif



