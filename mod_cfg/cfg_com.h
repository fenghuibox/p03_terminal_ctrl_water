/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/



#ifndef ___CFG_COMM_H
#define ___CFG_COMM_H


#include "com_includes.h"


#include "cfg_aes.h"


typedef struct
{
    u32 write_cnt;
    u32 flash_is_new;
	
    u32 cfg_ver;
    u32 sleep_sec;  // def: 15
    u32 work_sec;   // def:  5

	
	u32 ctrl_mode;                // 控制模式  0：命令控制模式  1：周期控制模式   def:0
	
	u32 cmd_ctrl_open_sec;      // 命令控制时，开的时长 def:60
	u32 cmd_ctrl_start_sec;     // (内部使用)执行命令控制时的时间戳 

	

	u32 period_ctrl_open_minute;  // 自动周期控制时， 开的时长   def:  1
	u32 period_ctrl_close_minute; // 自动周期控制时， 关的时长   def: 60

	u32 period_ctrl_timeout_sec; // (内部使用) 自动周期控制时，定时的时间戳  
	u32 period_ctrl_action;      // (内部使用) 自动周期控制时，定时到时的控制行为 ( 1: 开  0:关)
	

	u32 ctrl_state;// 水阀的状态  0:关

    u32 aes_switch;                // def: 0
    u8 aes_key[EEP_LEN_CFG_AES_KEY];
	
	
    u32 end;
}ST_CONFIG;






extern ST_CONFIG _stAppConfig;
extern u8 _cfgModify;





#endif

