/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
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
简单应答值定义		
--------------------------------------------------------------------------------
简单应答值	应答名	解释  rsp:  response  响应	
--------------------------------------------------------------------------------
0x20		ACK		帧成员解析正确，并能正确执行此命。
0x21		NAK		帧成员解析正确，但执行命令时出错(当前忙等其它原因)。
0x22		ERROR	帧成员解析出错。
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
简单应答帧格式（版本号：0）		rsp:  response  响应	
--------------------------------------------------------------------------------
编号	帧成员名	字节数	解释
--------------------------------------------------------------------------------
A1		帧开始			1	值：0xAA。
A2		帧长度			1	帧的总字节数，   值：6。
A3		帧版本			1	帧格式的版本号， 值：0。
A4		校验和			1	所有帧数据以无符号数的形式按单字节累加，忽略溢出。
A5		网关/终端ID		8	产品ID。
A6		会话ID			1	
A7		简单应答值		1	详见简单应答帧的值定义。
A8		帧结束			1	值：0x88。
--------------------------------------------------------------------------------*/
typedef struct
{
	u8 head;     // 
	u8 len;
	u8 ver;
	u8 check;
	u8 pMac[MAC_ADDR_LEN];  // mac
	u8 sid;      // 会话ID
	EN_RSP_FRAME_VAL val;
	u8 tail;
}ST_RSP_FRAME; 



//===================================================================================
//==============txt_frame_exe.h========================================================
//===================================================================================

typedef struct // 位置不能变
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
	u8 config_ver:1;   //  3 配置版本号
	u8 def:1;	//	4 恢复出厂设置
	u8 aes_switch:1;   //  5 加密开关
	u8 aes_key:1;	//	6 加密密钥
	u8 reboot:1;   //  7 设备启动
	u8 ver:1;	//	8 设备的版本
	u8 dev_type:1;	 //  9 设备的类型
	u8 heartbeat:1;   //  10 设备的心跳
	u8 battery:1;	//	11 设备的电量
	u8 work_state:1;   //  12 设备的工作状态
	u8 ctrl_in:1;	//	13 控制器检测输入
	u8 ctrl_out:1;	 //  14 控制器继电器输出
	u8 zigbee_to_reset:1;	//	15 zigbee_复位
	u8 zigbee_to_def:1;   //  16 zigbee_恢复出厂设置
	u8 zigbee_auto_net:1;	//	17 zigbee_自组网功能
	u8 zigbee_allow_join:1;   //  18 zigbee_允许从机入网
	u8 zigbee_del_by_mac_addr:1;   //  19 zigbee_用MAC删除从机
	u8 zigbee_child_info:1;   //  20 zigbee_查询节点信息
	u8 zigbee_work_state:1;   //  21 zigbee_查询主机状态
	u8 zigbee_info:1;	//	22 zigbee_配置信息
	u8 g4_to_reset:1;	//	23 4G_复位
	u8 g4_to_def:1;   //  24 4G_恢复出厂设置
	u8 g4_state_get:1;	 //  25 4G_查询状态
	u8 g4_imei_get:1;	//	26 4G_IMEI
	u8 g4_rssi_ber_get:1;	//	27 4G_查询信号强度
	u8 g4_qmt_open_net:1;	//	28 4G_MQTT_连接网址
	u8 g4_qmt_conn_user:1;	 //  29 4G_MQTT_登录用户名
	u8 g4_qmt_conn_pwd:1;	//	30 4G_MQTT_登录密码
	u8 g4_qmt_client_id:1;	 //  31 4G_MQTT_客户端编号
	u8 g4_qmt_pubex_qos:1;	 //  32 4G_MQTT_发布信息传递服务质量  
	u8 g4_qmt_sub_topic_qos:1;	 //  33 4G_MQTT_订阅信息传递服务质量  
	u8 uart485:1;	//	34 485总线
	u8 adc1:1;	 //  35 ADC通道1
	u8 adc2:1;	 //  36 ADC通道2
	u8 dac1:1;	 //  37 DAC通道1
	u8 dac2:1;	 //  38 DAC通道2

	u8 ctrl_out1_on_sec:1;	 //  39 继电器1输出时长
	u8 ctrl_out2_on_sec:1;	 //  40 继电器2输出时长
	u8 ctrl_out3_on_sec:1;	 //  41 继电器3输出时长
	u8 ctrl_out4_on_sec:1;	 //  42 继电器4输出时长
	u8 ctrl_out5_on_sec:1;	 //  43 继电器5输出时长
	u8 ctrl_out6_on_sec:1;	 //  44 继电器6输出时长
	u8 ctrl_out7_on_sec:1;	 //  45 继电器7输出时长
	u8 ctrl_out8_on_sec:1;	 //  46 继电器8输出时长
	u8 ctrl_out9_on_sec:1;	 //  47 继电器9输出时长
	u8 ctrl_out10_on_sec:1;   //  48 继电器10输出时长
	u8 ctrl_out11_on_sec:1;   //  49 继电器11输出时长
	u8 ctrl_out12_on_sec:1;   //  50 继电器12输出时长
	u8 ctrl_out13_on_sec:1;   //  51 继电器13输出时长
	u8 ctrl_out14_on_sec:1;   //  52 继电器14输出时长
	u8 ctrl_out15_on_sec:1;   //  53 继电器15输出时长
	u8 ctrl_out16_on_sec:1;   //  54 继电器16输出时长
	u8 ctrl_out17_on_sec:1;   //  55 继电器17输出时长
	u8 ctrl_out18_on_sec:1;   //  56 继电器18输出时长
	u8 ctrl_out19_on_sec:1;   //  57 继电器19输出时长
	u8 ctrl_out20_on_sec:1;   //  58 继电器20输出时长
	u8 ctrl_out21_on_sec:1;   //  59 继电器21输出时长
	u8 ctrl_out22_on_sec:1;   //  60 继电器22输出时长
	u8 ctrl_out23_on_sec:1;   //  61 继电器23输出时长
	u8 ctrl_out24_on_sec:1;   //  62 继电器24输出时长
	u8 ctrl_out25_on_sec:1;   //  63 继电器25输出时长
	u8 ctrl_out26_on_sec:1;   //  64 继电器26输出时长
	u8 ctrl_out27_on_sec:1;   //  65 继电器27输出时长
	u8 ctrl_out28_on_sec:1;   //  66 继电器28输出时长
	u8 ctrl_out29_on_sec:1;   //  67 继电器29输出时长
	u8 ctrl_out30_on_sec:1;   //  68 继电器30输出时长
	u8 ctrl_out31_on_sec:1;   //  69 继电器31输出时长


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







typedef struct // 位置不能变
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
终端的端口ID 定义
---------------------------
ID号	解释
---------------------------
0		终端自身
1		终端的 UART1
2		终端的 UART2
3		终端的 UART3
4		终端的 UART4
5		终端的 I2C1
6		终端的 I2C2
---------------------------*/
typedef enum 
{
	DPACK_PORT_ID_SELF = 0, 
	DPACK_PORT_ID_UART1, // 4
	DPACK_PORT_ID_MAX
}EN_DPACK_PORT_ID; // 





typedef enum 
{
	DPACK_PARA_ID_CONFIG_VER = 1,  //  配置版本号	由于更换传感器等原因而需要修改配置，此配置的版本号，当服务器检查到版本不对时，会将用户的配置更新到设备上。
	DPACK_PARA_ID_DEF = 2,	//	恢复出厂设置   0bit0:zigbee;  bit1:4g; bit2:STM主控
	DPACK_PARA_ID_AES_SWITCH = 3,  //  加密开关   设备发送的数据是否进行加密
	DPACK_PARA_ID_AES_KEY = 4,	//	加密密钥   加密密钥
	DPACK_PARA_ID_REBOOT = 5,  //  设备启动   设备启动时主动发送此信息
	DPACK_PARA_ID_VER = 20,  //  设备的版本   HHHH WWWW
	DPACK_PARA_ID_DEV_TYPE = 21,  //  设备的类型   1：网关	2：路由 3：采集终端  4：控制终端
	DPACK_PARA_ID_HEARTBEAT = 22,  //  设备的心跳	只自动报告
	DPACK_PARA_ID_BATTERY = 23,  //  设备的电量   0～100：电量百分比
	DPACK_PARA_ID_WORK_STATE = 27,	//	设备的工作状态	 0：正常工作态	1：配置态
	DPACK_PARA_ID_CTRL_IN = 28,  //  控制器检测输入   64位，前32位对应输入的检测位置(最左位对应硬件板上第1个检测位置),后32位对应继电器输出状态(最左位对应硬件板上第1个继电器)
	DPACK_PARA_ID_CTRL_OUT = 29,  //  控制器继电器输出	 32位，对应继电器输出状态(最左位对应硬件板上第1个继电器)
	DPACK_PARA_ID_ZIGBEE_TO_RESET = 151,  //  zigbee_复位	zigbee 复位
	DPACK_PARA_ID_ZIGBEE_TO_DEF = 152,	//	zigbee_恢复出厂设置   zigbee 恢复出厂设置
	DPACK_PARA_ID_ZIGBEE_AUTO_NET = 153,  //  zigbee_自组网功能   1：开启  0：关闭
	DPACK_PARA_ID_ZIGBEE_ALLOW_JOIN = 154,	//	zigbee_允许从机入网   允许的时间
	DPACK_PARA_ID_ZIGBEE_DEL_BY_MAC_ADDR = 155,  //  zigbee_用MAC删除从机	8字节MAC地址
	DPACK_PARA_ID_ZIGBEE_CHILD_INFO = 159,	//	zigbee_查询节点信息   从机数量 MAC地址1 + 网络地址1 + … + MAC地址N + 网络地址N
	DPACK_PARA_ID_ZIGBEE_WORK_STATE = 160,	//	zigbee_查询主机状态   主机： 0：空闲 1：正在检测网络  2：允许从机加入网络
	DPACK_PARA_ID_ZIGBEE_INFO = 161,  //  zigbee_配置信息	out: DEV_INFO | in: PowerLevel+RetryNum+TranTimeout
	DPACK_PARA_ID_G4_TO_RESET = 191,  //  4G_复位	
	DPACK_PARA_ID_G4_TO_DEF = 192,	//	4G_恢复出厂设置   
	DPACK_PARA_ID_G4_STATE_GET = 193,  //  4G_查询状态	 
	DPACK_PARA_ID_G4_IMEI_GET = 194,  //  4G_IMEI	
	DPACK_PARA_ID_G4_RSSI_BER_GET = 195,  //  4G_查询信号强度	
	DPACK_PARA_ID_G4_QMT_OPEN_NET = 196,  //  4G_MQTT_连接网址	 
	DPACK_PARA_ID_G4_QMT_CONN_USER = 197,  //  4G_MQTT_登录用户名	
	DPACK_PARA_ID_G4_QMT_CONN_PWD = 198,  //  4G_MQTT_登录密码	 
	DPACK_PARA_ID_G4_QMT_CLIENT_ID = 199,  //  4G_MQTT_客户端编号	
	DPACK_PARA_ID_G4_QMT_PUBEX_QOS = 200,  //  4G_MQTT_发布信息传递服务质量 	
	DPACK_PARA_ID_G4_QMT_SUB_TOPIC_QOS = 201,  //  4G_MQTT_订阅信息传递服务质量 	
	DPACK_PARA_ID_UART485 = 220,  //  485总线	485总线通信
	DPACK_PARA_ID_ADC1 = 240,  //  ADC通道1   第1路ADC通道
	DPACK_PARA_ID_ADC2 = 241,  //  ADC通道2   第2路ADC通道
	DPACK_PARA_ID_DAC1 = 260,  //  DAC通道1   2路DAC通道
	DPACK_PARA_ID_DAC2 = 261,  //  DAC通道2   2路DAC通道
	DPACK_PARA_ID_CTRL_OUT1_ON_SEC = 401,  //  继电器1输出时长	 第1个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT2_ON_SEC = 402,  //  继电器2输出时长	 第2个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT3_ON_SEC = 403,  //  继电器3输出时长	 第3个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT4_ON_SEC = 404,  //  继电器4输出时长	 第4个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT5_ON_SEC = 405,  //  继电器5输出时长	 第5个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT6_ON_SEC = 406,  //  继电器6输出时长	 第6个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT7_ON_SEC = 407,  //  继电器7输出时长	 第7个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT8_ON_SEC = 408,  //  继电器8输出时长	 第8个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT9_ON_SEC = 409,  //  继电器9输出时长	 第9个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT10_ON_SEC = 410,	//	继电器10输出时长   第10个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT11_ON_SEC = 411,	//	继电器11输出时长   第11个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT12_ON_SEC = 412,	//	继电器12输出时长   第12个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT13_ON_SEC = 413,	//	继电器13输出时长   第13个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT14_ON_SEC = 414,	//	继电器14输出时长   第14个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT15_ON_SEC = 415,	//	继电器15输出时长   第15个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT16_ON_SEC = 416,	//	继电器16输出时长   第16个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT17_ON_SEC = 417,	//	继电器17输出时长   第17个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT18_ON_SEC = 418,	//	继电器18输出时长   第18个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT19_ON_SEC = 419,	//	继电器19输出时长   第19个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT20_ON_SEC = 420,	//	继电器20输出时长   第20个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT21_ON_SEC = 421,	//	继电器21输出时长   第21个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT22_ON_SEC = 422,	//	继电器22输出时长   第22个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT23_ON_SEC = 423,	//	继电器23输出时长   第23个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT24_ON_SEC = 424,	//	继电器24输出时长   第24个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT25_ON_SEC = 425,	//	继电器25输出时长   第25个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT26_ON_SEC = 426,	//	继电器26输出时长   第26个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT27_ON_SEC = 427,	//	继电器27输出时长   第27个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT28_ON_SEC = 428,	//	继电器28输出时长   第28个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT29_ON_SEC = 429,	//	继电器29输出时长   第29个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT30_ON_SEC = 430,	//	继电器30输出时长   第30个输出口开的时长
	DPACK_PARA_ID_CTRL_OUT31_ON_SEC = 431,	//	继电器31输出时长   第31个输出口开的时长




}EN_DPACK_PARA_ID; // 




/*
数据包 格式定义		
------------------------------------------------------
数据包成员名	字节数	解释
------------------------------------------------------
长度				1	数据包的长度。
终端的端口ID		1	产品的端口编号。
终端端口的通信地址	1	例：485地址号。
参数ID				2	数据包的参数编号。
参数值				n	参数的值。
-----------------------------------------------------*/
typedef struct
{
	u8 len;
	u8 portId;
	u8 portAddr;
	u16 paraId;  // 
	u8 *pPara;   // 
}ST_DPACK; 


#define FRAME_DATA_PACK_CONST_ELE_LEN  (5)  // 数据包 中 除参数以外的元素长度

//===================================================================================
//==============txt_frame.h==========================================================
//===================================================================================

/*
内容帧 行为 定义		
----------------------------------------------------------------------------------
值			名						解释
----------------------------------------------------------------------------------
0x01	ACTION_SET				设置值的行为。
0x02	ACTION_GET				获取值的行为。
0x03	ACTION_REPORT_ACK_GET	为响应ACTION_GET而报告值的行为（被动报告）。
0x04	ACTION_REPORT_AUTO		自动报告值的行为（主动报告）。
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
数据帧类型 定义
------------------------------------
值	   类型	       名字
------------------------------------
1	常规数据包	
2	协议数据包	
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
	u8 sid;      // 会话ID
	EN_TXT_FRAME_PACK_TYPE packType;
	u8 *pPack;   // 数据包
	u8 tail;
}ST_TXT_FRAME; 



//===================================================================================
//==============frame.h==========================================================
//===================================================================================
/*
内容帧格式（版本号：0）			
----------------------------------------------------------------------------------
编号	帧成员名	字节数	解释
----------------------------------------------------------------------------------
D1		帧开始		1		值：0xAA。
D2		帧长度		1		帧的总字节数。
D3		帧版本		1		帧格式的版本号。
D4		帧行为		1		帧的操作行为描述。
D5		校验和		1		所有帧数据按无符号数单字节累加，忽略溢出。
D6		目标ID		8		MAC。
D7		会话ID		1		详见相关章节的描述。
D8	    包类型	    1	    1：数据包  2：协议包
D9		    包		n		暂约定 n < 230。
D10		帧结束		1		值：0x88。
----------------------------------------------------------------------------------*/


//-------------  解码 frame--------------------
typedef enum
{
	FRAME_UNPACK_NOT_DEF = 0,
	FRAME_UNPACK_OK = 1,
	FRAME_UNPACK_NG_HEAD,
	FRAME_UNPACK_NG_LEN,
	FRAME_UNPACK_NG_VER,
	FRAME_UNPACK_NG_ACTION, // 5
	FRAME_UNPACK_NG_CHECK,
	FRAME_UNPACK_NG_ID, // 目标ID
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

#define BROADCAST_ADDR  (0xFFFF) // 广播地址


#define FRAME_PACK_LEN_MAX  (222)//(230) // 帧中包的长度  fenghuiwait
#define FRAME_PACK_ELE_LEN  (10)  // 除包以外的元素长度

/*
内容帧格式（版本号：0）			
----------------------------------------------------------------------------------
编号	帧成员名	字节数	解释
----------------------------------------------------------------------------------
D1		帧开始		1		值：0xAA。
D2		帧长度		1		帧的总字节数。
D3		帧版本		1		帧格式的版本号。
D4		帧行为		1		帧的操作行为描述。
D5		校验和		1		所有帧数据按无符号数单字节累加，忽略溢出。
D6		目标ID		8		产品ID。
D7		会话ID		1		详见相关章节的描述。
D8	    包类型	    1	    1：数据包  2：协议包
D9		    包		n		暂约定 n < 230。
D10		帧结束		1		值：0x88。
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
	u8 sid;      // 会话ID
	//EN_TXT_FRAME_PACK_TYPE packType;
	u8 packType;
	u8 pBuf[FRAME_PACK_LEN_MAX + 1];   // 数据包 + 帧结束
}ST_FRAME;







extern ST_G2S   gstG2S;


#endif

#endif


