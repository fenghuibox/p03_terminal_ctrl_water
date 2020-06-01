/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#include "com_typedef.h"



/*
返回值  > -1 : ch 在 pBuf 中 第 n 次 出现时的 index
返回值  = -1 : 没有找到

例: pBuf = 11 01 05 00 05 03
    bufChNposGet( pBuf, 6, 5, 2 ) = 4
*/
int bufChNposGet( u8 *pBuf, u16 bufLen, u8 ch, u16 n )
{
	u16 nCnt;
	u8 *pTemp;
	u8 *pEnd;


	if( pBuf == NULL )
		return -1;

	if( bufLen < n )
		return -1;

	if( n == 0 )
		return -1;
	
    nCnt = 0;
	pEnd = pBuf + bufLen;
	
	
    for(  pTemp = pBuf; pTemp < pEnd; pTemp++ )
    {
        if( *pTemp == ch ) 
		{
			++nCnt;
			
            if( nCnt == n ) 
            {
				return pTemp - pBuf;
            }
       }
    }
    
    return -1;
}


/*
返回值  > -1 : ch 在 pBuf 中 第 1 次 出现时的 index
返回值  = -1 : 没有找到

例: pBuf = 11 01 05 00 05 03
    bufChIndexGet( pBuf, 6, 5 ) = 2
*/
int bufChIndexGet( u8 *pBuf, u16 bufLen, u8 ch )
{
	u8 *pTemp;
	u8 *pEnd;

	if( pBuf == NULL )
		return -1;
	
	pEnd = pBuf + bufLen;
	
    for(  pTemp = pBuf; pTemp < pEnd; pTemp++ )
    {
        if( *pTemp == ch ) 
		{
			return pTemp - pBuf;
       }
    }
    
    return -1;
}



/*---------------------------------------------------
pBuf = 12345678  len  = 8

pSub = 45  subLen = 2   return : pBuf + 3
pSub = AB  subLen = 2   return : NULL
------------------------------------------------------*/
u8 *bufbuf( u8 *pBuf, u16 len, u8 *pSub, u16 subLen )
{
	u8 *pCp, *pEnd, *pSubEnd, *s1, *s2;

	if( len < subLen )
		return NULL;

	pCp  = pBuf;
	pEnd = pBuf + len - subLen;

	pSubEnd = pSub + subLen - 1;

    while ( pCp <= pEnd )
    {
        s1 = pCp;
        s2 = pSub;

        while ( s2 <= pSubEnd   )
        {
        	if( *s1 != *s2 )
        	{
				break;
        	}
			else
			{
	            s1++;
				s2++; // 相等继续找
			}
        }

        if ( s2 > pSubEnd ) // 找到了
        {
            return pCp;
        }

        pCp++;
    }

    return NULL;
}


