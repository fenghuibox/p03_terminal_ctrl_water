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



#define LED_1_PORT  ( GpioPortA )
#define LED_1_PIN   ( GpioPin2 )
#define LED_1_AF    ( GpioAf0 )






//---------led 1----------------------------------------------------------
void driLed1H( void )
{
	Gpio_SetIO(LED_1_PORT, LED_1_PIN);
}

void driLed1L( void )
{
	Gpio_ClrIO(LED_1_PORT, LED_1_PIN);
}



void driLed1Open( void )
{
	driLed1L();
}

void driLed1Close( void )
{
	driLed1H();
}


void driLed1Toggle( void )
{
	if( gB1.led )
	{
		driLed1L();
		gB1.led = 0;
	}
	else
	{
		driLed1H();
		gB1.led = 1;
	}
}


static void _ioLed1Init(void)
{
    stc_gpio_cfg_t stcGpioCfg;
	

	DDL_ZERO_STRUCT(stcGpioCfg);

	driLed1H();

    ///< 端口方向配置
    stcGpioCfg.enDir = GpioDirOut;
	
    ///< 端口上下拉配置
    stcGpioCfg.enPu = GpioPuDisable;
    stcGpioCfg.enPd = GpioPdDisable;

	
    ///< 端口初始化
    Gpio_Init(LED_1_PORT, LED_1_PIN, &stcGpioCfg);

	driLed1H();

}


//-------------------------------------------------------------------

void driIoLedInit( void )
{
	_ioLed1Init();
	
}

//----------sleep and wakeup---------------------------------------------------------

void driIoLedToSleep( void )
{
	// 1:  set io = in_down
	// 2: close clk	
}

void driIoLedOnWakeup( void )
{
	                  // 1: open clk
	
	_ioLed1Init(); // 2: io = init

	
}



