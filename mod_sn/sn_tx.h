/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 
#if 0

#ifndef __SG_RX_QUEUE_H
#define __SG_RX_QUEUE_H

// sg: Server and gateway communication  ������������ͨ��

#include "com_typedef.h"




extern u8 sgRxQueueIsFull( u8 len );



extern u8 sgRxQueueIsEmpty( void );


extern void sgRxQueueClear( void );


// ���
extern u8 sgRxQueueEn( u8 *pData, u8 len );



// ����
extern u8 sgRxQueueDe( u8 *pData, u32 *pLen );







//extern u8 sgRxQueue( void );//  server rx --> queue  ||  --> tx zigbee node


extern void sgRxQueueInit( void );





#endif

#endif



