/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 
#if 1

#include "com_includes.h"


#include "f_frame_comm.h"
#include "f_response_frame.h"

#include "zgb_mac.h"

/*
*****��Ӧ��֡��ʽ��֧�� ͨ�Ŷ�ʶ��� �汾�� rsp:  response  ��Ӧ*****	
-----------------------------------------------------------------------
֡��Ա��	�ֽ���	                     ����                      
-----------------------------------------------------------------------
֡��ʼ	      1	      ֵ��0xAA��
-----------------------------------------------------------------------
֡����	      1	      ֡�����ֽ�����
-----------------------------------------------------------------------
֡�汾	      1	       
                       bit6:   ͨ�Ŷ˱�־(1:�ڵ������� 0:�ڵ��������)��
                       bit5-0: ֡��ʽ�İ汾�š�
-----------------------------------------------------------------------
У���	      1	      ����֡���ݰ��޷��������ֽ��ۼӣ����������
-----------------------------------------------------------------------
Ŀ��ID	      8	      ��ƷID��                                      
-----------------------------------------------------------------------
�ỰID	      1	      �������½ڵ�������                           
-----------------------------------------------------------------------
��Ӧ��ֵ    1	      �����Ӧ��֡��ֵ���塣
-----------------------------------------------------------------------
֡����	      1	      ֵ��0x88��
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




/* *********************** rsp frame ���� *****************************  
-----------------------------------------------------------------------
֡��Ա��	�ֽ���	                     ����                      
-----------------------------------------------------------------------
֡��ʼ	      1	      ֵ��0xAA��
-----------------------------------------------------------------------
֡����	      1	      ֡�����ֽ�����
-----------------------------------------------------------------------
֡�汾	      1	       
                       bit6:   ͨ�Ŷ˱�־(1:�ڵ������� 0:�ڵ��������)��
                       bit5-0: ֡��ʽ�İ汾�š�
-----------------------------------------------------------------------
У���	      1	      ����֡���ݰ��޷��������ֽ��ۼӣ����������
-----------------------------------------------------------------------
Ŀ��ID	      8	      ��ƷID��                                      
-----------------------------------------------------------------------
�ỰID	      1	      �������½ڵ�������                           
-----------------------------------------------------------------------
��Ӧ��ֵ    1	      �����Ӧ��֡��ֵ���塣
-----------------------------------------------------------------------
֡����	      1	      ֵ��0x88��
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





/* *********************** rsp frame ����  *****************************  
-----------------------------------------------------------------------
֡��Ա��	�ֽ���	                     ����                      
-----------------------------------------------------------------------
֡��ʼ	      1	      ֵ��0xAA��
-----------------------------------------------------------------------
֡����	      1	      ֡�����ֽ�����
-----------------------------------------------------------------------
֡�汾	      1	       
                       bit6:   ͨ�Ŷ˱�־(1:�ڵ������� 0:�ڵ�������� and �����������, )��
                       bit5-0: ֡��ʽ�İ汾�š�
-----------------------------------------------------------------------
У���	      1	      ����֡���ݰ��޷��������ֽ��ۼӣ����������
-----------------------------------------------------------------------
Ŀ��ID	      8	      ��ƷID��                                      
-----------------------------------------------------------------------
�ỰID	      1	      �������½ڵ�������                           
-----------------------------------------------------------------------
��Ӧ��ֵ    1	      �����Ӧ��֡��ֵ���塣
-----------------------------------------------------------------------
֡����	      1	      ֵ��0x88��
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



