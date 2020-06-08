/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
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
֡��Ա��	�ֽ���	                     ����                             �ı�����
------------------------------------------------------------------------------------
֡��ʼ	      1	      ֵ��0xAA��
--------------------------------------------------------------------
֡����	      1	      ֡�����ֽ�����
--------------------------------------------------------------------
֡�汾	      1	       bit7:   ���ܱ�־(1����)��
                       bit6:   ͨ�Ŷ˱�־(1:�ڵ������� 0:�ڵ��������)��
                       bit5-0: ֡��ʽ�İ汾�š�
--------------------------------------------------------------------
֡��Ϊ	      1       ֡�Ĳ�����Ϊ������
--------------------------------------------------------------------
У���	      1	      ����֡���ݰ��޷��������ֽ��ۼӣ����������
--------------------------------------------------------------------
Ŀ��ID	      8	      ��ƷID��                                                ����
------------------------------------------------------------------------------------
�ỰID	      1	      �������½ڵ�������                                ����/����
--------------------------------------------------------------------
������	      1	      1�����ݰ�  2��Э���
--------------------------------------------------------------------
��	          n	      ��Լ�� n < 230��
--------------------------------------------------------------------
֡����	      1	      ֵ��0x88��
------------------------------------------------------------------------------------
*/

/*
����ֵ: TURE ������Ч  FALSE ������Ч
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
			_zgbRxUnpackRst = UART_ZIGBEE_UNPACK_RST_PASS_RSP;      //  *** �� 3 �������� ***   ͸��
		else
			_zgbRxUnpackRst = UART_ZIGBEE_UNPACK_RST_RSP_FRAME; // *** �� 2 �������� *** 
		
		return TRUE;
	}



	//------------- 2 txt frame ---------------------------
	if( txtFrameIsPass(pFrame, len) ) //  *** �� 3 �������� ***   ͸��
	{
		_zgbRxUnpackRst = UART_ZIGBEE_UNPACK_RST_PASS_TXT;
			
		return TRUE;
	}


	// *** �� 2 �������� *** 

	#if 0 // Լ��������  fenghuiwait_1
	//--------------���ܴ���--------------------------------
	if( txtFrameIsEnc( pFrame, inLen ) == TRUE ) // �Ƿ����
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








