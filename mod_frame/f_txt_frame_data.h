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

#ifndef __F_TXT_FRAME_DATA_H
#define __F_TXT_FRAME_DATA_H


#include "com_typedef.h"

#include "f_frame_comm.h"

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



//------------------------------------------------------
#define  DPACK_ELE_LEN_LEN        (1)
#define  DPACK_ELE_LEN_PORT_ID    (1)
#define  DPACK_ELE_LEN_PORT_ADDR  (1)
#define  DPACK_ELE_LEN_PARA_ID    (2)

//------------------------------------------------------
#define DPACK_LEN_CONST_ELE     (DPACK_ELE_LEN_LEN + DPACK_ELE_LEN_PORT_ID + DPACK_ELE_LEN_PORT_ADDR + DPACK_ELE_LEN_PARA_ID)
#define DPACK_LEN_MIN           DPACK_LEN_CONST_ELE
#define DPACK_LEN_MAX           (230)

//------------------------------------------------------
#define DPACK_OFFSET_LEN          (0)
#define DPACK_OFFSET_PORT_ID      (DPACK_OFFSET_LEN       + DPACK_ELE_LEN_LEN)
#define DPACK_OFFSET_PORT_ADDR    (DPACK_OFFSET_PORT_ID   + DPACK_ELE_LEN_PORT_ID)
#define DPACK_OFFSET_PARA_ID_1    (DPACK_OFFSET_PORT_ADDR + DPACK_ELE_LEN_PORT_ADDR)
#define DPACK_OFFSET_PARA_ID_2    (DPACK_OFFSET_PARA_ID_1 + 1)
#define DPACK_OFFSET_PARA         (DPACK_OFFSET_PARA_ID_2 + 1) // 5
#define DPACK_OFFSET_PARA_2       (DPACK_OFFSET_PARA   + 1) 
#define DPACK_OFFSET_PARA_3       (DPACK_OFFSET_PARA_2 + 1) 
#define DPACK_OFFSET_PARA_4       (DPACK_OFFSET_PARA_3 + 1) 
#define DPACK_OFFSET_PARA_5       (DPACK_OFFSET_PARA_4 + 1) 
#define DPACK_OFFSET_PARA_6       (DPACK_OFFSET_PARA_5 + 1)  // 10
#define DPACK_OFFSET_PARA_7       (DPACK_OFFSET_PARA_6 + 1) 
#define DPACK_OFFSET_PARA_8       (DPACK_OFFSET_PARA_7 + 1) 
#define DPACK_OFFSET_PARA_9       (DPACK_OFFSET_PARA_8 + 1) 
#define DPACK_OFFSET_PARA_10       (DPACK_OFFSET_PARA_9 + 1) 
#define DPACK_OFFSET_PARA_11       (DPACK_OFFSET_PARA_10 + 1) // 15
#define DPACK_OFFSET_PARA_12       (DPACK_OFFSET_PARA_11 + 1) 
#define DPACK_OFFSET_PARA_13       (DPACK_OFFSET_PARA_12 + 1) 
#define DPACK_OFFSET_PARA_14       (DPACK_OFFSET_PARA_13 + 1) 
#define DPACK_OFFSET_PARA_15      (DPACK_OFFSET_PARA_14 + 1) 
#define DPACK_OFFSET_PARA_16       (DPACK_OFFSET_PARA_15 + 1) // 20







extern u8 dpackPortIdIsOk( u8 portId );


extern u16 dpackGetParaId( u8 *pDpack );

extern EN_FRAME_UNPACK dpackUnpack( u8 *pDpack );




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
extern void dpackCreate( EN_DPACK_PORT_ID portId, u8 addr, EN_DPACK_PARA_ID paraId, u8 *pVal,u8 valLen, u8 *pDpack );

extern void dpackCreate1( EN_DPACK_PORT_ID portId, u8 addr, EN_DPACK_PARA_ID paraId, u8 valLen, u8 *pDpack );



#define dpackCreate2( portId, addr, paraId, valLen )   {\
	u16 temp = paraId;\
	_stRfTxFrame.pBuf[DPACK_OFFSET_LEN]        = DPACK_LEN_CONST_ELE + valLen; \
	_stRfTxFrame.pBuf[DPACK_OFFSET_PORT_ID]    = portId; \
	_stRfTxFrame.pBuf[DPACK_OFFSET_PORT_ADDR]  = addr; \
	u16splitToByteHL(temp, _stRfTxFrame.pBuf + DPACK_OFFSET_PARA_ID_1);\
} 



#define dpackCreate3( portId, addr,  valLen )   {\
	_stRfTxFrame.pBuf[DPACK_OFFSET_LEN]        = DPACK_LEN_CONST_ELE + valLen; \
	_stRfTxFrame.pBuf[DPACK_OFFSET_PORT_ID]    = portId; \
	_stRfTxFrame.pBuf[DPACK_OFFSET_PORT_ADDR]  = addr; \
	_stRfTxFrame.pBuf[DPACK_OFFSET_PARA_ID_1] = _stExeFrame.pBuf[DPACK_OFFSET_PARA_ID_1];\
	_stRfTxFrame.pBuf[DPACK_OFFSET_PARA_ID_2] = _stExeFrame.pBuf[DPACK_OFFSET_PARA_ID_2];\
} 





extern int dpackExe(ST_FRAME *pstFrame );



#endif

#endif


