/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __DEV_STATE_H
#define __DEV_STATE_H





#include "com_includes.h"








#define DEV_WAIT_SEC_IDLE      (10 * 5 ) // 空闲等待时间
#define DEV_WAIT_SEC_WORK      (5)       // 工作 到 空闲 的过度时间
#define DEV_WAIT_SEC_CFG       (60 * 10)  // 配置等待时间

#define DEV_WAIT_SEC_WARNING   (10)      // 警告指示时间
#define DEV_WAIT_SEC_ERR_HINT  (60 * 10) // 
#define DEV_WAIT_SEC_REBOOT    (5)       // 重启指示时间



#define DEV_ERR_BIT_ZIGBEE         (0x00000001) // 
#define DEV_ERR_BIT_MASTER         (0x00000010) // 
//#define DEV_ERR_BIT_PTL          (0x00000002) 
//#define DEV_ERR_BIT_CFG          (0x00000004) // 3 配置错误
//#define DEV_ERR_BIT_PORT         (0x00000008) // 4 端口无响应 等
//#define DEV_ERR_BIT_TEMP         (0x00000010) // 5 过温
//#define DEV_ERR_BIT_MEM       (0x00000020)    // 1 内存出错
//#define DEV_ERR_BIT_PTL       (0x00000040)    // 2 接收的协议错误








typedef enum 
{
	DEV_STATE_NOT_DEF = 0,

	DEV_STATE_INIT, // 1
	DEV_STATE_IDLE, // 2
	DEV_STATE_WORK, // 3
	
	DEV_STATE_CFG,    // 配置态
	DEV_STATE_UART_PASS,    // debug uart 透传态
	
	DEV_STATE_SLEEP,  

	//-------------------------------
	DEV_STATE_WARNING = 50,

	DEV_STATE_WARNING_PTL, 	 // 
	DEV_STATE_WARNING_CFG, 	 // 
	DEV_STATE_WARNING_PORT,	 // 

	//-------------------------------
	DEV_STATE_ERR = 80,
	DEV_STATE_ERR_HINT,
	DEV_STATE_ERR_HINT_ZIGBEE, // ziggee模块 或 网络 错误
	DEV_STATE_ERR_HINT_MASTER, // 主机错误  无应答等
		
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

	
	DEV_EVENT_IDLE_START, //
	DEV_EVENT_IDLE_END,   //

	
	DEV_EVENT_WORK_START, // 
	DEV_EVENT_WORK_END,   // 
	

	DEV_EVENT_UART_PASS_START, // 
	DEV_EVENT_UART_PASS_END,   // 
	
	DEV_EVENT_CFG_START, // 
	DEV_EVENT_CFG_END,   // 

		
	DEV_EVENT_SLEEP_START, // 
	DEV_EVENT_SLEEP_END,   // 

	DEV_EVENT_NET_OK, // 
	DEV_EVENT_NET_NG,  // 

	DEV_EVENT_CMD_REBOOT,


   //-----------------------------------
	DEV_EVENT_WARNING = 51,
	DEV_EVENT_WARNING_PTL_ERR,
	DEV_EVENT_WARNING_CFG_ERR,
	DEV_EVENT_WARNING_PORT_ERR,

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
	DEV_EVENT_ERR_STOP_TEMP_HIGH,          // 过温 
	
    
	//-------------------------------------------
	DEV_EVENT_ERR_TO_OK = 120,
	DEV_EVENT_T_TO_OK,		               // 105 过温 恢复正常
	
	DEV_EVENT_ZIGBEE_STATE_TO_OK,
	DEV_EVENT_MASTER_STATE_TO_OK,

}EN_DEV_EVENT;

extern u8 devErrIsHaveZigbee( void );
extern u8 devErrIsHaveMaster( void );

extern EN_DEV_STATE devStateGet( void );


extern u8 devStateIsIdle( void );
extern u8 devStateIsWork( void );
extern u8 devStateIsUartPass( void );

extern u8 devStateIsNg( void );

extern u8 devStateIsZigbeeErr( void );



extern u8 devStateIsMasterErr( void );



extern void devOnEvent( EN_DEV_EVENT e, void *data);

extern void devStateInit( void );

















#endif

