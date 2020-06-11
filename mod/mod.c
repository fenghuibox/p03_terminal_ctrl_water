/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#include "com_includes.h"
#include "mod_includes.h"









void modInit( void )
{
#if 1

	timerInit();  // 1 
	
	configInit(); // 2 read/def eeprom
	
	dbgInit();

	
	aesInit();
	
	zgbInit();
	
	ctrlInit(); // ctrl

	ledInit();
	
	snInit();	   // 3 通信通道

	frameInit();

	
#else


	m485Init();





#endif


	

}



