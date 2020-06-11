/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/



#ifndef ___CONFIG_H
#define ___CONFIG_H


#include "com_includes.h"


#include "cfg_page_id.h"
#include "cfg_base.h"
#include "cfg_aes.h"
#include "cfg_ctrl.h"








#define FLASH_NEW_VAL   (0xFF)//(0xFFFFFFFF) // flash 未写时读出为 0xFF

#define CONFIG_DEF_FLASH_IS_NEW (0)


//======flash is new======================================

//extern u8 cfgNewGet( void );

//extern u8 cfgNewSet( u8 eepNew );

//extern u8 cfgNewDef( void );




//======config to def======================================

extern void configDef( void );


extern void configLoad( void );




extern void configInit( void );


extern void configUpdate( void );





#ifdef TEST_MOD_CONFIG

extern void testConfig( void );

#endif


#endif

