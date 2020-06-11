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


#define CONFIG_DEF_CTRL_MODE                    (0)  // 0：命令控制模式  1：周期控制模式


#define CONFIG_DEF_CMD_CTRL_OPEN_SEC           (60*5L)

#define CONFIG_DEF_PERIOD_CTRL_OPEN_MINUTE      (1)
#define CONFIG_DEF_PERIOD_CTRL_CLOSE_MINUTE    (60)


//#define CONFIG_DEF_WORK_STATE   (0)



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




#endif




