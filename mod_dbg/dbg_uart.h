/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __DBG_UART_H
#define __DBG_UART_H


#include "com_typedef.h"




extern void dprintf(const char *pFormat, ...);

extern void dprintfBuf( char *pStr, u8 *pBuf, u32 len, u8 print0D0A );



extern void dbgUartInit( void );



extern void debugUartTxPass( u8 *str,  u8 len );




#ifdef TEST_MOD_DBG_UART
	void testModDbgUart( void );
#endif




#endif

