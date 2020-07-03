/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/



#ifndef ___CFG_CTRL_H
#define ___CFG_CTRL_H


#include "com_includes.h"


#define CONFIG_DEF_CTRL_STATE                   (0)

#define CONFIG_DEF_CTRL_MODE                    (0)  // 0���������ģʽ  1�����ڿ���ģʽ



#ifdef DEV_DEBUG_ING
	#define CONFIG_CTRL_OPEN_SEC_MIN         (  5 * 1 )       // ��ˮ�����ֵ�ʱ�� ��Сֵ
	#define CONFIG_DEF_CMD_CTRL_OPEN_SEC     ( 30 * 1L)
#else
	#define CONFIG_CTRL_OPEN_SEC_MIN         ( 60 * 1 )     // ��ˮ�����ֵ�ʱ�� ��Сֵ fenghuiw 
	#define CONFIG_DEF_CMD_CTRL_OPEN_SEC     ( 60 * 3L)     // ��ˮ�����ֵ�ʱ�� Ĭ��ֵ
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







//======�Զ����ڿ���ʱ�� ���͹ص�ʱ�� =====================================
extern void cfgPeriodCtrlGapGet( u32 *pOpenMinute, u32 *pCloseMinute);

extern void cfgPeriodCtrlGapSet( u32 openMinute, u32 closeMinute );

extern void cfgPeriodCtrlGapDef( void );







#endif




