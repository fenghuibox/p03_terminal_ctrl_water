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

///< �˿�����
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
///< LPUART����
static void _zgbUartCfg(void)
{
    stc_uart_cfg_t    stcCfg;

    DDL_ZERO_STRUCT(stcCfg);
    
	
    ///<UART Init
    stcCfg.enRunMode        = UartMskMode1;          ///<ģʽ1
    stcCfg.enStopBit        = UartMsk1bit;           ///<1bitֹͣλ
    stcCfg.enMmdorCk        = UartMskDataOrAddr;     ///<ż����
    stcCfg.stcBaud.u32Baud  = 57600;                  ///<������9600
    stcCfg.stcBaud.enClkDiv = UartMsk8Or16Div;       ///<ͨ��������Ƶ����
    stcCfg.stcBaud.u32Pclk  = Sysctrl_GetPClkFreq(); ///<�������ʱ�ӣ�PCLK��Ƶ��ֵ
    Uart_Init(ZGB_UART_HANDLE, &stcCfg);                   ///<���ڳ�ʼ��
    
    ///<UART�ж�ʹ��
    Uart_ClrStatus(ZGB_UART_HANDLE,UartRC);                ///<���������
    Uart_ClrStatus(ZGB_UART_HANDLE,UartTC);                ///<���������
    Uart_EnableIrq(ZGB_UART_HANDLE,UartRxIrq);             ///<ʹ�ܴ��ڽ����ж�
    Uart_EnableIrq(ZGB_UART_HANDLE,UartTxIrq);             ///<ʹ�ܴ��ڽ����ж�    
    EnableNvic(ZGB_UART_IRQ_ID, ZGB_UART_IRQ_LEVEL, TRUE);  ///<ϵͳ�ж�ʹ��
}







//==========================================================================
//UART0�жϺ���
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







