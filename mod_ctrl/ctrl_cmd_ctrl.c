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







#ifdef TEST_MOD_CTRL

#include "dbg_uart.h"

static void _timerCB( void )
{
	static u16 _cnt=0;
	
	if( (_cnt++ & 1) == 0 )
	{
		dprintf(" \r\n %d start ctrl close", _cnt/2 + 1);
		
		ctrlCmdCtrlClose();
	}
	else
	{
		dprintf(" \r\n %d start ctrl open", _cnt/2 + 1);
		ctrlCmdCtrlOpen();
	}
}




void testCtrlCmdCtrl( void )
{

	timerStartSec( 3, TIMER_REPEAT_FOREVER, _timerCB );

}

#endif



