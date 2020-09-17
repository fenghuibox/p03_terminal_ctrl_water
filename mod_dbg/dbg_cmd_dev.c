/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 


#if 1

#include "com_includes.h"
#include "timer.h"


#include "dbg_uart.h"

#include "dev_state.h"
#include "cfg.h"


//=================================================


const char strCmdDevHead[] =      "dev";




const char strCmdDevCtrlInfoGet[]  = "infoget";

#define CMD_DEV_CTRL_INFO_GET_LEN  (7)


const char strCmdDevVer[]  = "ver";

#define CMD_DEV_VER_LEN  (3)


/*

����/����    1Byte |  0:����  1������
����ʱ��     4Byte |  ��λ����
�������     1Byte |  0:��  1����
����ʱ��     4Byte |  ��λ����
�Ƿ�������ʱ 1Byte |  0:��  1��������ʱ

*/




static u8 _rspVer( void )
{
	// paraVerGet()

	dprintf( "zl@17E" );

	return TRUE;

	
}



// str =
u8 debugCmdDev( u8 *str,  u8 len )
{

	if( len == CMD_DEV_CTRL_INFO_GET_LEN )
	{
		if( memcmp( ( const char *)str, strCmdDevCtrlInfoGet, CMD_DEV_CTRL_INFO_GET_LEN ) == 0 )
		{
			dprintf("d/n=%d w=%d s=%d o=%d", gB1.isDebug, cfgWorkSecGet(), cfgSleepSecGet(), cfgCtrlOpenSecGet() );
			return TRUE;
		}
	}
	else if( len == 3 )
	{
		if( memcmp( ( const char *)str, strCmdDevVer, CMD_DEV_VER_LEN ) == 0 )
		{
			return _rspVer();
			//return TRUE;
		}
	}




	return FALSE;


}


#endif

