/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __COM_SQLIST_H
#define __COM_SQLIST_H


#include "com_typedef.h"

#define  SQ_LIST_E_ADD_CNT   (3)

#define  SQ_LIST_OK          (1)
#define  SQ_LIST_NO_ELEM     (0) // ����Ԫ��ʱ ����û�����Ԫ��

#define  SQ_LIST_ERR_MEM    (-1) // �ڴ����ʧ��
#define  SQ_LIST_ERR_INDEX  (-2)
#define  SQ_LIST_ERR_EMPTY  (-3) // ɾ��ʱ��Ϊ��
#define  SQ_LIST_ERR_PARA   (-4) // ��������



typedef U32 SQ_LIST_ElemType; /* ElemType���͸���ʵ������������������ΪU32 */


typedef struct 
{  
	SQ_LIST_ElemType *pElem;  // ����ռ����ַ       
	int len;                  // ��¼��ǰ������    
	int size;                 // �����ģ 	
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






/*----------��˳����в���ֵ�� -------------------
	i: < 1      --> i = 1      first
    i: > L.len	--> i = L.len  end
    i: 1 -- L.len 
---------------------------------------------------*/
extern int sqListInsert(SqList *L ,int i, SQ_LIST_ElemType e);
extern int sqListAppend(SqList *L, SQ_LIST_ElemType e);


// ok: return 1 -- L.len
// er:
extern int sqListLocate(SqList *L, SQ_LIST_ElemType e );



/*----------��˳�����deleteֵ�� -------------------
	i: < 1      --> i = 1      first
    i: > L.len	--> i = L.len  end
    i: 1 -- L.len 
---------------------------------------------------*/
extern int sqListDelete(SqList *L, int i, SQ_LIST_ElemType *e);
extern int sqListDeleteTail(SqList *L, SQ_LIST_ElemType *e);// del ���һ��ֵ






extern void sqListClear(SqList *L);


extern void sqListDestroy( SqList *L );


extern int sqListIsEmpty( SqList *L);



extern int sqListLen(SqList *L);   



extern int sqListTraverse(SqList *L, FunSQListTraverseCB funCB );


extern int sqListTest( void );



#endif

