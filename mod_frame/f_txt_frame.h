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

#ifndef _F_TXT_FRAME_H
#define _F_TXT_FRAME_H


#include "com_typedef.h"

#include "f_frame_comm.h"

#include "f_txt_frame_data.h"

/*
内容帧格式（版本号：0）			
----------------------------------------------------------------------------------
编号	帧成员名	字节数	解释
----------------------------------------------------------------------------------
D1		帧开始		1		值：0xAA。
D2		帧长度		1		帧的总字节数。
D3		帧版本		1		帧格式的版本号。
D4		帧行为		1		帧的操作行为描述。
D5		校验和		1		所有帧数据按无符号数单字节累加，忽略溢出。
D6		目标ID		8		产品ID。
D7		会话ID		1		详见相关章节的描述。
D8	    包类型	    1	    1：数据包  2：协议包
D9		    包		n		暂约定 n < 230。
D10		帧结束		1		值：0x88。
----------------------------------------------------------------------------------*/



//------------------------------------------------------
#define  TXT_FRAME_ELE_LEN_HEAD       (1)
#define  TXT_FRAME_ELE_LEN_LEN        (1)
#define  TXT_FRAME_ELE_LEN_VER        (1)
#define  TXT_FRAME_ELE_LEN_ACTION     (1)
#define  TXT_FRAME_ELE_LEN_CHECK      (1)
#define  TXT_FRAME_ELE_LEN_TARGET_ID  (8)
#define  TXT_FRAME_ELE_LEN_SID        (1)
#define  TXT_FRAME_ELE_LEN_PACK_TYPE  (1)
//#define  TXT_FRAME_ELE_LEN_PACK     (N)
#define  TXT_FRAME_ELE_LEN_TAIL       (1)



//------------------------------------------------------


#define TXT_FRAME_LEN_CONST_ELE  ( TXT_FRAME_ELE_LEN_HEAD + TXT_FRAME_ELE_LEN_LEN + TXT_FRAME_ELE_LEN_VER + \
	                               TXT_FRAME_ELE_LEN_ACTION + TXT_FRAME_ELE_LEN_CHECK + TXT_FRAME_ELE_LEN_TARGET_ID + \
	                               TXT_FRAME_ELE_LEN_SID + TXT_FRAME_ELE_LEN_PACK_TYPE + TXT_FRAME_ELE_LEN_TAIL )
	                               

#define TXT_FRAME_LEN_MIN  ( TXT_FRAME_LEN_CONST_ELE + DPACK_LEN_MIN )

	                    

#define TXT_FRAME_LEN_MAX  (252)


//------------------------------------------------------
#define TXT_FRAME_OFFSET_HEAD          (0)
#define TXT_FRAME_OFFSET_LEN           (TXT_FRAME_OFFSET_HEAD      + TXT_FRAME_ELE_LEN_HEAD)
#define TXT_FRAME_OFFSET_VER           (TXT_FRAME_OFFSET_LEN       + TXT_FRAME_ELE_LEN_LEN)
#define TXT_FRAME_OFFSET_ACTION        (TXT_FRAME_OFFSET_VER       + TXT_FRAME_ELE_LEN_VER)
#define TXT_FRAME_OFFSET_CHECK         (TXT_FRAME_OFFSET_ACTION    + TXT_FRAME_ELE_LEN_ACTION)
#define TXT_FRAME_OFFSET_TARGET_ID     (TXT_FRAME_OFFSET_CHECK     + TXT_FRAME_ELE_LEN_CHECK)
#define TXT_FRAME_OFFSET_SID           (TXT_FRAME_OFFSET_TARGET_ID + TXT_FRAME_ELE_LEN_TARGET_ID)
#define TXT_FRAME_OFFSET_PACK_TYPE     (TXT_FRAME_OFFSET_SID       + TXT_FRAME_ELE_LEN_SID)
#define TXT_FRAME_OFFSET_PACK          (TXT_FRAME_OFFSET_PACK_TYPE + TXT_FRAME_ELE_LEN_PACK_TYPE)
//#define TXT_FRAME_OFFSET_TAIL          (TXT_FRAME_OFFSET_PACK       + 4) //


#define  TXT_FRAME_VER_ENC_BIT                 (0x80) // 帧的加密位
#define  TXT_FRAME_VER_COMM_TERMINAL_BIT       (0x40) // 通信端标志 Communication terminal flag   1:节点与网关 0:节点与服务器
#define  TXT_FRAME_VER_BIT_MASK                ( TXT_FRAME_VER_ENC_BIT | TXT_FRAME_VER_COMM_TERMINAL_BIT )


//------------------------------------------------------
#define TXT_FRAME_START  (0xAA)
#define TXT_FRAME_END    (0x88)

#define TXT_FRAME_VER_01    (0x01) // 基本版
//#define TXT_FRAME_VER_02    (0x02) //






extern U8 txtFrameHeadIsOk( u8 head );


extern u8 txtFrameTailIsOk( u8 tail );


extern u8 txtFrameVerIsOk( u8 ver );

extern u8 txtFrameVerIsEnc( u8 ver );
extern void txtFrameEncBitSet( u8 *pVer );
extern void txtFrameEncBitClear( u8 *pVer );

extern u8 txtFrameLenIsOk( u8 len );


extern u8 txtFrameActionIsOk( u8 action );



extern u8 txtFramePackTypeIsOk( u8 type );




extern u8 txtFramePackTypeIsD( u8 type );// data pack



extern u8 txtFramePackTypeIsP( u8 type );// protocol pack



extern u8 txtFrameCheckGet( u8 *pFrame );


extern u8 txtFrameCheckIsOk( u8 *pFrame );




//解帧出错时，是否回复
extern u8 txtFrameOnErrIsToRsp( u8 *pFrame, u8 len );


/* ********************* 内容帧是不是透传  ****************************  
-----------------------------------------------------------------------
	通信端标志 如果 是 1, 则是 节点与网关通信, 不是透传
-----------------------------------------------------------------------
	通信端标志 如果 是 0, 则是 节点与服务器通信, 是透传
-----------------------------------------------------------------------
*/
extern u8 txtFrameIsPass( u8 *pFrame, u8 len );

//extern u8 txtFrameIsEnc( u8 *pFrame, u8 len );


extern EN_FRAME_UNPACK txtFrameUnpackHeadNotMac( u8 *pFrame, u8 len );


extern EN_FRAME_UNPACK txtFrameUnpackNotMac( u8 *pFrame, u8 len );


// 解码 txtFrame
extern EN_FRAME_UNPACK txtFrameUnpack( u8 *pFrame, u8 len, u8 isNode );







/*
内容帧格式（版本号：0）			
----------------------------------------------------------------------------------
编号	帧成员名	字节数	解释
----------------------------------------------------------------------------------
D1		帧开始		1		值：0xAA。
D2		帧长度		1		帧的总字节数。
D3		帧版本		1		帧格式的版本号。
D4		帧行为		1		帧的操作行为描述。
D5		校验和		1		所有帧数据按无符号数单字节累加，忽略溢出。
D6		目标ID		8		产品ID。
D7		会话ID		1		详见相关章节的描述。
D8	    包类型	    1	    1：数据包  2：协议包
D9		    包		n		暂约定 n < 230。
D10		帧结束		1		值：0x88。
----------------------------------------------------------------------------------*/
// in : dpack is OK
extern u8 txtFrameCreateG2S( EN_TXT_FRAME_ACTION action, u8 sid, ST_FRAME  *pFrame );



extern u8 txtFrameCreateG2N( EN_TXT_FRAME_ACTION action, u8 sid, ST_FRAME  *pFrame );


#endif

#endif


