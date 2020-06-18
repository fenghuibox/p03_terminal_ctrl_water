/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __ZGB_UART_H
#define __ZGB_UART_H


#include "com_typedef.h"



extern u8 zgbUartTxPoll( void ); // >50 ms



//extern u8 modUartZigbeeIsIdle( void );
//extern u8 zgbUartIsIdle( void );


//extern void modUartZigbeeTx( u8 *str,  u8 len );
extern int zgbUartTx( u8 *str,  u16 len );




extern void zgbUartInit( void );

extern u8 zgbUartIsIdle( void );


#ifdef TEST_MOD_ZGB_UART
	void testModZgbUart( void );
#endif




#endif

