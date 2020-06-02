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

#ifndef __COM_QUEUE_H
#define __COM_QUEUE_H


#include "com_typedef.h"



typedef u8  QUEUE_ElemType; /* ElemType类型根据实际情况而定，这里假设为U32 */







#define QUEUE_LEN_MAX (512)


typedef enum 
{
	EN_QUEUE_RST_NOT_DEF = 0,
		
	EN_QUEUE_RST_OK = 1, 
	
	EN_QUEUE_RST_ERR_MEM,       // 内存不够
	EN_QUEUE_RST_ERR_LEN,       //
	EN_QUEUE_RST_ERR_EN_FULL,  
	EN_QUEUE_RST_ERR_DE_EMPTY,  



}EN_QUEUE_RST; //





typedef struct SeqQueue
{
    int front;
    int rear;
	int len;
    QUEUE_ElemType *pData;
}ST_QUEUE;




typedef  void ( *FunQueueTraverseCB)( QUEUE_ElemType *pElem, void *pPara ); 





//=================================================================


extern ST_QUEUE *queueInit( U32 capacity, EN_QUEUE_RST *pRst );



//销毁队列
extern void queueDestroy( ST_QUEUE *pstQueue );// 执行完后，下一条马上执行 pstQueue = NULL; 


//清空队列
extern void queueClear( ST_QUEUE *pstQueue );



//判断队列是否为空
extern int queueIsEmpty( ST_QUEUE *pstQueue );




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
extern int queueIsFull(  ST_QUEUE *pstQueue );



//获得队列长度
extern int queueLenGet(  ST_QUEUE *pstQueue );



//entry queue
//新元素入队 [先进先出原则：在队尾的位置插入] element-要插入元素
extern EN_QUEUE_RST queueEn( ST_QUEUE *pstQueue, QUEUE_ElemType elem );



//新元素出队,同时保存出队的元素 [先进先出原则：在队头的位置删除]
extern EN_QUEUE_RST queueDe( ST_QUEUE *pstQueue, QUEUE_ElemType *pElem );



//只获取要出队的元素,不删除它
extern EN_QUEUE_RST queueGet( ST_QUEUE *pstQueue, QUEUE_ElemType *pElem );




//遍历队列
extern void queueTraverse( ST_QUEUE *pstQueue, FunQueueTraverseCB funCB, void *pPara );





//========================================================================



extern void queueTest( void );












#endif

#endif

