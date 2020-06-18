/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/


// 内部使用



//-----------------------------------------------------
static FunN2sTxCB _funN2sTxCB;

void snN2sTxCBset( FunN2sTxCB fun )
{
	_funN2sTxCB = fun;
}

FunN2sTxCB snN2sTxCBget( void )
{
	return _funN2sTxCB;
}

u8 snN2sTxCBisNULL( void )
{
	return _funN2sTxCB == NULL ? 1:0;
}
//-----------------------------------------------------




static int _snN2sTx( u8 *pFrame, u32 len )
{
	if( _funN2sTxCB == NULL )
		return FALSE;

	return _funN2sTxCB(pFrame, len );
		
}

static void _n2sTx( u8 *pFrame, u8 *pLen )
{
	if( aesSwitchGet() == FALSE )
	{
		_snN2sTx( pFrame, *pLen );
		return;
	}

	if( aesEnc( pFrame, pLen ) == FALSE )// aes ERR
	{
		dprintf("_n2sTx X1");
		
		_snN2sTx( pFrame, *pLen ); // 加密 出错明文传输 t
	}
	else
	{
		_snN2sTx( pFrame, *pLen ); // aes OK
	}
}


//========================================================
//========================================================




static int _n2sRspParser( u8 isRedo )
{
	if( gstN2S.frame_parser_rsp == 0 )
		return FALSE;
	
	_snN2sTx( (u8 *)&_stRspFrameParser, RSP_FRAME_LEN ); 

	return TRUE;
}

static int _n2sRspExe( u8 isRedo )
{
	if( gstN2S.frame_exe_rsp == 0 )
		return FALSE;
	
	_snN2sTx( (u8 *)&_stRspFrameExe, RSP_FRAME_LEN );  
	
	return TRUE;
}




static int _n2s_config_ver(  u8 isRedo )
{	
	if( gstN2S.config_ver == 0 )
		return FALSE;
	
	if( isRedo )
	{
		_snN2sTx( (u8 *)&_stRfTxFrame, _stRfTxFrame.len );
		return TRUE;
	}

	paraCfgVerGet( _stRfTxFrame.pBuf + DPACK_OFFSET_PARA );
	
	dpackCreate2( DPACK_PORT_ID_SELF, 0, DPACK_PARA_ID_CONFIG_VER, 4);
	
	txtFrameCreateN2S( TXT_FRAME_ACTION_REPORT_ACK_GET, _stExeFrame.sid, &_stRfTxFrame);

	_n2sTx( (u8 *)&_stRfTxFrame, &_stRfTxFrame.len );
	
	txtFrameExeStateOnEvent( TXT_FRAME_EXE_EVENT_RSP_REPORT );
	_autoReportSid   = _stExeFrame.sid;
	
	return TRUE;
}


static int _n2s_def(  u8 isRedo )
{	
	if( gstN2S.def == 0 )
		return FALSE;

	return TRUE;
}



static int _n2s_aes_switch(  u8 isRedo )
{	
	u8 val;
	
	if( gstN2S.aes_switch == 0 )
		return FALSE;
	
	if( isRedo )
	{
		_snN2sTx( (u8 *)&_stRfTxFrame, _stRfTxFrame.len );
		return TRUE;
	}

	val = paraAesSwitchGet();
	
	dpackCreate( DPACK_PORT_ID_SELF, 0, DPACK_PARA_ID_AES_SWITCH, &val, 1, _stRfTxFrame.pBuf);
	
	txtFrameCreateN2S( TXT_FRAME_ACTION_REPORT_ACK_GET, _stExeFrame.sid, &_stRfTxFrame);

	_n2sTx( (u8 *)&_stRfTxFrame, &_stRfTxFrame.len );
	
	txtFrameExeStateOnEvent( TXT_FRAME_EXE_EVENT_RSP_REPORT );
	_autoReportSid   = _stExeFrame.sid;
	
	return TRUE;
}


static int _n2s_aes_key(  u8 isRedo )
{	
	if( gstN2S.aes_key == 0 )
		return FALSE;
	
	if( isRedo )
	{
		_snN2sTx( (u8 *)&_stRfTxFrame, _stRfTxFrame.len );
		return TRUE;
	}

	paraAesKeyGet( _stRfTxFrame.pBuf + DPACK_OFFSET_PARA );
	
	dpackCreate2( DPACK_PORT_ID_SELF, 0, DPACK_PARA_ID_AES_KEY, AES_KEY_12_LEN );
	
	txtFrameCreateN2S( TXT_FRAME_ACTION_REPORT_ACK_GET, _stExeFrame.sid, &_stRfTxFrame);

	_n2sTx( (u8 *)&_stRfTxFrame, &_stRfTxFrame.len );
	
	txtFrameExeStateOnEvent( TXT_FRAME_EXE_EVENT_RSP_REPORT );
	_autoReportSid   = _stExeFrame.sid;
	
	return TRUE;
}


static int _n2s_reboot( u8 isRedo )
{
#if 0
	if( gstN2S.reboot == 0 )
		return FALSE;
	
	if( isRedo )
	{
		_snN2sTx( (u8 *)&_stRfTxFrame, _stRfTxFrame.len );
		return TRUE;
	}
		
	dpackCreate( DPACK_PORT_ID_SELF, 0, DPACK_PARA_ID_REBOOT, NULL, 0, _stRfTxFrame.pBuf);
	
	txtFrameCreateN2S( TXT_FRAME_ACTION_REPORT_ACK_GET, _stExeFrame.sid, &_stRfTxFrame);

	_n2sTx( (u8 *)&_stRfTxFrame, &_stRfTxFrame.len );
	
	txtFrameExeStateOnEvent( TXT_FRAME_EXE_EVENT_RSP_REPORT );
	
	_autoReportSid   = _stExeFrame.sid;
	
	return TRUE;
#else
	if( gstN2S.reboot == 0 )
		return FALSE;

	if( isRedo )
	{
		_snN2sTx( (u8 *)&_stRfTxFrame, _stRfTxFrame.len );
		return TRUE;
	}
		
	dpackCreate( DPACK_PORT_ID_SELF, 0, DPACK_PARA_ID_REBOOT, NULL, 0, _stRfTxFrame.pBuf);


	if( txtFrameExeStateIsWaitRspResport() == FALSE ) // _stExeFrame 无效
	{
		_autoReportSid++;
		
		txtFrameCreateN2S( TXT_FRAME_ACTION_REPORT_AUTO, _autoReportSid, &_stRfTxFrame);
	}
	else
	{
		txtFrameCreateN2S( TXT_FRAME_ACTION_REPORT_ACK_GET, _stExeFrame.sid, &_stRfTxFrame);
		
		txtFrameExeStateOnEvent( TXT_FRAME_EXE_EVENT_RSP_REPORT );
		_autoReportSid = _stExeFrame.sid;
	}
	
	_n2sTx( (u8 *)&_stRfTxFrame, &_stRfTxFrame.len );


	return TRUE;


#endif

	

}


static int _n2s_sleep_sec( u8 isRedo )
{
	if( gstN2S.sleep_sec == 0 )
		return FALSE;
	
	if( isRedo )
	{
		_snN2sTx( (u8 *)&_stRfTxFrame, _stRfTxFrame.len );
		return TRUE;
	}

	paraSleepSecGet( _stRfTxFrame.pBuf + DPACK_OFFSET_PARA );
	
	dpackCreate2( DPACK_PORT_ID_SELF, 0, DPACK_PARA_ID_SLEEP_SEC, 4);
	
	txtFrameCreateN2S( TXT_FRAME_ACTION_REPORT_ACK_GET, _stExeFrame.sid, &_stRfTxFrame);

	_n2sTx( (u8 *)&_stRfTxFrame, &_stRfTxFrame.len );
	
	txtFrameExeStateOnEvent( TXT_FRAME_EXE_EVENT_RSP_REPORT );
	_autoReportSid   = _stExeFrame.sid;
	
	return TRUE;

}


static int _n2s_work_sec( u8 isRedo )
{
	if( gstN2S.work_sec == 0 )
		return FALSE;
	
	if( isRedo )
	{
		_snN2sTx( (u8 *)&_stRfTxFrame, _stRfTxFrame.len );
		return TRUE;
	}

	paraWorkSecGet( _stRfTxFrame.pBuf + DPACK_OFFSET_PARA );
	
	dpackCreate2( DPACK_PORT_ID_SELF, 0, DPACK_PARA_ID_WORK_SEC, 4);
	
	txtFrameCreateN2S( TXT_FRAME_ACTION_REPORT_ACK_GET, _stExeFrame.sid, &_stRfTxFrame);

	_n2sTx( (u8 *)&_stRfTxFrame, &_stRfTxFrame.len );
	
	txtFrameExeStateOnEvent( TXT_FRAME_EXE_EVENT_RSP_REPORT );
	_autoReportSid   = _stExeFrame.sid;
	
	return TRUE;

}





static int _n2s_ver(  u8 isRedo )
{
	u8 ver;
	
	if( gstN2S.ver == 0 )
		return FALSE;
	
	if( isRedo )
	{
		_snN2sTx( (u8 *)&_stRfTxFrame, _stRfTxFrame.len );
		return TRUE;
	}

	ver = paraVerGet();
	
	dpackCreate( DPACK_PORT_ID_SELF, 0, DPACK_PARA_ID_VER, &ver, 1, _stRfTxFrame.pBuf);
	
	txtFrameCreateN2S( TXT_FRAME_ACTION_REPORT_ACK_GET, _stExeFrame.sid, &_stRfTxFrame);

	_n2sTx( (u8 *)&_stRfTxFrame, &_stRfTxFrame.len );
	
	txtFrameExeStateOnEvent( TXT_FRAME_EXE_EVENT_RSP_REPORT );
	_autoReportSid   = _stExeFrame.sid;
	
	return TRUE;
}

static int _n2s_dev_type(  u8 isRedo )
{
	u8 val;
	
	if( gstN2S.dev_type== 0 )
		return FALSE;

	if( isRedo )
	{
		_snN2sTx( (u8 *)&_stRfTxFrame, _stRfTxFrame.len );
		return TRUE;
	}

	val = paraDevTypeGet();
	
	dpackCreate( DPACK_PORT_ID_SELF, 0, DPACK_PARA_ID_DEV_TYPE, &val, 1, _stRfTxFrame.pBuf);
	
	txtFrameCreateN2S( TXT_FRAME_ACTION_REPORT_ACK_GET, _stExeFrame.sid, &_stRfTxFrame);

	_n2sTx( (u8 *)&_stRfTxFrame, &_stRfTxFrame.len );
	
	txtFrameExeStateOnEvent( TXT_FRAME_EXE_EVENT_RSP_REPORT );
	_autoReportSid   = _stExeFrame.sid;
	
	return TRUE;
}

static int _n2s_heartbeat( u8 isRedo )
{	
	if( gstN2S.heartbeat == 0 )
		return FALSE;
	
	if( isRedo )
	{
		_snN2sTx( (u8 *)&_stRfTxFrame, _stRfTxFrame.len );
		return TRUE;
	}

	dpackCreate( DPACK_PORT_ID_SELF, 0, DPACK_PARA_ID_HEARTBEAT, NULL, 0, _stRfTxFrame.pBuf);

	if( txtFrameExeStateIsWaitRspResport() == FALSE ) // _stExeFrame 无效
	{
		_autoReportSid++;
		
		txtFrameCreateN2S( TXT_FRAME_ACTION_REPORT_AUTO, _autoReportSid, &_stRfTxFrame);
	}
	else
	{
		txtFrameCreateN2S( TXT_FRAME_ACTION_REPORT_ACK_GET, _stExeFrame.sid, &_stRfTxFrame);
		
		txtFrameExeStateOnEvent( TXT_FRAME_EXE_EVENT_RSP_REPORT );
		_autoReportSid = _stExeFrame.sid;
	}
	
	_n2sTx( (u8 *)&_stRfTxFrame, &_stRfTxFrame.len );
	
	return TRUE;
}

static int _n2s_battery(  u8 isRedo )
{	
	u8 pVal[2];

	if( gstN2S.battery == 0 )
		return FALSE;
	
	if( isRedo )
	{
		_snN2sTx( (u8 *)&_stRfTxFrame, _stRfTxFrame.len );
		return TRUE;
	}

	paraBatteryGet( pVal );
	
	dpackCreate( DPACK_PORT_ID_SELF, 0, DPACK_PARA_ID_BATTERY, pVal, 2, _stRfTxFrame.pBuf);
	

	if( txtFrameExeStateIsWaitRspResport() == FALSE ) // _stExeFrame 无效
	{
		_autoReportSid++;
		txtFrameCreateN2S( TXT_FRAME_ACTION_REPORT_ACK_GET, _autoReportSid, &_stRfTxFrame);
	}
	else
	{
		txtFrameCreateN2S( TXT_FRAME_ACTION_REPORT_ACK_GET, _stExeFrame.sid, &_stRfTxFrame);
		
		txtFrameExeStateOnEvent( TXT_FRAME_EXE_EVENT_RSP_REPORT );
		_autoReportSid	 = _stExeFrame.sid;
	}

	_n2sTx( (u8 *)&_stRfTxFrame, &_stRfTxFrame.len );
	
	
	return TRUE;
}




static int _n2s_ctrl_mode(  u8 isRedo )
{	
	u8 ctrlMode;

	if( gstN2S.ctrl_mode == 0 )
		return FALSE;
	
	if( isRedo )
	{
		_snN2sTx( (u8 *)&_stRfTxFrame, _stRfTxFrame.len );
		return TRUE;
	}

	ctrlMode = paraCtrlModeGet();
	
	dpackCreate( DPACK_PORT_ID_SELF, 0, DPACK_PARA_ID_CTRL_MODE, &ctrlMode, 1, _stRfTxFrame.pBuf);
	
	txtFrameCreateN2S( TXT_FRAME_ACTION_REPORT_ACK_GET, _stExeFrame.sid, &_stRfTxFrame);

	_n2sTx( (u8 *)&_stRfTxFrame, &_stRfTxFrame.len );
	
	txtFrameExeStateOnEvent( TXT_FRAME_EXE_EVENT_RSP_REPORT );
	_autoReportSid   = _stExeFrame.sid;
	
	return TRUE;
}





static int _n2s_cmd_ctrl(  u8 isRedo )
{	
	u8 val;

	if( gstN2S.cmd_ctrl == 0 )
		return FALSE;
	
	if( isRedo )
	{
		_snN2sTx( (u8 *)&_stRfTxFrame, _stRfTxFrame.len );
		return TRUE;
	}

	val = paraCmdCtrlGet();
	
	dpackCreate( DPACK_PORT_ID_SELF, 0, DPACK_PARA_ID_CMD_CTRL, &val, 1, _stRfTxFrame.pBuf);
	
	txtFrameCreateN2S( TXT_FRAME_ACTION_REPORT_ACK_GET, _stExeFrame.sid, &_stRfTxFrame);

	_n2sTx( (u8 *)&_stRfTxFrame, &_stRfTxFrame.len );
	
	txtFrameExeStateOnEvent( TXT_FRAME_EXE_EVENT_RSP_REPORT );
	_autoReportSid   = _stExeFrame.sid;
	
	return TRUE;
}




static int _n2s_open_sec( u8 isRedo )
{
	if( gstN2S.open_sec == 0 )
		return FALSE;
	
	if( isRedo )
	{
		_snN2sTx( (u8 *)&_stRfTxFrame, _stRfTxFrame.len );
		return TRUE;
	}

	paraCtrlOpenSecGet( _stRfTxFrame.pBuf + DPACK_OFFSET_PARA );
	
	dpackCreate2( DPACK_PORT_ID_SELF, 0, DPACK_PARA_ID_OPEN_SEC, 4);
	
	txtFrameCreateN2S( TXT_FRAME_ACTION_REPORT_ACK_GET, _stExeFrame.sid, &_stRfTxFrame);

	_n2sTx( (u8 *)&_stRfTxFrame, &_stRfTxFrame.len );
	
	txtFrameExeStateOnEvent( TXT_FRAME_EXE_EVENT_RSP_REPORT );
	_autoReportSid   = _stExeFrame.sid;
	
	return TRUE;

}


static int _n2s_period_ctrl( u8 isRedo )
{
	if( gstN2S.period_ctrl == 0 )
		return FALSE;
	
	if( isRedo )
	{
		_snN2sTx( (u8 *)&_stRfTxFrame, _stRfTxFrame.len );
		return TRUE;
	}

	paraPeriodCtrlGet( _stRfTxFrame.pBuf + DPACK_OFFSET_PARA );
	
	dpackCreate2( DPACK_PORT_ID_SELF, 0, DPACK_PARA_ID_PERIOD_CTRL, 8);
	
	txtFrameCreateN2S( TXT_FRAME_ACTION_REPORT_ACK_GET, _stExeFrame.sid, &_stRfTxFrame);

	_n2sTx( (u8 *)&_stRfTxFrame, &_stRfTxFrame.len );
	
	txtFrameExeStateOnEvent( TXT_FRAME_EXE_EVENT_RSP_REPORT );
	_autoReportSid   = _stExeFrame.sid;
	
	return TRUE;

}


	
static int _n2s_ctrl_pack( u8 isRedo )
{
	int len;
	
	if( gstN2S.ctrl_pack == 0 )
		return FALSE;
	
	if( isRedo )
	{
		_snN2sTx( (u8 *)&_stRfTxFrame, _stRfTxFrame.len );
		return TRUE;
	}

	len = paraCtrlPackGet( _stRfTxFrame.pBuf + DPACK_OFFSET_PARA );
	
	dpackCreate2( DPACK_PORT_ID_SELF, 0, DPACK_PARA_ID_CTRL_PACK,  len );
	
	txtFrameCreateN2S( TXT_FRAME_ACTION_REPORT_ACK_GET, _stExeFrame.sid, &_stRfTxFrame);

	_n2sTx( (u8 *)&_stRfTxFrame, &_stRfTxFrame.len );
	
	txtFrameExeStateOnEvent( TXT_FRAME_EXE_EVENT_RSP_REPORT );
	_autoReportSid	 = _stExeFrame.sid;
	
	return TRUE;

}



//----------------zigbee------------------------------------------------------------


static int _n2s_zigbee_to_reset(  u8 isRedo )
{	
	if( gstN2S.zigbee_to_reset == 0 )
		return FALSE;
	
	return TRUE;
}

static int _n2s_zigbee_to_def(  u8 isRedo )
{	
	if( gstN2S.zigbee_to_def == 0 )
		return FALSE;
	
	return TRUE;
}


static int _n2s_zigbee_auto_net(  u8 isRedo )
{	
	u8  val;

	if( gstN2S.zigbee_auto_net == 0 )
		return FALSE;
	
	if( isRedo )
	{
		_snN2sTx( (u8 *)&_stRfTxFrame, _stRfTxFrame.len );
		return TRUE;
	}

	val = paraZigbeeAutoNetGet();  
	
	dpackCreate( DPACK_PORT_ID_SELF, 0, DPACK_PARA_ID_ZIGBEE_AUTO_NET, &val, 1, _stRfTxFrame.pBuf);
	
	txtFrameCreateN2S( TXT_FRAME_ACTION_REPORT_ACK_GET, _stExeFrame.sid, &_stRfTxFrame);

	_n2sTx( (u8 *)&_stRfTxFrame, &_stRfTxFrame.len );

	
	txtFrameExeStateOnEvent( TXT_FRAME_EXE_EVENT_RSP_REPORT );
	_autoReportSid	 = _stExeFrame.sid;
	
	return TRUE;
}





static int _n2s_zigbee_state(  u8 isRedo )
{	
	u8  val;
	
	if( gstN2S.zigbee_state == 0 )
		return FALSE;
	

	if( isRedo )
	{
		_snN2sTx( (u8 *)&_stRfTxFrame, _stRfTxFrame.len );
		return TRUE;
	}

	val = paraZigbeeWorkStateGet();  
	
	dpackCreate( DPACK_PORT_ID_SELF, 0, DPACK_PARA_ID_ZIGBEE_STATE, &val, 1, _stRfTxFrame.pBuf);
	
	txtFrameCreateN2S( TXT_FRAME_ACTION_REPORT_ACK_GET, _stExeFrame.sid, &_stRfTxFrame);

	_n2sTx( (u8 *)&_stRfTxFrame, &_stRfTxFrame.len );

	
	txtFrameExeStateOnEvent( TXT_FRAME_EXE_EVENT_RSP_REPORT );
	_autoReportSid	 = _stExeFrame.sid;

	return TRUE;
}

static int _n2s_zigbee_info(  u8 isRedo )
{	
	ST_ZIGBEE_DEV_INFO_RF  stInfoRf;
	
	if( gstN2S.zigbee_info == 0 )
		return FALSE;
	

	if( isRedo )
	{
		_snN2sTx( (u8 *)&_stRfTxFrame, _stRfTxFrame.len );
		return TRUE;
	}

	paraZigbeeInfoGet( &stInfoRf );  
	
	dpackCreate( DPACK_PORT_ID_SELF, 0, DPACK_PARA_ID_ZIGBEE_INFO, (u8 *)&stInfoRf, sizeof(ST_ZIGBEE_DEV_INFO_RF ), _stRfTxFrame.pBuf);
	
	txtFrameCreateN2S( TXT_FRAME_ACTION_REPORT_ACK_GET, _stExeFrame.sid, &_stRfTxFrame);

	_n2sTx( (u8 *)&_stRfTxFrame, &_stRfTxFrame.len );

	
	txtFrameExeStateOnEvent( TXT_FRAME_EXE_EVENT_RSP_REPORT );
	_autoReportSid	 = _stExeFrame.sid;
	
	return TRUE;
}




//------------------- water ctrl ----------------------------------------------------------------





static int _n2s_uart485(  u8 isRedo )
{	
	#if 0
		#include "m485_uart.h"
		
		U16 len;
		U8 addr;
		
		if( gstN2S.uart485 == 0 )
			return FALSE;

		
		
		if( isRedo )
		{
			_snN2sTx( (u8 *)&_stRfTxFrame, _stRfTxFrame.len );
			return TRUE;
		}


		len = uart485RxGet( _stRfTxFrame.pBuf + DPACK_OFFSET_PARA );
		addr = modUart485AddrGet();
		
		dpackCreate2( DPACK_PORT_ID_UART1, addr, DPACK_PARA_ID_UART485, len );


		if( txtFrameExeStateIsWaitRspResport() == FALSE ) // _stExeFrame 无效
		{
			_autoReportSid++;
			txtFrameCreateN2S( TXT_FRAME_ACTION_REPORT_AUTO, _autoReportSid, &_stRfTxFrame);
		}
		else
		{
			txtFrameCreateN2S( TXT_FRAME_ACTION_REPORT_ACK_GET, _stExeFrame.sid, &_stRfTxFrame);
			
			txtFrameExeStateOnEvent( TXT_FRAME_EXE_EVENT_RSP_REPORT );
			_autoReportSid	 = _stExeFrame.sid;
		}

		
		_n2sTx( (u8 *)&_stRfTxFrame, &_stRfTxFrame.len );
		
		return TRUE;

	#endif

	return FALSE;

}






//-----主动拉取服务器上的信息-----------------------------

static int _n2s_ctrl_pack_get( u8 isRedo )
{
	u8 pVal[2];
	//int len;
	
	if( gstN2S.ctrl_pack_get == 0 )
		return FALSE;
	
	if( isRedo )
	{
		_snN2sTx( (u8 *)&_stRfTxFrame, _stRfTxFrame.len );
		return TRUE;
	}

	//len = paraCtrlPackGet( _stRfTxFrame.pBuf + DPACK_OFFSET_PARA );

	
	paraBatteryGet( pVal );
	
	dpackCreate( DPACK_PORT_ID_SELF, 0, DPACK_PARA_ID_BATTERY, pVal, 2, _stRfTxFrame.pBuf);
	
	//dpackCreate2( DPACK_PORT_ID_SELF, 0, DPACK_PARA_ID_CTRL_PACK,  0 );

	_autoReportSid++;
	txtFrameCreateN2S( TXT_FRAME_ACTION_GET, _autoReportSid, &_stRfTxFrame);

	_n2sTx( (u8 *)&_stRfTxFrame, &_stRfTxFrame.len );
	
	txtFrameExeStateOnEvent( TXT_FRAME_EXE_EVENT_RSP_REPORT ); // fenghuiw  TXT_FRAME_EXE_EVENT_RSP_REPORT ?
	
	return TRUE;

}







typedef  int ( *FunN2sCB)(  u8 isRedo );

const FunN2sCB _n2sArr[]={
	NULL,
	_n2sRspParser, // 1
	_n2sRspExe,    // 2
	//--------------------------------
	
	_n2s_config_ver,// 3
	_n2s_def,// 4
	_n2s_aes_switch,// 5
	_n2s_aes_key,// 6
	_n2s_reboot,// 7
	_n2s_sleep_sec,// 8
	_n2s_work_sec,// 9
	_n2s_ver,// 10
	_n2s_dev_type,// 11
	_n2s_heartbeat,// 12
	_n2s_battery,// 13
	_n2s_ctrl_mode,// 14
	_n2s_cmd_ctrl,// 15
	_n2s_open_sec,// 16
	_n2s_period_ctrl,// 17
	_n2s_ctrl_pack,// 18
	_n2s_zigbee_to_reset,// 19
	_n2s_zigbee_to_def,// 20
	_n2s_zigbee_auto_net,// 21
	_n2s_zigbee_state,// 22
	_n2s_zigbee_info,// 23
	_n2s_uart485,// 24

	//-----主动拉取服务器上的信息-----------------------------
	_n2s_ctrl_pack_get,


};


//=======================================================================
//=======================================================================


static void _rspRspParser( void )
{
	gstN2S.frame_parser_rsp = 0;
}

static void _rspRspExe( void )
{
	gstN2S.frame_exe_rsp = 0;
}

static void _rsp_config_ver( void )
{
	gstN2S.config_ver = 0;
}

static void _rsp_def( void )
{
	gstN2S.def = 0;
}

static void _rsp_aes_switch( void )
{
	gstN2S.aes_switch = 0;
}

static void _rsp_aes_key( void )
{
	gstN2S.aes_key = 0;
}

static void _rsp_reboot( void )
{
	gstN2S.reboot = 0;
}

static void _rsp_sleep_sec( void )
{
	gstN2S.sleep_sec = 0;
}

static void _rsp_work_sec( void )
{
	gstN2S.work_sec = 0;
}

static void _rsp_ver( void )
{
	gstN2S.ver = 0;
}

static void _rsp_dev_type( void )
{
	gstN2S.dev_type = 0;
}

static void _rsp_heartbeat( void )
{
	gstN2S.heartbeat = 0;
}

static void _rsp_battery( void )
{
	gstN2S.battery = 0;

	//gB1.battTxFinish = 1;
}

static void _rsp_ctrl_mode( void )
{
	gstN2S.ctrl_mode = 0;
}

static void _rsp_cmd_ctrl( void )
{
	gstN2S.cmd_ctrl = 0;
}


static void _rsp_open_sec( void )
{
	gstN2S.open_sec = 0;
}


static void _rsp_period_ctrl( void )
{
	gstN2S.period_ctrl = 0;
}

static void _rsp_ctrl_pack( void )
{
	gstN2S.ctrl_pack = 0;
}


static void _rsp_zigbee_to_reset( void )
{
	gstN2S.zigbee_to_reset = 0;
}

static void _rsp_zigbee_to_def( void )
{
	gstN2S.zigbee_to_def = 0;
}

static void _rsp_zigbee_auto_net( void )
{
	gstN2S.zigbee_auto_net = 0;
}


static void _rsp_zigbee_state( void )
{
	gstN2S.zigbee_state = 0;
}

static void _rsp_zigbee_info( void )
{
	gstN2S.zigbee_info = 0;
}



static void _rsp_uart485( void )
{
	gstN2S.uart485 = 0;
}



//-----主动拉取服务器上的信息-----------------------------

static void _rsp_ctrl_pack_get( void )
{
	gstN2S.ctrl_pack_get = 0;
}


//=================================================
//=================================================








typedef  void ( *FunRspCB)(  void );

const FunRspCB _rspArr[]={
	NULL,
	_rspRspParser, // 1
	_rspRspExe,    // 2
	//-------------------------------
	
	_rsp_config_ver,// 3
	_rsp_def,// 4
	_rsp_aes_switch,// 5
	_rsp_aes_key,// 6
	_rsp_reboot,// 7
	_rsp_sleep_sec,// 8
	_rsp_work_sec,// 9
	_rsp_ver,// 10
	_rsp_dev_type,// 11
	_rsp_heartbeat,// 12
	_rsp_battery,// 13
	_rsp_ctrl_mode,// 14
	_rsp_cmd_ctrl,// 15
	_rsp_open_sec,// 16
	_rsp_period_ctrl,// 17
	_rsp_ctrl_pack,// 18
	_rsp_zigbee_to_reset,// 19
	_rsp_zigbee_to_def,// 20
	_rsp_zigbee_auto_net,// 21
	_rsp_zigbee_state,// 22
	_rsp_zigbee_info,// 23
	_rsp_uart485,// 24

	_rsp_ctrl_pack_get,


};


