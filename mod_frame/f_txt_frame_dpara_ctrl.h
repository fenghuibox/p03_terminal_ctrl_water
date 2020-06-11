/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#if 1

#ifndef __F_TXT_FRAME_DPARA_CTRL_H
#define __F_TXT_FRAME_DPARA_CTRL_H


#include "com_typedef.h"

#include "f_frame_comm.h"

//#include "cfg_ctrl.h"









// ------------- ctrlMode  -----------------------------------------


int paraCtrlModeSet( u8 *pPara  );


u8 paraCtrlModeGet( void );


u8 para_ctrl_mode_exe( ST_FRAME *pstFrame );



// ------------- cmd ctrl  -----------------------------------------

int paraCmdCtrlSet( u8 *pPara  );



u8 paraCmdCtrlGet( void );

u8 para_cmd_ctrl_exe( ST_FRAME *pstFrame );




// ------------- ctrl open sec  -----------------------------------------

void paraCtrlOpenSecSet( u8 *pPara );


void paraCtrlOpenSecGet( u8 *pPara );




u8 para_open_sec_exe( ST_FRAME *pstFrame );



// ------------- period ctrl  -----------------------------------------



void paraPeriodCtrlSet( u8 *pPara );


void paraPeriodCtrlGet( u8 *pPara );



u8 para_period_ctrl_exe( ST_FRAME *pstFrame );




// ------------- ctrl pack  -----------------------------------------



void paraCtrlPackSet( u8 *pPara );


int paraCtrlPackGet( u8 *pPara );


u8 para_ctrl_pack_exe( ST_FRAME *pstFrame );








#endif

#endif


