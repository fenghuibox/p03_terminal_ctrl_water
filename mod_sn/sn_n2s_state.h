/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __SN_N2S_STATE_H
#define __SN_N2S_STATE_H

 // sn: Server and node communication    服务器和节点通信
// n2s: node to server                   节点发送给服务器

#include "com_typedef.h"




typedef enum 
{
	TXT_FRAME_EXE_STATE_NOT_DEF = 0, 
	TXT_FRAME_EXE_STATE_IDLE, 
	TXT_FRAME_EXE_STATE_UNPACK,
	TXT_FRAME_EXE_STATE_EXE,
	TXT_FRAME_EXE_STATE_WAIT_RSP_REPORT,
}EN_TXT_FRAME_EXE_STATE; // 



typedef enum 
{
	TXT_FRAME_EXE_EVENT_NOT_DEF = 0,
	TXT_FRAME_EXE_EVENT_INIT, 
	TXT_FRAME_EXE_EVENT_RX_TXT, 		
	TXT_FRAME_EXE_EVENT_UNPACK_OK, 
	TXT_FRAME_EXE_EVENT_UNPACK_NG,
	TXT_FRAME_EXE_EVENT_EXE_OK,
	TXT_FRAME_EXE_EVENT_EXE_NG,
	TXT_FRAME_EXE_EVENT_TO_WAIT_RSP_REPORT,
	TXT_FRAME_EXE_EVENT_RSP_REPORT,
	TXT_FRAME_EXE_EVENT_WAIT_RSP_TIMEOUT,

	//TXT_FRAME_GET_EVENT,
	//TXT_FRAME_GET_EVENT_WAIT_TIMEOUT,
	
}EN_TXT_FRAME_EXE_EVENT; // 






//========================================================================

extern u8 txtFrameExeStateIsIdle( void );



extern u8 txtFrameExeStateIsUnpack( void );




extern u8 txtFrameExeStateIsExe( void );


extern u8 txtFrameExeStateIsWaitRspResport( void );

extern void txtFrameExeStateOnEvent( EN_TXT_FRAME_EXE_EVENT event );


extern void snN2sStateInit( void );

#endif

