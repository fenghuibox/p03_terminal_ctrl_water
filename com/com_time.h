/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __COM_TIME_H
#define __COM_TIME_H


#include "com_typedef.h"

typedef struct _ST_DATE_TIME
{
    int  year;     //时间：年
    u8  month;     //时间：月
    u8  day;       //时间：日    
    u8  hour;      //时间：时
    u8  minute;    //时间：分
    u8  sec;       //时间：秒    
} ST_DATE_TIME;


u32 dateTime2Sec( ST_DATE_TIME *pstDT );





#ifdef TEST_COM_TIME
	
	void testComTime( void );
	
#endif


#endif

