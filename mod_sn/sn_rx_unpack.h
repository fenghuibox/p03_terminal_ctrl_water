/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __SN_RX_UNPACK_H
#define __SN_RX_UNPACK_H

#include "com_typedef.h"






extern u8 snRxUnpackRstIsRsp( void );


extern u8 snRxUnpackRstIsTxtFrame( void );




/*
����ֵ: TURE ������Ч  FALSE ������Ч
*/
extern u8 snRxUnpack( u8 *pFrame, u8 len );



extern void snRxUnpackInit( void );



#endif

