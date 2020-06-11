

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


#include "f_txt_frame.h"


#include "zgb_mac.h"



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



//--------------------------------------------------------------------------------------------------


U8 txtFrameHeadIsOk( u8 head )
{
	if( head == TXT_FRAME_START )
		return TRUE;

	return FALSE;
}

u8 txtFrameTailIsOk( u8 tail )
{
	if( tail == TXT_FRAME_END )
		return TRUE;

	return FALSE;
}

u8 txtFrameVerIsOk( u8 ver )
{
	if(  ( ver & ( ~ TXT_FRAME_VER_BIT_MASK ) ) == TXT_FRAME_VER_01 )
		return TRUE;

	return FALSE;
}

u8 txtFrameVerIsEnc( u8 ver )
{
	if( ver & TXT_FRAME_VER_ENC_BIT )
		return TRUE;

	return FALSE;
}

void txtFrameEncBitSet( u8 *pVer )
{
	*pVer |= TXT_FRAME_VER_ENC_BIT;
}

void txtFrameEncBitClear( u8 *pVer )
{
	*pVer &= (~TXT_FRAME_VER_ENC_BIT);
}


u8 txtFrameLenIsOk( u8 len )
{
	if( len < TXT_FRAME_LEN_MIN || len > TXT_FRAME_LEN_MAX )
		return FALSE;

	return TRUE;
}


u8 txtFrameActionIsOk( u8 action )
{
	if( action < TXT_FRAME_ACTION_SET || action > TXT_FRAME_ACTION_REPORT_AUTO )
		return FALSE;

	return TRUE;
}


u8 txtFramePackTypeIsOk( u8 type )
{
	if( type == TXT_FRAME_PACK_TYPE_DATA || type == TXT_FRAME_PACK_TYPE_PROTOCOL )
		return TRUE;

	return FALSE;
}



u8 txtFramePackTypeIsD( u8 type )// data pack
{
	if( type == TXT_FRAME_PACK_TYPE_DATA  )
		return TRUE;

	return FALSE;
}


u8 txtFramePackTypeIsP( u8 type )// protocol pack
{
	if( type == TXT_FRAME_PACK_TYPE_PROTOCOL  )
		return TRUE;

	return FALSE;
}


u8 txtFrameCheckGet( u8 *pFrame )
{
#if 1
	int i;
	u8 sum;

	//modUartDebugTxU8buf( pFrame, pFrame[TXT_FRAME_OFFSET_LEN] );
	
	for( sum = 0, i = pFrame[TXT_FRAME_OFFSET_LEN] - 1; i != 0; i-- )
	{
		if( i != TXT_FRAME_OFFSET_CHECK )
			sum += pFrame[i];
	}

	sum += pFrame[0];
	
	return sum;
#else

	int i;
	u8 sum;
	u8 len;

	len = pFrame[TXT_FRAME_OFFSET_LEN];

	//modUartDebugTxU8buf( pFrame, pFrame[TXT_FRAME_OFFSET_LEN] );

	for( sum = 0, i = 0; i < len; i++ )
	{
		if( i != TXT_FRAME_OFFSET_CHECK )
			sum += pFrame[i];
	}

	return sum;
#endif	

}


u8 txtFrameCheckIsOk( u8 *pFrame )
{
	if( txtFrameCheckGet(pFrame) == pFrame[TXT_FRAME_OFFSET_CHECK] )
		return TRUE;
		
	return FALSE;
}



#if 1 // fenghuiw


//解帧出错时，是否回复
u8 txtFrameOnErrIsToRsp( u8 *pFrame, u8 len )
{
/*
	ST_TXT_FRAME *pTxtFrame;
	
	if( txtFrameLenIsOk( len ) == FALSE )
		return FALSE;

	if( txtFrameHeadIsOk( *pFrame ) == FALSE )
		return FALSE;

	if( txtFrameLenIsOk( pFrame[TXT_FRAME_OFFSET_LEN] ) == FALSE )
		return FALSE;

	if( txtFrameVerIsOk( pFrame[TXT_FRAME_OFFSET_VER] ) == FALSE )
		return FALSE;

	//if( txtFrameAddrIsMy( pFrame ) )
	//	return TRUE;


	pTxtFrame = (ST_TXT_FRAME *)pFrame;

	if( modNodeMacIsNode( pTxtFrame->pMac ) )
		return TRUE;

	return FALSE;
*/

	return FALSE;
	
}








EN_FRAME_UNPACK txtFrameUnpackHeadNotMac( u8 *pFrame, u8 len )
{
	if( txtFrameLenIsOk( len ) == FALSE )
		return FRAME_UNPACK_NG_LEN;

	if( txtFrameHeadIsOk( *pFrame ) == FALSE )
		return FRAME_UNPACK_NG_HEAD;

	if( txtFrameLenIsOk( pFrame[TXT_FRAME_OFFSET_LEN] ) == FALSE )
		return FRAME_UNPACK_NG_LEN;

	if( txtFrameVerIsOk( pFrame[TXT_FRAME_OFFSET_VER] ) == FALSE )
		return FRAME_UNPACK_NG_VER;

	return FRAME_UNPACK_OK;

}



EN_FRAME_UNPACK txtFrameUnpackNotMac( u8 *pFrame, u8 len )
{
	if( txtFrameLenIsOk( len ) == FALSE )
		return FRAME_UNPACK_NG_LEN;

	if( txtFrameHeadIsOk( *pFrame ) == FALSE )
		return FRAME_UNPACK_NG_HEAD;

	if( txtFrameLenIsOk( pFrame[TXT_FRAME_OFFSET_LEN] ) == FALSE )
		return FRAME_UNPACK_NG_LEN;

	if( txtFrameVerIsOk( pFrame[TXT_FRAME_OFFSET_VER] ) == FALSE )
		return FRAME_UNPACK_NG_VER;

	if( txtFrameTailIsOk( pFrame[ len - 1 ] ) == FALSE )
		return FRAME_UNPACK_NG_TAIL;
	
	if( txtFramePackTypeIsOk( pFrame[ TXT_FRAME_OFFSET_PACK_TYPE ] ) == FALSE )
		return FRAME_UNPACK_NG_PACK_TYPE;

	if( txtFrameCheckIsOk( pFrame ) == FALSE )
		return FRAME_UNPACK_NG_CHECK;
	
	return FRAME_UNPACK_OK;

}



/* ******************************** txtFrame 解码 ********************************  
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
EN_FRAME_UNPACK txtFrameUnpack( u8 *pFrame, u8 len, u8 isNode )
{
	EN_FRAME_UNPACK rst;
	
	rst = txtFrameUnpackNotMac( pFrame, len );

	if( FRAME_UNPACK_OK != rst )
		return rst;

	if( macIsOk( pFrame + TXT_FRAME_OFFSET_TARGET_ID ) == FALSE )
		return FRAME_UNPACK_NG_ID;
	
	return FRAME_UNPACK_OK;

}







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
u8 txtFrameCreateN2S( EN_TXT_FRAME_ACTION action, u8 sid, ST_FRAME  *pFrame )
{
	pFrame->head = TXT_FRAME_START;
	pFrame->pBuf[ pFrame->pBuf[DPACK_OFFSET_LEN] ] = TXT_FRAME_END;
	pFrame->len  = TXT_FRAME_LEN_CONST_ELE + pFrame->pBuf[DPACK_OFFSET_LEN];
	pFrame->ver  = TXT_FRAME_VER_01;
	pFrame->action = action;
	//pFrame->check

	macMyGet( pFrame->pMac );
	
	pFrame->sid    = sid;
	pFrame->packType = TXT_FRAME_PACK_TYPE_DATA;

	pFrame->check = txtFrameCheckGet( (u8 *)pFrame);

	return TRUE;
}




// in : dpack is OK
u8 txtFrameCreateG2N( EN_TXT_FRAME_ACTION action, u8 sid, ST_FRAME  *pFrame )
{
	pFrame->head = TXT_FRAME_START;
	pFrame->pBuf[ pFrame->pBuf[DPACK_OFFSET_LEN] ] = TXT_FRAME_END;
	pFrame->len  = TXT_FRAME_LEN_CONST_ELE + pFrame->pBuf[DPACK_OFFSET_LEN];
	pFrame->ver  = TXT_FRAME_VER_01 | TXT_FRAME_VER_COMM_TERMINAL_BIT;
	pFrame->action = action;
	//pFrame->check

	//zigbeeMyMacGet( pFrame->pMac );
	
	pFrame->sid    = sid;
	pFrame->packType = TXT_FRAME_PACK_TYPE_DATA;

	pFrame->check = txtFrameCheckGet( (u8 *)pFrame);

	return TRUE;
}


#endif


