/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __NS_CH_H
#define __NS_CH_H

// 服务器和节点通信通道
// Server and node communication channel

#include "com_typedef.h"





extern u8 snChIsZgb( void );
extern u8 snChIs485( void );


extern void snChInit( void );

#endif

