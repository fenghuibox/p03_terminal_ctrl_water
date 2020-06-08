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



#define ZGB_RESET_PORT  ( GpioPortA )
#define ZGB_RESET_PIN   ( GpioPin11 )
#define ZGB_RESET_AF    ( GpioAf0 )


#define ZGB_DETECT_PORT  ( GpioPortB )
#define ZGB_DETECT_PIN   ( GpioPin5 )
#define ZGB_DETECT_AF    ( GpioAf0 )


#define ZGB_ACK_PORT  ( GpioPortA )
#define ZGB_ACK_PIN   ( GpioPin15 )
#define ZGB_ACK_AF    ( GpioAf0 )



#define ZGB_WAKEUP_PORT  ( GpioPortB )
#define ZGB_WAKEUP_PIN   ( GpioPin3 )
#define ZGB_WAKEUP_AF    ( GpioAf0 )


#define ZGB_SLEEP_PORT  ( GpioPortB )
#define ZGB_SLEEP_PIN   ( GpioPin4 )
#define ZGB_SLEEP_AF    ( GpioAf0 )







//---------sleep----------------------------------------------------------
void driZgbSleepH( void )
{
	Gpio_SetIO(ZGB_SLEEP_PORT, ZGB_SLEEP_PIN);
}

void driZgbSleepL( void )
{
	Gpio_ClrIO(ZGB_SLEEP_PORT, ZGB_SLEEP_PIN);
}



static void _ioZgbSleepInit(void)
{
    stc_gpio_cfg_t stcGpioCfg;
	

	DDL_ZERO_STRUCT(stcGpioCfg);

	driZgbSleepH();

    ///< 端口方向配置
    stcGpioCfg.enDir = GpioDirOut;
	
    ///< 端口上下拉配置
    stcGpioCfg.enPu = GpioPuEnable;
    stcGpioCfg.enPd = GpioPdDisable;

	
    ///< 端口初始化
    Gpio_Init(ZGB_SLEEP_PORT, ZGB_SLEEP_PIN, &stcGpioCfg);

	driZgbSleepH();

}

 
 //---------reset----------------------------------------------------------
 void driZgbResetH( void )
 {
	 Gpio_SetIO(ZGB_RESET_PORT, ZGB_RESET_PIN );
 }
 
 void driZgbResetL( void )
 {
	 Gpio_ClrIO(ZGB_RESET_PORT, ZGB_RESET_PIN );
 }
 
 
 
 static void _ioZgbResetInit(void)
 {
	 stc_gpio_cfg_t stcGpioCfg;
	 
	 
	 DDL_ZERO_STRUCT(stcGpioCfg);
	 
	 driZgbResetH();
	 
	 ///< 端口方向配置
	 stcGpioCfg.enDir = GpioDirOut;
	 
	 ///< 端口上下拉配置
	 stcGpioCfg.enPu = GpioPuEnable;
	 stcGpioCfg.enPd = GpioPdDisable;
	 
	 
	 ///< 端口初始化
	 Gpio_Init(ZGB_RESET_PORT, ZGB_RESET_PIN, &stcGpioCfg);

 
	 driZgbResetH();
 
 }


//---------wakeup----------------------------------------------------------
void driZgbWakeupH( void )
{
	Gpio_SetIO(ZGB_WAKEUP_PORT, ZGB_WAKEUP_PIN );
}

void driZgbWakeupL( void )
{
	Gpio_ClrIO(ZGB_WAKEUP_PORT, ZGB_WAKEUP_PIN );
}



static void _ioZgbWakeupInit(void)
{
	stc_gpio_cfg_t stcGpioCfg;
	
	
	DDL_ZERO_STRUCT(stcGpioCfg);
	
	driZgbWakeupH();
	
	///< 端口方向配置
	stcGpioCfg.enDir = GpioDirOut;
	
	///< 端口上下拉配置
	stcGpioCfg.enPu = GpioPuEnable;
	stcGpioCfg.enPd = GpioPdDisable;
	
	
	///< 端口初始化
	Gpio_Init(ZGB_WAKEUP_PORT, ZGB_WAKEUP_PIN, &stcGpioCfg);


	driZgbWakeupH();

}

//---------detect----------------------------------------------------------
void driZgbDetectH( void )
{
	Gpio_SetIO(ZGB_DETECT_PORT, ZGB_DETECT_PIN );
}

void driZgbDetectL( void )
{
	Gpio_ClrIO(ZGB_DETECT_PORT, ZGB_DETECT_PIN );
}



static void _ioZgbDetectInit(void)
{
	stc_gpio_cfg_t stcGpioCfg;
	
	
	DDL_ZERO_STRUCT(stcGpioCfg);
	
	driZgbDetectH();
	
	///< 端口方向配置
	stcGpioCfg.enDir = GpioDirOut;
	
	///< 端口上下拉配置
	stcGpioCfg.enPu = GpioPuEnable;
	stcGpioCfg.enPd = GpioPdDisable;
	
	
	///< 端口初始化
	Gpio_Init( ZGB_DETECT_PORT, ZGB_DETECT_PIN, &stcGpioCfg);


	driZgbDetectH();

}





//---------ACK----------------------------------------------------------


u8 driZgbAckGet( void )
{
	if( Gpio_ReadOutputIO(ZGB_ACK_PORT, ZGB_ACK_PIN) == 0 )
		return 0;

	return 1;
}

static void _ioZgbAckInit(void)
{
	stc_gpio_cfg_t stcGpioCfg;
	
	DDL_ZERO_STRUCT(stcGpioCfg);
	
	
	///< 端口方向配置
	stcGpioCfg.enDir = GpioDirIn;
	
	///< 端口上下拉配置
	stcGpioCfg.enPu = GpioPuDisable;
	stcGpioCfg.enPd = GpioPdDisable;
	
	
	///< 端口初始化
	Gpio_Init( ZGB_ACK_PORT, ZGB_ACK_PIN, &stcGpioCfg);

}


//-------------------------------------------------------------------

void driIoZgbInit( void )
{
	#if 1
	_ioZgbSleepInit();
	_ioZgbResetInit();
	_ioZgbWakeupInit();
	_ioZgbDetectInit();
	_ioZgbAckInit();	
	#endif
	
}




