/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __SN_RX__H
#define __SN_RX__H

// sn: Server and node communication	服务器和节点通信

#include "com_typedef.h"



extern int snRx( u8 *pBuf, u8 len );



extern u8 snIsIdle( void );



extern void snRxInit( void );





#endif

