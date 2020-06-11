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

#include "dri_io_ctrl.h"

#define CTRL_12VSWITCH_PORT  ( GpioPortC )
#define CTRL_12VSWITCH_PIN   ( GpioPin4 )
#define CTRL_12VSWITCH_AF    ( GpioAf0 )

#define CTRL_12VEN_PORT  ( GpioPortA )
#define CTRL_12VEN_PIN   ( GpioPin7 )
#define CTRL_12VEN_AF    ( GpioAf0 )


#define CTRL_ON_PORT  ( GpioPortA )
#define CTRL_ON_PIN   ( GpioPin8 )
#define CTRL_ON_AF    ( GpioAf0 )


#define CTRL_OFF_PORT  ( GpioPortA )
#define CTRL_OFF_PIN   ( GpioPin9 )
#define CTRL_OFF_AF    ( GpioAf0 )






//--------- 12V switch ----------------------------------------------------------
void driCtrl12VswitchH( void )
{
	Gpio_SetIO(CTRL_12VSWITCH_PORT, CTRL_12VSWITCH_PIN);
}

void driCtrl12VswitchL( void )
{
	Gpio_ClrIO(CTRL_12VSWITCH_PORT, CTRL_12VSWITCH_PIN);
}



static void _ioCtrl12VswitchInit(void)
{
    stc_gpio_cfg_t stcGpioCfg;
	

	DDL_ZERO_STRUCT(stcGpioCfg);

	driCtrl12VswitchL();

    ///< 端口方向配置
    stcGpioCfg.enDir = GpioDirOut;
	
    ///< 端口上下拉配置
    stcGpioCfg.enPu = GpioPuDisable;
    stcGpioCfg.enPd = GpioPdEnable;

	
    ///< 端口初始化
    Gpio_Init(CTRL_12VSWITCH_PORT, CTRL_12VSWITCH_PIN, &stcGpioCfg);

	driCtrl12VswitchL();

}


//--------- 12V en ----------------------------------------------------------
void driCtrl12VenH( void )
{
	Gpio_SetIO(CTRL_12VEN_PORT, CTRL_12VEN_PIN);
}

void driCtrl12VenL( void )
{
	Gpio_ClrIO(CTRL_12VEN_PORT, CTRL_12VEN_PIN);
}



static void _ioCtrl12VenInit(void)
{
    stc_gpio_cfg_t stcGpioCfg;
	

	DDL_ZERO_STRUCT(stcGpioCfg);

	driCtrl12VenL();

    ///< 端口方向配置
    stcGpioCfg.enDir = GpioDirOut;
	
    ///< 端口上下拉配置
    stcGpioCfg.enPu = GpioPuDisable;
    stcGpioCfg.enPd = GpioPdEnable;

	
    ///< 端口初始化
    Gpio_Init(CTRL_12VEN_PORT, CTRL_12VEN_PIN, &stcGpioCfg);

	driCtrl12VenL();

}






//--------- on pin ----------------------------------------------------------
void driCtrlOnH( void )
{
	Gpio_SetIO(CTRL_ON_PORT, CTRL_ON_PIN);
}

void driCtrlOnL( void )
{
	Gpio_ClrIO(CTRL_ON_PORT, CTRL_ON_PIN);
}



static void _ioCtrlOnInit(void)
{
    stc_gpio_cfg_t stcGpioCfg;
	

	DDL_ZERO_STRUCT(stcGpioCfg);

	driCtrlOnL();

    ///< 端口方向配置
    stcGpioCfg.enDir = GpioDirOut;
	
    ///< 端口上下拉配置
    stcGpioCfg.enPu = GpioPuDisable;
    stcGpioCfg.enPd = GpioPdEnable;

	
    ///< 端口初始化
    Gpio_Init(CTRL_ON_PORT, CTRL_ON_PIN, &stcGpioCfg);

	driCtrlOnL();

}

 
 //---------off pin ----------------------------------------------------------
 void driCtrlOffH( void )
 {
	 Gpio_SetIO(CTRL_OFF_PORT, CTRL_OFF_PIN );
 }
 
 void driCtrlOffL( void )
 {
	 Gpio_ClrIO(CTRL_OFF_PORT, CTRL_OFF_PIN );
 }
 
 
 
 static void _ioCtrlOffInit(void)
 {
	 stc_gpio_cfg_t stcGpioCfg;
	 
	 
	 DDL_ZERO_STRUCT(stcGpioCfg);
	 
	 driCtrlOffL();
	 
	 ///< 端口方向配置
	 stcGpioCfg.enDir = GpioDirOut;
	 
	 ///< 端口上下拉配置
	 stcGpioCfg.enPu = GpioPuDisable;
	 stcGpioCfg.enPd = GpioPdEnable;
	 
	 
	 ///< 端口初始化
	 Gpio_Init(CTRL_OFF_PORT, CTRL_OFF_PIN, &stcGpioCfg);

 
	 driCtrlOffL();
 
 }


//--------- open  close  finish ---------------------------------------


void driCtrlOpen( void )
{
	driCtrlOnH();
	driCtrlOffL();
}


void driCtrlClose( void )
{
	driCtrlOnL();
	driCtrlOffH();
}


void driCtrlFinish( void )
{
	driCtrlOnL();
	driCtrlOffL();
}




//-------------------------------------------------------------------

void driIoCtrlInit( void )
{
	_ioCtrl12VswitchInit();
	_ioCtrl12VenInit();
	_ioCtrlOnInit();
	_ioCtrlOffInit();
	
}




