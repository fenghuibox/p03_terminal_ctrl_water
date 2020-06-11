/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __SN_RX_QUEUE_H
#define __SN_RX_QUEUE_H

// sn: Server and node communication	服务器和节点通信

#include "com_typedef.h"




extern u8 snRxQueueIsFull( u8 len );



extern u8 snRxQueueIsEmpty( void );


extern void snRxQueueClear( void );


// 入队
extern u8 snRxQueueEn( u8 *pData, u8 len );



// 出队
extern u8 snRxQueueDe( u8 *pData, u32 *pLen );







//extern u8 snRxQueue( void );//  server rx --> queue  ||  --> tx zigbee node


extern void snRxQueueInit( void );





#endif

