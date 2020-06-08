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

#include "dbg_uart.h"

#include "zgb_cmd.h"
#include "zgb_uart.h"





//====================================================================================
//===== // step1 ====================================================================
//====================================================================================
#include "zgb_cmd_setp1.h"





typedef struct
{
	u8 autoNet:1;    // 1:开启
	u8 workState:2;  // 
	//u8 headIncludeSaddr:1; 
	u8 C:1; 
	u8 D:1; 
	u8 E:1;
	u8 isOk:1; // _stZdevInfo 参数是否可用
}ST_ZCMD_PARA;




//=================================================
ST_ZCMD_TX           _stZcmdTx;

ST_ZCMD_PARA         _stZcmdPara;
ST_ZIGBEE_DEV_INFO   _stZdevInfo;
static u8  _Lqi = 0;

//-------------------------------------
static void _zcmdTxClear( void )
{
	memset( &_stZcmdTx, 0, sizeof(ST_ZCMD_TX) );
}


static u8 _zcmdTxIsEmpty( void )
{
	
	ST_ZCMD_TX stZcmdTxTemp = {0}; //  sizeof(ST_ZCMD_TX) = 2

	//modUartDebugTxStrU32("\r\n sizeof(ST_ZCMD_TX) = ", sizeof(ST_ZCMD_TX) );

	if( memcmp( &_stZcmdTx, &stZcmdTxTemp, sizeof(ST_ZCMD_TX)) == 0 )
		return TRUE;

	return FALSE;

	/*

	if( * ((u16 *)&_stZcmdTx) == 0 )
		return TRUE;

	return FALSE;
	*/
}


//-------------------------------------
static void _zcmdParaClear( void )
{
	memset( &_stZcmdPara, 0, sizeof(ST_ZCMD_PARA) );

	_stZcmdPara.workState = ZIGBEE_WORK_STATE_NOT_DEF;

	 _Lqi = 0;
	 
	 memset( &_stZdevInfo, 0, sizeof(ST_ZIGBEE_DEV_INFO) );
}


//====================================================================================
//===== // step 5 ====================================================================
//====================================================================================
#include "zgb_cmd_setp5.h"



//====================================================================================
//===== // step 4 ====================================================================
//====================================================================================
#include "zgb_cmd_setp4.h"


//====================================================================================
//===== // step 3 ====================================================================
//====================================================================================
#include "zgb_cmd_setp3.h"



//====================================================================================
//===== // step 2 ====================================================================
//====================================================================================
#include "zgb_cmd_setp2.h"





//==========================================================
int zcmdTxCB( void )
{
	if( _zcmdTxIsEmpty() )
		return FALSE;

	
	if( _stZcmdTx.devInfoSet ) // 先写
	{
		//dprintf("z1");
		_zcmdDevInfoSet();
		return TRUE;
	}
	
	if( _stZcmdTx.devInfoGet ) // 再读
	{
		//dprintf("z2");
		_zcmdDevInfoGet();
		return TRUE;
	}

	if( _stZcmdTx.def) // 先恢复出厂设置命令
	{
		//dprintf("z3");
		_zcmdDef();
		return TRUE;
	}	
	

	if( _stZcmdTx.reboot ) // 再 重启
	{
		//dprintf("z5");
		_zcmdReboot();
		return TRUE;
	}

	if( _stZcmdTx.autoNet) // 自组网功能命令
	{
		//dprintf("z6");
		_zcmdAutoNet();
		return TRUE;
	}	

	

	if( _stZcmdTx.workState) // 查询主从机状态
	{
		//dprintf("za");
		_zcmdWorkStateGet();
		return TRUE;
	}	

	//--------------------------------------------------------
	if( _stZcmdTx.lqi ) // 查询节点的信号强度命令
	{
		//dprintf("zb");
		_zcmdLqiGet();
		return TRUE;
	}

	if( _stZcmdTx.sleep ) // 
	{
		//dprintf("zc");
		_zcmdSleep();
		return TRUE;
	}	
	
	// -----------------------------------------------

	return FALSE;
	
}





void zgbCmdInit( void )
{
	_zcmdParaClear();
	_zcmdTxClear();

	 _Lqi = 0;
	 
	 memset( &_stZdevInfo, 0, sizeof(ST_ZIGBEE_DEV_INFO) );
	 
	zcmdDevInfoGet();
	zcmdWorkStateGet();

	zcmdAutoNet( 1 ); // 开启自组网功能
}




