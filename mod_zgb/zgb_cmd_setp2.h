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
//===== // step 2 =========传入参数(可选)，设置发送命令标志===========================
//====================================================================================
int zcmdDevInfoGet( void )
{
	if( _stZcmdTx.devInfoGet == 1 )
	{
		return FALSE;
	}

	_stZcmdTx.devInfoGet = 1;
	
	return TRUE;
}


int zcmdDevInfoSet( ST_ZIGBEE_DEV_INFO_RF *pstSet )
{
	if( _stZcmdPara.isOk == 0 )
		return FALSE;
	
	if( _stZcmdTx.devInfoSet == 1 )
	{
		return FALSE;
	}
	
	_stZdevInfo.PowerLevel	= pstSet->PowerLevel;
	_stZdevInfo.RetryNum	= pstSet->RetryNum;
	_stZdevInfo.TranTimeout = pstSet->TranTimeout;
	
	_stZcmdTx.devInfoSet = 1;

	//modUartDebugTxU8buf( (u8 *)&_stZdevInfo, sizeof(ST_ZIGBEE_DEV_INFO) );

	return TRUE;
}

int zcmdReboot( void )
{
	if( _stZcmdTx.reboot == 1 )
	{
		return FALSE;
	}
	
	_stZcmdTx.reboot = 1; 

	return TRUE;
}


int zcmdDef( void )
{
	if( _stZcmdTx.def == 1 )
	{
		return FALSE;
	}
	
	_stZcmdTx.def = 1;

	_stZcmdTx.reboot = 1; // 注意: 需要 RESET

	return TRUE;
}





int zcmdAutoNet( u8 open )
{
#if 0
	if( _stZcmdTx.autoNet == 1 )
	{
		if( _stZcmdPara.autoNet == open )
		{
			return FALSE;
		}

		if( open )
			_stZcmdPara.autoNet = 1;
		else
			_stZcmdPara.autoNet = 0;
			
		return TRUE;
	}

	_stZcmdTx.autoNet = 1;
	
	return TRUE;
#else
	if( _stZcmdTx.autoNet == 1 )
	{	
		return FALSE;
	}

	if( open )
		_stZcmdPara.autoNet = 1;
	else
		_stZcmdPara.autoNet = 0;

	_stZcmdTx.autoNet = 1;

	return TRUE;

#endif

	
}



int zcmdWorkStateGet( void )
{
	if( _stZcmdTx.workState == 1 )
	{
		return FALSE;
	}

	_stZcmdTx.workState = 1;
	
	return TRUE;
}


//=============================================================
int zcmdLqiGet( void )
{
	if( _stZcmdTx.lqi == 1 )
	{
		return FALSE;
	}

	_stZcmdTx.lqi = 1;
	
	return TRUE;
}

int zcmdSleep( void )
{
	if( _stZcmdTx.sleep == 1 )
	{
		return FALSE;
	}

	_stZcmdTx.sleep = 1;
	
	return TRUE;
}




