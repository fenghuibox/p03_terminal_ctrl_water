/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __SN_RX_QUEUE_H
#define __SN_RX_QUEUE_H

// sn: Server and node communication	�������ͽڵ�ͨ��

#include "com_typedef.h"




extern u8 snRxQueueIsFull( u8 len );



extern u8 snRxQueueIsEmpty( void );


extern void snRxQueueClear( void );


// ���
extern u8 snRxQueueEn( u8 *pData, u8 len );



// ����
extern u8 snRxQueueDe( u8 *pData, u32 *pLen );







//extern u8 snRxQueue( void );//  server rx --> queue  ||  --> tx zigbee node


extern void snRxQueueInit( void );





#endif

