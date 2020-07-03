/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/



#ifndef ___CFG_CTRL_H
#define ___CFG_CTRL_H


#include "com_includes.h"


#define CONFIG_DEF_CTRL_STATE                   (0)

#define CONFIG_DEF_CTRL_MODE                    (0)  // 0：命令控制模式  1：周期控制模式



#ifdef DEV_DEBUG_ING
	#define CONFIG_CTRL_OPEN_SEC_MIN         (  5 * 1 )       // 开水阀保持的时长 最小值
	#define CONFIG_DEF_CMD_CTRL_OPEN_SEC     ( 30 * 1L)
#else
	#define CONFIG_CTRL_OPEN_SEC_MIN         ( 60 * 1 )     // 开水阀保持的时长 最小值 fenghuiw 
	#define CONFIG_DEF_CMD_CTRL_OPEN_SEC     ( 60 * 3L)     // 开水阀保持的时长 默认值
#endif

#define CONFIG_DEF_PERIOD_CTRL_OPEN_MINUTE      (1)
#define CONFIG_DEF_PERIOD_CTRL_CLOSE_MINUTE    (60)


//====== ctrl state  =====================================
extern u8 cfgCtrlStateGet( void );


extern void cfgCtrlStateSet( u32 ctrlState );


extern void cfgCtrlStateDef( void );



//======ctrl mode =====================================
extern u8 cfgCtrlModeGet( void ); //


extern void cfgCtrlModeSet( u32 sec );


extern void cfgCtrlModeDef( void );


//====== ctrl open sec =====================================
extern u32 cfgCtrlOpenSecGet( void ) ;//


extern void cfgCtrlOpenSecSet( u32 sec );


extern void cfgCtrlOpenSecDef( void );



//====== ctrl open start sec  =====================================
u32 cfgCtrlOpenStartGet( void );

void cfgCtrlOpenStartSet( u32 ctrlOpenStartSec );

void cfgCtrlOpenStartDef( void );







//======自动周期控制时， 开和关的时长 =====================================
extern void cfgPeriodCtrlGapGet( u32 *pOpenMinute, u32 *pCloseMinute);

extern void cfgPeriodCtrlGapSet( u32 openMinute, u32 closeMinute );

extern void cfgPeriodCtrlGapDef( void );







#endif




