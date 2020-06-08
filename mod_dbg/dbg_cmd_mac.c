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


#include "dbg_uart.h"
#include "zgb_mac.h"




//=================================================


const char strCmdMacHead[] =      "mac";




const char strCmdMacGet[]  = "get";

#define CMD_MAC_GET_LEN  (3)


static u8 _rspMac( void )
{

	#define DBG_CMD_MAC_RSP_LEN  (21)
	// zl@MMMMMMMMMMMMMMMMCC

	int i;
	u8 pMyMac[MAC_ADDR_LEN];
	
	u8 pRsp[DBG_CMD_MAC_RSP_LEN + 3]= "zl@";

	u8 sum;
	
	
	if( macMyGet( pMyMac ) == FALSE )
	{
		dprintf( "\r\n mac read err" );
		return TRUE;
	}

	for( i = sum = 0; i < MAC_ADDR_LEN; i++ )	
	{
		sum += pMyMac[i];
	}	
	

	macToHexStr( pMyMac, pRsp + 3 );	

	decU8toHexStr( sum, pRsp + 3 + 16 );

	pRsp[DBG_CMD_MAC_RSP_LEN] = 0;

	dprintf( (const char *)pRsp );

	return TRUE;

	
}





u8 debugCmdMac( u8 *str,  u8 len )
{
	if( len == 3 )
	{
		if( memcmp( ( const char *)str, strCmdMacGet, CMD_MAC_GET_LEN ) == 0 )
		{
			return _rspMac();
			//return TRUE;
		}
	}
	


	return FALSE;


}


#endif

