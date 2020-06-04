


/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2020-06-01                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/

#include "com_includes.h"
#include "dri_includes.h"
#include "mod_includes.h"
#include "dev.h"




#define TEST_PORT  (GpioPortA)
#define TEST_PIN   (GpioPin2)


static void _testLedInit(void)
{
    stc_gpio_cfg_t stcGpioCfg;
	

	DDL_ZERO_STRUCT(stcGpioCfg);
	
	
    ///< 打开GPIO外设时钟门控
   // Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE); 
    
    ///< 端口方向配置->输出(其它参数与以上（输入）配置参数一致)
    stcGpioCfg.enDir = GpioDirOut;
	
    ///< 端口上下拉配置->下拉
    stcGpioCfg.enPu = GpioPuDisable;
    stcGpioCfg.enPd = GpioPdEnable;
    
    ///< LED关闭
    Gpio_ClrIO(TEST_PORT, TEST_PIN);
    
    ///< GPIO IO LED端口初始化
    Gpio_Init(TEST_PORT, TEST_PIN, &stcGpioCfg);
    
}







static void _test( void )
{
	//_testAes();
	
	#ifdef TEST_COM_DELAY
		testDelay();
	#endif

	
	#ifdef TEST_MOD_TIMER
		testTimer();
	#endif	

	
	#ifdef TEST_DRI_UART_DEBUG
		//testDriUartDbg( );
	#endif

	#ifdef TEST_MOD_CONFIG
		testConfig();
	#endif	

	
	#ifdef TEST_MOD_DBG_UART
		testModDbgUart();
	#endif	


	#ifdef TEST_AES_128_HW
	
		#include "aes_128.h"
		testAesHw();
	#endif		

	#ifdef TEST_MOD_AES
		testModAes();
	#endif	

	#ifdef TEST_ZGB_NODE
		testZgbNode();
	#endif	

	#ifdef TEST_CTRL_OUT
		testCtrlOut();
	#endif		
}





int main(void)
{  
	gB1.inited = 0;

	driInit();

	_testLedInit();

	modInit();

	devInit();

	//ledInit();
	
	_test();

	
	dprintf("p03_terminal_ctrl_water V0.1_20200613 fenghui\r\n");

	gB1.inited = 1;

	
	while(1)
    {
		driTimerLoopIrqCB();

		#ifdef USE_IWDG
			iwdgRefresh();
		#endif
    }
	

	return TRUE;

	
}

