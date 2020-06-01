/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/



#ifndef ___TIMER_H
#define ___TIMER_H


#include "com_includes.h"

#include "dri_timer.h"

#define TIMER_UNIT_MS  DRI_TIMER_UNIT_MS 


//=====================================================
//--------- 内部使用的 固定 timerId--------------------
/*
typedef enum
{
	TID_RPT_1,
	TID_RPT_2,
	TID_RPT_3,
	TID_PIR_DEAD_ZONE,  //   盲区时间 (15 秒 )
	TID_PIR_NOT_TRIGER, //   PIR没有触发的等待时间（如果PIR此时间内没有被触发， 将发送basic set command(0x00)到关联的设备。）	
}EN_TIMER_ID;
*/

//typedef void ( *FunTimeCB)( u8 timerId, u8 *pRepeats, u32 *pT, FunTimeCB *pTimerCB, void *data);

typedef void ( *FunTimeCB)( void );




extern void timerInit( void );



//=====================================================
#define TIMER_ID_ERROR        (0xFF)
#define TIMER_REPEAT_FOREVER  (0xFF)
//-----------------------------------------------------
//       t: 定时时间 ( 单位:TIMER_UNIT_MS )  MS
// repeats: 重复次数 ( TIMER_REPEAT_FOREVER : 无限次)
// timerCB: 回调函数 (可以为 null)
//-----------------------------------------------------
// return :   OK: timerId     ERROR: TIMER_ID_ERROR
//-----------------------------------------------------
extern u8 timerStart( u32 t, u8 repeats, FunTimeCB timerCB );


//=====================================================
//       t: 定时时间 ( 单位:s )
// repeats: 重复次数 ( TIMER_REPEAT_FOREVER : 无限次)
// timerCB: 回调函数 (可以为 null)
//-----------------------------------------------------
// return :   OK: timerId     ERROR: TIMER_ID_ERROR
//-----------------------------------------------------
extern u8 timerStartSec( u32 t,  u8 repeats, FunTimeCB timerCB );



extern void timerStop( u8 *pTimerId );


//----------------------------------------------------
//void timerIdChange( u8 *pOldTimerId, u8 newTimerId );


//======================================
extern void timerDelay( u32 ms );



#ifdef TEST_MOD_TIMER

extern void testTimer( void );

#endif


#endif

