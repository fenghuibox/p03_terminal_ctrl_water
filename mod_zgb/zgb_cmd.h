/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __ZGB_CMD_H
#define __ZGB_CMD_H


#include "com_typedef.h"


#include "zgb_mac.h"
//#include "f_frame_comm.h"



#define Z_ST_DEV_INFO (65)


/*----------------------------------------------
临时参数配置协议与命令
------------------------------------------------
3 字节（协议标志）  1 字节    N 字节
 DE DF EF           功能码     参数
------------------------------------------------*/
extern const u8 zcmdTempHead[];
#define ZCMD_TEMP_HEAD_LEN      (3)
#define ZCMD_TEMP_ID_OFFSET     (3)



//-----------功能码----------------------------

#define ZCMD_TEMP_HEAD_ID_LQI                (0xDA) // 查询节点的信号强度命令
#define ZCMD_TEMP_HEAD_ID_LQI_LEN               (6)
#define ZCMD_TEMP_HEAD_ID_LQI_RST_LEN           (7)


#define ZCMD_TEMP_HEAD_ID_SLEEP              (0xD8) // 进入休眠命令
#define ZCMD_TEMP_HEAD_ID_SLEEP_LEN             (5)
#define ZCMD_TEMP_HEAD_ID_SLEEP_RST_LEN         (0) // **








/*----------------------------------------------
永久参数配置协议与命令
------------------------------------------------
3 字节（协议标志）   1 字节     N 字节      1 字节（帧尾）
    AB BC CD       命令标识符   命令实体      AA
------------------------------------------------*/
extern const u8 zcmdForeverHead[];
#define ZCMD_FOREVER_HEAD_LEN       (3)

#define ZCMD_FOREVER_ID_OFFSET      (3) // 功能码偏移量
#define ZCMD_FOREVER_PARA1_OFFSET   (ZCMD_FOREVER_ID_OFFSET + 1)
#define ZCMD_FOREVER_PARA2_OFFSET   (ZCMD_FOREVER_ID_OFFSET + 2)
#define ZCMD_FOREVER_PARA3_OFFSET   (ZCMD_FOREVER_ID_OFFSET + 3)
#define ZCMD_FOREVER_PARA4_OFFSET   (ZCMD_FOREVER_ID_OFFSET + 4)


#define ZCMD_FOREVER_TAIL_BYTE  (0xAA)
#define ZCMD_FOREVER_TAIL_LEN   (1)


//-----------功能码----------------------------------------------------------
#define ZCMD_FOREVER_HEAD_ID_DEV_INFO_GET          (0xD1) // 读取本地配置	
#define ZCMD_FOREVER_HEAD_ID_DEV_INFO_GET_LEN       (5)
#define ZCMD_FOREVER_HEAD_ID_DEV_INFO_GET_RST_LEN   (74)
#define ZCMD_FOREVER_HEAD_ID_DEV_INFO_GET_PARA1_OFFSET    ( ZCMD_FOREVER_PARA1_OFFSET ) //


#define ZCMD_FOREVER_HEAD_ID_DEV_INFO_SET          (0xD6) //设置本地配置	
#define ZCMD_FOREVER_HEAD_ID_DEV_INFO_SET_LEN       (72)
#define ZCMD_FOREVER_HEAD_ID_DEV_INFO_SET_RST_LEN   (7)
#define ZCMD_FOREVER_HEAD_ID_DEV_INFO_SET_NETADDR_OFFSET  ( ZCMD_FOREVER_PARA1_OFFSET )
#define ZCMD_FOREVER_HEAD_ID_DEV_INFO_SET_DEV_INFO_OFFSET ( ZCMD_FOREVER_PARA3_OFFSET )


#define ZCMD_FOREVER_HEAD_ID_REBOOT                    (0xDA) // 
#define ZCMD_FOREVER_HEAD_ID_REBOOT_LEN                 (9)
#define ZCMD_FOREVER_HEAD_ID_REBOOT_RST_LEN             (0) // **



#define ZCMD_FOREVER_HEAD_ID_DEF                    (0xDA) // 恢复出厂设置命令
#define ZCMD_FOREVER_HEAD_ID_DEF_LEN                 (9)
#define ZCMD_FOREVER_HEAD_ID_DEF_RST_LEN             (9)





#define ZCMD_FOREVER_HEAD_ID_AUTO_NET                (0xE5) // 启用自组网功能命令
#define ZCMD_FOREVER_HEAD_ID_AUTO_NET_LEN               (7)
#define ZCMD_FOREVER_HEAD_ID_AUTO_NET_RST_LEN           (7)



#define ZCMD_FOREVER_HEAD_ID_AUTO_NET_PARA1_OFFSET    ( ZCMD_FOREVER_PARA1_OFFSET ) // OPEN OR CLOSE
#define ZCMD_FOREVER_HEAD_ID_AUTO_NET_PARA2_OFFSET    ( ZCMD_FOREVER_PARA2_OFFSET) // MASTER OR S


#define ZCMD_FOREVER_HEAD_ID_WORK_STATE                (0xE8) // 查询主从机状态
#define ZCMD_FOREVER_HEAD_ID_WORK_STATE_LEN               (5)
#define ZCMD_FOREVER_HEAD_ID_WORK_STATE_RST_LEN           (6)









/*
------------------------------------------------------------------------
信息        偏移地址  长度      备注                默认值
------------------------------------------------------------------------
DevName           0    16    设备名称               ZLG Device
DevPwd           16    16    设备密码               88888
DevMode          32     1    设备类型 ①            终端设备
Chan             33     1    通道号                 0x19 ( CH 25 )
PanID            34     2    网络 ID (PanID)        0x1001
MyAddr           36     2    本地网络地址           0x2001
MyIEEE           38     8    本地物理地址(MAC)      不可修改
DstAddr          46     2    目标网络地址           0x2002
DstIEEE          48     8    目标物理地址 (保留)    00 00 00 00 00 00 00 00
Reserve          56     1    保留                    0x00
PowerLevel       57     1    发射功率②              0x03
RetryNum         58     1    发送数据重试次数        0x1E
TranTimeout      59     1    发送数据重试间隔(ms)    0x0A
Serial_Rate      60     1    串口波特率③            0x06
Serial_DataB     61     1    串口数据位④            0x08
Serial_StopB     62     1    串口停止位⑤            0x01
Serial_ParityB   63     1    串口校验位⑥            0x00
Reserve          64     1    发送模式⑦              0x00
------------------------------------------------------------------------
①:设备类型分为终端设备与路由设备，默认为终端设备;
②:配置工具中发射功率分为 4 个档位 0x00：-32dBm、0x01：-20.5dBm、0x02：-9dBm、0x03：+2.5dBm；
③:串口波特率 0x01～0x07，对应波特率：2400、4800、9600、19200、38400、57600、115200；
④:串口数据位：5～8，数据位如果设置为 5、6、7 位，则不可以获取配置信息；
⑤:串口停止位：1～2；
⑥:串口校验位：0x00 表示无校验、0x01 表示奇校验、0x02 表示偶校验；
⑦:发送模式分为两种 0x00 表示单播模式、0x01 表示广播模式。
------------------------------------------------------------------------*/

typedef struct
{
	 u8 DevName[16];
	 u8 DevPwd[16];
	 u8 DevMode;
	 u8 Chan;
	u16 PanID;
	u16 MyAddr;
	 u8 MyIEEE[8];
    u16 DstAddr;
	 u8 DstIEEE[8];
	 u8 Reserve;
	 u8 PowerLevel;
	 u8 RetryNum;
	 u8 TranTimeout;
	 u8 Serial_Rate;
	 u8 Serial_DataB;
	 u8 Serial_StopB;
	 u8 Serial_ParityB;
	 u8 Reserve1;
}ST_ZIGBEE_DEV_INFO; 


typedef struct
{
	 //u8 DevName[16];
	 u8 PowerLevel;
	 u8 RetryNum;
	 u8 TranTimeout;
}ST_ZIGBEE_DEV_INFO_RF; 


/*
主机返回的状态值
-------------------------
00 主机空闲
01 主机正在检测网络
02 主机允许从机加入网络
-------------------------
从机返回的状态值
-------------------------
00 从机正在加入网络
01 从机已加入网络
02 从机已退出网络
*/
typedef enum
{
	ZIGBEE_WORK_STATE_IDLE = 0,
	ZIGBEE_WORK_STATE_CHECK  = 1,
	ZIGBEE_WORK_STATE_ALLOW_JOIN = 2,
	ZIGBEE_WORK_STATE_NOT_DEF  = 3,
}EN_ZIGBEE_WORK_STATE;


//============== step 2 =============================================
extern int zcmdDevInfoGet( void );

extern int zcmdDevInfoSet( ST_ZIGBEE_DEV_INFO_RF *pstSet );

extern int zcmdReboot( void );

extern int zcmdDef( void );


extern int zcmdAutoNet( u8 isOpen );



extern int zcmdWorkStateGet( void );

extern int zcmdLqiGet( void );

extern int zcmdSleep( void );


extern int zcmdRx( u8 *pBuf, u32 len );



//==========================================================

extern int zcmdTxCB( void );

extern void zgbCmdInit( void );




//============ step 5 ==============================================
extern u16 zigbeeRebootIsOk( void );

extern u16 zigbeeTargetAddrGet( void );

extern u16 zigbeeMyAddrGet( void );

extern u8 zigbeeMyMacGet( u8 *pMac );



extern u8 zigbeeWorkStateGet( EN_ZIGBEE_WORK_STATE *pState );



extern u8 zigbeeAutoNetGet( void );



extern u8 zigbeeLqiGet( void );

extern void zigbeeInfoRfGet( ST_ZIGBEE_DEV_INFO_RF *pstInfoRf );



#endif

