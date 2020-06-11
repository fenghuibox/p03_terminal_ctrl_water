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

#include "ctrl_mode.h"

#include "cfg_ctrl.h"



void ctrlModeSet( EN_CTRL_MODE ctrlMode )
{
	if( ctrlMode == CTRL_MODE_CMD )
		cfgCtrlModeSet( 0 );
	else
		cfgCtrlModeSet( 1 );
}



u8 ctrlModeIsCmd( void )
{
	if( cfgCtrlModeGet() == 0 )
		return TRUE;

	return FALSE;

}



void ctrlModeInit( void )
{

}






