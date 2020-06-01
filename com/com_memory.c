
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
#include "com_memory.h"


void comMallocEr( void )
{
	while(1);
}

void* comMemcpy(void *dest, void *src, u32 n)
{
	u8 *ret = (u8 *)dest;
	u8 *d   = ret;
	u8 *s   = (u8 *)src;

	while (n--)
	{
		*d++ = *s++;
	}	

	return ret;

}  




int comMemcmp(const u8 *pBuf1, const u8 *pBuf2, u32 cnt)
{
	const u8 *p1, *p2;

	#if 0
	
	if(cnt < 1)
		return COM_MEM_PARA_ERROR;

	if(pBuf1 == NULL)
		return COM_MEM_PARA_ERROR;
	
	if(pBuf2 == NULL)
		return COM_MEM_PARA_ERROR;
	
	#endif

	p1 = pBuf1;
	p2 = pBuf2;
	
	while( *p1++ == *p2++ )
	{
		if( --cnt == 0)
			break;
	}

	p1--;
	p2--;
	
	return ( *p1 - *p2);

	
}


u8 *comMemset( u8 *pBuf, u8 ch, u32 n)
{
	u8	*pTemp;
	int i;
	
	pTemp = pBuf;
	
	for( i = n; i != 0; i-- )
	{
		*pTemp++  = ch;					
	}

	return pBuf;
}







