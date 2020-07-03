
#if 1

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
#include "dri.h"
#include "timer.h"

#include "f_txt_frame_dpara_ctrl.h"
#include "f_txt_frame_data.h"

#include "cfg_ctrl.h"



#include "dbg_uart.h"














// ------------- ctrlMode  -----------------------------------------

#include "ctrl_mode.h"


int paraCtrlModeSet( u8 *pPara  )
{
	if( *pPara == 0 )
	{
		ctrlModeSet( CTRL_MODE_CMD );
	}
	else if( *pPara == 1 )
	{
		ctrlModeSet( CTRL_MODE_PERIOD );
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}


u8 paraCtrlModeGet( void )
{
	if( ctrlModeIsCmd() )
		return 0;

	return 1;
}


u8 para_ctrl_mode_exe( ST_FRAME *pstFrame )
{
	if( pstFrame->action == TXT_FRAME_ACTION_GET )
	{
		gstN2S.ctrl_mode = 1;
		gB1.txtFrameExeOKhaveRspReport = 1;

		return TRUE;
	}
	else if( pstFrame->action == TXT_FRAME_ACTION_SET )
	{
		if( paraCtrlModeSet( pstFrame->pBuf + DPACK_OFFSET_PARA ) == FALSE )
			return FALSE;
		
		//gstN2S.ctrl_mode = 1;
		//gB1.txtFrameExeOKhaveRspReport = 1;

		return TRUE;
	}
	return FALSE;
}



// ------------- cmd ctrl  -----------------------------------------
#include "ctrl_cmd_ctrl.h"

int paraCmdCtrlSet( u8 *pPara  )
{
	if( *pPara == 0 )
	{
		ctrlCmdCtrlClose();
	}
	else if( *pPara == 1 )
	{
		ctrlCmdCtrlOpen();
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}


u8 paraCmdCtrlGet( void )
{
	if( ctrlCmdCtrlStateIsOpen() )
		return 1;

	return 0;
}


u8 para_cmd_ctrl_exe( ST_FRAME *pstFrame )
{
	if( pstFrame->action == TXT_FRAME_ACTION_GET )
	{
		gstN2S.cmd_ctrl = 1;
		gB1.txtFrameExeOKhaveRspReport = 1;

		return TRUE;
	}
	else if( pstFrame->action == TXT_FRAME_ACTION_SET )
	{
		if( paraCmdCtrlSet( pstFrame->pBuf + DPACK_OFFSET_PARA ) == FALSE )
			return FALSE;
		
		//gstN2S.cmd_ctrl = 1;
		//gB1.txtFrameExeOKhaveRspReport = 1;

		return TRUE;
	}
	return FALSE;
}




// ------------- ctrl open sec  -----------------------------------------
#include "ctrl_cmd_ctrl_open_sec.h"

void paraCtrlOpenSecSet( u8 *pPara )
{
	u32 temp;
	
	temp = byteMergeto32( pPara[0], pPara[1], pPara[2], pPara[3] );

	ctrlOpenSecSet( temp );
}


void paraCtrlOpenSecGet( u8 *pPara )
{
	u32 temp;

	temp = ctrlOpenSecGet();
	
	u32splitToByte( temp, pPara );
}




u8 para_open_sec_exe( ST_FRAME *pstFrame )
{	
	if( pstFrame->action == TXT_FRAME_ACTION_GET )
	{
		gstN2S.open_sec = 1;

		gB1.txtFrameExeOKhaveRspReport = 1;

		return TRUE;
	}
	else if( pstFrame->action == TXT_FRAME_ACTION_SET )
	{
		paraCtrlOpenSecSet( pstFrame->pBuf + DPACK_OFFSET_PARA );
		
		//gstN2S.open_sec = 1;

		//gB1.txtFrameExeOKhaveRspReport = 1;

		return TRUE;
	}
	
	return FALSE;
}



// ------------- period ctrl  -----------------------------------------


#include "ctrl_period_ctrl.h"

void paraPeriodCtrlSet( u8 *pPara )
{
	u32 openM, closeM;
	
	openM  = byteMergeto32( pPara[0], pPara[1], pPara[2], pPara[3] );
	closeM = byteMergeto32( pPara[4], pPara[5], pPara[6], pPara[7] );

	cfgPeriodCtrlGapSet( openM, closeM );
}


void paraPeriodCtrlGet( u8 *pPara )
{

	u32 openM, closeM;

	cfgPeriodCtrlGapGet( &openM, &closeM );
	
	u32splitToByte( openM, pPara );
	u32splitToByte( closeM, pPara + 4 );
	
}



u8 para_period_ctrl_exe( ST_FRAME *pstFrame )
{	
	if( pstFrame->action == TXT_FRAME_ACTION_GET )
	{
		gstN2S.period_ctrl = 1;

		gB1.txtFrameExeOKhaveRspReport = 1;

		return TRUE;
	}
	else if( pstFrame->action == TXT_FRAME_ACTION_SET )
	{
		paraPeriodCtrlSet( pstFrame->pBuf + DPACK_OFFSET_PARA );
		
		//gstN2S.period_ctrl = 1;

		//gB1.txtFrameExeOKhaveRspReport = 1;

		return TRUE;
	}
	
	return FALSE;
}






// ------------- ctrl pack  -----------------------------------------
#include "f_txt_frame_dpara_base.h"
#include "ctrl.h"
#include "dri_rtc.h"

/*
SERVER->NODE
report
正常/调试    1Byte |  0:正常  1：调试
休眠时间     4Byte |  单位：秒
命令控制     1Byte |  0:关  1：开
开启时长     4Byte |  单位：秒
是否重启记时 1Byte |  0:否  1：重启记时
*/


#define CTRL_PACK_OFFSET_DEBUG          (0)
#define CTRL_PACK_OFFSET_SLEEP1         (1)
#define CTRL_PACK_OFFSET_SLEEP2         (2)
#define CTRL_PACK_OFFSET_SLEEP3         (3)
#define CTRL_PACK_OFFSET_SLEEP4         (4)
#define CTRL_PACK_OFFSET_CMD_CTRL       (5)
#define CTRL_PACK_OFFSET_OPEN_SEC1      (6)
#define CTRL_PACK_OFFSET_OPEN_SEC2      (7)
#define CTRL_PACK_OFFSET_OPEN_SEC3      (8)
#define CTRL_PACK_OFFSET_OPEN_SEC4      (9)
#define CTRL_PACK_OFFSET_RESTART        (10)

#define CTRL_PACK_PARA_LEN              (11)


static u8 _rxPara[ CTRL_PACK_PARA_LEN + 1 ];

static u8 _paraCtrlTimerId = TIMER_ID_ERROR;


void ctrlPackClear( void )
{
	_rxPara[CTRL_PACK_OFFSET_DEBUG] = 0;
}

u8 ctrlPackRxIsDbg( void )
{
	if( _rxPara[CTRL_PACK_OFFSET_DEBUG] == 0 )
		return FALSE;

	return TRUE;
}

static void _debugSet( u8 isDebug )
{
	if( gB1.isDebug ==  isDebug )
		return;

	
	if( isDebug  == 0 )
		gB1.isDebug = 0;
	else
		gB1.isDebug = 1;

	dprintf("isDbg=%d", gB1.isDebug );
}

static void _ctrlPackSet( u8 *pPara )
{
	u8 reStart;
	u32 openSec;

	_debugSet( pPara[CTRL_PACK_OFFSET_DEBUG] );
	
	paraSleepSecSet( pPara + CTRL_PACK_OFFSET_SLEEP1 );


	if( pPara[CTRL_PACK_OFFSET_CMD_CTRL] == 0 )
	{
		ctrlCmdCtrlClose();
	}
	else
	{
		ctrlCmdCtrlOpen();
		
		openSec = byteMergeto32( 
			pPara[CTRL_PACK_OFFSET_OPEN_SEC1], 
			pPara[CTRL_PACK_OFFSET_OPEN_SEC2], 
			pPara[CTRL_PACK_OFFSET_OPEN_SEC3], 
			pPara[CTRL_PACK_OFFSET_OPEN_SEC4]
		);
		
		ctrlOpenSecSet( openSec );
		
		if( pPara[CTRL_PACK_OFFSET_RESTART] == 0 )
			return;

		ctrlOpenStartSecUpdate();
	}

	
}



static void _paraCtrlTimerCB( void )
{
	if( ctrlIsIdle() )
	{
		_paraCtrlTimerId = TIMER_ID_ERROR;
		_ctrlPackSet( _rxPara );
	}
	else
	{
		_paraCtrlTimerId = timerStart( 2/TIMER_UNIT_MS, 1, _paraCtrlTimerCB );
	}
}




void paraCtrlPackSet( u8 *pPara )
{
	memcpy( _rxPara, pPara, CTRL_PACK_PARA_LEN );

	if( _paraCtrlTimerId == TIMER_ID_ERROR )
	{
		_paraCtrlTimerCB();
	}
	
}


int paraCtrlPackGet( u8 *pPara )
{
	#if 0
		u32 curSec, startSec, openSec, rst;
		
		
		paraBatteryGet( pPara );
		paraWorkSecGet( pPara + CTRL_PACK_OFFSET_SLEEP1 );

		if( ctrlStateGet() == 0 )
		{
			pPara[CTRL_PACK_OFFSET_CMD_CTRL] = 0;
			paraCtrlOpenSecGet( pPara + CTRL_PACK_OFFSET_OPEN_SEC1 );
		}
		else
		{
			pPara[CTRL_PACK_OFFSET_CMD_CTRL] = 1;

			curSec = driRtcGetDateTimeSec();

			startSec = cfgCtrlOpenStartGet();

			openSec = cfgCtrlOpenSecGet();

			rst = openSec - ( curSec - startSec );

			u32splitToByte( rst, pPara + CTRL_PACK_OFFSET_OPEN_SEC1 );
		}

		pPara[CTRL_PACK_OFFSET_RESTART] = 0;

		return CTRL_PACK_OFFSET_RESTART + 1;
	
	#endif

	return 0;
}

int paraCtrlPackToServerGet( u8 *pPara )
{
	/*
	NODE->SERVER
	get 
	电量	  2Byte  |	
	水阀状态  1Byte  |	0:关  1：开*/

	paraBatteryGet( pPara );


	if( gB1.ctrlOpenTimeoutClose == 0 )
	{
		pPara[2] = 0xFF;
	}
	else
	{
		#if 0 // fenghuiw
			pPara[2] = 0;
		#else
			if( paraCmdCtrlGet() ) 
				pPara[2] = 1;
			else
				pPara[2] = 0;
		#endif
	}

	return 3;
}











u8 para_ctrl_pack_exe( ST_FRAME *pstFrame )
{	
	#include "sn_n2s.h"
	#include "dev_state.h"
	
	if( pstFrame->action == TXT_FRAME_ACTION_GET )
	{
		/*
		gstN2S.ctrl_pack = 1;

		gB1.txtFrameExeOKhaveRspReport = 1;

		return TRUE;
		*/

		return FALSE;
	}
	else if( pstFrame->action == TXT_FRAME_ACTION_SET  )
	{
		paraCtrlPackSet( pstFrame->pBuf + DPACK_OFFSET_PARA );

		gB1.ctrlOpenTimeoutClose = 0;

		if( pstFrame->pBuf[DPACK_OFFSET_PARA] == 0 )
		{
			devOnEvent( DEV_EVENT_DBG_END, NULL );
		}
		
		//gstN2S.ctrl_pack = 1;

		//gB1.txtFrameExeOKhaveRspReport = 1;

		return TRUE;
	}
	else if(  pstFrame->action == TXT_FRAME_ACTION_REPORT_ACK_GET )
	{
		//dprintf("rx_rpt");
		//n2sPrint();
		gB1.ctrlOpenTimeoutClose = 0;
		
		paraCtrlPackSet( pstFrame->pBuf + DPACK_OFFSET_PARA );


		//gB1.ctrlPackFinish = 1; // fenghuiw
		
		//snN2sOnRsp();

		return TRUE;
	}

	
	return FALSE;
}



/*
void paraCtrlPackRptExe( ST_FRAME *pstFrame )
{
	dprintf("rx_rpt");
	n2sPrint();
	gB1.ctrlOpenTimeoutClose = 0;
	
	paraCtrlPackSet( pstFrame->pBuf + DPACK_OFFSET_PARA );
	
	
	//gB1.ctrlPackFinish = 1; // fenghuiw
	
	snN2sOnRsp();
	
	return TRUE;
}
*/




#endif

