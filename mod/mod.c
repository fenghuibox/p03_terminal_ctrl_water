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
	
	
#else



	sgInit();	   // 3 通信通道

	ctrlInit(); // ctrl

	m485Init();

	g4Init();

	frameInit();

	ipadInit();


#endif


	

}



