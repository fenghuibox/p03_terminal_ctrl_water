/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __ZGB_RX_PASS_H
#define __ZGB_RX_PASS_H


#include "com_typedef.h"



#define ZGB_RX_PASS_UNIT_LEN_MAX   (240)



extern u8 modUartZgbPassRxIsFull( u8 len );

extern u8 modUartZgbPassRxIsEmpty( void );

extern void modUartZgbPassRxClear( void );


extern u8 modUartZgbPassRxEn( u8 *pData, u8 len );


extern u8 modUartZgbPassRxDe( u8 *pData, u32 *pLen );





extern void zgbPassRxInit( void );


//extern u8 modUartZgbPassTo4g( void );


#endif

