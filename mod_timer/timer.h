/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/



#ifndef ___TIMER_H
#define ___TIMER_H


#include "com_includes.h"

#include "dri_timer.h"

#define TIMER_UNIT_MS  DRI_TIMER_UNIT_MS 


//=====================================================
//--------- �ڲ�ʹ�õ� �̶� timerId--------------------
/*
typedef enum
{
	TID_RPT_1,
	TID_RPT_2,
	TID_RPT_3,
	TID_PIR_DEAD_ZONE,  //   ä��ʱ�� (15 �� )
	TID_PIR_NOT_TRIGER, //   PIRû�д����ĵȴ�ʱ�䣨���PIR��ʱ����û�б������� ������basic set command(0x00)���������豸����	
}EN_TIMER_ID;
*/

//typedef void ( *FunTimeCB)( u8 timerId, u8 *pRepeats, u32 *pT, FunTimeCB *pTimerCB, void *data);

typedef void ( *FunTimeCB)( void );




extern void timerInit( void );



//=====================================================
#define TIMER_ID_ERROR        (0xFF)
#define TIMER_REPEAT_FOREVER  (0xFF)
//-----------------------------------------------------
//       t: ��ʱʱ�� ( ��λ:TIMER_UNIT_MS )  MS
// repeats: �ظ����� ( TIMER_REPEAT_FOREVER : ���޴�)
// timerCB: �ص����� (����Ϊ null)
//-----------------------------------------------------
// return :   OK: timerId     ERROR: TIMER_ID_ERROR
//-----------------------------------------------------
extern u8 timerStart( u32 t, u8 repeats, FunTimeCB timerCB );


//=====================================================
//       t: ��ʱʱ�� ( ��λ:s )
// repeats: �ظ����� ( TIMER_REPEAT_FOREVER : ���޴�)
// timerCB: �ص����� (����Ϊ null)
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

