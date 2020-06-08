/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __ZGB_G2N_H
#define __ZGB_G2N_H

// g2n: gateway to node 

#include "com_typedef.h"






extern int modUartZgbG2NonRxMacGetIndex( u8 *pRxMac );

extern u8 modUartZgbG2N( void );


extern void modUartZgbG2NupdateIndex( void );


extern int modUartZgbG2Nrx( u8 *pBuf, u32 len );



extern void zgbG2Ninit( void );


#endif

