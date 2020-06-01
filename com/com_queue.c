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



#include "com_queue.h"
 


//#define TEST_COM_QUEUE



/* 队列: 只允许在表的一端(队尾rear)进行插入操作，而在另一端(队头front)进行删除操作的线性表
 * 插入操作简称为入队  删除操作简称为出队   队列具有先进先出的特点
 */

/*=====队列的入队、出队示意图========
 *
 *  出队 ----------------- 入队
 *   <--- a1,a2,a3,...,an <---
 *      -----------------
 *
 *================================*/






//创建队列 capacity : 队列容量
ST_QUEUE *queueInit( U32 capacity, EN_QUEUE_RST *pRst )
{
	ST_QUEUE *q = NULL;


	
	if( capacity == 0 || capacity > QUEUE_LEN_MAX )
	{
		if( pRst != NULL )
			*pRst =  EN_QUEUE_RST_ERR_LEN;
		
		return NULL;
	}

	capacity += 1;

	
    q = (ST_QUEUE *)malloc( sizeof(ST_QUEUE) );
    if( q == NULL )
    {
		comMallocEr();
		
		if( pRst != NULL )
			*pRst =  EN_QUEUE_RST_ERR_MEM; //内存分配失败 	
			
		return NULL;
    }
	
    q->front = 0;
    q->rear  = 0;
    q->len   = capacity;
	
    q->pData = (QUEUE_ElemType * )malloc( capacity * sizeof(QUEUE_ElemType) );
    if( q->pData == NULL)
    {
    	free(q);
		comMallocEr();

		if( pRst != NULL )
			*pRst =  EN_QUEUE_RST_ERR_MEM; //内存分配失败 	 
			
		return NULL;
    }

    return q;
}



//销毁队列
void queueDestroy( ST_QUEUE *pstQueue ) // 执行完后，下一条马上执行 pstQueue = NULL; 
{
	free( pstQueue->pData );
	
    free( pstQueue );  
	
    //pstQueue = NULL;    
}


//清空队列
void queueClear( ST_QUEUE *pstQueue )
{
    pstQueue->front = 0; //队头索引清0
    pstQueue->rear  = 0; //队尾索引清0
}


//判断队列是否为空
int queueIsEmpty( ST_QUEUE *pstQueue )
{
    if( pstQueue->front == pstQueue->rear )  //队头==队尾，说明为空
        return TRUE;

    return FALSE;
}



/*
 *在循环队列中,“队满”和“队空”的条件有可能是相同的，都是front==rear，
 
 *这种情况下，无法区别是“队满”还是“队空”。
 
 *针对这个问题，有3种可能的处理方法：
 
 *（1）另设一个标志以区别是“队满”还是“队空”。（即入队/出队前检查是否“队满”/“队空”）
 
 *（2）设一个计数器，此时甚至还可以省去一个指针。
 
 *（3）少用一个元素空间，即约定队头指针在队尾指针的下一位置时就作为“队满”的标志，
 
 *即“队满”条件为：(PQueue->rear+1)%MAX_SIZE == PQueue->front。
 
 *  【这里采用了第3种处理方法】
 */
//判断队列是否为满
int queueIsFull(  ST_QUEUE *pstQueue )
{
    if( (pstQueue->rear + 1) % pstQueue->len == pstQueue->front )  //队列满
        return TRUE;

    return FALSE;
}


//获得队列长度
int queueLenGet(  ST_QUEUE *pstQueue )
{
    //正常情况下，队列长度为队尾队头指针之差，但如果首尾指针跨容量最大值时，要%
    
    return ( pstQueue->rear - pstQueue->front + pstQueue->len ) % pstQueue->len;
}

//entry queue
//新元素入队 [先进先出原则：在队尾的位置插入] element-要插入元素
EN_QUEUE_RST queueEn( ST_QUEUE *pstQueue, QUEUE_ElemType elem )
{
    if( queueIsFull(pstQueue) == TRUE )
    {
        return EN_QUEUE_RST_ERR_EN_FULL;
    }

    //向队列中添加新元素
    pstQueue->pData[pstQueue->rear] = elem;
    pstQueue->rear = (pstQueue->rear+1) % pstQueue->len; //将rear赋予新的合适的值

    return EN_QUEUE_RST_OK;
}



//新元素出队,同时保存出队的元素 [先进先出原则：在队头的位置删除]
EN_QUEUE_RST queueDe( ST_QUEUE *pstQueue, QUEUE_ElemType *pElem )
{
    //如果队列为空,则返回false
    if( queueIsEmpty(pstQueue) == TRUE )
    {
        return EN_QUEUE_RST_ERR_DE_EMPTY;
    }

	if( pElem != NULL )
    	*pElem = pstQueue->pData[pstQueue->front];       //先进先出
    	
    pstQueue->front = (pstQueue->front+1) % pstQueue->len; //移到下一位置

    return EN_QUEUE_RST_OK;
}


//只获取要出队的元素,不删除它
EN_QUEUE_RST queueGet( ST_QUEUE *pstQueue, QUEUE_ElemType *pElem )
{
    //如果队列为空,则返回false
    if( queueIsEmpty(pstQueue) == TRUE )
    {
        return EN_QUEUE_RST_ERR_DE_EMPTY;
    }

    *pElem = pstQueue->pData[pstQueue->front];       //

    return EN_QUEUE_RST_OK;
}




//遍历队列
void queueTraverse( ST_QUEUE *pstQueue, FunQueueTraverseCB funCB, void *pPara )
{
    int i;

	i = pstQueue->front;           //从头开始遍历
    
    while( i != pstQueue->rear )     //如果没有到达rear位置，就循环
    {
        funCB( & pstQueue->pData[i], pPara );
		
        i = (i+1) % pstQueue->len;              //移到下一位置
    }

}





//========================================================================




#ifdef TEST_COM_QUEUE

#include "mod_uart_debug.h"


static void _queueTravCB( QUEUE_ElemType *pElem, void *pPara )
{
	modUartDebugTxStrU32( " ", *pElem );
}



void queueTest( void )
{
    ST_QUEUE *q;
    u32 i;

	EN_QUEUE_RST rst;

	QUEUE_ElemType elem;
	

	modUartDebugTx0( "queueTest" );

	q = queueInit( 10, &rst );
	if( q == NULL )
	{
		modUartDebugTx0( "x1" );
		return;
	}

    for( i = 1; i < 12; i++ )
    {
        if( queueEn( q, i ) != EN_QUEUE_RST_OK )
    	{
    		modUartDebugTxStrU32( "xEN", i );
    	}
    }

	i = queueLenGet( q );
	modUartDebugTxStrU32( "L=", i );


	if( queueIsEmpty( q ) == TRUE )
	{
		modUartDebugTx0( "x2" );
	}

	if( queueIsFull( q ) == FALSE )
	{
		modUartDebugTx0( "x3" );
	}

	
	queueTraverse(q, _queueTravCB, NULL );

	
	if( queueGet( q, &elem ) == EN_QUEUE_RST_OK )
	{
		modUartDebugTxStrU32( "get=", elem );
	}


	
	if( queueEn( q, elem) != EN_QUEUE_RST_ERR_EN_FULL )
	{
		modUartDebugTx0( "x4" );
	}




	for( i = 0; i < 5; i++ )
	{
		elem = 0;
		if( queueDe( q, &elem) == EN_QUEUE_RST_OK )
		{
			modUartDebugTxStrU32( "de=", elem );
		}
	}

	i = queueLenGet( q );
	modUartDebugTxStrU32( "L=", i );
	queueTraverse(q, _queueTravCB, NULL );





	for( i = 0; i< 8; i++ )
	{
		elem = 11 + i;
		if( queueEn( q, elem) != EN_QUEUE_RST_OK )
		{
			modUartDebugTx0( "x5" );
		}
	}

	i = queueLenGet( q );
	modUartDebugTxStrU32( "L=", i );
	queueTraverse(q, _queueTravCB, NULL );


	if( queueIsFull( q ) == FALSE )
	{
		modUartDebugTx0( "x6" );
	}





	for( i = 0; i < 12; i++ )
	{
		elem = 0;
		if( queueDe( q, &elem) == EN_QUEUE_RST_OK )
		{
			modUartDebugTxStrU32( "de=", elem );
		}
	}

	if( queueIsEmpty( q ) != TRUE )
	{
		modUartDebugTx0( "x7" );
	}

	i = queueLenGet( q );
	modUartDebugTxStrU32( "L=", i );



	for( i = 0; i< 5; i++ )
	{
		elem = 20 + i;
		if( queueEn( q, elem) != EN_QUEUE_RST_OK )
		{
			modUartDebugTx0( "x5" );
		}
	}

	i = queueLenGet( q );
	modUartDebugTxStrU32( "L=", i );
	queueTraverse(q, _queueTravCB, NULL );

	
	modUartDebugTx0( "Test ok" );

	


}


#endif


















#endif

