/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __DEV_STATE_H
#define __DEV_STATE_H





#include "com_includes.h"


#ifdef DEV_DEBUG_ING

#define DEV_WAIT_SEC_HEARTBEAT         (  8 * 1 )       // ����״̬�� ����ʱ�����������ʱ�� ��
#define DEV_WAIT_SEC_DEBUG_MIN         ( 20 * 1 )       // ������С������
#define DEV_WAIT_SEC_POWER_ON          ( 30 * 1 )       // �ϵ繤��3����

#else

#define DEV_WAIT_SEC_HEARTBEAT         (  8 * 1 )       // ����״̬�� ����ʱ�����������ʱ�� ��
#define DEV_WAIT_SEC_DEBUG_MIN         ( 60 * 1 )       // ������С������
#define DEV_WAIT_SEC_POWER_ON          ( 60 * 5 )       // �ϵ繤��3����


#endif





#define DEV_WAIT_SEC_READ_CTRL_INFO           (3)       // ���� �� ���� �Ĺ���ʱ��
#define DEV_WAIT_SEC_UART_PASS         ( 60 * 5 )       // 


#define DEV_WAIT_SEC_IDLE      (10 * 5 ) // ���еȴ�ʱ��
#define DEV_WAIT_SEC_CFG       (60 * 10)  // ���õȴ�ʱ��

#define DEV_WAIT_SEC_WARNING   (10)      // ����ָʾʱ��
#define DEV_WAIT_SEC_ERR_HINT  (10) // 
#define DEV_WAIT_SEC_REBOOT    (5)       // ����ָʾʱ��



#define DEV_ERR_BIT_ZIGBEE         (0x00000001) // 
#define DEV_ERR_BIT_MASTER         (0x00000010) // 
//#define DEV_ERR_BIT_PTL          (0x00000002) 
//#define DEV_ERR_BIT_CFG          (0x00000004) // 3 ���ô���
//#define DEV_ERR_BIT_PORT         (0x00000008) // 4 �˿�����Ӧ ��
//#define DEV_ERR_BIT_TEMP         (0x00000010) // 5 ����
//#define DEV_ERR_BIT_MEM       (0x00000020)    // 1 �ڴ����
//#define DEV_ERR_BIT_PTL       (0x00000040)    // 2 ���յ�Э�����








typedef enum 
{
	DEV_STATE_NOT_DEF = 0,

	DEV_STATE_INIT,            // 1	
	DEV_STATE_DBG,             // 2 ����̬
	DEV_STATE_READ_CTRL_INFO,  // 3 ��ȡ������Ϣ̬
	DEV_STATE_SLEEP,           // 4 ����̬
	DEV_STATE_UART_PASS,       // 5 debug uart ͸��̬

	//-------------------------------
	DEV_STATE_WARNING = 50,

	//-------------------------------
	DEV_STATE_ERR = 80,
	DEV_STATE_ERR_HINT,
	DEV_STATE_ERR_HINT_ZIGBEE, // ziggeeģ�� �� ���� ����
	DEV_STATE_ERR_HINT_MASTER, // ��������  ��Ӧ���
		
	DEV_STATE_ERR_REBOOT = 91,
	DEV_STATE_ERR_REBOOT_MEM, 	 // 

	DEV_STATE_ERR_STOP  = 100,
	DEV_STATE_ERR_STOP_TEMP, 	 // 

}EN_DEV_STATE;



typedef enum 
{
	DEV_EVENT_NOT_DEF = 0,
		
	DEV_EVENT_INIT_START, // 1
	DEV_EVENT_INIT_END,   // 2
	
	DEV_EVENT_DBG_START, // 
	DEV_EVENT_DBG_END,   // 

	DEV_EVENT_READ_CTRL_INFO_START, // 
	DEV_EVENT_READ_CTRL_INFO_END,   // 

	DEV_EVENT_UART_PASS_START, // 
	DEV_EVENT_UART_PASS_END,   // 
	
		
	DEV_EVENT_SLEEP_START, // 
	DEV_EVENT_SLEEP_END,   // 


	DEV_EVENT_CMD_REBOOT,
	DEV_EVENT_ERR_TIMEOUT,
	DEV_EVENT_DBG_TIMEOUT,
	DEV_EVENT_UARTPASS_TIMEOUT,
	
   //-----------------------------------
	DEV_EVENT_WARNING = 51,
	//DEV_EVENT_WARNING_PTL_ERR,
	//DEV_EVENT_WARNING_CFG_ERR,
	//DEV_EVENT_WARNING_PORT_ERR,

	//-------------------------------------------
	DEV_EVENT_ERR = 70,
	DEV_EVENT_ERR_HINT = 71,
	DEV_EVENT_ERR_HINT_ZIGBEE_STATE_NG,
	DEV_EVENT_ERR_HINT_MASTER_STATE_NG,
	

	//-------------------------------------------
	DEV_EVENT_ERR_REBOOT = 81,
	DEV_EVENT_ERR_REBOOT_MEM,

	
	//-------------------------------------------
	DEV_EVENT_ERR_STOP = 100,
	DEV_EVENT_ERR_STOP_TEMP_HIGH,          // ���� 
	
    
	//-------------------------------------------
	DEV_EVENT_ERR_TO_OK = 120,
	DEV_EVENT_T_TO_OK,		               // 105 ���� �ָ�����
	
	DEV_EVENT_ZIGBEE_STATE_TO_OK,
	DEV_EVENT_MASTER_STATE_TO_OK,

}EN_DEV_EVENT;


extern void devHeartbeatUpdate( void );


extern u8 devErrIsHaveZigbee( void );
extern u8 devErrIsHaveMaster( void );

extern EN_DEV_STATE devStateGet( void );


extern u8 devStateIsNormal( void );

extern u8 devStateIsDbg( void );
extern u8 devStateIsReadCtrlInfo( void );
extern u8 devStateIsUartPass( void );

extern u8 devStateIsNg( void );

extern u8 devStateIsZigbeeErr( void );



extern u8 devStateIsMasterErr( void );



extern void devOnEvent( EN_DEV_EVENT e, void *data);

extern void devStateInit( void );




extern void devDebugCntToEnd( void );













#endif

