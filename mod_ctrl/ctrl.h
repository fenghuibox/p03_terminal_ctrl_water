/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __CTRL_H
#define __CTRL_H


#include "com_typedef.h"


#include "ctrl_mode.h"
#include "ctrl_cmd_ctrl.h"
#include "ctrl_cmd_ctrl_open_sec.h"
#include "ctrl_period_ctrl.h"





u8 ctrlStateGet( void );


void ctrlOpenStartSecUpdate( void );


void ctrlOpen( void );


void ctrlClose( void );


u8 ctrlIsIdle( void );




void ctrlStatePoll( void ); // 50 ms

void ctrlOpenSecPoll( void ); // 200 ms



extern void ctrlInit( void );




#endif

