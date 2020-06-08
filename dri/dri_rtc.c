 
#include "com_typedef.h"
 
#include "com_includes.h"









void App_RtcCfg(void)
{
    stc_rtc_initstruct_t RtcInitStruct;
    stc_rtc_alarmtime_t RtcAlmStruct;
    
    DDL_ZERO_STRUCT(RtcInitStruct);                      //变量初始值置零
    DDL_ZERO_STRUCT(RtcAlmStruct);
    
    Sysctrl_SetPeripheralGate(SysctrlPeripheralRtc,TRUE);//RTC模块时钟打开    
    
    Sysctrl_ClkSourceEnable(SysctrlClkXTL, TRUE);        //使能外部XTL时钟作为RTC时钟
    
    RtcInitStruct.rtcAmpm = RtcPm;                       //24小时制
    RtcInitStruct.rtcClksrc = RtcClkXtl;                 //外部低速时钟
    RtcInitStruct.rtcPrdsel.rtcPrdsel = RtcPrds;         //周期中断类型PRDS
    RtcInitStruct.rtcPrdsel.rtcPrds = RtcNone;           //不产生周期中断
    RtcInitStruct.rtcTime.u8Second = 0x55;               //配置RTC时间2019年4月17日10:01:55
    RtcInitStruct.rtcTime.u8Minute = 0x01;
    RtcInitStruct.rtcTime.u8Hour   = 0x10;
    RtcInitStruct.rtcTime.u8Day    = 0x17;
    RtcInitStruct.rtcTime.u8DayOfWeek = 0x04;
    RtcInitStruct.rtcTime.u8Month  = 0x04;
    RtcInitStruct.rtcTime.u8Year   = 0x19;
    RtcInitStruct.rtcCompen = RtcCompenEnable;           // 使能时钟误差补偿
    RtcInitStruct.rtcCompValue = 0;                      //补偿值  根据实际情况进行补偿
    Rtc_Init(&RtcInitStruct);
    
    RtcAlmStruct.RtcAlarmSec = 0x05;
    RtcAlmStruct.RtcAlarmMinute = 0x02;
    RtcAlmStruct.RtcAlarmHour = 0x10;
    RtcAlmStruct.RtcAlarmWeek = 0x7f;                    //从周一到周日，每天10:02:05启动一次闹铃    
    Rtc_SetAlarmTime(&RtcAlmStruct);                     //配置闹铃时间    
    Rtc_AlmIeCmd(TRUE);                                  //使能闹钟中断
    
    EnableNvic(RTC_IRQn, IrqLevel3, TRUE);               //使能RTC中断向量
    Rtc_Cmd(TRUE);                                       //使能RTC开始计数
}






void driRtcInit( void )
{
	_driAdcEnInit();

	_driAdcInit();

	_funAdcCB = NULL;
	
}



