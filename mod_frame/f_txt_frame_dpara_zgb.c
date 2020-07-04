
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

#include "f_txt_frame_dpara_zgb.h"
#include "f_txt_frame_data.h"


#include "zgb_cmd.h"




//---------------- reset ---------------------------------------
u8 para_zigbee_to_reset_exe( ST_FRAME *pstFrame )
{
	if( pstFrame->action == TXT_FRAME_ACTION_SET )
	{
		zcmdReboot();
		gB1.txtFrameExeOKhaveRspReport = 0;
		
		return TRUE;
	}

	return FALSE;
}


//---------------- def ---------------------------------------
u8 para_zigbee_to_def_exe( ST_FRAME *pstFrame )
{
	if( pstFrame->action == TXT_FRAME_ACTION_SET )
	{
		zcmdDef();
		gB1.txtFrameExeOKhaveRspReport = 0;
		
		return TRUE;
	}

	return FALSE;
}





//---------------- auto net ---------------------------------------

u8 paraZigbeeAutoNetGet( void )
{
	return zigbeeAutoNetGet();
}


u8 para_zigbee_auto_net_exe( ST_FRAME *pstFrame )
{
	if( pstFrame->action == TXT_FRAME_ACTION_GET )
	{		
		gstN2S.zigbee_auto_net = 1;
		gB1.txtFrameExeOKhaveRspReport = 1;

		return TRUE;
	}
	else if( pstFrame->action == TXT_FRAME_ACTION_SET )
	{
		zcmdAutoNet( pstFrame->pBuf[DPACK_OFFSET_PARA] );
		
		//gstN2S.zigbee_auto_net = 1;
		//gB1.txtFrameExeOKhaveRspReport = 1;

		return TRUE;
	}
	
	return FALSE;
}



//---------------- LQI ---------------------------------------

u8 paraZigbeeLqiGet( void )
{
	return zigbeeLqiGet();
}

u8 para_zigbee_lqi_exe( ST_FRAME *pstFrame )
{
	if( pstFrame->action == TXT_FRAME_ACTION_GET )
	{
		zcmdLqiGet();
		
		gstN2S.zigbee_lqi = 1;
		gB1.txtFrameExeOKhaveRspReport = 1;

		return TRUE;
	}
	
	return FALSE;
}





//---------------- zigbee work state ---------------------------------------
u8 paraZigbeeWorkStateGet( void )
{
	EN_ZIGBEE_WORK_STATE s;


	zigbeeWorkStateGet( &s );


	return (u8)s;
}


u8 para_zigbee_state_exe( ST_FRAME *pstFrame )
{
	if( pstFrame->action == TXT_FRAME_ACTION_GET )
	{
		zcmdWorkStateGet();
		
		gstN2S.zigbee_state = 1;
		gB1.txtFrameExeOKhaveRspReport = 1;

		return TRUE;
	}
	
	return FALSE;
}







//---------------- zigbee dev info  ---------------------------------------

void paraZigbeeInfoGet( ST_ZIGBEE_DEV_INFO_RF *pstInfoRf )
{
	zigbeeInfoRfGet( pstInfoRf );
}


u8 para_zigbee_info_exe( ST_FRAME *pstFrame )
{
	if( pstFrame->action == TXT_FRAME_ACTION_GET )
	{
		zcmdDevInfoGet();
		
		gstN2S.zigbee_info = 1;
		gB1.txtFrameExeOKhaveRspReport = 1;

		return TRUE;
	}
	else if( pstFrame->action == TXT_FRAME_ACTION_SET )
	{
		zcmdDevInfoSet( (ST_ZIGBEE_DEV_INFO_RF *) (pstFrame->pBuf + DPACK_OFFSET_PARA ) );
		
		//gstN2S.zigbee_info = 1;
		//gB1.txtFrameExeOKhaveRspReport = 1;

		return TRUE;
	}
	
	return FALSE;
}

















#endif





