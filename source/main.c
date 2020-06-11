


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


	#ifdef TEST_MOD_ZGB_UART
		testModZgbUart();
	#endif


	#ifdef TEST_COM_TIME
		testComTime();
	#endif	

	#ifdef TEST_CTRL_OUT
		testCtrlOut();
	#endif		
}





int main(void)
{  
	gB1.inited = 0;

	driInit();

	modInit();

	devInit();

	
	

	dprintf("\r\np03_terminal_ctrl_water V0.1_20200613 fenghui\r\n");

	gB1.inited = 1;
	
	_test();
	
	while(1)
    {
		driTimerLoopIrqCB();

		#ifdef USE_IWDG
			iwdgRefresh();
		#endif
    }
	

	return TRUE;

	
}

