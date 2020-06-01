/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __COM_BUF_H
#define __COM_BUF_H


#include "com_typedef.h"




/*
����ֵ  > -1 : ch �� pBuf �� �� n �� ����ʱ�� index
����ֵ  = -1 : û���ҵ�

��: pBuf = 11 01 05 00 05 03
    bufChNposGet( pBuf, 6, 5, 2 ) = 4
*/
extern int bufChNposGet( u8 *pBuf, u16 bufLen, u8 ch, u16 n );




/*
����ֵ  > -1 : ch �� pBuf �� �� 1 �� ����ʱ�� index
����ֵ  = -1 : û���ҵ�

��: pBuf = 11 01 05 00 05 03
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

