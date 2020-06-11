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

#include "com_includes.h"


#include "f_frame_comm.h"
#include "f_response_frame.h"

#include "zgb_mac.h"

/*
*****简单应答帧格式（支持 通信端识别的 版本） rsp:  response  响应*****	
-----------------------------------------------------------------------
帧成员名	字节数	                     解释                      
-----------------------------------------------------------------------
帧开始	      1	      值：0xAA。
-----------------------------------------------------------------------
帧长度	      1	      帧的总字节数。
-----------------------------------------------------------------------
帧版本	      1	       
                       bit6:   通信端标志(1:节点与网关 0:节点与服务器)。
                       bit5-0: 帧格式的版本号。
-----------------------------------------------------------------------
校验和	      1	      所有帧数据按无符号数单字节累加，忽略溢出。
-----------------------------------------------------------------------
目标ID	      8	      产品ID。                                      
-----------------------------------------------------------------------
会话ID	      1	      详见相关章节的描述。                           
-----------------------------------------------------------------------
简单应答值    1	      详见简单应答帧的值定义。
-----------------------------------------------------------------------
帧结束	      1	      值：0x88。
-----------------------------------------------------------------------*/

U8 rspFrameHeadIsOk( u8 head )
{
	if( head == RSP_FRAME_START )
		return TRUE;

	return FALSE;
}

u8 rspFrameTailIsOk( u8 tail )
{
	if( tail == RSP_FRAME_END )
		return TRUE;

	return FALSE;
}

u8 rspFrameVerIsOk( u8 ver )
{
	ver &= ~RSP_FRAME_VER_BIT_MASK;
	
	if( ver == RSP_FRAME_VER )
		return TRUE;

	return FALSE;
}

u8 rspFrameLenIsOk( u8 len )
{
	if( len != RSP_FRAME_LEN )
		return FALSE;

	return TRUE;
}


u8 rspFrameRspValIsOk( u8 val )
{
	if( val == RSP_FRAME_VAL_ACK || val ==  RSP_FRAME_VAL_NAK || val  ==  RSP_FRAME_VAL_ERR )
		return TRUE;

	return FALSE;
}




u8 rspFrameCheckGet( u8 *pRspFrame )
{
	int i;
	u8 sum;
	
	for( sum = 0, i = RSP_FRAME_LEN - 1; i != 0; i-- )
	{
		if( i != RSP_FRAME_OFFSET_CHECK )
			sum += pRspFrame[i];
	}

	sum += pRspFrame[0];
	
	return sum;

}


u8 rspFrameCheckIsOk( u8 *pFrame )
{
	if( rspFrameCheckGet(pFrame) == pFrame[RSP_FRAME_OFFSET_CHECK] )
		return TRUE;
		
	return FALSE;
}




EN_FRAME_UNPACK rspFrameUnpackNotMac( u8 *pFrame, u8 len )
{
	if( rspFrameLenIsOk( len ) == FALSE )
		return FRAME_UNPACK_NG_LEN;

	if( rspFrameHeadIsOk( *pFrame ) == FALSE )
		return FRAME_UNPACK_NG_HEAD;

	if( rspFrameLenIsOk( pFrame[RSP_FRAME_OFFSET_LEN] ) == FALSE )
		return FRAME_UNPACK_NG_LEN;

	if( rspFrameVerIsOk( pFrame[RSP_FRAME_OFFSET_VER] ) == FALSE )
		return FRAME_UNPACK_NG_VER;

	if( rspFrameTailIsOk( pFrame[ len - 1 ] ) == FALSE )
		return FRAME_UNPACK_NG_TAIL;
	
	if( rspFrameRspValIsOk( pFrame[ RSP_FRAME_OFFSET_RSP_VAL] ) == FALSE )
		return FRAME_UNPACK_NG_RSP_VAL;

	if( rspFrameCheckIsOk( pFrame ) == FALSE )
		return FRAME_UNPACK_NG_CHECK;

	return FRAME_UNPACK_OK;

}




/* *********************** rsp frame 解码 *****************************  
-----------------------------------------------------------------------
帧成员名	字节数	                     解释                      
-----------------------------------------------------------------------
帧开始	      1	      值：0xAA。
-----------------------------------------------------------------------
帧长度	      1	      帧的总字节数。
-----------------------------------------------------------------------
帧版本	      1	       
                       bit6:   通信端标志(1:节点与网关 0:节点与服务器)。
                       bit5-0: 帧格式的版本号。
-----------------------------------------------------------------------
校验和	      1	      所有帧数据按无符号数单字节累加，忽略溢出。
-----------------------------------------------------------------------
目标ID	      8	      产品ID。                                      
-----------------------------------------------------------------------
会话ID	      1	      详见相关章节的描述。                           
-----------------------------------------------------------------------
简单应答值    1	      详见简单应答帧的值定义。
-----------------------------------------------------------------------
帧结束	      1	      值：0x88。
-----------------------------------------------------------------------
*/
EN_FRAME_UNPACK rspFrameUnpack( u8 *pFrame, u8 len, u8 isNode )
{
	EN_FRAME_UNPACK rst;
	
	rst = rspFrameUnpackNotMac( pFrame,  len);
	
	if( FRAME_UNPACK_OK != rst )
		return rst;

	if( macIsOk( pFrame + RSP_FRAME_OFFSET_TARGET_ID ) == FALSE )
		return FRAME_UNPACK_NG_ID;

	return FRAME_UNPACK_OK;

}





/* *********************** rsp frame 创建  *****************************  
-----------------------------------------------------------------------
帧成员名	字节数	                     解释                      
-----------------------------------------------------------------------
帧开始	      1	      值：0xAA。
-----------------------------------------------------------------------
帧长度	      1	      帧的总字节数。
-----------------------------------------------------------------------
帧版本	      1	       
                       bit6:   通信端标志(1:节点与网关 0:节点与服务器 and 网关与服务器, )。
                       bit5-0: 帧格式的版本号。
-----------------------------------------------------------------------
校验和	      1	      所有帧数据按无符号数单字节累加，忽略溢出。
-----------------------------------------------------------------------
目标ID	      8	      产品ID。                                      
-----------------------------------------------------------------------
会话ID	      1	      详见相关章节的描述。                           
-----------------------------------------------------------------------
简单应答值    1	      详见简单应答帧的值定义。
-----------------------------------------------------------------------
帧结束	      1	      值：0x88。
-----------------------------------------------------------------------
*/
void resFrameCreate( ST_RSP_FRAME *pstRspFrame, u8 isNodeAndGateway )
{
	pstRspFrame->head = RSP_FRAME_START;
	pstRspFrame->len  = RSP_FRAME_LEN;
	pstRspFrame->ver  = RSP_FRAME_VER;

	if( isNodeAndGateway )
		pstRspFrame->ver |= RSP_FRAME_VER_BIT_ID_COMM_TERMINAL;
	
	pstRspFrame->tail = RSP_FRAME_END;
	pstRspFrame->check = rspFrameCheckGet( (u8 *)pstRspFrame);
	
}









#endif



