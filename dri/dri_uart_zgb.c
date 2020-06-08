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


#include "dri_uart_zgb.h"



/*

PB06 UART0 TX
PB07 UART0 RX

*/


//==========================================================================
#define ZGB_TX_PORT  ( GpioPortB )
#define ZGB_TX_PIN   ( GpioPin6 )
#define ZGB_TX_AF    ( GpioAf2 )

#define ZGB_RX_PORT  ( GpioPortB )
#define ZGB_RX_PIN   ( GpioPin7 )
#define ZGB_RX_AF    ( GpioAf2 )

#define ZGB_UART_Peripheral_ID  SysctrlPeripheralUart0


#define ZGB_UART_IRQ_ID        UART0_2_IRQn

#define ZGB_UART_IRQ_LEVEL        IrqLevel3


//==========================================================================

static irqCB _uartIrqCB;
//==========================================================================

///< 端口配置
static void _zgbUartPortCfg(void)
{
    stc_gpio_cfg_t stcGpioCfg;
	
    
    DDL_ZERO_STRUCT(stcGpioCfg);
    
    
    ///<TX
    stcGpioCfg.enDir =  GpioDirOut;
    Gpio_Init( ZGB_TX_PORT, ZGB_TX_PIN, &stcGpioCfg);
    Gpio_SetAfMode( ZGB_TX_PORT,ZGB_TX_PIN,ZGB_TX_AF ); 

	
    //<RX
    stcGpioCfg.enDir =  GpioDirIn;
    Gpio_Init( ZGB_RX_PORT,ZGB_RX_PIN,&stcGpioCfg);
    Gpio_SetAfMode( ZGB_RX_PORT,ZGB_RX_PIN, ZGB_RX_AF ); 
    
}





//==========================================================================
///< LPUART配置
static void _zgbUartCfg(void)
{
    stc_uart_cfg_t    stcCfg;

    DDL_ZERO_STRUCT(stcCfg);
    
	
    ///<UART Init
    stcCfg.enRunMode        = UartMskMode1;          ///<模式1
    stcCfg.enStopBit        = UartMsk1bit;           ///<1bit停止位
    stcCfg.enMmdorCk        = UartMskDataOrAddr;     ///<偶检验
    stcCfg.stcBaud.u32Baud  = 57600;                  ///<波特率9600
    stcCfg.stcBaud.enClkDiv = UartMsk8Or16Div;       ///<通道采样分频配置
    stcCfg.stcBaud.u32Pclk  = Sysctrl_GetPClkFreq(); ///<获得外设时钟（PCLK）频率值
    Uart_Init(ZGB_UART_HANDLE, &stcCfg);                   ///<串口初始化
    
    ///<UART中断使能
    Uart_ClrStatus(ZGB_UART_HANDLE,UartRC);                ///<清接收请求
    Uart_ClrStatus(ZGB_UART_HANDLE,UartTC);                ///<清接收请求
    Uart_EnableIrq(ZGB_UART_HANDLE,UartRxIrq);             ///<使能串口接收中断
    Uart_EnableIrq(ZGB_UART_HANDLE,UartTxIrq);             ///<使能串口接收中断    
    EnableNvic(ZGB_UART_IRQ_ID, ZGB_UART_IRQ_LEVEL, TRUE);  ///<系统中断使能
}







//==========================================================================
//UART0中断函数
void Uart0_IRQHandler(void)
{
	if( _uartIrqCB )
		_uartIrqCB();
}





void driUartZgbIrqCBset( irqCB funIrqCB )
{
	_uartIrqCB = funIrqCB;
}



void driUartZgbInit( irqCB funIrqCB )
{
	_zgbUartPortCfg();

	_zgbUartCfg();

	_uartIrqCB = funIrqCB;
}



//============================================================================







