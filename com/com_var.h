/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __COM_VAR_H
#define __COM_VAR_H


#include "com_typedef.h"

typedef struct
{
	//u8 txtFrameIsExeIng:1;           // 正在执行中
	//u8 txtFrameExeIsWaitReport:1;    // 执行完帧后，正在等待应答的报告
	u8 txtFrameExeOKhaveRspReport:1; // 执行完帧后，需要等待应答的报告
	//u8 txtFrameExeIsRspReport:1;     // 执行完帧后， 应答了报告
	//u8 para_communication_state:1; 
	//u8 para_zigbee_auto_net:1; 
	//u8 para_zigbee_work_state:2; // not save to eep |  reboot read

	
	u8 g4UartTxIsIdle:1; 
	u8 ipadUartTxIsIdle:1; // 
	u8 zgbUartTxIsIdle:1; // 
	u8 m485UartTxIsIdle:1; // 
	u8 dbgUartTxIsIdle:1; // 

	
	//u8 adcHaveVal:1; // 
	u8 vbattIsLow:1; // 

	u8 inited; // 初始化是否完成了  0:没有完成  1:完成

}ST_BOOL;


extern ST_BOOL gB1; // 只为节省空间








extern void valBitSet1(U32 *pVar, U32 bitMask);

extern void valBitSet0(U32 *pVar, U32 bitMask);

extern void valBitReverse(U32 *pVar, U32 bitMask);



extern void comSwapU32( u32 *pD1, u32 *pD2);

extern void comSwapU8( u8 *pD1, u8 *pD2);


extern void comU8Inc( u8 *pVal );
extern void comU8Dec( u8 *pVal );

extern void comU32Inc( u32 *pVal );
extern void comU32Dec( u32 *pVal );



//=====================================

extern u16 byteMergeto16( u8 high, u8 low );


// high -> pBuf[0]
extern void u16splitToByteHL( u16 val, u8 *pBuf );

// low -> pBuf[0]
extern void u16splitToByteLH( u16 val, u8 *pBuf );


extern u32 byteMergeto32( u8 highMax, u8 high, u8 low, u8 lowMin );


// high -> pBuf[0]  
extern void u32splitToByte( u32 val, u8 *pBuf );

// 0x01020304 --> 0x04030201
extern void u32Image( u8 *pU32 );

// 0x01020304 --> 0x40302010
void u32Image2( u8 *pU32 );




#endif

