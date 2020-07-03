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





extern u8 ctrlStateGet( void );


extern void ctrlOpenStartSecUpdate( void );


extern void ctrlOpen( void );


extern void ctrlClose( void );


extern u8 ctrlIsIdle( void );




extern void ctrlStatePoll( void ); // 50 ms

extern void ctrlOpenSecPoll( void ); // 200 ms

extern u8 ctrlOpenSecIsTimeout( void );


extern void ctrlInit( void );




#endif

