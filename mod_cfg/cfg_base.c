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
	#if 1
		return 10;// fenghuitest
	#else
    	return _stAppConfig.sleep_sec; 
	#endif
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
	#if 1
		return 0;// fenghuitest
	#else
    	return _stAppConfig.work_sec;
	#endif

    
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



