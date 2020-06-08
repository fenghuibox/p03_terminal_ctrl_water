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
//===== // step 5 =======获取结果=====================================================
//====================================================================================

u16 zigbeeRebootIsOk( void )
{
	return _stZcmdPara.isOk;
}




u16 zigbeeTargetAddrGet( void )
{
	return _stZdevInfo.DstAddr;
}



u16 zigbeeMyAddrGet( void )
{
	return _stZdevInfo.MyAddr;
}




u8 zigbeeMyMacGet( u8 *pMac )
{
	if( _stZcmdPara.isOk == FALSE )
		return FALSE;

	memcpy( pMac, _stZdevInfo.MyIEEE, MAC_ADDR_LEN );
	
	return TRUE;
}





u8 zigbeeWorkStateGet( EN_ZIGBEE_WORK_STATE *pState )
{
	if(_stZcmdPara.isOk == 0 )
	{
		*pState = ZIGBEE_WORK_STATE_NOT_DEF;
		return FALSE;
	}
	
	*pState = (EN_ZIGBEE_WORK_STATE)_stZcmdPara.workState;

	return TRUE;
}


u8 zigbeeAutoNetGet( void )
{
	//modUartDebugTxStrU32("zigbeeAutoNetGet", _stZcmdPara.autoNet );
	
	return _stZcmdPara.autoNet;
}




u8 zigbeeLqiGet( void )
{
	return _Lqi;
}



void zigbeeInfoRfGet( ST_ZIGBEE_DEV_INFO_RF *pstInfoRf )
{
	pstInfoRf->PowerLevel   = _stZdevInfo.PowerLevel;
	pstInfoRf->RetryNum     = _stZdevInfo.RetryNum;
	pstInfoRf->TranTimeout  = _stZdevInfo.TranTimeout;
}





