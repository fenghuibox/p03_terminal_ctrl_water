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
    u32 cfg_ver;
    u32 sleep_sec;
    u32 work_sec;

	u32 open_sec;
	u32 close_sec;

	

    u8 aes_key[EEP_LEN_CFG_AES_KEY];
    u8 aes_switch;
    u8 flash_is_new;
    u8 work_state;

	
    u32 end;
}ST_CONFIG;






extern ST_CONFIG _stAppConfig;
extern u8 _cfgModify;





#endif

