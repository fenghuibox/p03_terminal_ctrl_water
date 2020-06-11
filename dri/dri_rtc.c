 
#include "com_typedef.h"
 
#include "com_includes.h"


#include "dri_rtc.h"










void Rtc_IRQHandler(void)
{
	#include "dbg_uart.h"
	
	ST_DATE_TIME stDT;
	u32 sec;
	
    if (Rtc_GetPridItStatus() == TRUE) //�����ж�
    {
        Rtc_ClearPrdfItStatus();   
		
        #if 0
		if( driRtcGetDateTime( &stDT ) == TRUE )
		{
			sec = dateTime2Sec( &stDT );
			dprintf("%04d-%02d-%02d %02d:%02d:%02d  %d", stDT.year, stDT.month, stDT.day, stDT.hour, stDT.minute, stDT.sec, sec );   

		}
		else
		{
			dprintf("\r\nread date time err");   
		}
		#endif
		
    }
}




u8 driRtcGetDateTime( ST_DATE_TIME *pstDT)
{
	stc_rtc_time_t  stT = {0};

	en_result_t rst;
	u16 temp;
	int i;

	for( i = 0; i < 10; i++ )
	{
		rst = Rtc_ReadDateTime( &stT );
		
		if( rst == Ok )
		{
			temp = BCD2DEC( stT.u8Year ); // 19
			pstDT->year   = temp + 2000;  // 2019

			pstDT->month  = BCD2DEC( stT.u8Month );
			pstDT->day    = BCD2DEC( stT.u8Day );

			pstDT->hour   = BCD2DEC( stT.u8Hour );
			pstDT->minute = BCD2DEC( stT.u8Minute );
			pstDT->sec    = BCD2DEC( stT.u8Second );

			return TRUE;
		}
	}

	return FALSE;

}







u32 driRtcGetDateTimeSec( void )
{
	//#include "dbg_uart.h"
	
	ST_DATE_TIME stDT;
	u32 sec = 0;
	
    
	if( driRtcGetDateTime( &stDT ) == TRUE )
	{
		sec = dateTime2Sec( &stDT );
		//dprintf("%04d-%02d-%02d %02d:%02d:%02d  %d", stDT.year, stDT.month, stDT.day, stDT.hour, stDT.minute, stDT.sec, sec );   
	}
	else
	{
		//dprintf( "\r\ndriRtcGetDateTimeSec err");   
	}

	return sec;

	
}








static void _rtcDateTimeInit( void )
{
    stc_rtc_initstruct_t RtcInitStruct;
    
    DDL_ZERO_STRUCT(RtcInitStruct);                      // ������ʼֵ����
    
    Sysctrl_SetPeripheralGate(SysctrlPeripheralRtc,TRUE);// RTCģ��ʱ�Ӵ�    
    
    Sysctrl_ClkSourceEnable(SysctrlClkXTL, TRUE);        // ʹ���ⲿXTLʱ����ΪRTCʱ��
    
    RtcInitStruct.rtcAmpm             = RtcPm;           // 24Сʱ��
    RtcInitStruct.rtcClksrc           = RtcClkXtl;       // �ⲿ����ʱ��
    RtcInitStruct.rtcPrdsel.rtcPrdsel = RtcPrdx;         // �����ж�����PRDX
    
    RtcInitStruct.rtcPrdsel.rtcPrdx   = RTC_PRDX_10_S;    // 5S ���������ж�
    //RtcInitStruct.rtcPrdsel.rtcPrds   = RtcNone;       // �����������ж�
    
    RtcInitStruct.rtcTime.u8Second    = 0x55;            // ����RTCʱ��2019��4��17��10:01:55
    RtcInitStruct.rtcTime.u8Minute    = 0x01;
    RtcInitStruct.rtcTime.u8Hour      = 0x10;
    RtcInitStruct.rtcTime.u8Day       = 0x17;
    RtcInitStruct.rtcTime.u8DayOfWeek = 0x04;
    RtcInitStruct.rtcTime.u8Month     = 0x04;
    RtcInitStruct.rtcTime.u8Year      = 0x19;
    RtcInitStruct.rtcCompen           = RtcCompenEnable;  // ʹ��ʱ������
    RtcInitStruct.rtcCompValue        = 0;                // ����ֵ  ����ʵ��������в���
    Rtc_Init(&RtcInitStruct);
    
    
    EnableNvic(RTC_IRQn, IrqLevel3, TRUE);               // ʹ��RTC�ж�����
    Rtc_Cmd(TRUE);                                       // ʹ��RTC��ʼ����
}




void driRtcInit( void )
{
	_rtcDateTimeInit();	
}








