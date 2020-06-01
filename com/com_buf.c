/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#include "com_typedef.h"



/*
����ֵ  > -1 : ch �� pBuf �� �� n �� ����ʱ�� index
����ֵ  = -1 : û���ҵ�

��: pBuf = 11 01 05 00 05 03
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
����ֵ  > -1 : ch �� pBuf �� �� 1 �� ����ʱ�� index
����ֵ  = -1 : û���ҵ�

��: pBuf = 11 01 05 00 05 03
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
				s2++; // ��ȼ�����
			}
        }

        if ( s2 > pSubEnd ) // �ҵ���
        {
            return pCp;
        }

        pCp++;
    }

    return NULL;
}


