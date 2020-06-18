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
#include "dri_io_zgb.h"


#include "zgb_io.h"
#include "timer.h"



//---------sleep----------------------------------------------------------

static void _zigbeeSleepCB( void )
{
	driZgbSleepH();

	gB1.zgbSleepFinish = 1;
}


void modIoZgbSleep( void )
{
	driZgbSleepL();
	timerStart(DRI_ZIGBEE_TO_SLEEP_KEEP_L_MS/TIMER_UNIT_MS,  1,  _zigbeeSleepCB );
}



static void _ioZgbSleepInit( void )
{
	driZgbSleepH();
}




//---------reset----------------------------------------------------------
static void _zigbeeResetCB( void )
{
	driZgbResetH();
}


void modIoZgbReset( void )
{
	driZgbResetL();
	timerStart(DRI_ZIGBEE_TO_RESET_KEEP_L_MS/TIMER_UNIT_MS,  1,  _zigbeeResetCB );
}



static void _ioZgbResetInit( void )
{
	driZgbResetH();
}


//---------wakeup----------------------------------------------------------
static void _zigbeeWakeCB( void )
{
	driZgbWakeupH();

	gB1.zgbWakeupFinish = 1;
}





void modIoZgbWakeup( void )
{
	gB1.zgbWakeupTx = 1;
	gB1.zgbWakeupFinish = 0;
	
	driZgbWakeupL();
	timerStart(DRI_ZIGBEE_TO_WAKEUP_KEEP_L_MS/TIMER_UNIT_MS,  10,  _zigbeeWakeCB );
}





static void _ioZgbWakeupInit( void )
{
	driZgbWakeupH();
}


//---------detect----------------------------------------------------------

static void _zigbeeDetectCB( void )
{
	driZgbDetectH();
}


void modIoZgbDetect( void )
{
	driZgbDetectL();
	timerStart(DRI_ZIGBEE_TO_DETECT_KEEP_L_MS/TIMER_UNIT_MS,  1,  _zigbeeDetectCB );
}



static void _ioZgbDetectInit( void )
{
	driZgbDetectH();
}




//---------ACK-------- IN --------------------------------------------------


#define _ZGB_ACK_CHECK_GAP_MS  (2)
#define _ZGB_ACK_TIMEOUT_MS   (50)

#define _ZGB_ACK_CHECK_CNT (_ZGB_ACK_TIMEOUT_MS/_ZGB_ACK_CHECK_GAP_MS)

static u8 _zgbHaveAck = 0 ;

static void _zgbAckCheckCB( void )
{
	if( driZgbAckGet() )
	{
		_zgbHaveAck = 1;
	}
}


// 1 要求先调用  modIoZgbAckCheckStart()
// 2 check 时长 : _ZGB_ACK_TIMEOUT_MS
u8 modIoZgbAckGet( void )
{
	return _zgbHaveAck;
}


void modIoZgbAckCheckStart( void )
{
	_zgbHaveAck = 0;
	
	timerStart(_ZGB_ACK_CHECK_GAP_MS/TIMER_UNIT_MS,  _ZGB_ACK_CHECK_CNT,  _zgbAckCheckCB );
	
}


//-------------------------------------------------------------------

void zgbIoInit( void )
{
	_ioZgbSleepInit();
	_ioZgbResetInit();
	_ioZgbWakeupInit();
	_ioZgbDetectInit();
	
}








