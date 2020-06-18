/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/

// sg: Server and gateway communication  服务器和网关通信
// g2s: gateway to server                 网关发送给服务器

#include "com_includes.h"

#include "timer.h"
#include "dbg_uart.h"


#include "aes_mod.h"
#include "frame.h"


#include "zgb_cmd.h"


#include "sn_n2s.h"
#include "sn_n2s_state.h"
#include "sn_rx_unpack.h"
#include "sn_master_state.h"




static ST_FRAME _stExeFrame; // rf in to exe
static ST_FRAME _stRfTxFrame;// rf out 


static ST_RSP_FRAME _stRspFrameExe;
static ST_RSP_FRAME _stRspFrameParser;

ST_N2S gstN2S;

static u8 _autoReportSid = 0;


static u8 _n2sReDoCnt    = N2S_REDO_CNT;       // 发送次数记数
static u8 _n2sReDoGapCnt = N2S_REDO_GAP_CNT ;  // 
static EN_N2S_SEND_CMD_ID _n2sCurId      = N2S_SEND_CID_NULL ; // 当前发送的ID



u8 snN2sIsRspCurTxCmdSid( u8 sid )
{
	if( _stRfTxFrame.sid == sid )
		return TRUE;

	return FALSE;
}


void snN2sPoll( void ) // 50ms
{
	comU8Dec( &_n2sReDoGapCnt );	
}


u8 snN2sIsIng( void ) // 正在发送中
{
	if( _n2sCurId == N2S_SEND_CID_NULL )
		return FALSE;

	return TRUE;
}


static int _n2sCurIsRsp( void ) // 当前发送的数据项 是不是 应答帧
{
	if( _n2sCurId == N2S_SEND_CID_FRAME_EXE_RSP || _n2sCurId == N2S_SEND_CID_FRAME_PARSER_RSP )
		return TRUE;

	return FALSE;
}


u8 n2sIsHave( void ) // 有数据项要发送
{
	ST_N2S temp = {0};

	if( memcmp( &gstN2S, &temp, sizeof(ST_N2S) ) != 0 )
		return TRUE;
	
	return FALSE;
}




static void _n2sClearCur( void ) // 清除当前发送的数据项
{
	snN2sOnRsp();
	_n2sCurId = N2S_SEND_CID_NULL;
}





// id: 1-- N2S_CNT
static EN_N2S_SEND_CMD_ID _n2sGetId( void ) // 得到 要发送数据项的ID
{
	if( gstN2S.frame_parser_rsp )
		return N2S_SEND_CID_FRAME_PARSER_RSP;

	if( gstN2S.frame_exe_rsp )
		return N2S_SEND_CID_FRAME_EXE_RSP;
	
	if( gstN2S.config_ver)
		return N2S_SEND_CID_CONFIG_VER;

	if( gstN2S.def)
		return N2S_SEND_CID_DEF;
	
	if( gstN2S.aes_switch)
		return N2S_SEND_CID_AES_SWITCH;
	
	if( gstN2S.aes_key)
		return N2S_SEND_CID_AES_KEY;

	if( gstN2S.reboot)
		return N2S_SEND_CID_REBOOT;

	if( gstN2S.sleep_sec)
		return N2S_SEND_CID_SLEEP_SEC;
	
	if( gstN2S.work_sec)
		return N2S_SEND_CID_WORK_SEC;
		
	if( gstN2S.ver)
		return N2S_SEND_CID_VER;

	if( gstN2S.dev_type)
		return N2S_SEND_CID_DEV_TYPE;

	if( gstN2S.heartbeat)
		return N2S_SEND_CID_HEARTBEAT;

	if( gstN2S.battery)
		return N2S_SEND_CID_BATTERY;
	
	if( gstN2S.ctrl_mode)
		return N2S_SEND_CID_CTRL_MODE;

	if( gstN2S.cmd_ctrl)
		return N2S_SEND_CID_CMD_CTRL;
	
	if( gstN2S.open_sec)
		return N2S_SEND_CID_OPEN_SEC;
	
	if( gstN2S.period_ctrl)
		return N2S_SEND_CID_PERIOD_CTRL;

	if( gstN2S.ctrl_pack)
		return N2S_SEND_CID_CTRL_PACK;

	if( gstN2S.zigbee_to_reset)
		return N2S_SEND_CID_ZIGBEE_TO_RESET;
	
	if( gstN2S.zigbee_to_def)
		return N2S_SEND_CID_ZIGBEE_TO_DEF;

	if( gstN2S.zigbee_auto_net)
		return N2S_SEND_CID_ZIGBEE_AUTO_NET;

	if( gstN2S.zigbee_state)
		return N2S_SEND_CID_ZIGBEE_STATE;	
	
	if( gstN2S.zigbee_info)
		return N2S_SEND_CID_ZIGBEE_INFO;

	if( gstN2S.uart485 )
		return N2S_SEND_CID_UART485;

	
	//-----主动拉取服务器上的信息-----------------------------
	if( gstN2S.ctrl_pack_get )
		return N2S_SEND_CID_CTRL_PACK_GET;

	//----------------------------------------

	return N2S_SEND_CID_NULL;
}


void n2sHeartbeat( void )
{
	gstN2S.heartbeat = 1;
}

void n2sBattRpt( void )
{
	gstN2S.battery = 1;
}


void n2sCtrlPackGet( void )
{
	gstN2S.ctrl_pack_get = 1;
}


#include "sn_n2s_fun.h" // 内部使用



static int _n2s( u8 isRedo )
{
	if( _n2sCurId ==  N2S_SEND_CID_NULL )
		return FALSE;

	return _n2sArr[ (u8)_n2sCurId ]( isRedo );
}


void snN2sOnRsp( void )
{
	#include "dev_state.h"
	
	if( _n2sCurId ==  N2S_SEND_CID_NULL )
		return;


	if( _n2sCurId == N2S_SEND_CID_CTRL_PACK_GET )
	{
		gB1.ctrlPackFinish = 1; // 
	}
	/*
	else if( _n2sCurId == N2S_SEND_CID_BATTERY )
	{
		gB1.battTxFinish = 1;
	}*/

	_rspArr[ (u8)_n2sCurId ]();
	

	if( devStateIsReadCtrlInfo() )
	{
		devOnEvent( DEV_EVENT_READ_CTRL_INFO_END, NULL );
	}
}




u8 n2sCB( void ) //
{
	if( snN2sIsIng() ) // 正在发送中
	{
		if( _n2sReDoGapCnt != 0 ) 
		{
			return FALSE;  // 重发间隔时间没有到
		}
		
		_n2sReDoGapCnt = N2S_REDO_GAP_CNT; // 重发间隔时间已到， 重新装载
		
		comU8Dec( &_n2sReDoCnt );
		
		if( _n2sReDoCnt == 0 && _n2sCurId != N2S_SEND_CID_REBOOT )// 重发次数用完了
		{
			_n2sClearCur(); 

			modMasterStateSet( MASTER_STATE_NG );
			
			dprintf("c" ); // redo clear
		}
		else// 重发
		{
			_n2s( 1 );
			return TRUE;
		}

		return FALSE;
	}



	// 空闲中
	if( n2sIsHave() == FALSE ) 
		return FALSE;
	

	_n2sCurId = _n2sGetId();
	if( _n2sCurId == N2S_SEND_CID_NULL )
	{
		dprintf( "_n2sGetId() err" );
		return FALSE;
	}
	

	//  有数据项要发送
	_n2s( 0 );

	if( _n2sCurIsRsp() )
	{
		_n2sClearCur(); 
	}

	
	_n2sReDoGapCnt = N2S_REDO_GAP_CNT;
	_n2sReDoCnt    = N2S_REDO_CNT;

	return TRUE;	
}









//========================================================


static void _txtFrameExeToRsp( EN_RSP_FRAME_VAL val, u8 sid )
{	
	//dprintf("exeRsp=%d", val);

	_stRspFrameExe.val    = val;

	zigbeeMyMacGet( _stRspFrameExe.pMac );
	_stRspFrameExe.sid    = sid;
	resFrameCreate( &_stRspFrameExe, 0 );

	//dprintfBuf( NULL, (u8 *) &_stRspFrameExe, _stRspFrameExe.len, 0 );

	gstN2S.frame_exe_rsp = 1;

}

static void _txtFrameParserToRsp( EN_RSP_FRAME_VAL val, u8 sid )
{
	//dprintf("parserRsp=%d", val);

	_stRspFrameParser.val    = val;
	
	zigbeeMyMacGet( _stRspFrameExe.pMac );
	
	_stRspFrameParser.sid    = sid;
	
	resFrameCreate( &_stRspFrameParser, 0 );

	gstN2S.frame_parser_rsp = 1;

}




int _txtFrameExe( u8 *pFrame, u8 len )
{
	int rst;

	// 1 copy to _stExeFrame
	memcpy( &_stExeFrame, pFrame, len);

	// 3 frame pack data
	//dprintf("_dpackexe_");
	
	if( dpackExe( &_stExeFrame ) == TRUE )
	{
		_txtFrameExeToRsp( RSP_FRAME_VAL_ACK, _stExeFrame.sid);	

		rst = TRUE;

		txtFrameExeStateOnEvent( TXT_FRAME_EXE_EVENT_EXE_OK );

		//dprintf("_dpack exe ok_");
	}
	else
	{
		dprintfBuf("_txtFrameExe", pFrame,len, 0 );
		
		_txtFrameExeToRsp( RSP_FRAME_VAL_ERR, _stExeFrame.sid);
		rst = FALSE;

		txtFrameExeStateOnEvent( TXT_FRAME_EXE_EVENT_EXE_NG );

	}

	return rst;


}



int n2sTxCmdOnRxOkRsp( void )
{
	txtFrameExeStateOnEvent( TXT_FRAME_EXE_EVENT_RX_TXT );

	if( txtFrameExeStateIsUnpack() == FALSE )
	{
		dprintf("sgTxCmdOnRxOkRsp ERR1");
		return FALSE;
	}
	
	// ---- rsp frame -----
	modMasterStateSet( MASTER_STATE_OK );
	
	_n2sClearCur();
	return TRUE;
}



int snOnRx( u8 *pFrame, u8 inLen )
{
	EN_FRAME_UNPACK rst;
	u8 len;

	if( snRxUnpack( pFrame, inLen ) == FALSE )
	{
		return FALSE;
	}

	txtFrameExeStateOnEvent( TXT_FRAME_EXE_EVENT_RX_TXT );

	
	if( txtFrameExeStateIsUnpack() == FALSE )
	{
		dprintf("txtFrameExeERR1");
		return FALSE;
	}

	/*
	// ---- rsp frame -----
	if( sgRxUnpackRstIsRsp() ) // 接收到 正确的 RSP
	{
		modMasterStateSet( MASTER_STATE_OK );
		
		_n2sClearCur();
		return TRUE;
	}	
	*/


	// ---- txt frame -----
	len = inLen;

	//--------------加密处理--------------------------------
	if( txtFrameVerIsEnc( pFrame[TXT_FRAME_OFFSET_VER]  ) == TRUE ) // 是否加密
	{	
		aesDec( pFrame, &len );
	}
	//------------------------------------------------------

	
	rst = txtFrameUnpack( pFrame, len, 0);
	if( rst  != FRAME_UNPACK_OK )
	{
		if( txtFrameOnErrIsToRsp( pFrame, len ) )
		{
			_txtFrameParserToRsp(RSP_FRAME_VAL_ERR, pFrame[TXT_FRAME_OFFSET_SID] );
		}

		txtFrameExeStateOnEvent( TXT_FRAME_EXE_EVENT_UNPACK_NG );
		
		dprintfBuf("txtFrameExeERR2_unknow_",  pFrame, len, 0);
		
		return FALSE;
	}
	
	//dprintf("_unpack ok_");

	modMasterStateSet( MASTER_STATE_OK );


	
	txtFrameExeStateOnEvent( TXT_FRAME_EXE_EVENT_UNPACK_OK );


	if( txtFrameExeStateIsExe() == FALSE )
	{
		dprintf("txtFrameExeERR3");
		return FALSE;
	}

	//dprintf("_to exe_");

	return _txtFrameExe(pFrame, len);
}





void snN2sInit( void )
{
	memset( &_stExeFrame,  0, sizeof(ST_FRAME) );
	memset( &_stRfTxFrame, 0, sizeof(ST_FRAME) );

	memset( &_stRspFrameExe,    0, sizeof(ST_RSP_FRAME) );
	memset( &_stRspFrameParser, 0, sizeof(ST_RSP_FRAME) );

	
	memset( &gstN2S, 0, sizeof(ST_N2S) );

	_autoReportSid = 0;


	_n2sCurId      = N2S_SEND_CID_NULL ; // 当前发送的ID
	_n2sReDoCnt    = N2S_REDO_CNT;       // 发送次数记数
	_n2sReDoGapCnt = N2S_REDO_GAP_CNT ;  //

	_funN2sTxCB = NULL;

}







