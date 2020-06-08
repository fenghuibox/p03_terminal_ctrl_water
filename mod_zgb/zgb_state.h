/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __ZGB_STATE_H
#define __ZGB_STATE_H


#include "com_typedef.h"




extern u8 modZgbStateIsOk( void );


extern void modZgbStatePoll( void );


//extern EN_ZIGBEE_WORK_STATE modZigbeeStateGet( void );


extern void zgbStateInit( void );



#endif

