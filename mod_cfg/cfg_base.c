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





//======dev cfg ver =====================================
u32 cfgCfgVerGet( void ) //
{
    return _stAppConfig.cfg_ver;
}


u32 cfgCfgVerSet( u32 cfgVer )
{
    if( _stAppConfig.cfg_ver == cfgVer )
        return cfgVer;

    _cfgModify = 1;
    return _stAppConfig.cfg_ver = cfgVer;
}

u32 cfgCfgVerDef( void )
{
    return cfgCfgVerSet( CONFIG_DEF_CFG_VER );
}



//======dev sleep sec =====================================
u32 cfgSleepSecGet( void ) //
{
    return _stAppConfig.sleep_sec;
}


u32 cfgSleepSecSet( u32 sec )
{
    if( _stAppConfig.sleep_sec == sec )
        return sec;

    _cfgModify = 1;

    return _stAppConfig.sleep_sec = sec;
}

u32 cfgSleepSecDef( void )
{
    return cfgSleepSecSet( CONFIG_DEF_SLEEP_SEC );
}


//======dev work sec =====================================
u32 cfgWorkSecGet( void ) //
{
    return _stAppConfig.work_sec;
}


u32 cfgWorkSecSet( u32 sec )
{
    if( _stAppConfig.work_sec == sec )
        return sec;

    _cfgModify = 1;

    return _stAppConfig.work_sec = sec;
}

u32 cfgWorkSecDef( void )
{
    return cfgWorkSecSet( CONFIG_DEF_WORK_SEC );
}


//======dev open sec =====================================
u32 cfgOpenSecGet( void ) //
{
    return _stAppConfig.open_sec;
}


u32 cfgOpenSecSet( u32 sec )
{
    if( _stAppConfig.open_sec == sec )
        return sec;

    _cfgModify = 1;

    return _stAppConfig.open_sec = sec;
}

u32 cfgOpenSecDef( void )
{
    return cfgOpenSecSet( CONFIG_DEF_OPEN_SEC );
}


//======dev close sec =====================================
u32 cfgCloseSecGet( void ) //
{
    return _stAppConfig.close_sec;
}


u32 cfgCloseSecSet( u32 sec )
{
    if( _stAppConfig.close_sec == sec )
        return sec;

    _cfgModify = 1;

    return _stAppConfig.close_sec = sec;
}

u32 cfgCloseSecDef( void )
{
    return cfgCloseSecSet( CONFIG_DEF_CLOSE_SEC );
}




//======dev work state =====================================
u8 cfgWorkStateIsNormal( void )
{
	return ( _stAppConfig.work_state == DEV_WORK_STATE_NORMAL)? 1:0;
}


u8 cfgWorkStateGet( void ) //
{
    return _stAppConfig.work_state;
}


u8 cfgWorkStateSet( u8 s )
{
    if( _stAppConfig.work_state == s )
        return s;

    _cfgModify = 1;

    return _stAppConfig.work_state = s;
}

u32 cfgWorkStateDef( void )
{
    return cfgWorkStateSet( CONFIG_DEF_WORK_STATE );
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



