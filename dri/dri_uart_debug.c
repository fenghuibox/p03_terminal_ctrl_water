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

///< �˿�����
static void _dbgUartPortCfg(void)
{
    stc_gpio_cfg_t stcGpioCfg;
	
    
    DDL_ZERO_STRUCT(stcGpioCfg);
    
    
    ///<TX
    stcGpioCfg.enDir =  GpioDirOut;
    Gpio_Init( DBG_TX_PORT, DBG_TX_PIN, &stcGpioCfg);
    Gpio_SetAfMode( DBG_TX_PORT,DBG_TX_PIN,DBG_TX_AF ); //����PA00ΪLPUART1_TX

	
    //<RX
    stcGpioCfg.enDir =  GpioDirIn;
    Gpio_Init( DBG_RX_PORT,DBG_RX_PIN,&stcGpioCfg);
    Gpio_SetAfMode( DBG_RX_PORT,DBG_RX_PIN, DBG_RX_AF ); //����PA01ΪLPUART1_RX
    
}





//==========================================================================
///< LPUART����
static void _dbgUartCfg(void)
{
    stc_lpuart_cfg_t  stcCfg;

    DDL_ZERO_STRUCT(stcCfg);
    
    ///<����ģ��ʱ��ʹ��
    Sysctrl_SetPeripheralGate( DBG_UART_Peripheral_ID, TRUE );    
    
    ///<LPUART ��ʼ��
    stcCfg.enStopBit = LPUart1bit;                   ///<1ֹͣλ  
    
    //stcCfg.enMmdorCk = LPUartEven;                   ///<żУ��
    stcCfg.enMmdorCk = LPUartDataOrAddr;                   ///
    
    stcCfg.stcBaud.enSclkSel = LPUartMskPclk;        ///<����ʱ��Դ
    stcCfg.stcBaud.u32Sclk   = Sysctrl_GetPClkFreq();  ///<PCLK��ȡ
    stcCfg.stcBaud.enSclkDiv = LPUartMsk4Or8Div;     ///<������Ƶ
    stcCfg.stcBaud.u32Baud   = 115200;                   ///<������

	//stcCfg.enRunMode         = LPUartMskMode3;               ///<����ģʽ
    stcCfg.enRunMode         = LPUartMskMode1;               ///<����ģʽ
    
    LPUart_Init( DBG_UART_HANDLE, &stcCfg );

	 
    ///<LPUART �ж�ʹ��
    LPUart_ClrStatus(  DBG_UART_HANDLE, LPUartRC );          ///<������ж�����
    LPUart_ClrStatus(  DBG_UART_HANDLE, LPUartTC );          ///<�巢���ж�����

   // LPUart_DisableIrq( DBG_UART_HANDLE, LPUartRxIrq );      ///<��ֹ�����ж�
    LPUart_EnableIrq( DBG_UART_HANDLE, LPUartRxIrq );      ///<ʹ�ܽ����ж�
    LPUart_EnableIrq(  DBG_UART_HANDLE, LPUartTxIrq );       ///<ʹ�ܷ����ж�
    EnableNvic(        DBG_UART_IRQ_ID, DBG_UART_IRQ_LEVEL, TRUE );         ///<ϵͳ�ж�ʹ��
}







//==========================================================================
///<LPUART1 �жϷ�����
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
    EnableNvic(        DBG_UART_IRQ_ID, DBG_UART_IRQ_LEVEL, FALSE );  // 1: �� �ж�
                                                                      // 2: io = in_down  
	                                                                  // 3: close clk

	LPUart_DisableIrq( DBG_UART_HANDLE, LPUartRxIrq ); 	 ///<ʹ�ܽ����ж�
	LPUart_DisableIrq(  DBG_UART_HANDLE, LPUartTxIrq );	   ///<ʹ�ܷ����ж�

	/*
    LPUartRenFunc    = 4u,    ///<0-TX; ///<1-��mode0ģʽ����RX&TX ,mode0ģʽ����RX;       
    LPUartDmaRxFunc  = 16u,   ///<DMA���չ���   
    LPUartDmaTxFunc  = 17u,   ///<DMA���͹���
    LPUartRtsFunc    = 18u,   ///<Ӳ����RTS����
    LPUartCtsFunc    = 19u,   ///<Ӳ����CTS����
    LPUartHdFunc     = 22u,   ///<���߰�˫������    

	*/
	//LPUart_DisableFunc( DBG_UART_HANDLE, LPUartRenFunc );


    Gpio_SetAfMode( DBG_TX_PORT, DBG_TX_PIN, GpioAf0 ); //
    Gpio_SetAfMode( DBG_TX_PORT, DBG_RX_PIN, GpioAf0 ); //

}

void driUartDbgOnWakeup( void )
{
	                                                                  // 1: open clk
	_dbgUartPortCfg();                                                // 2: io = init                                                                 
	EnableNvic(		 DBG_UART_IRQ_ID, DBG_UART_IRQ_LEVEL, TRUE );     // 3: �� �ж�

    ///<LPUART �ж�ʹ��
    LPUart_ClrStatus(  DBG_UART_HANDLE, LPUartRC );          ///<������ж�����
    LPUart_ClrStatus(  DBG_UART_HANDLE, LPUartTC );          ///<�巢���ж�����
	

	LPUart_EnableIrq( DBG_UART_HANDLE, LPUartRxIrq ); 	 ///<ʹ�ܽ����ж�
	LPUart_EnableIrq(  DBG_UART_HANDLE, LPUartTxIrq );	   ///<ʹ�ܷ����ж�


	/*
	LPUartDmaRxFunc  = 16u,   ///<DMA���չ���	
	LPUartDmaTxFunc  = 17u,   ///<DMA���͹���
	LPUartRtsFunc	 = 18u,   ///<Ӳ����RTS����
	LPUartCtsFunc	 = 19u,   ///<Ӳ����CTS����
	LPUartHdFunc	 = 22u,   ///<���߰�˫������	
	*/
	//LPUart_EnableFunc( DBG_UART_HANDLE, LPUartRenFunc );

	
}




