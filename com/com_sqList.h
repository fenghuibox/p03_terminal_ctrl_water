/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __COM_SQLIST_H
#define __COM_SQLIST_H


#include "com_typedef.h"

#define  SQ_LIST_E_ADD_CNT   (3)

#define  SQ_LIST_OK          (1)
#define  SQ_LIST_NO_ELEM     (0) // 查找元素时 表中没有这个元素

#define  SQ_LIST_ERR_MEM    (-1) // 内存分配失败
#define  SQ_LIST_ERR_INDEX  (-2)
#define  SQ_LIST_ERR_EMPTY  (-3) // 删除时表为空
#define  SQ_LIST_ERR_PARA   (-4) // 参数错误



typedef U32 SQ_LIST_ElemType; /* ElemType类型根据实际情况而定，这里假设为U32 */


typedef struct 
{  
	SQ_LIST_ElemType *pElem;  // 储存空间基地址       
	int len;                  // 记录当前链表长度    
	int size;                 // 链表规模 	
} SqList;

typedef  void ( *FunSQListTraverseCB)( SQ_LIST_ElemType *pElem ); 


//=========================================================================


extern int sqListInit( SqList *L, int elemCnt);


/*---------------------------------------------------
	i: < 1      --> i = 1      first
    i: > L.len	--> i = L.len  end
    i: 1 -- L.len 
---------------------------------------------------*/
extern int  sqListGetEle(SqList *L, int i, SQ_LIST_ElemType *e);






/*----------往顺序表中插入值。 -------------------
	i: < 1      --> i = 1      first
    i: > L.len	--> i = L.len  end
    i: 1 -- L.len 
---------------------------------------------------*/
extern int sqListInsert(SqList *L ,int i, SQ_LIST_ElemType e);
extern int sqListAppend(SqList *L, SQ_LIST_ElemType e);


// ok: return 1 -- L.len
// er:
extern int sqListLocate(SqList *L, SQ_LIST_ElemType e );



/*----------往顺序表中delete值。 -------------------
	i: < 1      --> i = 1      first
    i: > L.len	--> i = L.len  end
    i: 1 -- L.len 
---------------------------------------------------*/
extern int sqListDelete(SqList *L, int i, SQ_LIST_ElemType *e);
extern int sqListDeleteTail(SqList *L, SQ_LIST_ElemType *e);// del 最后一个值






extern void sqListClear(SqList *L);


extern void sqListDestroy( SqList *L );


extern int sqListIsEmpty( SqList *L);



extern int sqListLen(SqList *L);   



extern int sqListTraverse(SqList *L, FunSQListTraverseCB funCB );


extern int sqListTest( void );



#endif

