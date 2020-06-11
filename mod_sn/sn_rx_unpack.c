/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/

#include "dbg_uart.h"

#include "sn_rx_unpack.h"

#include "f_response_frame.h"
#include "f_txt_frame.h"

#include "zgb_mac.h"




 typedef enum 
 {
	 SN_RX_UNPACK_RST_NOT_DEF = 0,
	 SN_RX_UNPACK_RST_ERR,
	 
	 //SN_RX_UNPACK_RST_PASS_RSP,
	 //SN_RX_UNPACK_RST_PASS_TXT,
 
	 //SN_RX_UNPACK_RST_DATA_FRAME,
	 //SN_RX_UNPACK_RST_PROTOCOL_FRAME,
	 SN_RX_UNPACK_RST_TXT_FRAME,
	 SN_RX_UNPACK_RST_RSP_FRAME,
	 
	 //SN_RX_UNPACK_RST_NEW_MAC,
 
 }EN_SN_RX_UNPACK_RST; // 
 
 



 
 static EN_SN_RX_UNPACK_RST _snRxUnpackRst;

 
 
 
 u8 snRxUnpackRstIsRsp( void )
 {
	 if(  _snRxUnpackRst  == SN_RX_UNPACK_RST_RSP_FRAME )
		 return TRUE;
 
	 return FALSE;
 }
 
 
 u8 snRxUnpackRstIsTxtFrame( void )
 {
	 if(  _snRxUnpackRst  == SN_RX_UNPACK_RST_TXT_FRAME )
		 return TRUE;
 
	 return FALSE;
 }
 
 

 
 
 
 /*
 ------------------------------------------------------------------------------------
 帧成员名	 字节数 					  解释							   文本类型
 ------------------------------------------------------------------------------------
 帧开始 	   1	   值：0xAA。
 --------------------------------------------------------------------
 帧长度 	   1	   帧的总字节数。
 --------------------------------------------------------------------
 帧版本 	   1		bit7:	加密标志(1加密)。
						bit6:	通信端标志(1:节点与网关 0:节点与服务器)。
						bit5-0: 帧格式的版本号。
 --------------------------------------------------------------------
 帧行为 	   1	   帧的操作行为描述。
 --------------------------------------------------------------------
 校验和 	   1	   所有帧数据按无符号数单字节累加，忽略溢出。
 --------------------------------------------------------------------
 目标ID 	   8	   产品ID。 											   明文
 ------------------------------------------------------------------------------------
 会话ID 	   1	   详见相关章节的描述。 							   明文/密文
 --------------------------------------------------------------------
 包类型 	   1	   1：数据包  2：协议包
 --------------------------------------------------------------------
 包 		   n	   暂约定 n < 230。
 --------------------------------------------------------------------
 帧结束 	   1	   值：0x88。
 ------------------------------------------------------------------------------------
 */
 
 /*
 返回值: TURE 数据有效	FALSE 数据无效
 */
 u8 snRxUnpack( u8 *pFrame, u8 len )
 {
	 EN_FRAME_UNPACK rst;
 
	 //------------- 1 rsp frame ---------------------------
	 rst = rspFrameUnpackNotMac(pFrame, len); 
	 if( rst == FRAME_UNPACK_OK )
	 {
	 	if( macIsNode( pFrame + RSP_FRAME_OFFSET_TARGET_ID) )
	 	{
			_snRxUnpackRst = SN_RX_UNPACK_RST_RSP_FRAME; // *** 第 2 层数据流 *** 
	 	}
		else
		{
			_snRxUnpackRst = SN_RX_UNPACK_RST_ERR;

			dprintf( "\r\nsnRxUnpack_x1" );
			return FALSE;
		}
			
		 return TRUE;
	 }

 
	 //------------- 2 txt frame ---------------------------
	 rst = txtFrameUnpackHeadNotMac(pFrame, len);
	 
	if( rst == FRAME_UNPACK_OK )
	{
		if( macIsNode( pFrame + TXT_FRAME_OFFSET_TARGET_ID) )
	 	{
			_snRxUnpackRst = SN_RX_UNPACK_RST_TXT_FRAME; // *** 第 2 层数据流 *** 
	 	}
		else
		{
			dprintf( "\r\nsnRxUnpack_2" );
			_snRxUnpackRst = SN_RX_UNPACK_RST_ERR;
			return FALSE;
		}
		
		return TRUE;
	}
	else
	{
		dprintf( "\r\nsnRxUnpack_x_=%d", rst );
		
	}

	return FALSE;
	 
 }
 
 
 
 
 
 
 
 
 void snRxUnpackInit( void )
 {
	 _snRxUnpackRst = SN_RX_UNPACK_RST_NOT_DEF;
	 
 }
 
 
 
 


