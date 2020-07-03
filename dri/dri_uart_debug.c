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


#include "dri_uart_debug.h"



/*

PB00 LPUART0 TX
PB11 LPUART0 RX

*/


//==========================================================================
#define DBG_TX_PORT  ( GpioPortB )
#define DBG_TX_PIN   ( GpioPin0 )
#define DBG_TX_AF    ( GpioAf3 )

#define DBG_RX_PORT  ( GpioPortB )
#define DBG_RX_PIN   ( GpioPin11 )
#define DBG_RX_AF    ( GpioAf3 )

#define DBG_UART_Peripheral_ID  SysctrlPeripheralLpUart0


#define DBG_UART_IRQ_ID        LPUART0_IRQn

#define DBG_UART_IRQ_LEVEL        IrqLevel3


//==========================================================================

static irqCB _uartIrqCB;
//==========================================================================

///< 端口配置
static void _dbgUartPortCfg(void)
{
    stc_gpio_cfg_t stcGpioCfg;
	
    
    DDL_ZERO_STRUCT(stcGpioCfg);
    
    
    ///<TX
    stcGpioCfg.enDir =  GpioDirOut;
    Gpio_Init( DBG_TX_PORT, DBG_TX_PIN, &stcGpioCfg);
    Gpio_SetAfMode( DBG_TX_PORT,DBG_TX_PIN,DBG_TX_AF ); //配置PA00为LPUART1_TX

	
    //<RX
    stcGpioCfg.enDir =  GpioDirIn;
    Gpio_Init( DBG_RX_PORT,DBG_RX_PIN,&stcGpioCfg);
    Gpio_SetAfMode( DBG_RX_PORT,DBG_RX_PIN, DBG_RX_AF ); //配置PA01为LPUART1_RX
    
}





//==========================================================================
///< LPUART配置
static void _dbgUartCfg(void)
{
    stc_lpuart_cfg_t  stcCfg;

    DDL_ZERO_STRUCT(stcCfg);
    
    ///<外设模块时钟使能
    Sysctrl_SetPeripheralGate( DBG_UART_Peripheral_ID, TRUE );    
    
    ///<LPUART 初始化
    stcCfg.enStopBit = LPUart1bit;                   ///<1停止位  
    
    //stcCfg.enMmdorCk = LPUartEven;                   ///<偶校验
    stcCfg.enMmdorCk = LPUartDataOrAddr;                   ///
    
    stcCfg.stcBaud.enSclkSel = LPUartMskPclk;        ///<传输时钟源
    stcCfg.stcBaud.u32Sclk   = Sysctrl_GetPClkFreq();  ///<PCLK获取
    stcCfg.stcBaud.enSclkDiv = LPUartMsk4Or8Div;     ///<采样分频
    stcCfg.stcBaud.u32Baud   = 115200;                   ///<波特率

	//stcCfg.enRunMode         = LPUartMskMode3;               ///<工作模式
    stcCfg.enRunMode         = LPUartMskMode1;               ///<工作模式
    
    LPUart_Init( DBG_UART_HANDLE, &stcCfg );

	 
    ///<LPUART 中断使能
    LPUart_ClrStatus(  DBG_UART_HANDLE, LPUartRC );          ///<清接收中断请求
    LPUart_ClrStatus(  DBG_UART_HANDLE, LPUartTC );          ///<清发送中断请求

   // LPUart_DisableIrq( DBG_UART_HANDLE, LPUartRxIrq );      ///<禁止接收中断
    LPUart_EnableIrq( DBG_UART_HANDLE, LPUartRxIrq );      ///<使能接收中断
    LPUart_EnableIrq(  DBG_UART_HANDLE, LPUartTxIrq );       ///<使能发送中断
    EnableNvic(        DBG_UART_IRQ_ID, DBG_UART_IRQ_LEVEL, TRUE );         ///<系统中断使能
}







//==========================================================================
///<LPUART1 中断服务函数
void LpUart0_IRQHandler( void )
{
	if(_uartIrqCB)
		_uartIrqCB();
}





void driUartDebugIrqCBset( irqCB funIrqCB )
{
	_uartIrqCB = funIrqCB;
}



void driUartDebugInit( irqCB funIrqCB )
{
	_dbgUartPortCfg();

	_dbgUartCfg();

	_uartIrqCB = funIrqCB;
}



//============================================================================




//----------sleep and wakeup---------------------------------------------------------

void driUartDbgToSleep( void )
{
    EnableNvic(        DBG_UART_IRQ_ID, DBG_UART_IRQ_LEVEL, FALSE );  // 1: 关 中断
                                                                      // 2: io = in_down  
	                                                                  // 3: close clk

	LPUart_DisableIrq( DBG_UART_HANDLE, LPUartRxIrq ); 	 ///<使能接收中断
	LPUart_DisableIrq(  DBG_UART_HANDLE, LPUartTxIrq );	   ///<使能发送中断

	/*
    LPUartRenFunc    = 4u,    ///<0-TX; ///<1-非mode0模式代表RX&TX ,mode0模式代表RX;       
    LPUartDmaRxFunc  = 16u,   ///<DMA接收功能   
    LPUartDmaTxFunc  = 17u,   ///<DMA发送功能
    LPUartRtsFunc    = 18u,   ///<硬件流RTS功能
    LPUartCtsFunc    = 19u,   ///<硬件流CTS功能
    LPUartHdFunc     = 22u,   ///<单线半双工功能    

	*/
	//LPUart_DisableFunc( DBG_UART_HANDLE, LPUartRenFunc );


    Gpio_SetAfMode( DBG_TX_PORT, DBG_TX_PIN, GpioAf0 ); //
    Gpio_SetAfMode( DBG_TX_PORT, DBG_RX_PIN, GpioAf0 ); //

}

void driUartDbgOnWakeup( void )
{
	                                                                  // 1: open clk
	_dbgUartPortCfg();                                                // 2: io = init                                                                 
	EnableNvic(		 DBG_UART_IRQ_ID, DBG_UART_IRQ_LEVEL, TRUE );     // 3: 开 中断

    ///<LPUART 中断使能
    LPUart_ClrStatus(  DBG_UART_HANDLE, LPUartRC );          ///<清接收中断请求
    LPUart_ClrStatus(  DBG_UART_HANDLE, LPUartTC );          ///<清发送中断请求
	

	LPUart_EnableIrq( DBG_UART_HANDLE, LPUartRxIrq ); 	 ///<使能接收中断
	LPUart_EnableIrq(  DBG_UART_HANDLE, LPUartTxIrq );	   ///<使能发送中断


	/*
	LPUartDmaRxFunc  = 16u,   ///<DMA接收功能	
	LPUartDmaTxFunc  = 17u,   ///<DMA发送功能
	LPUartRtsFunc	 = 18u,   ///<硬件流RTS功能
	LPUartCtsFunc	 = 19u,   ///<硬件流CTS功能
	LPUartHdFunc	 = 22u,   ///<单线半双工功能	
	*/
	//LPUart_EnableFunc( DBG_UART_HANDLE, LPUartRenFunc );

	
}




