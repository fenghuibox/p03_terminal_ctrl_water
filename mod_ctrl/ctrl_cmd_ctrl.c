/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
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






