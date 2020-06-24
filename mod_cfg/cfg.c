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
#include "cfg_com.h"
#include "cfg.h"

#include "dri_flash_f_eep.h"






//======flash is new======================================

u32 cfgNewGet( void )
{
    return _stAppConfig.flash_is_new ;
}

void cfgNewSet( u32 eepNew )
{
    u32 eepIsNew;

    if( eepNew )
        eepIsNew = 1;
    else
        eepIsNew = 0;

    if( _stAppConfig.flash_is_new == eepIsNew )
        return;

    _stAppConfig.flash_is_new = eepIsNew;
	
    _cfgModify = 1;

}


void cfgNewDef( void )
{
    cfgNewSet( 0 );
}








//========================================================
//======config to def======================================

void configDef( void )
{
	if( _stAppConfig.write_cnt == 0xFFFFFFFF )
		_stAppConfig.write_cnt = 0;
	
    _stAppConfig.flash_is_new = CONFIG_DEF_FLASH_IS_NEW;

    _stAppConfig.cfg_ver   = CONFIG_DEF_CFG_VER;
	
    _stAppConfig.sleep_sec = CONFIG_DEF_SLEEP_SEC;
    _stAppConfig.work_sec  = CONFIG_DEF_WORK_SEC;
	
    _stAppConfig.ctrl_mode = CONFIG_DEF_CTRL_MODE;
    _stAppConfig.cmd_ctrl_open_sec = CONFIG_DEF_CMD_CTRL_OPEN_SEC;

	
    _stAppConfig.period_ctrl_open_minute  = CONFIG_DEF_PERIOD_CTRL_OPEN_MINUTE;
    _stAppConfig.period_ctrl_close_minute = CONFIG_DEF_PERIOD_CTRL_CLOSE_MINUTE;


    _stAppConfig.aes_switch = CONFIG_DEF_AES_SWITCH;
    memset( _stAppConfig.aes_key, CONFIG_DEF_AES_KEY_ONE, EEP_LEN_CFG_AES_KEY );


    _cfgModify = 1;

}

void configLoad( void )
{
    /*
    U32 addr = EEP_ADDR_START;
    u32 i;
    u32 *pTemp;

    pTemp = (u32 *)&_stAppConfig;

    for( i = 0; i < sizeof(ST_CONFIG); i+= 4 )
    {
        *pTemp = (*(__IO uint32_t*) addr);

        pTemp++;
        addr += 4;
    }*/

    u32 *pTemp;

    pTemp = (u32 *)&_stAppConfig;

    driFlashEepRead( cfgPageIdGet(), 0, pTemp, sizeof(ST_CONFIG)/4 );
}


static void _cfgSet( void )
{
	#include "dbg_uart.h"
    u32 *pTemp;
	u32 newPageId;

	
    pTemp = (u32 *)&_stAppConfig;
	
    _stAppConfig.write_cnt++;
	
	
	newPageId = cfgPageIdGet() - 1;
	
	if( cfgPageIdIsOk( newPageId ) )
	{
		if( _stAppConfig.write_cnt > PAGE_WRITE_CNT_MAX )
		{
			_stAppConfig.write_cnt = 1;
			
			driFlashEepWrite( newPageId, 0, pTemp, sizeof(ST_CONFIG)/4 + 1 ); // 将变量写入新的页

			cfgPageIdSet( newPageId );// 更新页ID
			return;
		}
		
	}


	if(gB1.inited == 1)
    	dprintf("wflash,PId=%d cnt=%d",  cfgPageIdGet(), _stAppConfig.write_cnt); 
	

    driFlashEepWrite( cfgPageIdGet(), 0, pTemp, sizeof(ST_CONFIG)/4 + 1 );
}








void configUpdate( void )
{
    if( _cfgModify == 0 )
        return;

      _cfgModify = 0;
      _cfgSet();

}

void configInit( void )
{
	cfgPageIdInit();
	
    configLoad();
    _cfgModify = 0;

    if( _stAppConfig.flash_is_new != 0 )// 第一次使用
    {
        configDef();
    }
    else
    {
        /*cfgCfgVerLoad();
        cfgSleepSecLoad();
        cfgWorkSecLoad();
        cfgWorkStateLoad();*/
    }
}



u8 cfgIsIdle( void )
{
	if( _cfgModify == 0 )
		return TRUE;

	return FALSE;
}




//=============================================
//=============================================
#ifdef TEST_MOD_CONFIG

#include "timer.h"
#include "dbg_uart.h"


#if 0
static void _testConfigTimerCB( void )
{
	//GPIOB->ODR ^= GPIO_PIN_5;
	//HAL_GPIO_TogglePin( GPIOB, GPIO_PIN_5);
}

void testConfig( void )
{
	U32 ver = 0x87654321;
	//cfgCfgVerSet(ver);
	cfgCfgVerSet(ver);
	
	configUpdate();
	configLoad();
 
	if( ver == _stAppConfig.cfg_ver )
	{
		//timerStartSec( 1, TIMER_REPEAT_FOREVER, _testConfigTimerCB ); // OK
		dprintf( "\r\n write flash ok\r\n" );
	}
	else
	{
		//timerStart( 200/TIMER_UNIT_MS, TIMER_REPEAT_FOREVER, _testConfigTimerCB ); // NG
		dprintf( "\r\n write flash ng\r\n" );
	}

	
	
}

#endif


#if 1

static u32 _ver = 1;


static void _testConfigTimerCB( void )
{
	dprintfBuf( "@", (u8 *)&_stAppConfig, sizeof(ST_CONFIG), 0 );
}



void testConfig( void )
{
	dprintfBuf( "*", (u8 *)&_stAppConfig, sizeof(ST_CONFIG), 0 );


   // _stAppConfig.flash_is_new = CONFIG_DEF_FLASH_IS_NEW;

    _stAppConfig.cfg_ver   = 3;
	
    _stAppConfig.sleep_sec = 5;
    _stAppConfig.work_sec  = 30;
	
    _stAppConfig.ctrl_mode = 1;
    _stAppConfig.cmd_ctrl_open_sec = 15;

	
    _stAppConfig.period_ctrl_open_minute  = 25;
    _stAppConfig.period_ctrl_close_minute = 35;


    _stAppConfig.aes_switch = 1;
    memset( _stAppConfig.aes_key, 0, EEP_LEN_CFG_AES_KEY );

	_cfgModify = 1;


	timerStartSec( 4,  2,  _testConfigTimerCB );

	
	
}

#endif





#endif

