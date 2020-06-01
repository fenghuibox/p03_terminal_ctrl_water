

/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#include "com_mac.h"




//===========================================================
void macCopy( u8 *dstMac, u8 *srcMac )
{
	memcpy(dstMac,srcMac,MAC_ADDR_LEN);
}



u8 macIsEqual( u8* pMac1, u8* pMac2 )
{
	if( memcmp(pMac1, pMac2, MAC_ADDR_LEN) == 0 )
		return TRUE;

	return FALSE;
}


int macIsGateway00( u8 *pMac )
{
	int i;
	u8 *p;

	for( i = MAC_ADDR_LEN, p = pMac; i != 0; i--, p++ )
	{
		if( *p != 0 )
			return FALSE;
	}

	return TRUE;
}


int macIsNodeFF( u8 *pMac )
{
	int i;
	u8 *p;

	for( i = MAC_ADDR_LEN, p = pMac; i != 0; i--, p++ )
	{
		if( *p != 0xFF )
			return FALSE;
	}

	return TRUE;
}

/*
u8 macIsBroadcast(u8 *pMacAddr)
{
	int i;
	u8 *p;

	for( i = MAC_ADDR_LEN, p = pMacAddr; i != 0; i--, p++ )
	{
		if( *p != 0xFF )
			return FALSE;
	}

	return TRUE;

}

*/




//===========================================================
void macSetToGateway00( u8 *pMac )
{
	memset( pMac, 0x00, MAC_ADDR_LEN );// 
}




void macSetToNodeFF( u8 *pMac )
{
	memset( pMac, 0xFF, MAC_ADDR_LEN );// 
}



//===========================================================







