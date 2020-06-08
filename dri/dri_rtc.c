 
#include "com_typedef.h"
 
#include "com_includes.h"









void App_RtcCfg(void)
{
    stc_rtc_initstruct_t RtcInitStruct;
    stc_rtc_alarmtime_t RtcAlmStruct;
    
    DDL_ZERO_STRUCT(RtcInitStruct);                      //������ʼֵ����
    DDL_ZERO_STRUCT(RtcAlmStruct);
    
    Sysctrl_SetPeripheralGate(SysctrlPeripheralRtc,TRUE);//RTCģ��ʱ�Ӵ�    
    
    Sysctrl_ClkSourceEnable(SysctrlClkXTL, TRUE);        //ʹ���ⲿXTLʱ����ΪRTCʱ��
    
    RtcInitStruct.rtcAmpm = RtcPm;                       //24Сʱ��
    RtcInitStruct.rtcClksrc = RtcClkXtl;                 //�ⲿ����ʱ��
    RtcInitStruct.rtcPrdsel.rtcPrdsel = RtcPrds;         //�����ж�����PRDS
    RtcInitStruct.rtcPrdsel.rtcPrds = RtcNone;           //�����������ж�
    RtcInitStruct.rtcTime.u8Second = 0x55;               //����RTCʱ��2019��4��17��10:01:55
    RtcInitStruct.rtcTime.u8Minute = 0x01;
    RtcInitStruct.rtcTime.u8Hour   = 0x10;
    RtcInitStruct.rtcTime.u8Day    = 0x17;
    RtcInitStruct.rtcTime.u8DayOfWeek = 0x04;
    RtcInitStruct.rtcTime.u8Month  = 0x04;
    RtcInitStruct.rtcTime.u8Year   = 0x19;
    RtcInitStruct.rtcCompen = RtcCompenEnable;           // ʹ��ʱ������
    RtcInitStruct.rtcCompValue = 0;                      //����ֵ  ����ʵ��������в���
    Rtc_Init(&RtcInitStruct);
    
    RtcAlmStruct.RtcAlarmSec = 0x05;
    RtcAlmStruct.RtcAlarmMinute = 0x02;
    RtcAlmStruct.RtcAlarmHour = 0x10;
    RtcAlmStruct.RtcAlarmWeek = 0x7f;                    //����һ�����գ�ÿ��10:02:05����һ������    
    Rtc_SetAlarmTime(&RtcAlmStruct);                     //��������ʱ��    
    Rtc_AlmIeCmd(TRUE);                                  //ʹ�������ж�
    
    EnableNvic(RTC_IRQn, IrqLevel3, TRUE);               //ʹ��RTC�ж�����
    Rtc_Cmd(TRUE);                                       //ʹ��RTC��ʼ����
}






void driRtcInit( void )
{
	_driAdcEnInit();

	_driAdcInit();

	_funAdcCB = NULL;
	
}



