/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef ___DBG_CMD_UART_PASS_H
#define ___DBG_CMD_UART_PASS_H


#include "com_typedef.h"




extern const char strCmdUartPassHead[];

#define   DEBUG_UART_PASS_HEAD_LEN          (8)

//--------------------------------------------------

typedef enum 
{
	DEBUG_UART_PASS_NOT_DEF = 0,

	DEBUG_UART_PASS_ZIGBEE, // 2

}EN_DEBUG_UART_PASS_PORT;






extern u8 debugPassIsZigbee( void );






//str = zigbee1 / port011 ......
extern u8 debugCmdUartPass( u8 *str,  u8 len  );


extern void debugCmdUartPassInit( void );



#endif

