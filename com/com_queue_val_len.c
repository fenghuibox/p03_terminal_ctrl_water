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
 

 
#include "com_typedef.h"
#include "com_memory.h"

 
#include "com_queue_val_len.h"
 
//#define TEST_COM_QUEUE_VAL_LEN


/*

https://www.jb51.net/article/101348.htm


循环队列, 元素变长(Element Variable length)

元素 = LEN + DATA
*/


 


 

//---------------------------------------------------------------------
// 初始化队列
//---------------------------------------------------------------------
// queueLen : 队列元素总长度 (字节)
//--------------------------------------------------------------------- 
QURUE_V *initQqueueV( u32 queueLen )
{
	QURUE_V *pQV;
	void *pMem;
	u32 len;

	len = queueLen +  sizeof(QURUE_V) + 3;
	
	pMem = malloc( len ); 
	if(pMem == NULL)
	{
		comMallocEr();
		return NULL;
	}

	memset(pMem, 0, len );
	
	pQV =  ( QURUE_V * )pMem;
	
	pQV->pArr  = ((u8 *)pMem) +  sizeof(QURUE_V) ;
	pQV->front = 0;
	pQV->rear  = 0;
	pQV->len   = queueLen;
	
	return pQV;
}







//---------------------------------------------------------------------
// 销毁队列
//---------------------------------------------------------------------
// queueLen : 队列元素总长度 (字节)
//---------------------------------------------------------------------  
u8 destroyQueueV( QURUE_V *pQV )
{
	free( pQV );
	return TRUE;
}



//---------------------------------------------------------------------
// 队列是否为空
//---------------------------------------------------------------------
// pQV : 
//---------------------------------------------------------------------
U8 IsEmptyQueueV( QURUE_V *pQV )
{
	return pQV->front == pQV->rear;
}


//---------------------------------------------------------------------
// 清除队列中的元素
//---------------------------------------------------------------------
// pQV : 
//---------------------------------------------------------------------
void clearQueueV( QURUE_V *pQV )
{
	pQV->front = 0;
	pQV->rear  = 0;
}


// 队列已使用的长度
u32 getUseLenQueueV( QURUE_V *pQV )
{
	// if( pQV->front == 0 &&  pQV->rear == 0 )
	//	return pQV->len;
	
	/* 若front > rear */
	if( pQV->front > pQV->rear )
	{
		return ( pQV->rear + pQV->len - pQV->front);
	}
	else
	{
		return ( pQV->rear - pQV->front );
	}
}

 
// 队列未使用的长度
u32 getUnuseLenQueueV( QURUE_V *pQV )
{
	return pQV->len - getUseLenQueueV( pQV );
}
 

//---------------------------------------------------------------------
// 入队   插入队尾
//---------------------------------------------------------------------
// pInData : 指向要入队的数据
// len     : 数据的长度   len = len(pData)
//---------------------------------------------------------------------
u8 enQueueV( QURUE_V *pQV, u8 *pInData, u32 len )
{
	u32 i; 
	u8 *pTemp;
	
	if( getUnuseLenQueueV( pQV ) < len + 1 )
		return FALSE;

	// 1 入队 数据的长度 len 
	pQV->pArr[pQV->rear] = len;
	pQV->rear = (pQV->rear + 1) % pQV->len;

	// 2 入队 数据 pData
	pTemp = pInData;
	for( i = 0; i < len; i++ )
	{
		pQV->pArr[pQV->rear] = *pTemp;

		pTemp++;
		
		pQV->rear = (pQV->rear + 1) % pQV->len;
	}

	return TRUE;
  
}


 
//---------------------------------------------------------------------
// 出队    返回队头元素
//---------------------------------------------------------------------
// pOutData  : 指向出队的数据
// pLen 	  : 指向出队的数据的长度   *pLen = len(pOutData)
//---------------------------------------------------------------------
int deQueueV( QURUE_V *pQV, u8 *pOutData, u32 *pLen )
{
	u32 i; 
	u8 *pTemp;
	u32 len;

	/* 判断队列是否为空 */
	if(pQV->front == pQV->rear)
	return FALSE;

	
	// 1 出队 数据的长度 len 
	len = pQV->pArr[pQV->front];
	pQV->front = (pQV->front + 1 ) % pQV->len;
	
	*pLen = len;


	// 2 出队 数据 pData
	pTemp = pOutData;
	for( i = 0; i < len; i++ )
	{

		*pTemp = pQV->pArr[pQV->front];
		
		pTemp++;
		
		pQV->front = (pQV->front + 1 ) % pQV->len;
	}


	return TRUE;
}
 
 

 
#ifdef TEST_COM_QUEUE_VAL_LEN


#include "mod_uart_debug.h"


 
static void _testEnQueueV( QURUE_V *pQV, int cnt)
{

	u8 pData1[] = { 'A', 'B'};
	u8 data1Len = 2;
	
	u8 pData2[] = { 'B', 'B', 0, 'B'};
	u8 data2Len = 4;
	
	u8 pData3[] = { 'C', 'C', '1', '2', '3'};
	u8 data3Len = 5;
	
	u8 pData4[] = { 'D'};
	u8 data4Len = 1;
	

	modUartDebugTx0("\r\nenQueue");

	
	if( enQueueV(pQV, pData1, data1Len ) == FALSE )
	{
		modUartDebugTx0("\r\ntestQueueV x2");
		return;
	}

	if( cnt == 1 )
		return;
	
	if( enQueueV(pQV, pData2, data2Len ) == FALSE )
	{
		modUartDebugTx0("\r\ntestQueueV x3");
		return;
	}
	
	if( cnt == 2 )
		return;


	if( enQueueV(pQV, pData3, data3Len ) == FALSE )
	{
		modUartDebugTx0("\r\ntestQueueV x4");
		return;
	}

	if( cnt == 3 )
		return;


	if( enQueueV(pQV, pData4, data4Len ) == FALSE )
	{
		modUartDebugTx0("\r\ntestQueueV x5");
		return;
	}
	
	if( cnt == 4 )
		return;



	return;



}


static void _testDeQueueV( QURUE_V *pQV, int cnt )
{

	u8 pDataOut[10] = {0};
	u32 dataOutLen;
	int i;


	//----------------------------------------------------------
	modUartDebugTx0("\r\ndeQueue");

	for(i = cnt; i != 0; i-- )
	{
		dataOutLen = 0;
		
		if( deQueueV(pQV, pDataOut, &dataOutLen ) == FALSE )
		{
			modUartDebugTxStrU32("\r\nt_testDeQueueV_xx i=", i);
			return;
		}
		else
		{
			modUartDebugTxU8buf( pDataOut, dataOutLen );
		}
	}

	



}


 
void testQueueV( void )
{
	QURUE_V *pQV;


	pQV = initQqueueV( 32 );
	if( pQV == NULL )
	{
		modUartDebugTx0("\r\ntestQueueV x1");
		return;
	}

	
	_testEnQueueV(pQV, 4);

	_testDeQueueV(pQV, 2);

	
	_testEnQueueV(pQV, 4);

	_testDeQueueV(pQV, 3);

	_testEnQueueV(pQV, 4);

	_testDeQueueV(pQV, 10);

	_testEnQueueV(pQV, 4);
	_testEnQueueV(pQV, 4);
	_testEnQueueV(pQV, 4);
	_testEnQueueV(pQV, 4);

	destroyQueueV( pQV );
	
	

}

#endif




#endif




