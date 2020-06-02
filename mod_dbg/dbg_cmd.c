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
#include "timer.h"


#include "dbg_cmd_uart_pass.h"
#include "dbg_cmd_aes.h"
#include "dbg_cmd_dev.h"



const char strDebugCmdHead[] =   "fh@";
#define DEBUG_CMD_HEAD_LEN   (3)




#define DEBUG_UART_PASS_LEN    ( DEBUG_CMD_HEAD_LEN + DEBUG_UART_PASS_HEAD_LEN )
#define DEBUG_AES_CMD_LEN      ( DEBUG_CMD_HEAD_LEN + DEBUG_AES_HEAD_LEN )








u8 debugCmd( u8 *str,  u8 len ) // fh@uartpass4g1
{
	if( len < DEBUG_CMD_HEAD_LEN )
		return FALSE;
	
	if( memcmp( str, strDebugCmdHead, DEBUG_CMD_HEAD_LEN) != 0 ) // "fh@"
	{
		return FALSE;
	}

	if( memcmp( str + DEBUG_CMD_HEAD_LEN, strCmdUartPassHead, DEBUG_UART_PASS_HEAD_LEN ) == 0 ) // uart pass cmd
	{	
		if( debugCmdUartPass(str + DEBUG_UART_PASS_LEN, len - DEBUG_UART_PASS_LEN ) == TRUE )
			return TRUE;
	}
	#if 0
	else if( memcmp( str + DEBUG_CMD_HEAD_LEN, strCmdAesHead, DEBUG_AES_HEAD_LEN) == 0 ) // aes cmd
	{
		if( debugCmdAes(str + DEBUG_AES_CMD_LEN, len - DEBUG_AES_CMD_LEN ) == TRUE )
			return TRUE;
	}
	#endif

	return FALSE;


}









