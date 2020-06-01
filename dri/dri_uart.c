 

#include "com_typedef.h"
#include "com_var.h"

#include "bt.h"
#include "lpm.h"


#include "dri_uart.h"
#include "dri.h"



#include "ddl.h"
#include "uart.h"
#include "gpio.h"
//#include "sysctrl.h"
#include "dri_uart.h"





#if 0


static void _rxIntCB(void)
{
   Uart_ReceiveData(UARTCH1);
}

void ErrIntCallback(void)
{
  
}


void PErrIntCallBack(void)
{
}


void CtsIntCallBack(void)
{

}


static void _uartPortInit(void)
{
    stc_gpio_config_t stcGpioCfg;
	
    DDL_ZERO_STRUCT(stcGpioCfg);
	
    stcGpioCfg.enDir = GpioDirOut;
    Gpio_Init(GpioPortA,GpioPin2,&stcGpioCfg);
    Gpio_SetAfMode(GpioPortA,GpioPin2,GpioAf1);//TX

	
    stcGpioCfg.enDir = GpioDirIn;
    Gpio_Init(GpioPortA,GpioPin3,&stcGpioCfg);
    Gpio_SetAfMode(GpioPortA,GpioPin3,GpioAf1);//RX
}




void driUartInit( void )
{  
    uint16_t u16Scnt     = 0;
    stc_uart_config_t    stcConfig;
    stc_uart_irq_cb_t    stcUartIrqCb;
    stc_uart_multimode_t stcMulti;
    stc_uart_baud_t      stcBaud;
    
    en_uart_mmdorck_t enTb8;

    DDL_ZERO_STRUCT(stcConfig);
    DDL_ZERO_STRUCT(stcUartIrqCb);
    DDL_ZERO_STRUCT(stcMulti);
    DDL_ZERO_STRUCT(stcBaud);
    
    _uartPortInit();
    
    stcUartIrqCb.pfnRxIrqCb   = _rxIntCB;
    stcUartIrqCb.pfnTxIrqCb   = 0;
    stcUartIrqCb.pfnRxFEIrqCb = ErrIntCallback;
    stcUartIrqCb.pfnPEIrqCb   = PErrIntCallBack;
    stcUartIrqCb.pfnCtsIrqCb  = CtsIntCallBack;
    stcConfig.pstcIrqCb = &stcUartIrqCb;
    stcConfig.bTouchNvic = TRUE;

	EnableNvic( UART1_IRQn, IRQ_LEVEL_UART, TRUE);
  

    stcConfig.enRunMode = UartMode3;     // 模式3
    stcConfig.enStopBit = Uart1bit;     // 1 位停止位 

    stcMulti.enMulti_mode = UartNormal; // 正常工作模式
    Uart_SetMultiMode(UARTCH1,&stcMulti);//多主机单独配置
    enTb8 = UartEven;// 偶校验
    Uart_SetMMDOrCk(UARTCH1,enTb8);
    
    Uart_Init(UARTCH1, &stcConfig);
    
    Uart_SetClkDiv(UARTCH1,Uart8Or16Div);
    stcBaud.u32Pclk = Sysctrl_GetPClkFreq();
    stcBaud.enRunMode = UartMode3;
    stcBaud.u32Baud = 2400;
    u16Scnt = Uart_CalScnt(UARTCH1,&stcBaud);
    Uart_SetBaud(UARTCH1,u16Scnt);
    
    Uart_ClrStatus(UARTCH1,UartRC);//清接收请求
    Uart_EnableIrq(UARTCH1,UartRxIrq);//使能串口中断  
    Uart_EnableFunc(UARTCH1,UartRx);//使能收发



	driUartCheckInit();
}



void driUartSend( u8 *pData, u32 len )
{
	u8 *pTemp;
	u32 i;

	pTemp = pData;
	
	for( i = len; i != 0; i--, pTemp++)
	{
		Uart_SetMMDOrCk(UARTCH1,UartEven);
		
		Uart_SendData( UARTCH1,  *pTemp );
	}

}



void driUartSendNum( u16 val, u8 isEnter )
{
	u8 pVal[10] = {0};
	u16 len;

	len = dec2str(val, (char *)pVal);


	driUartSend(pVal, len);

	if(isEnter)
	{
		pVal[0] = '\r';
		pVal[1] = '\n';
		driUartSend( pVal, 2 );
	}

}





void driUartCheckSleepIn( void )
{
	Gpio_EnableIrq(UART_CHECK_PORT, UART_CHECK_PIN,GpioIrqFalling);
    EnableNvic(UART_CHECK_PORT_NVIC, IRQ_LEVEL_UART_CHECK, TRUE);
}

void driUartCheckSleepOut( void )
{
	 if( TRUE == Gpio_GetIrqStatus(UART_CHECK_PORT, UART_CHECK_PIN) )
	 {
		Gpio_ClearIrq(UART_CHECK_PORT, UART_CHECK_PIN); // 清除中断标志
		EnableNvic(UART_CHECK_PORT_NVIC, IRQ_LEVEL_UART_CHECK, FALSE);
	 }
}

void driUartCheckInitIn( void )
{
    stc_gpio_config_t pstcGpioCfg;

	DDL_ZERO_STRUCT(pstcGpioCfg);
	
	pstcGpioCfg.enDir      = GpioDirIn;
	pstcGpioCfg.enDrv      = GpioDrvL;
	pstcGpioCfg.enPuPd     = GpioNoPuPd;    // GpioPd;//GpioNoPuPd;//GpioPu;
	pstcGpioCfg.enOD       = GpioOdDisable; // GpioOdEnable;//GpioOdDisable;
	pstcGpioCfg.enCtrlMode = GpioAHB;       // GpioAHB;

	Gpio_Init(  UART_CHECK_PORT,   UART_CHECK_PIN, &pstcGpioCfg);
}


void driUartCheckInit( void )
{
	driUartCheckInitIn();

	
}








/*

u8 driUartCheckRead( void )
{
	return Gpio_GetInputIO(UART_CHECK_PORT, UART_CHECK_PIN) ;   
}
*/


#else



static void _rxIntCB(void)
{
   Uart_ReceiveData(UARTCH1);
}

void ErrIntCallback(void)
{
  
}


void PErrIntCallBack(void)
{
}


void CtsIntCallBack(void)
{

}


static void _uartPortInit(void)
{
    stc_gpio_config_t stcGpioCfg;
	
    DDL_ZERO_STRUCT(stcGpioCfg);
	
    stcGpioCfg.enDir = GpioDirOut;
    Gpio_Init(GpioPortA,GpioPin2,&stcGpioCfg);
    Gpio_SetAfMode(GpioPortA,GpioPin2,GpioAf1);//TX

	
    stcGpioCfg.enDir = GpioDirIn;
    Gpio_Init(GpioPortA,GpioPin3,&stcGpioCfg);
    Gpio_SetAfMode(GpioPortA,GpioPin3,GpioAf1);//RX
}




void driUartInit( void )
{  
    uint16_t u16Scnt     = 0;
    stc_uart_config_t    stcConfig;
    stc_uart_irq_cb_t    stcUartIrqCb;
    stc_uart_multimode_t stcMulti;
    stc_uart_baud_t      stcBaud;
    
    en_uart_mmdorck_t enTb8;

    DDL_ZERO_STRUCT(stcConfig);
    DDL_ZERO_STRUCT(stcUartIrqCb);
    DDL_ZERO_STRUCT(stcMulti);
    DDL_ZERO_STRUCT(stcBaud);
    
    _uartPortInit();
    
    stcUartIrqCb.pfnRxIrqCb   = _rxIntCB;
    stcUartIrqCb.pfnTxIrqCb   = 0;
    stcUartIrqCb.pfnRxFEIrqCb = ErrIntCallback;
    stcUartIrqCb.pfnPEIrqCb   = PErrIntCallBack;
    stcUartIrqCb.pfnCtsIrqCb  = CtsIntCallBack;
    stcConfig.pstcIrqCb = &stcUartIrqCb;
    stcConfig.bTouchNvic = TRUE;

	EnableNvic( UART1_IRQn, IRQ_LEVEL_UART, TRUE);
  

    stcConfig.enRunMode = UartMode3;     // 模式3
    stcConfig.enStopBit = Uart1bit;     // 1 位停止位 

    stcMulti.enMulti_mode = UartNormal; // 正常工作模式
    Uart_SetMultiMode(UARTCH1,&stcMulti);//多主机单独配置
    enTb8 = UartEven;// 偶校验
    Uart_SetMMDOrCk(UARTCH1,enTb8);
    
    Uart_Init(UARTCH1, &stcConfig);
    
    Uart_SetClkDiv(UARTCH1,Uart8Or16Div);
    stcBaud.u32Pclk = Sysctrl_GetPClkFreq();
    stcBaud.enRunMode = UartMode3;
    stcBaud.u32Baud = 2400;
    u16Scnt = Uart_CalScnt(UARTCH1,&stcBaud);
    Uart_SetBaud(UARTCH1,u16Scnt);
    
    Uart_ClrStatus(UARTCH1,UartRC);//清接收请求
    Uart_EnableIrq(UARTCH1,UartRxIrq);//使能串口中断  
    Uart_EnableFunc(UARTCH1,UartRx);//使能收发



	driUartCheckInit();
}



void driUartSend( u8 *pData, u32 len )
{
	u8 *pTemp;
	u32 i;

	pTemp = pData;
	
	for( i = len; i != 0; i--, pTemp++)
	{
		Uart_SetMMDOrCk(UARTCH1,UartEven);
		
		Uart_SendData( UARTCH1,  *pTemp );
	}

}



void driUartSendNum( u16 val, u8 isEnter )
{
	u8 pVal[10] = {0};
	u16 len;

	len = dec2str(val, (char *)pVal);


	driUartSend(pVal, len);

	if(isEnter)
	{
		pVal[0] = '\r';
		pVal[1] = '\n';
		driUartSend( pVal, 2 );
	}

}




void driUartCheckInitIn( void )
{
    stc_gpio_config_t pstcGpioCfg;

	DDL_ZERO_STRUCT(pstcGpioCfg);
	
	pstcGpioCfg.enDir      = GpioDirIn;
	pstcGpioCfg.enDrv      = GpioDrvL;
	pstcGpioCfg.enPuPd     = GpioNoPuPd;    // GpioPd;//GpioNoPuPd;//GpioPu;
	pstcGpioCfg.enOD       = GpioOdDisable; // GpioOdEnable;//GpioOdDisable;
	pstcGpioCfg.enCtrlMode = GpioAHB;       // GpioAHB;

	Gpio_Init(  UART_CHECK_PORT,   UART_CHECK_PIN, &pstcGpioCfg);
}


void driUartCheckInit( void )
{
	driUartCheckInitIn();

	
}


#endif








