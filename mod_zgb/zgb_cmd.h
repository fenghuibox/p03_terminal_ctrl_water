/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
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
��ʱ��������Э��������
------------------------------------------------
3 �ֽڣ�Э���־��  1 �ֽ�    N �ֽ�
 DE DF EF           ������     ����
------------------------------------------------*/
extern const u8 zcmdTempHead[];
#define ZCMD_TEMP_HEAD_LEN      (3)
#define ZCMD_TEMP_ID_OFFSET     (3)



//-----------������----------------------------

#define ZCMD_TEMP_HEAD_ID_LQI                (0xDA) // ��ѯ�ڵ���ź�ǿ������
#define ZCMD_TEMP_HEAD_ID_LQI_LEN               (6)
#define ZCMD_TEMP_HEAD_ID_LQI_RST_LEN           (7)


#define ZCMD_TEMP_HEAD_ID_SLEEP              (0xD8) // ������������
#define ZCMD_TEMP_HEAD_ID_SLEEP_LEN             (5)
#define ZCMD_TEMP_HEAD_ID_SLEEP_RST_LEN         (0) // **








/*----------------------------------------------
���ò�������Э��������
------------------------------------------------
3 �ֽڣ�Э���־��   1 �ֽ�     N �ֽ�      1 �ֽڣ�֡β��
    AB BC CD       �����ʶ��   ����ʵ��      AA
------------------------------------------------*/
extern const u8 zcmdForeverHead[];
#define ZCMD_FOREVER_HEAD_LEN       (3)

#define ZCMD_FOREVER_ID_OFFSET      (3) // ������ƫ����
#define ZCMD_FOREVER_PARA1_OFFSET   (ZCMD_FOREVER_ID_OFFSET + 1)
#define ZCMD_FOREVER_PARA2_OFFSET   (ZCMD_FOREVER_ID_OFFSET + 2)
#define ZCMD_FOREVER_PARA3_OFFSET   (ZCMD_FOREVER_ID_OFFSET + 3)
#define ZCMD_FOREVER_PARA4_OFFSET   (ZCMD_FOREVER_ID_OFFSET + 4)


#define ZCMD_FOREVER_TAIL_BYTE  (0xAA)
#define ZCMD_FOREVER_TAIL_LEN   (1)


//-----------������----------------------------------------------------------
#define ZCMD_FOREVER_HEAD_ID_DEV_INFO_GET          (0xD1) // ��ȡ��������	
#define ZCMD_FOREVER_HEAD_ID_DEV_INFO_GET_LEN       (5)
#define ZCMD_FOREVER_HEAD_ID_DEV_INFO_GET_RST_LEN   (74)
#define ZCMD_FOREVER_HEAD_ID_DEV_INFO_GET_PARA1_OFFSET    ( ZCMD_FOREVER_PARA1_OFFSET ) //


#define ZCMD_FOREVER_HEAD_ID_DEV_INFO_SET          (0xD6) //���ñ�������	
#define ZCMD_FOREVER_HEAD_ID_DEV_INFO_SET_LEN       (72)
#define ZCMD_FOREVER_HEAD_ID_DEV_INFO_SET_RST_LEN   (7)
#define ZCMD_FOREVER_HEAD_ID_DEV_INFO_SET_NETADDR_OFFSET  ( ZCMD_FOREVER_PARA1_OFFSET )
#define ZCMD_FOREVER_HEAD_ID_DEV_INFO_SET_DEV_INFO_OFFSET ( ZCMD_FOREVER_PARA3_OFFSET )


#define ZCMD_FOREVER_HEAD_ID_REBOOT                    (0xDA) // 
#define ZCMD_FOREVER_HEAD_ID_REBOOT_LEN                 (9)
#define ZCMD_FOREVER_HEAD_ID_REBOOT_RST_LEN             (0) // **



#define ZCMD_FOREVER_HEAD_ID_DEF                    (0xDA) // �ָ�������������
#define ZCMD_FOREVER_HEAD_ID_DEF_LEN                 (9)
#define ZCMD_FOREVER_HEAD_ID_DEF_RST_LEN             (9)





#define ZCMD_FOREVER_HEAD_ID_AUTO_NET                (0xE5) // ������������������
#define ZCMD_FOREVER_HEAD_ID_AUTO_NET_LEN               (7)
#define ZCMD_FOREVER_HEAD_ID_AUTO_NET_RST_LEN           (7)



#define ZCMD_FOREVER_HEAD_ID_AUTO_NET_PARA1_OFFSET    ( ZCMD_FOREVER_PARA1_OFFSET ) // OPEN OR CLOSE
#define ZCMD_FOREVER_HEAD_ID_AUTO_NET_PARA2_OFFSET    ( ZCMD_FOREVER_PARA2_OFFSET) // MASTER OR S


#define ZCMD_FOREVER_HEAD_ID_WORK_STATE                (0xE8) // ��ѯ���ӻ�״̬
#define ZCMD_FOREVER_HEAD_ID_WORK_STATE_LEN               (5)
#define ZCMD_FOREVER_HEAD_ID_WORK_STATE_RST_LEN           (6)









/*
------------------------------------------------------------------------
��Ϣ        ƫ�Ƶ�ַ  ����      ��ע                Ĭ��ֵ
------------------------------------------------------------------------
DevName           0    16    �豸����               ZLG Device
DevPwd           16    16    �豸����               88888
DevMode          32     1    �豸���� ��            �ն��豸
Chan             33     1    ͨ����                 0x19 ( CH 25 )
PanID            34     2    ���� ID (PanID)        0x1001
MyAddr           36     2    ���������ַ           0x2001
MyIEEE           38     8    ���������ַ(MAC)      �����޸�
DstAddr          46     2    Ŀ�������ַ           0x2002
DstIEEE          48     8    Ŀ�������ַ (����)    00 00 00 00 00 00 00 00
Reserve          56     1    ����                    0x00
PowerLevel       57     1    ���书�ʢ�              0x03
RetryNum         58     1    �����������Դ���        0x1E
TranTimeout      59     1    �����������Լ��(ms)    0x0A
Serial_Rate      60     1    ���ڲ����ʢ�            0x06
Serial_DataB     61     1    ��������λ��            0x08
Serial_StopB     62     1    ����ֹͣλ��            0x01
Serial_ParityB   63     1    ����У��λ��            0x00
Reserve          64     1    ����ģʽ��              0x00
------------------------------------------------------------------------
��:�豸���ͷ�Ϊ�ն��豸��·���豸��Ĭ��Ϊ�ն��豸;
��:���ù����з��书�ʷ�Ϊ 4 ����λ 0x00��-32dBm��0x01��-20.5dBm��0x02��-9dBm��0x03��+2.5dBm��
��:���ڲ����� 0x01��0x07����Ӧ�����ʣ�2400��4800��9600��19200��38400��57600��115200��
��:��������λ��5��8������λ�������Ϊ 5��6��7 λ���򲻿��Ի�ȡ������Ϣ��
��:����ֹͣλ��1��2��
��:����У��λ��0x00 ��ʾ��У�顢0x01 ��ʾ��У�顢0x02 ��ʾżУ�飻
��:����ģʽ��Ϊ���� 0x00 ��ʾ����ģʽ��0x01 ��ʾ�㲥ģʽ��
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
�������ص�״ֵ̬
-------------------------
00 ��������
01 �������ڼ������
02 ��������ӻ���������
-------------------------
�ӻ����ص�״ֵ̬
-------------------------
00 �ӻ����ڼ�������
01 �ӻ��Ѽ�������
02 �ӻ����˳�����
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

