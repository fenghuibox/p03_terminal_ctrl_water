/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __SN_H
#define __SN_H

// sn: Server and node communication



#include "com_typedef.h"

#include "sn_ch.h"

#include "sn_master_state.h"
#include "sn_n2s_state.h"
#include "sn_n2s.h"


#include "sn_rx_unpack.h"

#include "sn_rx_queue.h"
#include "sn_rx.h"


extern void snPoll( void ); // 50ms

extern void snInit1( void );

extern void snInit2( void );

extern void snInit( void );

#endif

