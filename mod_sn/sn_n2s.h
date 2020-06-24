/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __SN_N2S_H
#define __SN_N2S_H

 // sn: Server and node communication    服务器和节点通信
// n2s: node to server                   节点发送给服务器

#include "com_typedef.h"


#include "zgb_uart.h"


#define N2S_POLL_GAP_MS                           (40)     // n2sCB 函数执行的间隔时间
#define N2S_REDO_CNT                               (1)     // 重发次数
#define N2S_REDO_GAP_MS                         (2800)     // 重发间隔毫秒
#define N2S_REDO_GAP_CNT        ( N2S_REDO_GAP_MS / N2S_POLL_GAP_MS )   // 重发间隔毫秒对应的次数

extern u8 snN2sCurIdIsCtrlPackGet( void );

extern u8 snN2sIsRspCurTxCmdSid( u8 sid );


extern void snN2sOnRsp( void );



extern void snN2sPoll( void ); // 40ms


extern void snN2sTxCBset( FunN2sTxCB fun );


extern u8 snN2sIsIng( void ); // 正在发送中



extern u8 n2sIsHave( void ); // 有数据项要发送


extern int n2sTxCmdOnRxOkRsp( void );


extern int snOnRx( u8 *pFrame, u8 len ); // Receive message to execute



extern void n2sHeartbeat( void );

extern void n2sBattRpt( void );


extern void n2sCtrlPackGet( void );


extern u8 n2sCB( void ); //  node send to server


extern void snN2sInit( void );



extern void n2sPrint( void );



#endif

