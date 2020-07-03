

#include "com_typedef.h"

#include "com_includes.h"





u32 gSysFreq;



//ʱ�ӳ�ʼ������
static void _clkDivInit( void )
{
    //ʱ�ӷ�Ƶ����
    Sysctrl_SetHCLKDiv(SysctrlHclkDiv1);
    Sysctrl_SetPCLKDiv(SysctrlPclkDiv1);
}

static void _systemClkInit_PLL48M_byRCH(void)
{
    stc_sysctrl_pll_cfg_t stcPLLCfg;    
    
    ///< RCHʱ�Ӳ�ͬƵ�ʵ��л�����Ҫ�Ƚ�ʱ���л���RCL
    Sysctrl_SetRCLTrim(SysctrlRclFreq32768);
    Sysctrl_SetRCLStableTime(SysctrlRclStableCycle64);
    Sysctrl_ClkSourceEnable(SysctrlClkRCL, TRUE);
    Sysctrl_SysClkSwitch(SysctrlClkRCL);
    
    ///< ����Ŀ��Ƶ�ʵ�RCH��TRIMֵ
    Sysctrl_SetRCHTrim(SysctrlRchFreq4MHz);
    ///< ʹ��RCH
    Sysctrl_ClkSourceEnable(SysctrlClkRCH, TRUE);
    
    stcPLLCfg.enInFreq    = SysctrlPllInFreq4_6MHz;     //RCH 4MHz
    stcPLLCfg.enOutFreq   = SysctrlPllOutFreq36_48MHz;  //PLL ���
    stcPLLCfg.enPllClkSrc = SysctrlPllRch;              //����ʱ��Դѡ��RCH
    stcPLLCfg.enPllMul    = SysctrlPllMul12;            //4MHz x 12 = 48MHz
    Sysctrl_SetPLLFreq(&stcPLLCfg); 
    
    ///< ��ʹ�õ�ʱ��ԴHCLK����24M������FLASH ���ȴ�����Ϊ1 cycle(Ĭ��ֵҲΪ1 cycle)
    Flash_WaitCycle(FlashWaitCycle1);    
    
    ///< ʹ��PLL
    Sysctrl_ClkSourceEnable(SysctrlClkPLL, TRUE);
    ///< ʱ���л���PLL
    Sysctrl_SysClkSwitch(SysctrlClkPLL);

}



///<��ע������ⲿ�������úꡪ��[SYSTEM_XTH],���ʹ��PLL��XTH����С��24MHz
static void _SystemClkInit_PLL48M_byXTH(void)
{
    stc_sysctrl_pll_cfg_t stcPLLCfg;    
    
    ///< �л�ʱ��ǰ�������ⲿ���پ�������XTHƵ�ʷ�Χ,���þ��������ʹ��Ŀ��ʱ�ӣ��˴�ΪSYSTEM_XTH = 32MHz
    Sysctrl_SetXTHFreq(SysctrlXthFreq4_8MHz);
    Sysctrl_XTHDriverCfg(SysctrlXtalDriver3);
    Sysctrl_SetXTHStableTime(SysctrlXthStableCycle16384);
    Sysctrl_ClkSourceEnable(SysctrlClkXTH, TRUE);
    delay1ms(10);
    
    stcPLLCfg.enInFreq    = SysctrlPllInFreq6_12MHz;    //XTH 8MHz
    stcPLLCfg.enOutFreq   = SysctrlPllOutFreq36_48MHz;  //PLL ���
    stcPLLCfg.enPllClkSrc = SysctrlPllRch;              //����ʱ��Դѡ��RCH
    stcPLLCfg.enPllMul    = SysctrlPllMul6;             //8MHz x 6 = 48MHz
    Sysctrl_SetPLLFreq(&stcPLLCfg); 
    
    ///< ��ʹ�õ�ʱ��ԴHCLK����24M������FLASH ���ȴ�����Ϊ1 cycle(Ĭ��ֵҲΪ1 cycle)
    Flash_WaitCycle(FlashWaitCycle1);    

    ///< ʹ��PLL
    Sysctrl_ClkSourceEnable(SysctrlClkPLL, TRUE);    
    ///< ʱ���л���PLL
    Sysctrl_SysClkSwitch(SysctrlClkPLL);

}






static void _clkCtrl( boolean_t onOrOff ) // true: on  false :off
{
	if( onOrOff == TRUE )
		Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio,onOrOff);

	Sysctrl_SetPeripheralGate(SysctrlPeripheralBaseTim,onOrOff);
	
	Sysctrl_SetPeripheralGate(SysctrlPeripheralUart0,onOrOff);
	Sysctrl_SetPeripheralGate(SysctrlPeripheralUart1,onOrOff);

	Sysctrl_SetPeripheralGate(SysctrlPeripheralLpUart0,onOrOff);
	

	Sysctrl_SetPeripheralGate(SysctrlPeripheralFlash,onOrOff);

	#ifdef USE_IWDG
		if( onOrOff == TRUE )
			Sysctrl_SetPeripheralGate(SysctrlPeripheralWdt,onOrOff);
	#endif

	
	Sysctrl_SetPeripheralGate(SysctrlPeripheralAdcBgr,onOrOff);

	#ifdef AES_128_USE_HW
		Sysctrl_SetPeripheralGate(SysctrlPeripheralAes, onOrOff);
	#endif

	//Sysctrl_SetPeripheralGate(SysctrlPeripheralTick,onOrOff);
	//Sysctrl_SetPeripheralGate(SysctrlPeripheralDma,onOrOff);
}









void driClkOnWakeup( void )// ˯�߻���
{
	 _clkCtrl( TRUE );
}



void driClkToSleep( void ) // ����˯��
{
	_clkCtrl( FALSE );
}




void driClkInit( void )
{

	_clkDivInit();
	//_SystemClkInit_PLL48M_byXTH();

	_systemClkInit_PLL48M_byRCH();
 	
    gSysFreq = Sysctrl_GetHClkFreq();  //

	_clkCtrl( TRUE );
}



