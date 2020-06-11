/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
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

	
	u32 ctrl_mode;                // ����ģʽ  0���������ģʽ  1�����ڿ���ģʽ   def:0
	
	u32 cmd_ctrl_open_sec;      // �������ʱ������ʱ�� def:60
	u32 cmd_ctrl_start_sec;     // (�ڲ�ʹ��)ִ���������ʱ��ʱ��� 

	

	u32 period_ctrl_open_minute;  // �Զ����ڿ���ʱ�� ����ʱ��   def:  1
	u32 period_ctrl_close_minute; // �Զ����ڿ���ʱ�� �ص�ʱ��   def: 60

	u32 period_ctrl_timeout_sec; // (�ڲ�ʹ��) �Զ����ڿ���ʱ����ʱ��ʱ���  
	u32 period_ctrl_action;      // (�ڲ�ʹ��) �Զ����ڿ���ʱ����ʱ��ʱ�Ŀ�����Ϊ ( 1: ��  0:��)
	

	u32 ctrl_state;// ˮ����״̬  0:��

    u32 aes_switch;                // def: 0
    u8 aes_key[EEP_LEN_CFG_AES_KEY];
	
	
    u32 end;
}ST_CONFIG;






extern ST_CONFIG _stAppConfig;
extern u8 _cfgModify;





#endif

