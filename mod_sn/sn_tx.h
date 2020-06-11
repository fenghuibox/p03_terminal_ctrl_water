/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 
#if 0

#ifndef __SG_RX_QUEUE_H
#define __SG_RX_QUEUE_H

// sg: Server and gateway communication  服务器和网关通信

#include "com_typedef.h"




extern u8 sgRxQueueIsFull( u8 len );



extern u8 sgRxQueueIsEmpty( void );


extern void sgRxQueueClear( void );


// 入队
extern u8 sgRxQueueEn( u8 *pData, u8 len );



// 出队
extern u8 sgRxQueueDe( u8 *pData, u32 *pLen );







//extern u8 sgRxQueue( void );//  server rx --> queue  ||  --> tx zigbee node


extern void sgRxQueueInit( void );





#endif

#endif



