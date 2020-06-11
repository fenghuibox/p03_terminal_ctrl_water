
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
//#include "dri.h"
//#include "timer.h"

#include "f_txt_frame_dpara_base.h"
#include "f_txt_frame_data.h"

//#include "cfg_base.h"



// ------------- exe -----------------------------------------
/* 
参数值 =  para1... --||
参数值 = exeTxt[N] --||

portId + addr + exeTxt
*/
int _485exeCmdOnPort( ST_FRAME *pstFrame )
{	
#if 0
	#include "m485_uart.h"

	EN_DPACK_PORT_ID portId;
	u8 len;	

	portId = (EN_DPACK_PORT_ID)pstFrame->pBuf[ DPACK_OFFSET_PORT_ID ];

	len = pstFrame->pBuf[ DPACK_OFFSET_LEN ] - FRAME_DATA_PACK_CONST_ELE_LEN; //  2 --> para1 + para2 
	
	switch( portId  )
	{
	case DPACK_PORT_ID_UART1:
	//case DPACK_PORT_ID_SELF:
		m485UartTxWithAddr( pstFrame->pBuf[DPACK_OFFSET_PORT_ADDR], pstFrame->pBuf + DPACK_OFFSET_PARA, len );
		gB1.txtFrameExeOKhaveRspReport = 1;
		return TRUE;
	}

	return FALSE;

	#endif

	return FALSE;

	
}




u8 para_uart485_exe( ST_FRAME *pstFrame )
{
	if( pstFrame->action == TXT_FRAME_ACTION_GET )
	{
		gstN2S.uart485 = 1;
		gB1.txtFrameExeOKhaveRspReport = 1;

		return TRUE;
	}
	else if( pstFrame->action == TXT_FRAME_ACTION_SET )
	{
		return _485exeCmdOnPort( pstFrame );
	}	
	
	return FALSE;
}



#endif
