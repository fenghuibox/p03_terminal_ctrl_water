

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

#include "dbg_uart.h"

#include "zgb_cmd.h"


//#include "f_frame_comm.h"




//===========================================================


u8 macMyGet(u8 *pMac )
{
	return zigbeeMyMacGet( pMac );
}

// 03772D3E00158D00
u8 macToHexStr( u8 *pMac, u8 *pMacHexStr  )
{
	u8 i;

	for( i = 0; i < MAC_ADDR_LEN; i++ )
	{
		decU8toHexStr( pMac[i], pMacHexStr + i * 2 );
	}

	return TRUE;
}



u8 macMyHexStrGet(u8 *pMacHexStr )
{
	u8 pMyMac[MAC_ADDR_LEN];
	
	if( macMyGet( pMyMac ) == FALSE )
		return FALSE;

	return macToHexStr( pMyMac, pMacHexStr );
}





u8 macIsNode( u8 *pMac )
{
	u8 pMyMac[MAC_ADDR_LEN];
	
	if( macIsNodeFF( pMac ) )
		return TRUE;

	if( macMyGet( pMyMac ) == FALSE )
		return FALSE;
	
	return macIsEqual( pMyMac, pMac );
}

//===========================================================


u8 macIsOk( u8 *pMac )
{
	return macIsNode(  pMac );
}





