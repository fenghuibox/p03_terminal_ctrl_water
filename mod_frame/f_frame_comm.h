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

#ifndef __F_FRAME_COMM_H
#define __F_FRAME_COMM_H


#include "com_typedef.h"

#include "com_mac.h"


#define NET_ADDR_LEN (2)

//===================================================================================
//==============response_frame.h========================================================
//===================================================================================
/*
--------------------------------------------------------------------------------
��Ӧ��ֵ����		
--------------------------------------------------------------------------------
��Ӧ��ֵ	Ӧ����	����  rsp:  response  ��Ӧ	
--------------------------------------------------------------------------------
0x20		ACK		֡��Ա������ȷ��������ȷִ�д�����
0x21		NAK		֡��Ա������ȷ����ִ������ʱ����(��ǰæ������ԭ��)��
0x22		ERROR	֡��Ա��������
---------------------------------------------------------------------------------*/
typedef enum 
{
	RSP_FRAME_VAL_NOT_DEF = 0, 
	RSP_FRAME_VAL_ACK = 0x20,
	RSP_FRAME_VAL_NAK = 0x21,
	RSP_FRAME_VAL_ERR = 0x22,
}EN_RSP_FRAME_VAL; // 




/*
--------------------------------------------------------------------------------
��Ӧ��֡��ʽ���汾�ţ�0��		rsp:  response  ��Ӧ	
--------------------------------------------------------------------------------
���	֡��Ա��	�ֽ���	����
--------------------------------------------------------------------------------
A1		֡��ʼ			1	ֵ��0xAA��
A2		֡����			1	֡�����ֽ�����   ֵ��6��
A3		֡�汾			1	֡��ʽ�İ汾�ţ� ֵ��0��
A4		У���			1	����֡�������޷���������ʽ�����ֽ��ۼӣ����������
A5		����/�ն�ID		8	��ƷID��
A6		�ỰID			1	
A7		��Ӧ��ֵ		1	�����Ӧ��֡��ֵ���塣
A8		֡����			1	ֵ��0x88��
--------------------------------------------------------------------------------*/
typedef struct
{
	u8 head;     // 
	u8 len;
	u8 ver;
	u8 check;
	u8 pMac[MAC_ADDR_LEN];  // mac
	u8 sid;      // �ỰID
	EN_RSP_FRAME_VAL val;
	u8 tail;
}ST_RSP_FRAME; 



//===================================================================================
//==============txt_frame_exe.h========================================================
//===================================================================================

typedef struct // λ�ò��ܱ�
{
	//--------rsp------------------
	u8 frame_parser_rsp:1;
	u8 frame_exe_rsp:1;

	//--------zcmd------------------
	//u8 devInfo:1;  //
	//u8 autoNet:1; 
	//u8 lqi:1; 

	//--------start repace----------------------------------------------------------
	
	//--------base----------------------------------
	u8 config_ver:1;   //  3 ���ð汾��
	u8 def:1;	//	4 �ָ���������
	u8 aes_switch:1;   //  5 ���ܿ���
	u8 aes_key:1;	//	6 ������Կ
	u8 reboot:1;   //  7 �豸����
	u8 ver:1;	//	8 �豸�İ汾
	u8 dev_type:1;	 //  9 �豸������
	u8 heartbeat:1;   //  10 �豸������
	u8 battery:1;	//	11 �豸�ĵ���
	u8 work_state:1;   //  12 �豸�Ĺ���״̬
	u8 ctrl_in:1;	//	13 �������������
	u8 ctrl_out:1;	 //  14 �������̵������
	u8 zigbee_to_reset:1;	//	15 zigbee_��λ
	u8 zigbee_to_def:1;   //  16 zigbee_�ָ���������
	u8 zigbee_auto_net:1;	//	17 zigbee_����������
	u8 zigbee_allow_join:1;   //  18 zigbee_����ӻ�����
	u8 zigbee_del_by_mac_addr:1;   //  19 zigbee_��MACɾ���ӻ�
	u8 zigbee_child_info:1;   //  20 zigbee_��ѯ�ڵ���Ϣ
	u8 zigbee_work_state:1;   //  21 zigbee_��ѯ����״̬
	u8 zigbee_info:1;	//	22 zigbee_������Ϣ
	u8 g4_to_reset:1;	//	23 4G_��λ
	u8 g4_to_def:1;   //  24 4G_�ָ���������
	u8 g4_state_get:1;	 //  25 4G_��ѯ״̬
	u8 g4_imei_get:1;	//	26 4G_IMEI
	u8 g4_rssi_ber_get:1;	//	27 4G_��ѯ�ź�ǿ��
	u8 g4_qmt_open_net:1;	//	28 4G_MQTT_������ַ
	u8 g4_qmt_conn_user:1;	 //  29 4G_MQTT_��¼�û���
	u8 g4_qmt_conn_pwd:1;	//	30 4G_MQTT_��¼����
	u8 g4_qmt_client_id:1;	 //  31 4G_MQTT_�ͻ��˱��
	u8 g4_qmt_pubex_qos:1;	 //  32 4G_MQTT_������Ϣ���ݷ�������  
	u8 g4_qmt_sub_topic_qos:1;	 //  33 4G_MQTT_������Ϣ���ݷ�������  
	u8 uart485:1;	//	34 485����
	u8 adc1:1;	 //  35 ADCͨ��1
	u8 adc2:1;	 //  36 ADCͨ��2
	u8 dac1:1;	 //  37 DACͨ��1
	u8 dac2:1;	 //  38 DACͨ��2

	u8 ctrl_out1_on_sec:1;	 //  39 �̵���1���ʱ��
	u8 ctrl_out2_on_sec:1;	 //  40 �̵���2���ʱ��
	u8 ctrl_out3_on_sec:1;	 //  41 �̵���3���ʱ��
	u8 ctrl_out4_on_sec:1;	 //  42 �̵���4���ʱ��
	u8 ctrl_out5_on_sec:1;	 //  43 �̵���5���ʱ��
	u8 ctrl_out6_on_sec:1;	 //  44 �̵���6���ʱ��
	u8 ctrl_out7_on_sec:1;	 //  45 �̵���7���ʱ��
	u8 ctrl_out8_on_sec:1;	 //  46 �̵���8���ʱ��
	u8 ctrl_out9_on_sec:1;	 //  47 �̵���9���ʱ��
	u8 ctrl_out10_on_sec:1;   //  48 �̵���10���ʱ��
	u8 ctrl_out11_on_sec:1;   //  49 �̵���11���ʱ��
	u8 ctrl_out12_on_sec:1;   //  50 �̵���12���ʱ��
	u8 ctrl_out13_on_sec:1;   //  51 �̵���13���ʱ��
	u8 ctrl_out14_on_sec:1;   //  52 �̵���14���ʱ��
	u8 ctrl_out15_on_sec:1;   //  53 �̵���15���ʱ��
	u8 ctrl_out16_on_sec:1;   //  54 �̵���16���ʱ��
	u8 ctrl_out17_on_sec:1;   //  55 �̵���17���ʱ��
	u8 ctrl_out18_on_sec:1;   //  56 �̵���18���ʱ��
	u8 ctrl_out19_on_sec:1;   //  57 �̵���19���ʱ��
	u8 ctrl_out20_on_sec:1;   //  58 �̵���20���ʱ��
	u8 ctrl_out21_on_sec:1;   //  59 �̵���21���ʱ��
	u8 ctrl_out22_on_sec:1;   //  60 �̵���22���ʱ��
	u8 ctrl_out23_on_sec:1;   //  61 �̵���23���ʱ��
	u8 ctrl_out24_on_sec:1;   //  62 �̵���24���ʱ��
	u8 ctrl_out25_on_sec:1;   //  63 �̵���25���ʱ��
	u8 ctrl_out26_on_sec:1;   //  64 �̵���26���ʱ��
	u8 ctrl_out27_on_sec:1;   //  65 �̵���27���ʱ��
	u8 ctrl_out28_on_sec:1;   //  66 �̵���28���ʱ��
	u8 ctrl_out29_on_sec:1;   //  67 �̵���29���ʱ��
	u8 ctrl_out30_on_sec:1;   //  68 �̵���30���ʱ��
	u8 ctrl_out31_on_sec:1;   //  69 �̵���31���ʱ��


	//--------end repace----------------------------------------------------------


	#if 0
	//--------error------------------
	u8 err_dev:1;	    //	
	//u8 err_zigbee:1;	//	
	//u8 err_sensor:1;	//	
	//u8 err_ptl:1;	    //	
	//u8 err_ptl_cfg:1;	//	
	#endif
	
}ST_G2S;




typedef enum 
{
	G2S_SEND_CID_NULL = 0,
	G2S_SEND_CID_FRAME_PARSER_RSP,  // 1
	G2S_SEND_CID_FRAME_EXE_RSP,	// 2

	//--------------------------------------
	
	G2S_SEND_CID_CONFIG_VER,	// 3
	G2S_SEND_CID_DEF,	// 4
	G2S_SEND_CID_AES_SWITCH,	// 5
	G2S_SEND_CID_AES_KEY,	// 6
	G2S_SEND_CID_REBOOT,	// 7
	G2S_SEND_CID_VER,	// 8
	G2S_SEND_CID_DEV_TYPE,	// 9
	G2S_SEND_CID_HEARTBEAT, // 10
	G2S_SEND_CID_BATTERY,	// 11
	G2S_SEND_CID_WORK_STATE,	// 12
	G2S_SEND_CID_CTRL_IN,	// 13
	G2S_SEND_CID_CTRL_OUT,	// 14
	G2S_SEND_CID_ZIGBEE_TO_RESET,	// 15
	G2S_SEND_CID_ZIGBEE_TO_DEF, // 16
	G2S_SEND_CID_ZIGBEE_AUTO_NET,	// 17
	G2S_SEND_CID_ZIGBEE_ALLOW_JOIN, // 18
	G2S_SEND_CID_ZIGBEE_DEL_BY_MAC_ADDR,	// 19
	G2S_SEND_CID_ZIGBEE_CHILD_INFO, // 20
	G2S_SEND_CID_ZIGBEE_WORK_STATE, // 21
	G2S_SEND_CID_ZIGBEE_INFO,	// 22
	G2S_SEND_CID_G4_TO_RESET,	// 23
	G2S_SEND_CID_G4_TO_DEF, // 24
	G2S_SEND_CID_G4_STATE_GET,	// 25
	G2S_SEND_CID_G4_IMEI_GET,	// 26
	G2S_SEND_CID_G4_RSSI_BER_GET,	// 27
	G2S_SEND_CID_G4_QMT_OPEN_NET,	// 28
	G2S_SEND_CID_G4_QMT_CONN_USER,	// 29
	G2S_SEND_CID_G4_QMT_CONN_PWD,	// 30
	G2S_SEND_CID_G4_QMT_CLIENT_ID,	// 31
	G2S_SEND_CID_G4_QMT_PUBEX_QOS,	// 32
	G2S_SEND_CID_G4_QMT_SUB_TOPIC_QOS,	// 33
	G2S_SEND_CID_UART485,	// 34
	G2S_SEND_CID_ADC1,	// 35
	G2S_SEND_CID_ADC2,	// 36
	G2S_SEND_CID_DAC1,	// 37
	G2S_SEND_CID_DAC2,	// 38
	G2S_SEND_CID_CTRL_OUT1_ON_SEC,	// 39
	G2S_SEND_CID_CTRL_OUT2_ON_SEC,	// 40
	G2S_SEND_CID_CTRL_OUT3_ON_SEC,	// 41
	G2S_SEND_CID_CTRL_OUT4_ON_SEC,	// 42
	G2S_SEND_CID_CTRL_OUT5_ON_SEC,	// 43
	G2S_SEND_CID_CTRL_OUT6_ON_SEC,	// 44
	G2S_SEND_CID_CTRL_OUT7_ON_SEC,	// 45
	G2S_SEND_CID_CTRL_OUT8_ON_SEC,	// 46
	G2S_SEND_CID_CTRL_OUT9_ON_SEC,	// 47
	G2S_SEND_CID_CTRL_OUT10_ON_SEC, // 48
	G2S_SEND_CID_CTRL_OUT11_ON_SEC, // 49
	G2S_SEND_CID_CTRL_OUT12_ON_SEC, // 50
	G2S_SEND_CID_CTRL_OUT13_ON_SEC, // 51
	G2S_SEND_CID_CTRL_OUT14_ON_SEC, // 52
	G2S_SEND_CID_CTRL_OUT15_ON_SEC, // 53
	G2S_SEND_CID_CTRL_OUT16_ON_SEC, // 54
	G2S_SEND_CID_CTRL_OUT17_ON_SEC, // 55
	G2S_SEND_CID_CTRL_OUT18_ON_SEC, // 56
	G2S_SEND_CID_CTRL_OUT19_ON_SEC, // 57
	G2S_SEND_CID_CTRL_OUT20_ON_SEC, // 58
	G2S_SEND_CID_CTRL_OUT21_ON_SEC, // 59
	G2S_SEND_CID_CTRL_OUT22_ON_SEC, // 60
	G2S_SEND_CID_CTRL_OUT23_ON_SEC, // 61
	G2S_SEND_CID_CTRL_OUT24_ON_SEC, // 62
	G2S_SEND_CID_CTRL_OUT25_ON_SEC, // 63
	G2S_SEND_CID_CTRL_OUT26_ON_SEC, // 64
	G2S_SEND_CID_CTRL_OUT27_ON_SEC, // 65
	G2S_SEND_CID_CTRL_OUT28_ON_SEC, // 66
	G2S_SEND_CID_CTRL_OUT29_ON_SEC, // 67
	G2S_SEND_CID_CTRL_OUT30_ON_SEC, // 68
	G2S_SEND_CID_CTRL_OUT31_ON_SEC, // 69


	
}EN_G2S_SEND_CMD_ID; // 







typedef struct // λ�ò��ܱ�
{
	u32 aa:1;        //  
	u32 ff:1; //  
	u32 cc:1;    //  

	
}ST_G2S_2;


//===================================================================================
//==============frame_ppack.h========================================================
//===================================================================================





//===================================================================================
//==============frame_dpack.h========================================================
//===================================================================================

/*--------------------------
�ն˵Ķ˿�ID ����
---------------------------
ID��	����
---------------------------
0		�ն�����
1		�ն˵� UART1
2		�ն˵� UART2
3		�ն˵� UART3
4		�ն˵� UART4
5		�ն˵� I2C1
6		�ն˵� I2C2
---------------------------*/
typedef enum 
{
	DPACK_PORT_ID_SELF = 0, 
	DPACK_PORT_ID_UART1, // 4
	DPACK_PORT_ID_MAX
}EN_DPACK_PORT_ID; // 





typedef enum 
{
	DPACK_PARA_ID_CONFIG_VER = 1,  //  ���ð汾��	���ڸ�����������ԭ�����Ҫ�޸����ã������õİ汾�ţ�����������鵽�汾����ʱ���Ὣ�û������ø��µ��豸�ϡ�
	DPACK_PARA_ID_DEF = 2,	//	�ָ���������   0bit0:zigbee;  bit1:4g; bit2:STM����
	DPACK_PARA_ID_AES_SWITCH = 3,  //  ���ܿ���   �豸���͵������Ƿ���м���
	DPACK_PARA_ID_AES_KEY = 4,	//	������Կ   ������Կ
	DPACK_PARA_ID_REBOOT = 5,  //  �豸����   �豸����ʱ�������ʹ���Ϣ
	DPACK_PARA_ID_VER = 20,  //  �豸�İ汾   HHHH WWWW
	DPACK_PARA_ID_DEV_TYPE = 21,  //  �豸������   1������	2��·�� 3���ɼ��ն�  4�������ն�
	DPACK_PARA_ID_HEARTBEAT = 22,  //  �豸������	ֻ�Զ�����
	DPACK_PARA_ID_BATTERY = 23,  //  �豸�ĵ���   0��100�������ٷֱ�
	DPACK_PARA_ID_WORK_STATE = 27,	//	�豸�Ĺ���״̬	 0����������̬	1������̬
	DPACK_PARA_ID_CTRL_IN = 28,  //  �������������   64λ��ǰ32λ��Ӧ����ļ��λ��(����λ��ӦӲ�����ϵ�1�����λ��),��32λ��Ӧ�̵������״̬(����λ��ӦӲ�����ϵ�1���̵���)
	DPACK_PARA_ID_CTRL_OUT = 29,  //  �������̵������	 32λ����Ӧ�̵������״̬(����λ��ӦӲ�����ϵ�1���̵���)
	DPACK_PARA_ID_ZIGBEE_TO_RESET = 151,  //  zigbee_��λ	zigbee ��λ
	DPACK_PARA_ID_ZIGBEE_TO_DEF = 152,	//	zigbee_�ָ���������   zigbee �ָ���������
	DPACK_PARA_ID_ZIGBEE_AUTO_NET = 153,  //  zigbee_����������   1������  0���ر�
	DPACK_PARA_ID_ZIGBEE_ALLOW_JOIN = 154,	//	zigbee_����ӻ�����   �����ʱ��
	DPACK_PARA_ID_ZIGBEE_DEL_BY_MAC_ADDR = 155,  //  zigbee_��MACɾ���ӻ�	8�ֽ�MAC��ַ
	DPACK_PARA_ID_ZIGBEE_CHILD_INFO = 159,	//	zigbee_��ѯ�ڵ���Ϣ   �ӻ����� MAC��ַ1 + �����ַ1 + �� + MAC��ַN + �����ַN
	DPACK_PARA_ID_ZIGBEE_WORK_STATE = 160,	//	zigbee_��ѯ����״̬   ������ 0������ 1�����ڼ������  2������ӻ���������
	DPACK_PARA_ID_ZIGBEE_INFO = 161,  //  zigbee_������Ϣ	out: DEV_INFO | in: PowerLevel+RetryNum+TranTimeout
	DPACK_PARA_ID_G4_TO_RESET = 191,  //  4G_��λ	
	DPACK_PARA_ID_G4_TO_DEF = 192,	//	4G_�ָ���������   
	DPACK_PARA_ID_G4_STATE_GET = 193,  //  4G_��ѯ״̬	 
	DPACK_PARA_ID_G4_IMEI_GET = 194,  //  4G_IMEI	
	DPACK_PARA_ID_G4_RSSI_BER_GET = 195,  //  4G_��ѯ�ź�ǿ��	
	DPACK_PARA_ID_G4_QMT_OPEN_NET = 196,  //  4G_MQTT_������ַ	 
	DPACK_PARA_ID_G4_QMT_CONN_USER = 197,  //  4G_MQTT_��¼�û���	
	DPACK_PARA_ID_G4_QMT_CONN_PWD = 198,  //  4G_MQTT_��¼����	 
	DPACK_PARA_ID_G4_QMT_CLIENT_ID = 199,  //  4G_MQTT_�ͻ��˱��	
	DPACK_PARA_ID_G4_QMT_PUBEX_QOS = 200,  //  4G_MQTT_������Ϣ���ݷ������� 	
	DPACK_PARA_ID_G4_QMT_SUB_TOPIC_QOS = 201,  //  4G_MQTT_������Ϣ���ݷ������� 	
	DPACK_PARA_ID_UART485 = 220,  //  485����	485����ͨ��
	DPACK_PARA_ID_ADC1 = 240,  //  ADCͨ��1   ��1·ADCͨ��
	DPACK_PARA_ID_ADC2 = 241,  //  ADCͨ��2   ��2·ADCͨ��
	DPACK_PARA_ID_DAC1 = 260,  //  DACͨ��1   2·DACͨ��
	DPACK_PARA_ID_DAC2 = 261,  //  DACͨ��2   2·DACͨ��
	DPACK_PARA_ID_CTRL_OUT1_ON_SEC = 401,  //  �̵���1���ʱ��	 ��1������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT2_ON_SEC = 402,  //  �̵���2���ʱ��	 ��2������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT3_ON_SEC = 403,  //  �̵���3���ʱ��	 ��3������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT4_ON_SEC = 404,  //  �̵���4���ʱ��	 ��4������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT5_ON_SEC = 405,  //  �̵���5���ʱ��	 ��5������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT6_ON_SEC = 406,  //  �̵���6���ʱ��	 ��6������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT7_ON_SEC = 407,  //  �̵���7���ʱ��	 ��7������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT8_ON_SEC = 408,  //  �̵���8���ʱ��	 ��8������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT9_ON_SEC = 409,  //  �̵���9���ʱ��	 ��9������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT10_ON_SEC = 410,	//	�̵���10���ʱ��   ��10������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT11_ON_SEC = 411,	//	�̵���11���ʱ��   ��11������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT12_ON_SEC = 412,	//	�̵���12���ʱ��   ��12������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT13_ON_SEC = 413,	//	�̵���13���ʱ��   ��13������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT14_ON_SEC = 414,	//	�̵���14���ʱ��   ��14������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT15_ON_SEC = 415,	//	�̵���15���ʱ��   ��15������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT16_ON_SEC = 416,	//	�̵���16���ʱ��   ��16������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT17_ON_SEC = 417,	//	�̵���17���ʱ��   ��17������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT18_ON_SEC = 418,	//	�̵���18���ʱ��   ��18������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT19_ON_SEC = 419,	//	�̵���19���ʱ��   ��19������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT20_ON_SEC = 420,	//	�̵���20���ʱ��   ��20������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT21_ON_SEC = 421,	//	�̵���21���ʱ��   ��21������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT22_ON_SEC = 422,	//	�̵���22���ʱ��   ��22������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT23_ON_SEC = 423,	//	�̵���23���ʱ��   ��23������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT24_ON_SEC = 424,	//	�̵���24���ʱ��   ��24������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT25_ON_SEC = 425,	//	�̵���25���ʱ��   ��25������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT26_ON_SEC = 426,	//	�̵���26���ʱ��   ��26������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT27_ON_SEC = 427,	//	�̵���27���ʱ��   ��27������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT28_ON_SEC = 428,	//	�̵���28���ʱ��   ��28������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT29_ON_SEC = 429,	//	�̵���29���ʱ��   ��29������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT30_ON_SEC = 430,	//	�̵���30���ʱ��   ��30������ڿ���ʱ��
	DPACK_PARA_ID_CTRL_OUT31_ON_SEC = 431,	//	�̵���31���ʱ��   ��31������ڿ���ʱ��




}EN_DPACK_PARA_ID; // 




/*
���ݰ� ��ʽ����		
------------------------------------------------------
���ݰ���Ա��	�ֽ���	����
------------------------------------------------------
����				1	���ݰ��ĳ��ȡ�
�ն˵Ķ˿�ID		1	��Ʒ�Ķ˿ڱ�š�
�ն˶˿ڵ�ͨ�ŵ�ַ	1	����485��ַ�š�
����ID				2	���ݰ��Ĳ�����š�
����ֵ				n	������ֵ��
-----------------------------------------------------*/
typedef struct
{
	u8 len;
	u8 portId;
	u8 portAddr;
	u16 paraId;  // 
	u8 *pPara;   // 
}ST_DPACK; 


#define FRAME_DATA_PACK_CONST_ELE_LEN  (5)  // ���ݰ� �� �����������Ԫ�س���

//===================================================================================
//==============txt_frame.h==========================================================
//===================================================================================

/*
����֡ ��Ϊ ����		
----------------------------------------------------------------------------------
ֵ			��						����
----------------------------------------------------------------------------------
0x01	ACTION_SET				����ֵ����Ϊ��
0x02	ACTION_GET				��ȡֵ����Ϊ��
0x03	ACTION_REPORT_ACK_GET	Ϊ��ӦACTION_GET������ֵ����Ϊ���������棩��
0x04	ACTION_REPORT_AUTO		�Զ�����ֵ����Ϊ���������棩��
---------------------------------------------------------------------------------*/
typedef enum 
{
	TXT_FRAME_ACTION_NOT_DEF = 0, 
	TXT_FRAME_ACTION_SET,
	TXT_FRAME_ACTION_GET,
	TXT_FRAME_ACTION_REPORT_ACK_GET,
	TXT_FRAME_ACTION_REPORT_AUTO,
}EN_TXT_FRAME_ACTION; // 



/*
����֡���� ����
------------------------------------
ֵ	   ����	       ����
------------------------------------
1	�������ݰ�	
2	Э�����ݰ�	
------------------------------------
*/
typedef enum 
{
	TXT_FRAME_PACK_TYPE_NOT_DEF = 0, 
	TXT_FRAME_PACK_TYPE_DATA,
	TXT_FRAME_PACK_TYPE_PROTOCOL,
}EN_TXT_FRAME_PACK_TYPE; // 






typedef struct
{
	u8 head;     // 
	u8 len;
	u8 ver;
	EN_TXT_FRAME_ACTION action;
	u8 check;
	u8 pMac[MAC_ADDR_LEN];  // mac
	u8 sid;      // �ỰID
	EN_TXT_FRAME_PACK_TYPE packType;
	u8 *pPack;   // ���ݰ�
	u8 tail;
}ST_TXT_FRAME; 



//===================================================================================
//==============frame.h==========================================================
//===================================================================================
/*
����֡��ʽ���汾�ţ�0��			
----------------------------------------------------------------------------------
���	֡��Ա��	�ֽ���	����
----------------------------------------------------------------------------------
D1		֡��ʼ		1		ֵ��0xAA��
D2		֡����		1		֡�����ֽ�����
D3		֡�汾		1		֡��ʽ�İ汾�š�
D4		֡��Ϊ		1		֡�Ĳ�����Ϊ������
D5		У���		1		����֡���ݰ��޷��������ֽ��ۼӣ����������
D6		Ŀ��ID		8		MAC��
D7		�ỰID		1		�������½ڵ�������
D8	    ������	    1	    1�����ݰ�  2��Э���
D9		    ��		n		��Լ�� n < 230��
D10		֡����		1		ֵ��0x88��
----------------------------------------------------------------------------------*/


//-------------  ���� frame--------------------
typedef enum
{
	FRAME_UNPACK_NOT_DEF = 0,
	FRAME_UNPACK_OK = 1,
	FRAME_UNPACK_NG_HEAD,
	FRAME_UNPACK_NG_LEN,
	FRAME_UNPACK_NG_VER,
	FRAME_UNPACK_NG_ACTION, // 5
	FRAME_UNPACK_NG_CHECK,
	FRAME_UNPACK_NG_ID, // Ŀ��ID
	FRAME_UNPACK_NG_PACK_TYPE,

	//------txt frame dpack-------------------------------
	FRAME_UNPACK_NG_DPACK_LEN,
	FRAME_UNPACK_NG_DPACK_PORT_ID, // 10
	FRAME_UNPACK_NG_DPACK_PARA_ID,

	//------txt frame ppack-------------------------------
	FRAME_UNPACK_NG_PPACK_CMD_CNT,

	//------rsp frame-------------------------------
	FRAME_UNPACK_NG_RSP_VAL,
	
	FRAME_UNPACK_NG_TAIL, // 14
}EN_FRAME_UNPACK;




typedef enum
{
	FRAME_TYPE_NOT_DEF = 0,
	FRAME_TYPE_TXT_DATA= 1,
	FRAME_TYPE_TXT_PROTOCOL,
	FRAME_TYPE_RSP,
}EN_FRAME_TYPE;

#define BROADCAST_ADDR  (0xFFFF) // �㲥��ַ


#define FRAME_PACK_LEN_MAX  (222)//(230) // ֡�а��ĳ���  fenghuiwait
#define FRAME_PACK_ELE_LEN  (10)  // ���������Ԫ�س���

/*
����֡��ʽ���汾�ţ�0��			
----------------------------------------------------------------------------------
���	֡��Ա��	�ֽ���	����
----------------------------------------------------------------------------------
D1		֡��ʼ		1		ֵ��0xAA��
D2		֡����		1		֡�����ֽ�����
D3		֡�汾		1		֡��ʽ�İ汾�š�
D4		֡��Ϊ		1		֡�Ĳ�����Ϊ������
D5		У���		1		����֡���ݰ��޷��������ֽ��ۼӣ����������
D6		Ŀ��ID		8		��ƷID��
D7		�ỰID		1		�������½ڵ�������
D8	    ������	    1	    1�����ݰ�  2��Э���
D9		    ��		n		��Լ�� n < 230��
D10		֡����		1		ֵ��0x88��
----------------------------------------------------------------------------------*/
typedef struct
{
	u8 head;     // 
	u8 len;
	u8 ver;
	//EN_TXT_FRAME_ACTION action;
	u8 action;
	u8 check;
	u8 pMac[MAC_ADDR_LEN];  // mac
	u8 sid;      // �ỰID
	//EN_TXT_FRAME_PACK_TYPE packType;
	u8 packType;
	u8 pBuf[FRAME_PACK_LEN_MAX + 1];   // ���ݰ� + ֡����
}ST_FRAME;







extern ST_G2S   gstG2S;


#endif

#endif


