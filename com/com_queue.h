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

#ifndef __COM_QUEUE_H
#define __COM_QUEUE_H


#include "com_typedef.h"



typedef u8  QUEUE_ElemType; /* ElemType���͸���ʵ������������������ΪU32 */







#define QUEUE_LEN_MAX (512)


typedef enum 
{
	EN_QUEUE_RST_NOT_DEF = 0,
		
	EN_QUEUE_RST_OK = 1, 
	
	EN_QUEUE_RST_ERR_MEM,       // �ڴ治��
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



//���ٶ���
extern void queueDestroy( ST_QUEUE *pstQueue );// ִ�������һ������ִ�� pstQueue = NULL; 


//��ն���
extern void queueClear( ST_QUEUE *pstQueue );



//�ж϶����Ƿ�Ϊ��
extern int queueIsEmpty( ST_QUEUE *pstQueue );




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
extern int queueIsFull(  ST_QUEUE *pstQueue );



//��ö��г���
extern int queueLenGet(  ST_QUEUE *pstQueue );



//entry queue
//��Ԫ����� [�Ƚ��ȳ�ԭ���ڶ�β��λ�ò���] element-Ҫ����Ԫ��
extern EN_QUEUE_RST queueEn( ST_QUEUE *pstQueue, QUEUE_ElemType elem );



//��Ԫ�س���,ͬʱ������ӵ�Ԫ�� [�Ƚ��ȳ�ԭ���ڶ�ͷ��λ��ɾ��]
extern EN_QUEUE_RST queueDe( ST_QUEUE *pstQueue, QUEUE_ElemType *pElem );



//ֻ��ȡҪ���ӵ�Ԫ��,��ɾ����
extern EN_QUEUE_RST queueGet( ST_QUEUE *pstQueue, QUEUE_ElemType *pElem );




//��������
extern void queueTraverse( ST_QUEUE *pstQueue, FunQueueTraverseCB funCB, void *pPara );





//========================================================================



extern void queueTest( void );












#endif

#endif

