
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


#define CTRL_PACK_OFFSET_WORK1          (0)
#define CTRL_PACK_OFFSET_WORK2          (1)
#define CTRL_PACK_OFFSET_WORK3          (2)
#define CTRL_PACK_OFFSET_WORK4          (3)
#define CTRL_PACK_OFFSET_SLEEP1         (4)
#define CTRL_PACK_OFFSET_SLEEP2         (5)
#define CTRL_PACK_OFFSET_SLEEP3         (6)
#define CTRL_PACK_OFFSET_SLEEP4         (7)
#define CTRL_PACK_OFFSET_CMD_CTRL       (8)
#define CTRL_PACK_OFFSET_OPEN_SEC1      (9)
#define CTRL_PACK_OFFSET_OPEN_SEC2      (10)
#define CTRL_PACK_OFFSET_OPEN_SEC3      (11)
#define CTRL_PACK_OFFSET_OPEN_SEC4      (12)
#define CTRL_PACK_OFFSET_RESTART        (13)


void paraCtrlPackSet( u8 *pPara )
{
//  | 设备单次工作时间 | 设备单次休眠时间 | 命令控制 | 开启时长 | 是否重启记时 | 

	u8 reStart;
	u32 openSec;
	

	paraWorkSecSet( pPara );
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


int paraCtrlPackGet( u8 *pPara )
{
	//	| 设备单次工作时间 | 设备单次休眠时间 | 命令控制 | 开启时长 | 是否重启记时 | 
    //                                          当前状态                  0
    //                                             0       开启时长       0
    //                                             1      还剩下时长      0

	u32 curSec, startSec, openSec, rst;
	
	
	paraWorkSecGet( pPara );
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
	

}



u8 para_ctrl_pack_exe( ST_FRAME *pstFrame )
{	
	if( pstFrame->action == TXT_FRAME_ACTION_GET )
	{
		/*
		gstN2S.ctrl_pack = 1;

		gB1.txtFrameExeOKhaveRspReport = 1;

		return TRUE;
		*/

		return FALSE;
	}
	else if( pstFrame->action == TXT_FRAME_ACTION_SET || pstFrame->action == TXT_FRAME_ACTION_REPORT_ACK_GET )
	{
		paraCtrlPackSet( pstFrame->pBuf + DPACK_OFFSET_PARA );
		
		//gstN2S.ctrl_pack = 1;

		//gB1.txtFrameExeOKhaveRspReport = 1;

		return TRUE;
	}

	
	return FALSE;
}




#endif

