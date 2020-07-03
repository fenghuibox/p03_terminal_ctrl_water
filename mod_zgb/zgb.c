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

#include "zgb.h"



void zgbInit( void )
{

#if 1 // fenghuiw
	zgbIoInit();
	
	zgbUartInit();

	zgbCmdInit();

	zgbStateInit();

	//zgbMacInit();


	//zgbUnpackInit();

	//zgbG2NstateInit();

	//zgbG2Ninit();

	//zgbPassRxInit();

	
	//zgbUartInit();

#else
	zgbIoInit();

	zgbUartInit();

	zgbCmdInit();

	zgbStateInit();

	//zgbMacInit();


	zgbUnpackInit();

	zgbG2NstateInit();

	zgbG2Ninit();

	zgbPassRxInit();


	//zgbUartInit();



#endif
	
}




