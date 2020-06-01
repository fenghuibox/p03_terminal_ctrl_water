/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __COM_DELAY_H
#define __COM_DELAY_H


#include "com_typedef.h"


void comDelay(u32 a);



//void comDelayUs(u32 us); // 小于 5us 请使用 comDelay1Us()

void comDelay12Us(u32 us);



void comDelayMs(u32 ms);  // ok


void comDelayS(u32 s);   // ok

//=============================================
//=============================================
#ifdef TEST_COM_DELAY

void testDelay( void );
#endif


#endif

