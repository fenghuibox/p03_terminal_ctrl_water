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
	
	dbgInit();
#else


	configInit(); // 2 read/def eeprom

	sgInit();	   // 3 ͨ��ͨ��


	ctrlInit(); // ctrl

	aesInit();


	m485Init();

	zgbInit();

	g4Init();

	frameInit();

	ipadInit();


#endif


	

}



