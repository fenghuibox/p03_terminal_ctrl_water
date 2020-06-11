/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/

#include "com_includes.h"

#include "ctrl_cmd_ctrl.h"
#include "timer.h"





#include "ctrl.h"







void ctrlCmdCtrlOpen( void )
{
	ctrlOpen();
}


void ctrlCmdCtrlClose( void )
{
	ctrlClose();
}



u8 ctrlCmdCtrlStateIsOpen( void )
{
	return ctrlStateGet();
}



void ctrlCmdCtrlInit( void )
{
	
}






