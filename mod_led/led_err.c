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
//#include "dri_includes.h"

//#include "mod_includes.h"

#include "led_com.h"

#include "timer.h"

//--------------------------------------------------------------------


//--------------------------------------------------------------------

#define _ERR_BLINK_ON_MS   ( 300)   // 128 
#define _ERR_BLINK_OFF_MS  ( 300)  // 80

//#define _ERR_BLINK_WAIT_MS  (16 * 20) // 320
#define _ERR_BLINK_WAIT_MS  (2000 - _ERR_BLINK_OFF_MS) // 1200



#define _ERR_BLINK_ON_CNT    ( _ERR_BLINK_ON_MS   / TIMER_UNIT_MS )
#define _ERR_BLINK_OFF_CNT   ( _ERR_BLINK_OFF_MS  / TIMER_UNIT_MS )
#define _ERR_BLINK_WAIT_CNT  ( _ERR_BLINK_WAIT_MS / TIMER_UNIT_MS )


//--------------------------------------------------------------------
static u8  _ledBlinkCnt = 0;
static u8  _repeats = 0;
static u8  _tid = TIMER_ID_ERROR;

//--------------------------------------------------------------------
//--------------------------------------------------------------------



static void _ledSetCB2( void );
static void _ledBlink( void );


static void _waitCB( void )
{
	_tid = TIMER_ID_ERROR;
	
	//_allOff();
	_repeats = _ledBlinkCnt;
	_ledBlink();
}


static void _ledSetCB1( void )
{
	_tid = TIMER_ID_ERROR;
	_allOff();
	_tid = timerStart( _ERR_BLINK_OFF_CNT, 1, _ledSetCB2 );
}


static void _ledSetCB2( void )
{
	_tid = TIMER_ID_ERROR;

	comU8Dec( &_repeats );

	if( _repeats != 0)
	{
		_allOn();
		_tid = timerStart( _ERR_BLINK_ON_CNT, 1, _ledSetCB1 );
	}
	else
	{
		
		_tid = timerStart( _ERR_BLINK_WAIT_CNT , 1, _waitCB );
	}

}




//=============================================================================


static void _ledBlinkStop( void )
{
	timerStop( &_tid );
	_repeats = 0;
	_ledBlinkCnt = 0;
}


static void _ledBlink( void )
{
	_allOn();
	
	_tid = timerStart( _ERR_BLINK_ON_CNT, 1, _ledSetCB1 );
}


//-----------------------------------------------------------------------------------

static void _blinkCntSet( u8 cnt )
{
	if( cnt == 0 )
	{
		_ledBlinkStop();
		return;
	}

	if( cnt == _ledBlinkCnt )
	{
		if( _tid != TIMER_ID_ERROR )//ING
			return;
	}

	
	_ledBlinkStop();
	_ledBlinkCnt = _repeats = cnt;
	_ledBlink();
}



void _errShow( EN_DEV_STATE s )
{
	u8 cnt = 0;
	
	switch( s )
	{
	case DEV_STATE_ERR_HINT_ZIGBEE:
		cnt = 2;
		break;
	
	case DEV_STATE_ERR_HINT_MASTER:
		cnt = 3;
		break;

	case DEV_STATE_ERR_STOP_TEMP:
		cnt = 4;
		break;
	
	default:
		break;
		
	}

	_blinkCntSet( cnt );
}




void _errShowStop( void )
{
	_ledBlinkStop();
}



