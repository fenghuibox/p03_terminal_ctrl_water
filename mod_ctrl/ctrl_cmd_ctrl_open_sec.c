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

//#include "timer.h"
#include "dbg_uart.h"





#include "cfg_ctrl.h"









void ctrlOpenSecSet( u32 openSec )
{
	cfgCtrlOpenSecSet( openSec );
}



u32 ctrlOpenSecGet( void )
{
	return cfgCtrlOpenSecGet();

}




void ctrlOpenSecInit( void )
{

}











