/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/




//====================================================================================
//===== // step 4 =====解释接收内容，转化为结果=======================================
//====================================================================================






static int _uartZgbG2NrxDataFrame( u8 *pFrame, u32 len )
{
	u8 *pDpack;
	u16 paraId;
	int index;
	
	if( pFrame[TXT_FRAME_OFFSET_ACTION] != TXT_FRAME_ACTION_REPORT_ACK_GET  )
	{
		dprintf("\r\n_uartZgbG2NrxDataFrame x1");
		return FALSE;
	}

	//  判定MAC  fenghuiwait_1
	index = modUartZgbG2NonRxMacGetIndex( pFrame + TXT_FRAME_OFFSET_TARGET_ID );
	if( index  < 0 )
	{
		dprintf("\r\n_uartZgbG2NrxDataFrame x2");
		return FALSE;
	}

	pDpack = pFrame + TXT_FRAME_OFFSET_PACK ;

	if( dpackUnpack( pDpack ) != FRAME_UNPACK_OK )
		return FALSE;

	paraId = dpackGetParaId( pDpack );
	
	if( paraId == DPACK_PARA_ID_AES_SWITCH )
	{
		if( aesSwitchIsEqu( pDpack[DPACK_OFFSET_PARA] )  )
		{
			modNodeG2NcmdSetAesSwitchBitClear( index );
			return TRUE;
		}
	}
	else if( paraId == DPACK_PARA_ID_AES_KEY )
	{
		if( aesKey12isEqu( pDpack + DPACK_OFFSET_PARA ) )
		{
			modNodeG2NcmdSetKeyBitClear( index );
			return TRUE;
		}
	
	}

	return FALSE;
}









int modUartZgbG2Nrx( u8 *pBuf, u32 len )
{
	int rst;
	
	if( modUartZgbRxUnpackRstIsRsp() )
	{
		modUartZgbG2NstateOnEvent( UART_ZGB_G2N_E_RX_ACK );
		return TRUE;
	}

	if( modUartZgbRxUnpackRstIsDataFrame() )
	{
		rst = _uartZgbG2NrxDataFrame( pBuf, len );
		if( rst )
		{
			modUartZgbG2NstateOnEvent( UART_ZGB_G2N_E_RX_TXT );
		}
		
		return rst;
	}	

	return FALSE;
	
}

