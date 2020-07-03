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

#include "dri_io_led.h"

#include "timer.h"
#include "dbg_uart.h"


#include "led_com.h"

#include "dev.h"


//======================================================
#define _LED_GAP_MS           (100)

#define _IDLE_GAP_MS           (100)
#define _IDLE_GAP_CNT           (_IDLE_GAP_MS/_LED_GAP_MS)

#define _WORK_GAP_MS            (500)
#define _WORK_GAP_CNT           (_WORK_GAP_MS/_LED_GAP_MS)

//======================================================




//======================================================




static u8 _ledCnt;





static void _normalShow( EN_DEV_STATE s ) 
{
	_ledCnt++;
	
	switch( s )
	{
	case DEV_STATE_DBG:
		if( (_ledCnt % _IDLE_GAP_CNT) == 0)
			driLed1Toggle();
		break;

	case DEV_STATE_READ_CTRL_INFO:
		driLed1Close();
		break;

	case DEV_STATE_UART_PASS:
		driLed1Open();
		break;	

	default:
		driLed1Close();
		
	}
}




//=================================================================





//---------------------------------------------------------








static void _ledPollCB( void )
{
	//
	
	EN_DEV_STATE s;
	

	s = devStateGet();

	/*if( s < DEV_STATE_WARNING ) // normal
	{
		_errShowStop();
		_normalShow();
	}
	else */
	if( s < DEV_STATE_ERR ) // warning
	{
		_errShowStop();
		_normalShow( s );
	}
	else // err
	{
		_errShow( s );
	}

}





void ledInit( void )
{
	_ledCnt = 0;
	timerStart( _LED_GAP_MS/TIMER_UNIT_MS,  TIMER_REPEAT_FOREVER,  _ledPollCB );
}


