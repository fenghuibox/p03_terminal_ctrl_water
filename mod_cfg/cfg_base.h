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







 
#define CONFIG_DEF_CFG_VER         (0)


#define CONFIG_MAX_SLEEP_SEC      (60*10) // 最大的休眠时间 10分钟
#define CONFIG_MIN_SLEEP_SEC      (5)     // 最大的休眠时间 5 秒
#define CONFIG_DEF_SLEEP_SEC      (10)    // 默认的休眠时间 10 秒



#define CONFIG_DEF_WORK_SEC     (60*3) // 调试时间  单位：秒     5分钟





//#define CONFIG_DEF_WORK_STATE   (0)



//#define CONFIG_DEF_SG_CH       (5) // 默认使用4G和IPAD   fenghuiw



//======dev cfg ver =====================================
extern u32 cfgCfgVerGet( void ); //

extern void cfgCfgVerSet( u32 cfgVer );

extern void cfgCfgVerDef( void );



//======dev sleep sec =====================================
extern u32 cfgSleepSecGet( void ); //


extern void cfgSleepSecSet( u32 sec );


extern void cfgSleepSecDef( void );


//======dev work sec =====================================
extern u32 cfgWorkSecGet( void ) ;//


extern void cfgWorkSecSet( u32 sec );


extern void cfgWorkSecDef( void );




#endif




