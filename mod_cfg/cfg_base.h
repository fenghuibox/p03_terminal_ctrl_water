/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/



#ifndef ___CFG_BASE_H
#define ___CFG_BASE_H


#include "com_includes.h"








#define CONFIG_DEF_CFG_VER      (0)

#define CONFIG_DEF_SLEEP_SEC    (0)
#define CONFIG_DEF_WORK_SEC    (60)

#define CONFIG_DEF_OPEN_SEC     (60)
#define CONFIG_DEF_CLOSE_SEC    (600)


#define CONFIG_DEF_WORK_STATE   (0)



//#define CONFIG_DEF_SG_CH       (5) // 默认使用4G和IPAD   fenghuiw



//======dev cfg ver =====================================
extern u32 cfgCfgVerGet( void ); //

extern u32 cfgCfgVerSet( u32 cfgVer );

extern u32 cfgCfgVerDef( void );



//======dev sleep sec =====================================
extern u32 cfgSleepSecGet( void ); //


extern u32 cfgSleepSecSet( u32 sec );


extern u32 cfgSleepSecDef( void );


//======dev work sec =====================================
extern u32 cfgWorkSecGet( void ) ;//


extern u32 cfgWorkSecSet( u32 sec );


extern u32 cfgWorkSecDef( void );


//======dev open sec =====================================
extern u32 cfgOpenSecGet( void ); //


extern u32 cfgOpenSecSet( u32 sec );


extern u32 cfgOpenSecDef( void );


//======dev close sec =====================================
extern u32 cfgCloseSecGet( void ) ;//


extern u32 cfgCloseSecSet( u32 sec );


extern u32 cfgCloseSecDef( void );


//======dev work state =====================================
typedef enum
{
	DEV_WORK_STATE_NORMAL = 0,
	DEV_WORK_STATE_CONFIG,
}EN_DEV_WORK_STATE;

extern u8 cfgWorkStateIsNormal( void );


extern u8 cfgWorkStateGet( void ) ;//



extern u8 cfgWorkStateSet( u8 s );


extern u32 cfgWorkStateDef( void );




//======dev  =====================================





#endif




