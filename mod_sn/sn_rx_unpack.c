/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
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
 ֡��Ա��	 �ֽ��� 					  ����							   �ı�����
 ------------------------------------------------------------------------------------
 ֡��ʼ 	   1	   ֵ��0xAA��
 --------------------------------------------------------------------
 ֡���� 	   1	   ֡�����ֽ�����
 --------------------------------------------------------------------
 ֡�汾 	   1		bit7:	���ܱ�־(1����)��
						bit6:	ͨ�Ŷ˱�־(1:�ڵ������� 0:�ڵ��������)��
						bit5-0: ֡��ʽ�İ汾�š�
 --------------------------------------------------------------------
 ֡��Ϊ 	   1	   ֡�Ĳ�����Ϊ������
 --------------------------------------------------------------------
 У��� 	   1	   ����֡���ݰ��޷��������ֽ��ۼӣ����������
 --------------------------------------------------------------------
 Ŀ��ID 	   8	   ��ƷID�� 											   ����
 ------------------------------------------------------------------------------------
 �ỰID 	   1	   �������½ڵ������� 							   ����/����
 --------------------------------------------------------------------
 ������ 	   1	   1�����ݰ�  2��Э���
 --------------------------------------------------------------------
 �� 		   n	   ��Լ�� n < 230��
 --------------------------------------------------------------------
 ֡���� 	   1	   ֵ��0x88��
 ------------------------------------------------------------------------------------
 */
 
 /*
 ����ֵ: TURE ������Ч	FALSE ������Ч
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
			_snRxUnpackRst = SN_RX_UNPACK_RST_RSP_FRAME; // *** �� 2 �������� *** 
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
			_snRxUnpackRst = SN_RX_UNPACK_RST_TXT_FRAME; // *** �� 2 �������� *** 
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
 
 
 
 


