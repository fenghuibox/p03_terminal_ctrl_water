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

#include "dri_adc.h"
#include "dev_vbatt.h"
#include "dbg_uart.h"
#include "timer.h"



//#define VBATT_SCAN_GAP_MS  ( 20 )
#define VBATT_SCAN_GAP_MS  ( 100 )




#define _ADC_VAL_CNT  (2)

static u32 _adcArr[_ADC_VAL_CNT];
static u32 _adcVal;
static  u8 _adcIndex;



u32 devVbattValGet( void )
{
	return _adcVal;
}



#define _3V_ADC  (2715)


static void _adcValIn( u32 val )
{
	driAdcEnClose();
	
	_adcArr[_adcIndex++] = val;
	
	if(_adcIndex == _ADC_VAL_CNT )
	{
		_adcIndex = 0;

		//_adcVal = ( _adcArr[0] + _adcArr[1] + _adcArr[2] ) / 3;
		_adcVal = ( _adcArr[0] + _adcArr[1] ) / 2;

		//dprintf( "\r\nvbat=%d",_adcVal );

		if( _adcVal  < _BATT_3D4_ADC )
			gB1.battIsLow = 1;
		
	}
	
}




static void _adcStartCB( void )
{
	driAdcStart();
}



static void _battStart( void )
{
	driAdcEnOpen();
	timerStart( 6/TIMER_UNIT_MS,  1,  _adcStartCB );
}


static void _vbattCB( void )
{
	_battStart();
}


void devVbattInit( void )
{
	#include "timer.h"

	driAdcFunSet( _adcValIn );

	timerStart( VBATT_SCAN_GAP_MS/TIMER_UNIT_MS,  TIMER_REPEAT_FOREVER,  _vbattCB );
}


