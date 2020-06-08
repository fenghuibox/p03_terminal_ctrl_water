/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __ZGB_UNPACK_H
#define __ZGB_UNPACK_H


#include "com_typedef.h"



typedef enum 
{
	UART_ZIGBEE_UNPACK_RST_NOT_DEF = 0,
	UART_ZIGBEE_UNPACK_RST_ERR,
	UART_ZIGBEE_UNPACK_RST_PASS_RSP,
	UART_ZIGBEE_UNPACK_RST_PASS_TXT,
	UART_ZIGBEE_UNPACK_RST_DATA_FRAME,
	UART_ZIGBEE_UNPACK_RST_PROTOCOL_FRAME,
	UART_ZIGBEE_UNPACK_RST_RSP_FRAME,
	UART_ZIGBEE_UNPACK_RST_NEW_MAC,

}EN_UART_ZIGBEE_UNPACK_RST; // 



extern u8 modUartZgbRxUnpackRstIsRsp( void );

extern u8 modUartZgbRxUnpackRstIsDataFrame( void );

extern u8 modUartZgbRxUnpackRstIsProtocolFrame( void );


extern u8 modUartZgbRxUnpackRstIsPassTxt( void );

extern u8 modUartZgbRxUnpackRstIsPass( void );


extern u8 modUartZgbRxUnpackRstIsNotPass( void );


/*
����ֵ: TURE ������Ч  FALSE ������Ч
*/
extern u8 modUartZgbUnpack( u8 *pFrame, u8 len );


extern void zgbUnpackInit( void );


#endif

