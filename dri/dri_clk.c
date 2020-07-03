

#include "com_typedef.h"

#include "com_includes.h"





u32 gSysFreq;



//时钟初始化配置
static void _clkDivInit( void )
{
    //时钟分频设置
    Sysctrl_SetHCLKDiv(SysctrlHclkDiv1);
    Sysctrl_SetPCLKDiv(SysctrlPclkDiv1);
}

static void _systemClkInit_PLL48M_byRCH(void)
{
    stc_sysctrl_pll_cfg_t stcPLLCfg;    
    
    ///< RCH时钟不同频率的切换，需要先将时钟切换到RCL
    Sysctrl_SetRCLTrim(SysctrlRclFreq32768);
    Sysctrl_SetRCLStableTime(SysctrlRclStableCycle64);
    Sysctrl_ClkSourceEnable(SysctrlClkRCL, TRUE);
    Sysctrl_SysClkSwitch(SysctrlClkRCL);
    
    ///< 加载目标频率的RCH的TRIM值
    Sysctrl_SetRCHTrim(SysctrlRchFreq4MHz);
    ///< 使能RCH
    Sysctrl_ClkSourceEnable(SysctrlClkRCH, TRUE);
    
    stcPLLCfg.enInFreq    = SysctrlPllInFreq4_6MHz;     //RCH 4MHz
    stcPLLCfg.enOutFreq   = SysctrlPllOutFreq36_48MHz;  //PLL 输出
    stcPLLCfg.enPllClkSrc = SysctrlPllRch;              //输入时钟源选择RCH
    stcPLLCfg.enPllMul    = SysctrlPllMul12;            //4MHz x 12 = 48MHz
    Sysctrl_SetPLLFreq(&stcPLLCfg); 
    
    ///< 当使用的时钟源HCLK大于24M：设置FLASH 读等待周期为1 cycle(默认值也为1 cycle)
    Flash_WaitCycle(FlashWaitCycle1);    
    
    ///< 使能PLL
    Sysctrl_ClkSourceEnable(SysctrlClkPLL, TRUE);
    ///< 时钟切换到PLL
    Sysctrl_SysClkSwitch(SysctrlClkPLL);

}



///<请注意根据外部晶振配置宏——[SYSTEM_XTH],如果使用PLL，XTH必须小于24MHz
static void _SystemClkInit_PLL48M_byXTH(void)
{
    stc_sysctrl_pll_cfg_t stcPLLCfg;    
    
    ///< 切换时钟前（根据外部高速晶振）设置XTH频率范围,配置晶振参数，使能目标时钟，此处为SYSTEM_XTH = 32MHz
    Sysctrl_SetXTHFreq(SysctrlXthFreq4_8MHz);
    Sysctrl_XTHDriverCfg(SysctrlXtalDriver3);
    Sysctrl_SetXTHStableTime(SysctrlXthStableCycle16384);
    Sysctrl_ClkSourceEnable(SysctrlClkXTH, TRUE);
    delay1ms(10);
    
    stcPLLCfg.enInFreq    = SysctrlPllInFreq6_12MHz;    //XTH 8MHz
    stcPLLCfg.enOutFreq   = SysctrlPllOutFreq36_48MHz;  //PLL 输出
    stcPLLCfg.enPllClkSrc = SysctrlPllRch;              //输入时钟源选择RCH
    stcPLLCfg.enPllMul    = SysctrlPllMul6;             //8MHz x 6 = 48MHz
    Sysctrl_SetPLLFreq(&stcPLLCfg); 
    
    ///< 当使用的时钟源HCLK大于24M：设置FLASH 读等待周期为1 cycle(默认值也为1 cycle)
    Flash_WaitCycle(FlashWaitCycle1);    

    ///< 使能PLL
    Sysctrl_ClkSourceEnable(SysctrlClkPLL, TRUE);    
    ///< 时钟切换到PLL
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









void driClkOnWakeup( void )// 睡眠唤醒
{
	 _clkCtrl( TRUE );
}



void driClkToSleep( void ) // 进入睡眠
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



