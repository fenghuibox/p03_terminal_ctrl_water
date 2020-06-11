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
	u8 sleep_sec:1;   //  8 设备单次休眠时间
	u8 work_sec:1;	 //  9 设备单次工作时间
	u8 ver:1;	//	10 设备的版本
	u8 dev_type:1;	 //  11 设备的类型
	u8 heartbeat:1;   //  12 设备的心跳
	u8 battery:1;	//	13 设备的电量
	u8 ctrl_mode:1;   //  14 控制模式 
	u8 cmd_ctrl:1;	 //  15 命令延时控制
	u8 open_sec:1;	 //  16 开启时长
	u8 period_ctrl:1;	//	17 周期控制
	u8 ctrl_pack:1;   //  18 控制信息包
	u8 zigbee_to_reset:1;	//	19 zigbee_复位
	u8 zigbee_to_def:1;   //  20 zigbee_恢复出厂
	u8 zigbee_auto_net:1;	//	21 zigbee_自组网功能
	u8 zigbee_state:1;	 //  22 zigbee_查询状态
	u8 zigbee_info:1;	//	23 zigbee_配置信息
	u8 uart485:1;	//	24 485总线



	//--------end repace----------------------------------------------------------


	#if 0
	//--------error------------------
	u8 err_dev:1;	    //	
	//u8 err_zigbee:1;	//	
	//u8 err_sensor:1;	//	
	//u8 err_ptl:1;	    //	
	//u8 err_ptl_cfg:1;	//	
	#endif
	
}ST_N2S;




typedef enum 
{
	N2S_SEND_CID_NULL = 0,
	N2S_SEND_CID_FRAME_PARSER_RSP,  // 1
	N2S_SEND_CID_FRAME_EXE_RSP,	// 2

	//--------------------------------------
	N2S_SEND_CID_CONFIG_VER,	// 3
	N2S_SEND_CID_DEF,	// 4
	N2S_SEND_CID_AES_SWITCH,	// 5
	N2S_SEND_CID_AES_KEY,	// 6
	N2S_SEND_CID_REBOOT,	// 7
	N2S_SEND_CID_SLEEP_SEC, // 8
	N2S_SEND_CID_WORK_SEC,	// 9
	N2S_SEND_CID_VER,	// 10
	N2S_SEND_CID_DEV_TYPE,	// 11
	N2S_SEND_CID_HEARTBEAT, // 12
	N2S_SEND_CID_BATTERY,	// 13
	N2S_SEND_CID_CTRL_MODE, // 14
	N2S_SEND_CID_CMD_CTRL,	// 15
	N2S_SEND_CID_OPEN_SEC,	// 16
	N2S_SEND_CID_PERIOD_CTRL,	// 17
	N2S_SEND_CID_CTRL_PACK, // 18
	N2S_SEND_CID_ZIGBEE_TO_RESET,	// 19
	N2S_SEND_CID_ZIGBEE_TO_DEF, // 20
	N2S_SEND_CID_ZIGBEE_AUTO_NET,	// 21
	N2S_SEND_CID_ZIGBEE_STATE,	// 22
	N2S_SEND_CID_ZIGBEE_INFO,	// 23
	N2S_SEND_CID_UART485,	// 24


	
}EN_N2S_SEND_CMD_ID; // 







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
	DPACK_PARA_ID_DEF = 2,	//	恢复出厂设置   
	DPACK_PARA_ID_AES_SWITCH = 3,  //  加密开关   设备发送的数据是否进行加密
	DPACK_PARA_ID_AES_KEY = 4,	//	加密密钥   加密密钥
	DPACK_PARA_ID_REBOOT = 5,  //  设备启动   set:设备启动	report:设备启动时主动报告此信息
	DPACK_PARA_ID_SLEEP_SEC = 18,  //  设备单次休眠时间   无符号数，单位秒，默认值10， 0:不休眠, 最大值：68399（24小时-1）
	DPACK_PARA_ID_WORK_SEC = 19,  //  设备单次工作时间	 无符号数，默认值5， 0:空闲时立即休眠
	DPACK_PARA_ID_VER = 20,  //  设备的版本   HHHH WWWW
	DPACK_PARA_ID_DEV_TYPE = 21,  //  设备的类型   1：网关	2：路由 3：采集终端  4：控制终端
	DPACK_PARA_ID_HEARTBEAT = 22,  //  设备的心跳	只自动报告
	DPACK_PARA_ID_BATTERY = 23,  //  设备的电量   0～100：电量百分比
	DPACK_PARA_ID_CTRL_MODE = 38,  //  控制模式    0：命令控制模式	1：周期控制模式
	DPACK_PARA_ID_CMD_CTRL = 39,  //  命令控制	 1：开启  0：关闭
	DPACK_PARA_ID_OPEN_SEC = 40,  //  开启时长	 开水阀时间,要求是休眠时间的倍数(单位:秒)
	DPACK_PARA_ID_PERIOD_CTRL = 41,  //  周期控制	前4字节：开水阀时间,后4字节：关水阀时间(单位:分钟)(0:0, 0:n 常关, n:0 常开 )
	DPACK_PARA_ID_CTRL_PACK = 42,  //  控制信息包	设备单次工作时间4Byte|设备单次休眠时间4Byte|命令控制1Byte|开启时长4Byte|是否重启记时1Byte
	DPACK_PARA_ID_ZIGBEE_TO_RESET = 151,  //  zigbee_复位	zigbee 复位
	DPACK_PARA_ID_ZIGBEE_TO_DEF = 152,	//	zigbee_恢复出厂   zigbee 恢复出厂设置
	DPACK_PARA_ID_ZIGBEE_AUTO_NET = 153,  //  zigbee_自组网功能   1：开启  0：关闭
	DPACK_PARA_ID_ZIGBEE_STATE = 160,  //  zigbee_查询状态	 0：正在加入网络 1：已加入网络	2：已退出网络
	DPACK_PARA_ID_ZIGBEE_INFO = 161,  //  zigbee_配置信息	out: DEV_INFO | in: PowerLevel+RetryNum+TranTimeout
	DPACK_PARA_ID_UART485 = 220,  //  485总线	485总线通信

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







extern ST_N2S   gstN2S;


#endif

#endif


