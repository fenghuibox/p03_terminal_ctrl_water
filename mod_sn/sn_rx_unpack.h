/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __SN_RX_UNPACK_H
#define __SN_RX_UNPACK_H

#include "com_typedef.h"






extern u8 snRxUnpackRstIsRsp( void );


extern u8 snRxUnpackRstIsTxtFrame( void );




/*
返回值: TURE 数据有效  FALSE 数据无效
*/
extern u8 snRxUnpack( u8 *pFrame, u8 len );



extern void snRxUnpackInit( void );



#endif

