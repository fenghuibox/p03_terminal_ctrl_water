/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/

 #if 1
 

 
#include "com_typedef.h"
#include "com_memory.h"



#include "com_queue.h"
 


//#define TEST_COM_QUEUE



/* ����: ֻ�����ڱ��һ��(��βrear)���в��������������һ��(��ͷfront)����ɾ�����������Ա�
 * ����������Ϊ���  ɾ���������Ϊ����   ���о����Ƚ��ȳ����ص�
 */

/*=====���е���ӡ�����ʾ��ͼ========
 *
 *  ���� ----------------- ���
 *   <--- a1,a2,a3,...,an <---
 *      -----------------
 *
 *================================*/






//�������� capacity : ��������
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
			*pRst =  EN_QUEUE_RST_ERR_MEM; //�ڴ����ʧ�� 	
			
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
			*pRst =  EN_QUEUE_RST_ERR_MEM; //�ڴ����ʧ�� 	 
			
		return NULL;
    }

    return q;
}



//���ٶ���
void queueDestroy( ST_QUEUE *pstQueue ) // ִ�������һ������ִ�� pstQueue = NULL; 
{
	free( pstQueue->pData );
	
    free( pstQueue );  
	
    //pstQueue = NULL;    
}


//��ն���
void queueClear( ST_QUEUE *pstQueue )
{
    pstQueue->front = 0; //��ͷ������0
    pstQueue->rear  = 0; //��β������0
}


//�ж϶����Ƿ�Ϊ��
int queueIsEmpty( ST_QUEUE *pstQueue )
{
    if( pstQueue->front == pstQueue->rear )  //��ͷ==��β��˵��Ϊ��
        return TRUE;

    return FALSE;
}



/*
 *��ѭ��������,���������͡��ӿա��������п�������ͬ�ģ�����front==rear��
 
 *��������£��޷������ǡ����������ǡ��ӿա���
 
 *���������⣬��3�ֿ��ܵĴ�������
 
 *��1������һ����־�������ǡ����������ǡ��ӿա����������/����ǰ����Ƿ񡰶�����/���ӿա���
 
 *��2����һ������������ʱ����������ʡȥһ��ָ�롣
 
 *��3������һ��Ԫ�ؿռ䣬��Լ����ͷָ���ڶ�βָ�����һλ��ʱ����Ϊ���������ı�־��
 
 *��������������Ϊ��(PQueue->rear+1)%MAX_SIZE == PQueue->front��
 
 *  ����������˵�3�ִ�������
 */
//�ж϶����Ƿ�Ϊ��
int queueIsFull(  ST_QUEUE *pstQueue )
{
    if( (pstQueue->rear + 1) % pstQueue->len == pstQueue->front )  //������
        return TRUE;

    return FALSE;
}


//��ö��г���
int queueLenGet(  ST_QUEUE *pstQueue )
{
    //��������£����г���Ϊ��β��ͷָ��֮��������βָ����������ֵʱ��Ҫ%
    
    return ( pstQueue->rear - pstQueue->front + pstQueue->len ) % pstQueue->len;
}

//entry queue
//��Ԫ����� [�Ƚ��ȳ�ԭ���ڶ�β��λ�ò���] element-Ҫ����Ԫ��
EN_QUEUE_RST queueEn( ST_QUEUE *pstQueue, QUEUE_ElemType elem )
{
    if( queueIsFull(pstQueue) == TRUE )
    {
        return EN_QUEUE_RST_ERR_EN_FULL;
    }

    //������������Ԫ��
    pstQueue->pData[pstQueue->rear] = elem;
    pstQueue->rear = (pstQueue->rear+1) % pstQueue->len; //��rear�����µĺ��ʵ�ֵ

    return EN_QUEUE_RST_OK;
}



//��Ԫ�س���,ͬʱ������ӵ�Ԫ�� [�Ƚ��ȳ�ԭ���ڶ�ͷ��λ��ɾ��]
EN_QUEUE_RST queueDe( ST_QUEUE *pstQueue, QUEUE_ElemType *pElem )
{
    //�������Ϊ��,�򷵻�false
    if( queueIsEmpty(pstQueue) == TRUE )
    {
        return EN_QUEUE_RST_ERR_DE_EMPTY;
    }

	if( pElem != NULL )
    	*pElem = pstQueue->pData[pstQueue->front];       //�Ƚ��ȳ�
    	
    pstQueue->front = (pstQueue->front+1) % pstQueue->len; //�Ƶ���һλ��

    return EN_QUEUE_RST_OK;
}


//ֻ��ȡҪ���ӵ�Ԫ��,��ɾ����
EN_QUEUE_RST queueGet( ST_QUEUE *pstQueue, QUEUE_ElemType *pElem )
{
    //�������Ϊ��,�򷵻�false
    if( queueIsEmpty(pstQueue) == TRUE )
    {
        return EN_QUEUE_RST_ERR_DE_EMPTY;
    }

    *pElem = pstQueue->pData[pstQueue->front];       //

    return EN_QUEUE_RST_OK;
}




//��������
void queueTraverse( ST_QUEUE *pstQueue, FunQueueTraverseCB funCB, void *pPara )
{
    int i;

	i = pstQueue->front;           //��ͷ��ʼ����
    
    while( i != pstQueue->rear )     //���û�е���rearλ�ã���ѭ��
    {
        funCB( & pstQueue->pData[i], pPara );
		
        i = (i+1) % pstQueue->len;              //�Ƶ���һλ��
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

