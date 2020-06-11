/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __COM_TIME_H
#define __COM_TIME_H


#include "com_typedef.h"

typedef struct _ST_DATE_TIME
{
    int  year;     //ʱ�䣺��
    u8  month;     //ʱ�䣺��
    u8  day;       //ʱ�䣺��    
    u8  hour;      //ʱ�䣺ʱ
    u8  minute;    //ʱ�䣺��
    u8  sec;       //ʱ�䣺��    
} ST_DATE_TIME;


u32 dateTime2Sec( ST_DATE_TIME *pstDT );





#ifdef TEST_COM_TIME
	
	void testComTime( void );
	
#endif


#endif

