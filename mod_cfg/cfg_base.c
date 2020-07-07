/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/


#include "cfg_base.h"

#include "cfg_com.h"

#include "dbg_uart.h"




//======dev cfg ver =====================================
u32 cfgCfgVerGet( void ) //
{
    return _stAppConfig.cfg_ver;
}


void cfgCfgVerSet( u32 cfgVer )
{
    if( _stAppConfig.cfg_ver == cfgVer )
        return;

	_stAppConfig.cfg_ver = cfgVer;
    _cfgModify = 1;

}

void cfgCfgVerDef( void )
{
    cfgCfgVerSet( CONFIG_DEF_CFG_VER );
}



//======dev sleep sec =====================================
u32 cfgSleepSecGet( void ) //
{
	#ifdef DEV_DEBUG_ING
		return 10;
	#else

		if( _stAppConfig.sleep_sec < CONFIG_MIN_SLEEP_SEC )
		{
			_stAppConfig.sleep_sec = CONFIG_MIN_SLEEP_SEC;
		}
		else if ( _stAppConfig.sleep_sec > CONFIG_MAX_SLEEP_SEC )
		{
			_stAppConfig.sleep_sec = CONFIG_MAX_SLEEP_SEC;
		}
	
	   return _stAppConfig.sleep_sec; 
	#endif
}


void cfgSleepSecSet( u32 sec )
{
	if( _stAppConfig.sleep_sec == sec )
		return;

	if( sec < CONFIG_MIN_SLEEP_SEC )
	{
		sec = CONFIG_MIN_SLEEP_SEC;
	}
	else if ( sec > CONFIG_MAX_SLEEP_SEC )
	{
		sec = CONFIG_MAX_SLEEP_SEC;
	}

	if( _stAppConfig.sleep_sec == sec )
		return;

	dprintf("cfgSSec=%d", sec);

    _stAppConfig.sleep_sec = sec;

	_cfgModify = 1;
	
}

void cfgSleepSecDef( void )
{
    cfgSleepSecSet( CONFIG_DEF_SLEEP_SEC );
}


//======dev work sec =====================================
u32 cfgWorkSecGet( void ) //
{
	#ifdef DEV_DEBUG_ING
		return 60*60;
	#else

		if( _stAppConfig.work_sec < CONFIG_MIN_WORK_SEC )
		{
			_stAppConfig.work_sec = CONFIG_MIN_WORK_SEC;
		}
		else if ( _stAppConfig.work_sec > CONFIG_MAX_WORK_SEC )
		{
			_stAppConfig.work_sec = CONFIG_MAX_WORK_SEC;
		}
		
    	return _stAppConfig.work_sec;
	#endif

    
}


void cfgWorkSecSet( u32 sec )
{
    if( _stAppConfig.work_sec == sec )
        return;


	if( sec < CONFIG_MIN_WORK_SEC )
	{
		sec = CONFIG_MIN_WORK_SEC;
	}
	else if ( sec > CONFIG_MAX_WORK_SEC )
	{
		sec = CONFIG_MAX_WORK_SEC;
	}

    if( _stAppConfig.work_sec == sec )
        return;

    _stAppConfig.work_sec = sec;

	
	dprintf("cfgWSec=%d", sec);
	
    _cfgModify = 1;
	
}

void cfgWorkSecDef( void )
{
    cfgWorkSecSet( CONFIG_DEF_WORK_SEC );
}










/*
//======dev to master ch =====================================

u8 cfgSgChGet( void ) //
{
    return _stAppConfig.sgCh;
}


u8 cfgSgCheSet( u8 ch )
{
    if( _stAppConfig.sgCh == ch )
        return ch;

    _cfgModify = 1;

    return _stAppConfig.sgCh = ch;
}


u8 cfgSgChDef( void )
{
    return cfgSgCheSet( CONFIG_DEF_SG_CH );
}
*/



