/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
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

正常/调试    1Byte |  0:正常  1：调试
休眠时间     4Byte |  单位：秒
命令控制     1Byte |  0:关  1：开
开启时长     4Byte |  单位：秒
是否重启记时 1Byte |  0:否  1：重启记时

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

