/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/


 // sn: Server and node communication    �������ͽڵ�ͨ��
// n2s: node to server                   �ڵ㷢�͸�������

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
	
	snChInit(); // Ҫ�� �� snG2sInit֮��
	
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

