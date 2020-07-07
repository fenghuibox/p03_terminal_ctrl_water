/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/


#include "com_includes.h"
#include "dri_timer.h"
#include "timer.h"


void _irqCB(void);


//--------------------------------------------------
typedef struct
{
	u8 repeats;      // 0x00: close 
	                 // 0xFF: open forever
	            
	u32 t;           // ��ʱʱ�� ��λ:100ms
	u32 startCnt;    // ��ʼ����ʱ�� _cnt ֵ
	
	FunTimeCB timerCB;// ������
}ST_TIME;

//--------------------------------------------------

#define TIMER_CNT_MAX  32 // ptl_exe max used 20

//--------------------------------------------------


static ST_TIME _timers[TIMER_CNT_MAX];
static u32 _cnt = 0; // Vmax = 4294967295  
                     // Vmax * 100ms / 1000 = 429496729s
                     //   429496729s / 3600 = 119304 h
                     //      119304 h / 24  = 4971 day
                     //      4971 day / 365 = 13 year
                     //----------------------------------
                     // 20ms = 13/5 = 2.6 year
                     
//====================================================

static void _varInit( void )
{	
	_cnt = 0;
	comMemset( (u8 * )_timers, 0,sizeof(_timers) );
}
					 

static u8 _timerIdGet( void )
{
	int i;
	ST_TIME *pTimers;

	pTimers = _timers;

	for( i = 0; i < TIMER_CNT_MAX; i++ )
	{
		if( pTimers->repeats == 0 )
			return i;

		pTimers++;
	}

	return TIMER_ID_ERROR;
}

static void _timerSet( u8 id, u32 t, u8 repeats, FunTimeCB timerCB )
{
	ST_TIME *pTimers;

	if( id > TIMER_CNT_MAX )
		return;

	pTimers = _timers + id;

	pTimers->t = t;
	pTimers->startCnt = _cnt;
	pTimers->repeats = repeats;
	pTimers->timerCB = timerCB;

	if( repeats != 0 )
	{
		if( _cnt == 0 ) // Ŀǰû������
			driTimerStart( _irqCB );
	}
		
}


/*
void timerInit( void )
{
	driTimerTickInit();
	_varInit();
}
*/

void timerInit( void )
{
	_varInit();
}


//#define PRINT_TIMER_MAX_ID

#ifdef PRINT_TIMER_MAX_ID
	static u8 _maxTimerId = 15; // max = 16  20191105
#endif

//=====================================================
//       t: ��ʱʱ�� ( ��λ:TIMER_UNIT_MS )  33MS
// repeats: �ظ����� ( TIMER_REPEAT_FOREVER : ���޴�)
// timerCB: �ص����� (����Ϊ null)
//-----------------------------------------------------
// return :   OK: timerId     ERROR: TIMER_ID_ERROR
//-----------------------------------------------------
u8 timerStart( u32 t,  u8 repeats, FunTimeCB timerCB )
{
	//#include "dbg_uart.h"
	
	u8 id;

	if( repeats == 0 || t == 0 )
		return TIMER_ID_ERROR;
	
	id = _timerIdGet();


	if(id == TIMER_ID_ERROR )
	{
		//dprintf("\r\n ***********timer err**********************"); 
		return id;
	}
	
	//assert( id != TIMER_ID_ERROR );

	

	_timerSet( id, t, repeats, timerCB );

	#ifdef PRINT_TIMER_MAX_ID
	if( _maxTimerId < id )
	{
		dprintf("max tid=%d", id );
		
		_maxTimerId = id;
	}
	#endif

	return id;
}


//=====================================================
//       t: ��ʱʱ�� ( ��λ:TIMER_UNIT_MS )  S
// repeats: �ظ����� ( TIMER_REPEAT_FOREVER : ���޴�)
// timerCB: �ص����� (����Ϊ null)
//-----------------------------------------------------
// return :   OK: timerId     ERROR: TIMER_ID_ERROR
//-----------------------------------------------------
u8 timerStartSec( u32 t,  u8 repeats, FunTimeCB timerCB )
{
	return timerStart( t * (1000/TIMER_UNIT_MS), repeats, timerCB );
}


void timerStop( u8 *pTimerId )
{
	_timerSet(*pTimerId, 0, 0, 0);

	*pTimerId = TIMER_ID_ERROR;
}

//#define TIME_CNT_MAX (0xFFFFF000)

//------------------------------------------------------------------
//------------------------------------------------------------------

static u8 _irqOneCB( ST_TIME *pTimer )
{

	u8 *pRepeats;
	u32 cnt;

	pRepeats = &(pTimer->repeats);
	
	if( *pRepeats == 0 ) // û������
		return 0;

	cnt = _cnt - pTimer->startCnt;
	if(cnt == 0)
		return 1; // ���øո�����
	
	if( cnt % pTimer->t == 0 ) // ����ʱ�䵽
	{
		if( *pRepeats != TIMER_REPEAT_FOREVER ) // ������ if ����λ�ò��ܻ�
			(*pRepeats)--;

		if( pTimer->timerCB )
			pTimer->timerCB();
	}

	return 1;
}


void _irqCB(void)
{
	ST_TIME *pTimer;
	u8 i;
	u8 r;

	_cnt++;

	pTimer = _timers;

	for(r = 0, i = 0; i < TIMER_CNT_MAX; i++ )
	{
		r |= _irqOneCB( pTimer++ );
	}

	if( r == 0 ) // û�� timer ��������
	{
		driTimerStop();
		_varInit();
	}	
}


/*
void timerIdChange( u8 *pOldTimerId, u8 newTimerId )
{
	if( *pOldTimerId != TIMER_ID_ERROR )
		timerStop( *pOldTimerId );
	
	*pOldTimerId = newTimerId;
}
*/
//=============================================


void timerDelay( u32 ms )
{
/*
	u32 msCnt;

	if(ms == 0)
		return;
	        
        msCnt = ms; 

	driTimer4Init(TIM4_PRESCALER_128, 125 - 1 );
	
	driTimer4Start(&msCnt);
	
	while( msCnt != 0 )
		;

	driTimer4Stop();
*/
	
}







//=============================================
//=============================================
#ifdef TEST_MOD_TIMER



static void _testTimerCB( void )
{
	static u8 _cnt = 0;

	if( _cnt == 0 )
	{
		Gpio_SetIO(GpioPortA, GpioPin2);
		_cnt = 1;
	}
	else
	{
		Gpio_ClrIO(GpioPortA, GpioPin2);
		_cnt = 0;
	}

}

void testTimer( void )
{
	timerStart( 1000/TIMER_UNIT_MS, TIMER_REPEAT_FOREVER, _testTimerCB);
}


#endif

