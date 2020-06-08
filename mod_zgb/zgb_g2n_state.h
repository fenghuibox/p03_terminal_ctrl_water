/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __ZGB_G2N_STATE_H
#define __ZGB_G2N_STATE_H

// g2n: gateway to node 

#include "com_typedef.h"



typedef enum 
{
	UART_ZGB_G2N_STATE_NOT_DEF = 0, 
		
	UART_ZGB_G2N_STATE_IDLE,  
	
	UART_ZGB_G2N_STATE_TX_TXT, // ����̬
	
	UART_ZGB_G2N_STATE_WAIT_RX_TXT, // �ȴ���������̬
	
	UART_ZGB_G2N_STATE_TX_ACK,     // Ӧ��̬
	
}EN_UART_ZGB_G2N_STATE; // 


typedef enum 
{
	UART_ZGB_G2N_E_NOT_DEF = 0, 
	UART_ZGB_G2N_E_TX_TXT, 
	UART_ZGB_G2N_E_TX_TXT_TIMEOUT,
	UART_ZGB_G2N_E_TX_ACK,
	
	UART_ZGB_G2N_E_RX_ACK,
	UART_ZGB_G2N_E_RX_TXT,
	UART_ZGB_G2N_E_RX_TXT_TIMEOUT,
	
}EN_UART_ZGB_G2N_EVENT; // 


extern u8 modUartZgbG2NstateIsCanTx( void );

extern u8 modUartZgbG2NstateIsTxAck( void );


extern u8 modUartZgbG2NstateIsIdle( void );


extern void modUartZgbG2NstateOnEvent( EN_UART_ZGB_G2N_EVENT e );


extern void modUartZgbG2NstatePollCB( void );


extern void zgbG2NstateInit( void );


#endif

