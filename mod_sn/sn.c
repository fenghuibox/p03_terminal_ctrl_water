/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/


 // sn: Server and node communication    服务器和节点通信
// n2s: node to server                   节点发送给服务器

#include "com_includes.h"

#include "dbg_uart.h"

#include "sn.h"





void snPoll( void ) // 50ms
{
	snN2sPoll();
}




void snInit1( void )
{
	snN2sInit();
	
	snChInit(); // 要求 在 snG2sInit之后
	
}

void snInit2( void )
{
	snRxQueueInit();

	
	snRxInit();
	
	snMasterStateInit();


	snN2sStateInit();

	snRxUnpackInit();
}

void snInit( void )
{
	snInit1();
	snInit2();

}

