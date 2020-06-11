/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
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
	
	snInit();	   // 3 ͨ��ͨ��

	frameInit();

	
#else


	m485Init();





#endif


	

}



