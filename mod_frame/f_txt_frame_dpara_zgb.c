
#if 0

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
		gstG2S.zigbee_auto_net = 1;
		gB1.txtFrameExeOKhaveRspReport = 1;

		return TRUE;
	}
	else if( pstFrame->action == TXT_FRAME_ACTION_SET )
	{
		zcmdAutoNet( pstFrame->pBuf[DPACK_OFFSET_PARA] );
		
		//gstG2S.zigbee_auto_net = 1;
		//gB1.txtFrameExeOKhaveRspReport = 1;

		return TRUE;
	}
	
	return FALSE;
}



//---------------- zigbee allow join  ---------------------------------------

void paraZigbeeAllowJoinSet( u8 *pPara )
{
	#include "zgb_io.h"

	u16 workSec;
	
	workSec = byteMergeto16( pPara[0], pPara[1] );

	#if 0


	zcmdAllowJoin( workSec );

	#else

	zigbeeAllowJoinSet( workSec );

	modIoZgbJoin( workSec );

	#endif
}

void paraZigbeeAllowJoinGet( u8 *pPara )
{
	u16 val;

	val = zigbeeAllowJoinGet();

	u16splitToByteHL( val, pPara );
}


u8 para_zigbee_allow_join_exe( ST_FRAME *pstFrame )
{
	if( pstFrame->action == TXT_FRAME_ACTION_GET )
	{		
		//gstG2S.zigbee_allow_join = 1;
		//gB1.txtFrameExeOKhaveRspReport = 1;

		return FALSE;
	}
	else if( pstFrame->action == TXT_FRAME_ACTION_SET )
	{
		paraZigbeeAllowJoinSet(  pstFrame->pBuf + DPACK_OFFSET_PARA  );
		
		//gstG2S.zigbee_allow_join = 1;
		//gB1.txtFrameExeOKhaveRspReport = 1;

		return TRUE;
	}
	
	return FALSE;
}



//---------------- zigbee del by mac---------------------------------------

u8 para_zigbee_del_by_mac_addr_exe( ST_FRAME *pstFrame )
{
	

	u8 *pMac;
	
	if( pstFrame->action == TXT_FRAME_ACTION_SET )
	{
		pMac = pstFrame->pBuf + DPACK_OFFSET_PARA;
		
		if( modNodeMacIsNode( pMac ) == FALSE )
			return FALSE;
		
		if( zcmdDelByMac( pMac ) == FALSE )
			return FALSE;
		
		modNodeDelByMac(  pMac );
		
		//gstG2S.zigbee_child_info = 1;     // fenghuiwait_1
		//gB1.txtFrameExeOKhaveRspReport = 1;

		return TRUE;
	}
	
	
	return FALSE;
}



//---------------- zigbee child info ---------------------------------------


/*
------pNodeBuf----------------------------------
         nodeCnt  startId   getCnt  pNodeMac
------------------------------------------------
  len:    1byte    1byte    1byte   8byte * n 
------------------------------------------------
  value:  1- n     1- n     0- n
------------------------------------------------
返回值: 总的字节数
*/
u8 paraZigbeeChildInfoGet( u8 *pPara ) // 
{
	return modNodeGet( pPara );
}


u8 para_zigbee_child_info_exe( ST_FRAME *pstFrame )
{
	if( pstFrame->action == TXT_FRAME_ACTION_GET )
	{
		modNodeStartIdSet( pstFrame->pBuf[ DPACK_OFFSET_PARA ] );
		
		gstG2S.zigbee_child_info = 1;
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


u8 para_zigbee_work_state_exe( ST_FRAME *pstFrame )
{
	if( pstFrame->action == TXT_FRAME_ACTION_GET )
	{
		zcmdWorkStateGet();
		
		gstG2S.zigbee_work_state = 1;
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
		
		gstG2S.zigbee_info = 1;
		gB1.txtFrameExeOKhaveRspReport = 1;

		return TRUE;
	}
	else if( pstFrame->action == TXT_FRAME_ACTION_SET )
	{
		zcmdDevInfoSet( (ST_ZIGBEE_DEV_INFO_RF *) (pstFrame->pBuf + DPACK_OFFSET_PARA ) );
		
		//gstG2S.zigbee_info = 1;
		//gB1.txtFrameExeOKhaveRspReport = 1;

		return TRUE;
	}
	
	return FALSE;
}

















#endif





