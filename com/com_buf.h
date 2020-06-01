/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __COM_BUF_H
#define __COM_BUF_H


#include "com_typedef.h"




/*
返回值  > -1 : ch 在 pBuf 中 第 n 次 出现时的 index
返回值  = -1 : 没有找到

例: pBuf = 11 01 05 00 05 03
    bufChNposGet( pBuf, 6, 5, 2 ) = 4
*/
extern int bufChNposGet( u8 *pBuf, u16 bufLen, u8 ch, u16 n );




/*
返回值  > -1 : ch 在 pBuf 中 第 1 次 出现时的 index
返回值  = -1 : 没有找到

例: pBuf = 11 01 05 00 05 03
    bufChIndexGet( pBuf, 6, 5 ) = 2
*/
extern int bufChIndexGet( u8 *pBuf, u16 bufLen, u8 ch );


/*---------------------------------------------------
pBuf = 12345678  len  = 8

pSub = 45  subLen = 2   return : pBuf + 3
pSub = AB  subLen = 2   return : NULL
------------------------------------------------------*/
extern u8 *bufbuf( u8 *pBuf, u16 len, u8 *pSub, u16 subLen );

#endif

