


/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2020-06-01                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/

#include "com_includes.h"
#include "dri_includes.h"
#include "mod_includes.h"
#include "dev.h"






static void _test( void )
{
	#ifdef RTC_ARL_USED_PERIOD

	#else
		//driRtcSetAlarm(5);
		//driRtcGetAlarm();
	#endif
	
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


	
	#ifdef TEST_MOD_CTRL
		testCtrlCmdCtrl( );
	#endif
}





int main(void)
{  
	
	gB1.inited = 0;
	gB1.isPowerOn = 1;

	driInit();

    delay1ms(500);

	modInit();

	devInit();

	modIoZgbWakeup(); // last 

    
	///< ===============================================
    ///< ============ ���棬���棬���棡����=============
    ///< ===============================================
    ///< ���������������������ģʽ������������д�����������ã���ֹ�������
    ///< ���ߺ�оƬ���Թ��ܲ����ٴ�ʹ�ã���
    ///< ��ʹ�ñ�����ʱ����ֹ��û�л��ѻ��Ƶ������ɾ���������д��롣
    delay1ms(1000);
	
	dprintf("\r\np03_terminal_ctrl_water V0.5_20200804 fenghui\r\n");

	gB1.inited = 1;
	
	_test();

	
	
	while(1)
    {
		driTimerLoopIrqCB();

		#ifdef USE_IWDG
			iwdgRefresh();
		#endif

		if( gB1.sleep )
		{
			devSleep();
		}
    }
	

	return TRUE;

	
}

