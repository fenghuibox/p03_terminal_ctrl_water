

#include "com_typedef.h"

#include "com_includes.h"
#include "dri_includes.h"

#include "dri.h"















void driSoftReset( void )
{
	NVIC_SystemReset();
}











//----------------------------------------------------------------

void driInit( void )
{
	driClkInit();

	driFlashEepInit();
	
	driTimerInit();
	
	driUartDebugInit(NULL);
	
	driUartZgbInit(NULL);

	
	driIoZgbInit();

	driAdcInit();

	driIoChInit();
	
	driIoCtrlInit();

	driIoLedInit();
	
	driRtcInit();

	

	
}



//----------sleep and wakeup---------------------------------------------------------


static void _driToSleep(void)
{
    ///< 打开GPIO外设时钟门控
   // Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);
    
    //swd as gpio
    //Sysctrl_SetFunc(SysctrlSWDUseIOEn, TRUE);
    
    ///< 配置为数字端口
    M0P_GPIO->PAADS = 0;
    M0P_GPIO->PBADS = 0;
    M0P_GPIO->PCADS = 0;
    M0P_GPIO->PDADS = 0;
    M0P_GPIO->PEADS = 0;
    M0P_GPIO->PFADS = 0;

	//------------------------------
    ///< 配置为端口输入（除 ZGB IO 端口外）
    M0P_GPIO->PADIR = 0XFCCF;  // LED=PA4  vbatt=PA5
    M0P_GPIO->PBDIR = 0XFFC7;// 0XFFC3;  // PB2=zgb_ack | PB3=zgb_wake | PB4=zgb_sleep | PB5=zgb_detect | PB0=TX | PB11=RX
    M0P_GPIO->PCDIR = 0XEFEF;  // PC12=zgb_reset
    M0P_GPIO->PDDIR = 0XFFFF;
    M0P_GPIO->PEDIR = 0XFFFF;
    M0P_GPIO->PFDIR = 0XFFFF;


	//------------------------------
    ///< 输入下拉（除 ZGB IO 端口以外）
    M0P_GPIO->PAPD = 0X0300;// 0xFFEB;  // led PA4
    M0P_GPIO->PBPD = 0X0000;//0XF702;  // DBG_TX_RX(PB0 PB11)   zgb_TX_RX(PB6 PB7)
    M0P_GPIO->PCPD = 0X0000;//0X2FFF;  // RTC=PC14 PC15, PC12=zgb_reset
    M0P_GPIO->PDPD = 0X0000;//0xFFFF;
    M0P_GPIO->PEPD = 0X0000;//0xFFFF;
    M0P_GPIO->PFPD = 0X0000;//0xFFDF; // MODE(PF5)



	//------------------------------
	#if 0
	    M0P_GPIO->PAPU = 0; 
	    M0P_GPIO->PBPU = 0; 
	    M0P_GPIO->PCPU = 0;
	    M0P_GPIO->PDPU = 0;
	    M0P_GPIO->PEPU = 0;
	    M0P_GPIO->PFPU = 0;
	#endif

	#if 0
	    M0P_GPIO->PAOUT = 0x0010; // PA15, 9,8,6,5
	    M0P_GPIO->PBOUT = 0; 
	    M0P_GPIO->PCOUT = 0;
	    M0P_GPIO->PDOUT = 0;
	    M0P_GPIO->PEOUT = 0;
	    M0P_GPIO->PFOUT = 0;
	#endif


	
    
}


void driContinueSleep( void )
{
	///< 进入低功耗模式——深度休眠（使能唤醒后退出中断自动休眠特性）
    Lpm_GotoDeepSleep( FALSE );
}

void driToSleep( void )
{	
#if 0
	#ifdef RTC_ARL_USED_PERIOD //----------

		ST_DATE_TIME stDT = {0};

		if( driRtcGetDateTime( &stDT) == FALSE )
			return;

		if( stDT.sec % 10 == 0 )
			return;
	#else //--------------------------------
		driRtcSetAlarm( 10 );
	#endif //--------------------------------
#endif

	
	driAdcToSleep();
	driTimerToSleep();
	driUartDbgToSleep();
	driUartZgbToSleep();
	
	driIoChToSleep();
	driIoCtrlToSleep();
	driIoLedToSleep();
	driIoZgbToSleep();

	_driToSleep();  // set io
	driClkToSleep(); // close clk
	

	///< 进入低功耗模式——深度休眠（使能唤醒后退出中断自动休眠特性）
    Lpm_GotoDeepSleep( FALSE );

}



void driOnWakeup( void )
{
	driClkOnWakeup(); // open clk
	
	driIoChOnWakeup();
	driIoCtrlOnWakeup();
	driIoLedOnWakeup();
	driIoZgbOnWakeup();
	
	driUartZgbOnWakeup();
	driUartDbgOnWakeup();
	driTimerOnWakeup();

	driAdcOnWakeup();

	
	
	
}


