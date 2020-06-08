/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/



#include "com_includes.h"

#include "dbg_uart.h"

#include "zgb_unpack.h"


#include "f_response_frame.h"
#include "f_txt_frame.h"




static EN_UART_ZIGBEE_UNPACK_RST _zgbRxUnpackRst;


u8 modUartZgbRxUnpackRstIsRsp( void )
{
	if(  _zgbRxUnpackRst  == UART_ZIGBEE_UNPACK_RST_RSP_FRAME )
		return TRUE;

	return FALSE;
}


u8 modUartZgbRxUnpackRstIsDataFrame( void )
{
	if(  _zgbRxUnpackRst  == UART_ZIGBEE_UNPACK_RST_DATA_FRAME )
		return TRUE;

	return FALSE;
}


u8 modUartZgbRxUnpackRstIsProtocolFrame( void )
{
	if(  _zgbRxUnpackRst  == UART_ZIGBEE_UNPACK_RST_PROTOCOL_FRAME )
		return TRUE;

	return FALSE;
}



u8 modUartZgbRxUnpackRstIsPassTxt( void )
{
	if(   _zgbRxUnpackRst  == UART_ZIGBEE_UNPACK_RST_PASS_TXT  )
		return TRUE;

	return FALSE;
}



u8 modUartZgbRxUnpackRstIsPass( void )
{
	if(  _zgbRxUnpackRst  == UART_ZIGBEE_UNPACK_RST_PASS_RSP || _zgbRxUnpackRst  == UART_ZIGBEE_UNPACK_RST_PASS_TXT  )
		return TRUE;

	return FALSE;
}




u8 modUartZgbRxUnpackRstIsNotPass( void )
{
	if(    _zgbRxUnpackRst  == UART_ZIGBEE_UNPACK_RST_DATA_FRAME 
		|| _zgbRxUnpackRst  == UART_ZIGBEE_UNPACK_RST_PROTOCOL_FRAME 
		|| _zgbRxUnpackRst  == UART_ZIGBEE_UNPACK_RST_RSP_FRAME       )
		return TRUE;

	return FALSE;
}





/*
------------------------------------------------------------------------------------
帧成员名	字节数	                     解释                             文本类型
------------------------------------------------------------------------------------
帧开始	      1	      值：0xAA。
--------------------------------------------------------------------
帧长度	      1	      帧的总字节数。
--------------------------------------------------------------------
帧版本	      1	       bit7:   加密标志(1加密)。
                       bit6:   通信端标志(1:节点与网关 0:节点与服务器)。
                       bit5-0: 帧格式的版本号。
--------------------------------------------------------------------
帧行为	      1       帧的操作行为描述。
--------------------------------------------------------------------
校验和	      1	      所有帧数据按无符号数单字节累加，忽略溢出。
--------------------------------------------------------------------
目标ID	      8	      产品ID。                                                明文
------------------------------------------------------------------------------------
会话ID	      1	      详见相关章节的描述。                                明文/密文
--------------------------------------------------------------------
包类型	      1	      1：数据包  2：协议包
--------------------------------------------------------------------
包	          n	      暂约定 n < 230。
--------------------------------------------------------------------
帧结束	      1	      值：0x88。
------------------------------------------------------------------------------------
*/

/*
返回值: TURE 数据有效  FALSE 数据无效
*/
u8 modUartZgbUnpack( u8 *pFrame, u8 len )
{
	EN_FRAME_UNPACK rst;
	u8 inLen;

	inLen = len;

	//------------- 1 rsp frame ---------------------------
	rst = rspFrameUnpack(pFrame, len, 1); 
	if( rst == FRAME_UNPACK_OK )
	{
		if( resFrameIsPass( (ST_RSP_FRAME *)pFrame ) )
			_zgbRxUnpackRst = UART_ZIGBEE_UNPACK_RST_PASS_RSP;      //  *** 第 3 层数据流 ***   透传
		else
			_zgbRxUnpackRst = UART_ZIGBEE_UNPACK_RST_RSP_FRAME; // *** 第 2 层数据流 *** 
		
		return TRUE;
	}



	//------------- 2 txt frame ---------------------------
	if( txtFrameIsPass(pFrame, len) ) //  *** 第 3 层数据流 ***   透传
	{
		_zgbRxUnpackRst = UART_ZIGBEE_UNPACK_RST_PASS_TXT;
			
		return TRUE;
	}


	// *** 第 2 层数据流 *** 

	#if 0 // 约定不加密  fenghuiwait_1
	//--------------加密处理--------------------------------
	if( txtFrameIsEnc( pFrame, inLen ) == TRUE ) // 是否加密
	{	
		 aesDec( pFrame, &len );
		return FALSE;
	}
	//------------------------------------------------------
	#endif 


	rst = txtFrameUnpack(pFrame, inLen, 1 ); 
	if( rst == FRAME_UNPACK_OK )
	{
		if( txtFramePackTypeIsD( pFrame[TXT_FRAME_OFFSET_PACK_TYPE]  ) )
		{
			//------------- txt frame data ---------------------------
			_zgbRxUnpackRst = UART_ZIGBEE_UNPACK_RST_DATA_FRAME;
		}
		else
		{
			//------------- txt frame protocol -----------------------
			_zgbRxUnpackRst = UART_ZIGBEE_UNPACK_RST_PROTOCOL_FRAME;
			
			dprintf( "_uartZgbUnpack NG_%d", rst);
		}

		return TRUE;
	}
	else
	{
		if( FRAME_UNPACK_NG_ID == rst )
		{
			_zgbRxUnpackRst = UART_ZIGBEE_UNPACK_RST_NEW_MAC;
			return TRUE;
		}
	}

	_zgbRxUnpackRst = UART_ZIGBEE_UNPACK_RST_ERR;

	return FALSE;

	
	
}







#if 0

int modUartZgbUnpack( u8 *pFrame, u8 inLen )
{
	u8 len;


	//modUartDebugTxU8buf( pFrame,len);

	
	modUartZgbRxStateOnEvent( UART_ZGB_RX_EVENT_RX_TXT );
	
	if( modUartZgbRxStateIsUnpack() == FALSE )
	{
		modUartDebugTx0("\r\nmodUartZgbUnpack x1");
		return FALSE;
	}

	len = inLen;

	 return _uartZgbUnpack( pFrame, len);
	 
	 //return TRUE;
	 

}
#endif




void zgbUnpackInit( void )
{
	_zgbRxUnpackRst = UART_ZIGBEE_UNPACK_RST_NOT_DEF;
	
}








