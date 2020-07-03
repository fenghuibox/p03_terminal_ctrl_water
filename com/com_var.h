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
	u8 led:1;          // toggle led
	
	u8 sleep:1;        // 1: 可以进入休眠     0: 不可以
	
	u8 ctrlPackTx:1;     // 1:发送了ctrl_pack_get包     0: 没有
	u8 ctrlPackFinish:1; // 1:ctrl_pack_get包处理完成   0:没有完成
	
	u8 ctrlOpenTimeoutClose:1;      // 程序因开的时长到了而关闭水阀
	
	u8 zgbSleepTx:1;    // 1:执行了 modIoZgbSleep   0: 没有
	u8 zgbSleepFinish:1;// 1:执行了完成             0: 没有

	u8 zgbWakeupTx:1;    // 1:执行了 modIoZgbWakeup  0: 没有
	u8 zgbWakeupFinish:1;// 1:执行了完成             0: 没有	

	u8 battRead:1;          // 1:执行了读取电压     0: 没有	
	u8 battReadFinish:1;    // 1:执行了完成         0: 没有	

	
	u8 openTimeoutCloseStart:1;    // 开水阀时长到时，开始 执行关水阀
	u8 openTimeoutCloseStateTx:1;  // 开水阀时长到时，执行了关水阀 ,状态发给服务器
	
	u8 openTimeoutCloseEnd:1;  // 开水阀时长到时，执行关水阀 完成
	
	
	u8 txtFrameExeOKhaveRspReport:1; // 执行完帧后，需要等待应答的报告

	
	//u8 battTx:1;       // 1:发送了电量包    0: 没有
	//u8 battTxFinish:1; // 1:执行了完成      0: 没有
	
	
	u8 battIsLow:1; // 
	
	u8 isDebug:1; // 
	u8 isPowerOn:1; // 

	

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

