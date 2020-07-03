/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/


#include "cfg_ctrl.h"

#include "cfg_com.h"
#include "dbg_uart.h"


//====== ctrl state  =====================================
u8 cfgCtrlStateGet( void ) //
{
    if( _stAppConfig.ctrl_state == 0 )
		return 0;

	return 1;
}


void cfgCtrlStateSet( u32 ctrlState )
{
    if( _stAppConfig.ctrl_state == ctrlState )
        return;

   _stAppConfig.ctrl_state = ctrlState;

   
   dprintf("cfgCtrlS %d", ctrlState);
   
   _cfgModify = 1;
   
}

void cfgCtrlStateDef( void )
{
    cfgCtrlStateSet( CONFIG_DEF_CTRL_STATE );
}



//====== ctrl mode  =====================================
u8 cfgCtrlModeGet( void ) //
{
    if( _stAppConfig.ctrl_mode == 0 )
		return 0;

	return 1;
}


void cfgCtrlModeSet( u32 ctrlMode )
{
    if( _stAppConfig.ctrl_mode == ctrlMode )
        return;

   _stAppConfig.ctrl_mode = ctrlMode;

   
   dprintf("cfgCtrlMode %d", ctrlMode);
   
   _cfgModify = 1;
   
}

void cfgCtrlModeDef( void )
{
    cfgCtrlModeSet( CONFIG_DEF_CTRL_MODE );
}





//====== ctrl open sec  =====================================
u32 cfgCtrlOpenSecGet( void ) //
{
	#ifdef DEV_DEBUG_ING
		return 15;
	#else
	
		if( _stAppConfig.cmd_ctrl_open_sec < CONFIG_CTRL_OPEN_SEC_MIN )
		{
			_stAppConfig.cmd_ctrl_open_sec = CONFIG_CTRL_OPEN_SEC_MIN;
		}
		
		return _stAppConfig.cmd_ctrl_open_sec;
		
	#endif
}


void cfgCtrlOpenSecSet( u32 ctrlOpenSec )
{
	if( ctrlOpenSec < CONFIG_CTRL_OPEN_SEC_MIN )
	{
		ctrlOpenSec = CONFIG_CTRL_OPEN_SEC_MIN;
	}

    if( _stAppConfig.cmd_ctrl_open_sec == ctrlOpenSec )
        return;

	//dprintf("cfgOpenSec %d", ctrlOpenSec );

   _stAppConfig.cmd_ctrl_open_sec = ctrlOpenSec;
   
   _cfgModify = 1;
   
}

void cfgCtrlOpenSecDef( void )
{
    cfgCtrlOpenSecSet( CONFIG_DEF_CMD_CTRL_OPEN_SEC );
}

//====== ctrl open start sec  =====================================
u32 cfgCtrlOpenStartGet( void ) //
{
    return _stAppConfig.cmd_ctrl_start_sec;
}


void cfgCtrlOpenStartSet( u32 ctrlOpenStartSec )
{
    if( _stAppConfig.cmd_ctrl_start_sec == ctrlOpenStartSec )
        return;

	

   _stAppConfig.cmd_ctrl_start_sec = ctrlOpenStartSec;
   
   //dprintf("cfgOpenStart %d", ctrlOpenStartSec);
   
   _cfgModify = 1;
   
}

void cfgCtrlOpenStartDef( void )
{
    cfgCtrlOpenSecSet( 0 );
}







//======dev  自动周期控制时， 开和关的时长 =====================================
void cfgPeriodCtrlGapGet( u32 *pOpenMinute, u32 *pCloseMinute) //
{
    *pOpenMinute  = _stAppConfig.period_ctrl_open_minute;
    *pCloseMinute = _stAppConfig.period_ctrl_close_minute;
}




void cfgPeriodCtrlGapSet( u32 openMinute, u32 closeMinute )
{
    if( _stAppConfig.period_ctrl_open_minute != openMinute )
    {
    	_stAppConfig.period_ctrl_open_minute = openMinute;
		_cfgModify = 1;
    }
	
    if( _stAppConfig.period_ctrl_close_minute != closeMinute )
    {
    	_stAppConfig.period_ctrl_close_minute = closeMinute;
		_cfgModify = 1;
    }


}

void cfgPeriodCtrlGapDef( void )
{
    cfgPeriodCtrlGapSet( CONFIG_DEF_PERIOD_CTRL_OPEN_MINUTE, CONFIG_DEF_PERIOD_CTRL_CLOSE_MINUTE );
}



