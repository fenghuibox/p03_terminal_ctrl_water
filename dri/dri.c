

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
	#if 0
    ///< 配置为端口输入（除 ZGB IO 端口外）
    M0P_GPIO->PADIR = 0XFFFF;
    M0P_GPIO->PBDIR = 0XFFC3;  // PB2=zgb_ack | PB3=zgb_wake | PB4=zgb_sleep | PB5=zgb_detect
    M0P_GPIO->PCDIR = 0XEFFF;  // PC12=zgb_reset
    M0P_GPIO->PDDIR = 0XFFFF;
    M0P_GPIO->PEDIR = 0XFFFF;
    M0P_GPIO->PFDIR = 0XFFFF;
	#endif

	#if 1
    ///< 配置为端口输入（除 ZGB IO 端口外）
    M0P_GPIO->PADIR = 0XFFFF;
    M0P_GPIO->PBDIR = 0XFFFF;  
    M0P_GPIO->PCDIR = 0XFFFF;  
    M0P_GPIO->PDDIR = 0XFFFF;
    M0P_GPIO->PEDIR = 0XFFFF;
    M0P_GPIO->PFDIR = 0XFFFF;


	#endif

	//------------------------------
	#if 0
    
    ///< 输入下拉（除 ZGB IO 端口以外）
    M0P_GPIO->PAPD = 0xFFFB; // led PA4 FK
    M0P_GPIO->PBPD = 0XFFC3; 
    M0P_GPIO->PCPD = 0XEFFF;
    M0P_GPIO->PDPD = 0xFFFF;
    M0P_GPIO->PEPD = 0xFFFF;
    M0P_GPIO->PFPD = 0xFFFF;
	#endif

	#if 1
    M0P_GPIO->PAPD = 0; // led PA4 FK
    M0P_GPIO->PBPD = 0; 
    M0P_GPIO->PCPD = 0;
    M0P_GPIO->PDPD = 0;
    M0P_GPIO->PEPD = 0;
    M0P_GPIO->PFPD = 0;


	#endif
	//------------------------------


	



	#if 0
    M0P_GPIO->PADIR = 0;
    M0P_GPIO->PBDIR = 0;  
    M0P_GPIO->PCDIR = 0;  
    M0P_GPIO->PDDIR = 0;
    M0P_GPIO->PEDIR = 0;
    M0P_GPIO->PFDIR = 0;
	#endif

	
	#if 0
    M0P_GPIO->PAOUT = 0x7C9F; // PA15, 9,8,6,5
    M0P_GPIO->PBOUT = 0xFFFF; 
    M0P_GPIO->PCOUT = 0xFFFF;
    M0P_GPIO->PDOUT = 0xFFFF;
    M0P_GPIO->PEOUT = 0xFFFF;
    M0P_GPIO->PFOUT = 0xFFFF;
	#endif


	
    
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


