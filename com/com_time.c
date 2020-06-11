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

#include "com_time.h"





u32 dateTime2Sec( ST_DATE_TIME *pstDT )
{
	struct tm stTM = {0};
	//u32 sec;
	
	stTM.tm_year = pstDT->year  - 1900;
	stTM.tm_mon  = pstDT->month - 1;
	stTM.tm_mday = pstDT->day;
	stTM.tm_hour = pstDT->hour;
	stTM.tm_min  = pstDT->minute;
	stTM.tm_sec  = pstDT->sec;

	return mktime( &stTM );
	//return sec;
}





#ifdef TEST_COM_TIME

static void testTimeCB( void )
{
	#define TYPE_CNT (15)
	
	static u8 _cnt = 0;
	time_t timep;
	
	struct tm stTM;
	
	memset( &stTM, 0, sizeof(struct tm));
	
	if( _cnt % TYPE_CNT == 0 )
	{
		stTM.tm_year = 1910;
		stTM.tm_mon  = 0;
		stTM.tm_mday = 1;
		stTM.tm_hour = 0;
		stTM.tm_min  = 0;
		stTM.tm_sec  = 5;  // -1893455995
	}		
	else if( _cnt % TYPE_CNT == 1 )
	{
		stTM.tm_year = 2020;
		stTM.tm_mon  = 0;
		stTM.tm_mday = 1;
		stTM.tm_hour = 0;
		stTM.tm_min  = 0;
		stTM.tm_sec  = 0;  // 1577836800
	}		
	else if( _cnt % TYPE_CNT == 2 )
	{
		stTM.tm_year = 2020;
		stTM.tm_mon  = 1;
		stTM.tm_mday = 0;
		stTM.tm_hour = 0;
		stTM.tm_min  = 0;
		stTM.tm_sec  = 0;  // 1580428800
	}		
	else if( _cnt % TYPE_CNT == 3 )
	{
		stTM.tm_year = 2020;
		stTM.tm_mon  = 2;
		stTM.tm_mday = 1;
		stTM.tm_hour = 0;
		stTM.tm_min  = 0;
		stTM.tm_sec  = 0;  // 1583020800
	}		
	else if( _cnt % TYPE_CNT == 4 )
	{
		stTM.tm_year = 2020;
		stTM.tm_mon  = 2;
		stTM.tm_mday = 1;
		stTM.tm_hour = 0;
		stTM.tm_min  = 0;
		stTM.tm_sec  = 5;  // 1583020805
	}
	else if( _cnt % TYPE_CNT == 5 )
	{
		stTM.tm_year = 2020;
		stTM.tm_mon  = 3;
		stTM.tm_mday = 1;
		stTM.tm_hour = 0;
		stTM.tm_min  = 0;
		stTM.tm_sec  = 5;  // 1585699205   2020-04-01 08:00:05
	}
	else if( _cnt % TYPE_CNT == 6 )
	{
		stTM.tm_year = 2020;
		stTM.tm_mon  = 4;
		stTM.tm_mday = 1;
		stTM.tm_hour = 0;
		stTM.tm_min  = 0;
		stTM.tm_sec  = 5;  // 1588291205  2020-05-01 08:00:05
	}
	else if( _cnt % TYPE_CNT == 7 )
	{
		stTM.tm_year = 2020;
		stTM.tm_mon  = 5;
		stTM.tm_mday = 1;
		stTM.tm_hour = 0;
		stTM.tm_min  = 0;
		stTM.tm_sec  = 5;  // 1590969605 2020-06-01 08:00:05
	}
	else if( _cnt % TYPE_CNT == 8 )
	{
		stTM.tm_year = 2021;
		stTM.tm_mon  = 0;
		stTM.tm_mday = 1;
		stTM.tm_hour = 0;
		stTM.tm_min  = 0;
		stTM.tm_sec  = 5;  // 1609459205  2021-01-01 08:00:05
	}
	else if( _cnt % TYPE_CNT == 9 )
	{
		stTM.tm_year = 2021;
		stTM.tm_mon  = 1;
		stTM.tm_mday = 1;
		stTM.tm_hour = 0;
		stTM.tm_min  = 0;
		stTM.tm_sec  = 5;  // 1612137605 2021-02-01 08:00:05
	}
	else if( _cnt % TYPE_CNT == 10 )
	{
		stTM.tm_year = 2021;
		stTM.tm_mon  = 2;
		stTM.tm_mday = 1;
		stTM.tm_hour = 0;
		stTM.tm_min  = 0;
		stTM.tm_sec  = 5;  // 1614556805 2021-03-01 08:00:05
	}
	else if( _cnt % TYPE_CNT == 11 )
	{
		stTM.tm_year = 2021;
		stTM.tm_mon  = 3;
		stTM.tm_mday = 1;
		stTM.tm_hour = 0;
		stTM.tm_min  = 0;
		stTM.tm_sec  = 5;  // 1617235205 2021-04-01 08:00:05
	}
	else if( _cnt % TYPE_CNT == 12 )
	{
		stTM.tm_year = 2021;
		stTM.tm_mon  = 4;
		stTM.tm_mday = 1;
		stTM.tm_hour = 0;
		stTM.tm_min  = 0;
		stTM.tm_sec  = 5;  // 1619827205  2021-05-01 08:00:05
	}
	else if( _cnt % TYPE_CNT == 13 )
	{
		stTM.tm_year = 2021;
		stTM.tm_mon  = 5;
		stTM.tm_mday = 1;
		stTM.tm_hour = 0;
		stTM.tm_min  = 0;
		stTM.tm_sec  = 5;  // 1622505605 2021-06-01 08:00:05
	}
	else if( _cnt % TYPE_CNT == 14 )
	{
		stTM.tm_year = 2021;
		stTM.tm_mon  = 6;
		stTM.tm_mday = 1;
		stTM.tm_hour = 0;
		stTM.tm_min  = 0;
		stTM.tm_sec  = 5;  // 1625097605 2021-07-01 08:00:05
	}

	stTM.tm_year -= 1900;

	
	timep = mktime( &stTM );
	
	dprintf("cnt=%d, time:%d\n",_cnt % TYPE_CNT, timep);

	_cnt++;

	
}



void testComTime( void )
{
	timerStartSec( 1,  TIMER_REPEAT_FOREVER,  testTimeCB );

}

#endif



