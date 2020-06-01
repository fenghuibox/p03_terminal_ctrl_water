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

#include "com_sqList.h"


//#define TEST_COM_SQLIST

int sqListInit( SqList *L, int elemCnt)
{	
	u32 len;

	len =  elemCnt * sizeof( SQ_LIST_ElemType ) ;
	
	L->pElem =(SQ_LIST_ElemType *) malloc ( len );
	if (L->pElem == NULL)      
	{	  
		//printf("顺序表初始化失败");	
		comMallocEr();
		return SQ_LIST_ERR_MEM; //内存分配失败 	 
	}
	
	L->len  = 0;	 
	L->size = elemCnt;  
	
	return SQ_LIST_OK;
}

/*---------------------------------------------------
	i: < 1      --> i = 1      first
    i: > L.len	--> i = L.len  end
    i: 1 -- L.len 
---------------------------------------------------*/
int  sqListGetEle(SqList *L, int i, SQ_LIST_ElemType *e)
{	    
	if ( i < 1 )
	{
		i = 1;
	}
	else if( i > L->len )
	{
		i = L->len;
	}
		
	*e = L->pElem[ i - 1 ];
	
	return SQ_LIST_OK; 
}  


static int _sqListOnAddElem( SqList *L )
{
	void * pVoid;   
	
	if( L->len >= L->size )
	{		
		// 第一个参数是线性表节点地址 第二个参数是在开辟多大的内存 。		
		pVoid = ( void *) realloc ( L->pElem, (L->size + SQ_LIST_E_ADD_CNT) * sizeof( SQ_LIST_ElemType ) ); 
		if( NULL == pVoid ) 
		{	  
			comMallocEr();
			//printf("顺序表初始化失败");	   
			return SQ_LIST_ERR_MEM; //内存分配失败 	 
		}
		
		L->pElem  = (SQ_LIST_ElemType *)pVoid;
		L->size  += SQ_LIST_E_ADD_CNT;
	}

	return SQ_LIST_OK; 
}



/*----------往顺序表中插入值。 -------------------
	i: < 1      --> i = 1      first
    i: > L.len	--> i = L.len  end
    i: 1 -- L.len 
---------------------------------------------------*/
int sqListInsert(SqList *L ,int i, SQ_LIST_ElemType e) 
{    
	SQ_LIST_ElemType *p,*q;
	int rst;
	
	rst = _sqListOnAddElem(L);
	if( rst != SQ_LIST_OK )
		return rst;
	
	q = & L->pElem[ i - 1 ];
	p = & L->pElem[ L->len ];
	
	for ( ; p >= q; p-- ) //元素储存位置挨个减一 ,插入第一个数不进入这个循环。     
	{    	
		*(p+1) = *p; 	
	}	
	
	*q = e;
	
	L->len++;
	
	return SQ_LIST_OK;

} 


int sqListAppend(SqList *L, SQ_LIST_ElemType e) 
{    
	int rst;
	
	rst = _sqListOnAddElem(L);
	if( rst != SQ_LIST_OK )
		return rst;
	
	L->pElem[ L->len ] = e;
		
	L->len++;
	
	return SQ_LIST_OK;
} 


// ok: return 1 -- L.len
// er:
int sqListLocate(SqList *L, SQ_LIST_ElemType e ) 
{   
	int i = 1;
	
	for( i = 0;  i < L->len; i++ )
	{
		if( L->pElem[i] == e )
			return i + 1;
	}  
	
	return SQ_LIST_NO_ELEM;
}  



/*----------往顺序表中delete值。 -------------------
	i: < 1      --> i = 1      first
    i: > L.len	--> i = L.len  end
    i: 1 -- L.len 
---------------------------------------------------*/
int sqListDelete(SqList *L, int i, SQ_LIST_ElemType *e)
{
	SQ_LIST_ElemType *p, *q;

	if( L->len < 1)
	{
		return SQ_LIST_ERR_EMPTY;
	}
	
	if ( i < 1 )
	{
		i = 1;
	}
	else if( i > L->len )
	{
		i = L->len;
	}

	
	p = &L->pElem [i-1]; // p-> del
	
	*e = *p;
	
	q = L->pElem + L->len - 1; // q-> end
	
	for( ; p < q; ++p )	 
	{	 	 
		*p= * ( p + 1 );
	}
	
	L->len--;
	
	return SQ_LIST_OK;
} 

// del 最后一个值
int sqListDeleteTail(SqList *L, SQ_LIST_ElemType *e)
{
	if( L->len < 1)
	{
		return SQ_LIST_ERR_EMPTY;
	}

	*e = L->pElem[ L->len - 1];
	
	L->len--;
	
	return SQ_LIST_OK;
} 




void sqListClear(SqList *L)
{	
	L->len = 0;
} 

void sqListDestroy( SqList *L )
{	
	free( L->pElem );	
	
	L->pElem = NULL;
	L->len   = 0;
	L->size  = 0;
}



int sqListIsEmpty( SqList *L) 
{	 
	return L->len == 0 ? 1 : 0 ; 	
}



int sqListLen(SqList *L)
{    
	return L->len ;     
}   



int sqListTraverse(SqList *L, FunSQListTraverseCB funCB )
{ 
	int i;

	if(funCB == NULL )
		return SQ_LIST_ERR_PARA;
	
	for (i = 0; i < L->len; i++ )
	{
		funCB( L->pElem + i );
	}

	return SQ_LIST_OK;
}



#ifdef TEST_COM_SQLIST

#include "mod_uart_debug.h"


static void _testSqListTraverseCB( SQ_LIST_ElemType *pElem)
{
	modUartDebugTxU32( (u32)(*pElem) );
}



int sqListTest( void )
{	
	SqList L;
	SQ_LIST_ElemType  e;
	int i;
	int rst;

	//void *pVoid;
	
	if( sqListInit(&L, 4) != SQ_LIST_OK )
	{
		return FALSE;
	}

	
	for(i=1;i<5;i++)
	{
		rst = sqListInsert( &L, i, 10+i ); 
	}
	rst =  sqListTraverse(&L, _testSqListTraverseCB);

	for(i=1;i<5;i++)
	{
		rst = sqListAppend( &L, 20 + i ); 
	}

	rst =  sqListTraverse(&L, _testSqListTraverseCB);

	i = sqListLocate( &L, 22);
	modUartDebugTxU32( i );

	
	rst = sqListDelete( &L, 2, &e);
	rst =  sqListTraverse(&L, _testSqListTraverseCB);
	
	rst = sqListDelete( &L, 0, &e);
	rst =  sqListTraverse(&L, _testSqListTraverseCB);	

	rst = sqListDelete( &L, 100, &e);
	rst =  sqListTraverse(&L, _testSqListTraverseCB);	
	
	rst = sqListDeleteTail( &L,  &e);
	rst =  sqListTraverse(&L, _testSqListTraverseCB);
	

	rst = sqListInsert( &L, 3, 30 ); 
	rst =  sqListTraverse(&L, _testSqListTraverseCB);


	for(i=1;i<50;i++)
	{
		rst = sqListAppend( &L, 50 + i ); 
	}

	sqListTraverse(&L, _testSqListTraverseCB);

	sqListGetEle(&L, 0, &e);
	modUartDebugTxU32( (u32)e );
	
	sqListGetEle(&L, 1000, &e);
	modUartDebugTxU32( (u32)e );
	
	sqListGetEle(&L, 3, &e);
	modUartDebugTxU32( (u32)e );
	
	if(rst )
		return rst;

	/*  

	comMallocEr();

	pVoid = ( void *) realloc ( L.pElem, (L.size + SQ_LIST_E_ADD_CNT) * sizeof( SQ_LIST_ElemType ) ); 
	if( pVoid == NULL )
		modUartDebugTxU32( 0 );
	else
		modUartDebugTxU32( (u32)(pVoid) );


	pVoid = ( void *) malloc ( (L.size + SQ_LIST_E_ADD_CNT) * sizeof( SQ_LIST_ElemType ) ); 
	if( pVoid == NULL )
		modUartDebugTxU32( 0 );
	else
		modUartDebugTxU32( (u32)(pVoid) );	

		*/

	
	return TRUE;
}

#endif

