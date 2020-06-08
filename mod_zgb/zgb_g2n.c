/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/

// g2n: gateway to node 

#include "com_includes.h"

#include "timer.h"
#include "dbg_uart.h"

#include "aes.h"
#include "frame.h"


#include "zgb_node.h"
#include "zgb_uart.h"
#include "zgb_g2n.h"
#include "zgb_g2n_state.h"
#include "zgb_unpack.h"



typedef struct
{
	u8 head;     // 
	u8 len;
	u8 ver;
	//EN_TXT_FRAME_ACTION action;
	u8 action;
	u8 check;
	u8 pMac[MAC_ADDR_LEN];  // mac
	u8 sid;      // 会话ID
	//EN_TXT_FRAME_PACK_TYPE packType;
	u8 packType;
	u8 pBuf[ DPACK_OFFSET_PARA_16 + 1 ];   //  
}ST_FRAME_G2N;  // 21 + 8 + 7 = 36




typedef struct
{
	u16 saddr;     // 
	ST_FRAME_G2N  frame;  // 36
}ST_G2N_TXT;


typedef struct
{
	u16 saddr;     // 
	ST_RSP_FRAME  frame; // 15
}ST_G2N_RSP;


//static u8  _g2nBuf[ sizeof(ST_G2N_TXT) ];

//static ST_G2N_TXT *_pstG2Ntxt;



#define _G2N_RSP_SID            ( 0xF1 )
#define _G2N_SET_AES_SWITCH_SID ( 0xF2 )
#define _G2N_SET_AES_KEY_SID    ( 0xF3 )




s8 _g2nIndex;


#include "zgb_g2n_setp4.h"


static u8 _g2nRspAck( u8 nodeIndex )
{
	ST_G2N_RSP stG2Nrsp;
	
	if( modNodeGetSaddrByIndex( nodeIndex, &stG2Nrsp.saddr) == FALSE )
		return FALSE;

	stG2Nrsp.frame.sid = _G2N_RSP_SID; // 
	stG2Nrsp.frame.val = RSP_FRAME_VAL_ACK;

	modNodeGetMacByIndex(  nodeIndex, stG2Nrsp.frame.pMac );
	
	resFrameCreate( &stG2Nrsp.frame, 1 );

	zgbUartTx( (u8 *)&stG2Nrsp,  stG2Nrsp.frame.len + 2 ); // 
	//zgbUartTx( (u8 *)&stG2Nrsp,  RSP_FRAME_LEN + 2 );    // 
	//zgbUartTx( (u8 *)&stG2Nrsp,  sizeof(ST_G2N_RSP) );   // fenghuiwait_1



	return TRUE;
	
}


static u8 _g2nAesSwitch(  u8 nodeIndex )
{	
	ST_G2N_TXT stG2Ntxt;
	u8 val;
	

	if( modNodeGetSaddrByIndex( nodeIndex, &stG2Ntxt.saddr) == FALSE )
		return FALSE;

	
	modNodeGetMacByIndex(  nodeIndex, stG2Ntxt.frame.pMac );

	val = aesSwitchGet();
	
	dpackCreate( DPACK_PORT_ID_SELF, 0, DPACK_PARA_ID_AES_SWITCH, &val, 1, stG2Ntxt.frame.pBuf );
	
	txtFrameCreateG2N( TXT_FRAME_ACTION_SET, _G2N_SET_AES_SWITCH_SID, (ST_FRAME  *) &stG2Ntxt.frame );
	
	zgbUartTx( (u8 *)&stG2Ntxt,  stG2Ntxt.frame.len + 2 ); // 

	return TRUE;
}




static u8 _g2nAesKey(  u8 nodeIndex )
{	
	ST_G2N_TXT stG2Ntxt;
	u16 paraId = DPACK_PARA_ID_AES_KEY;
	

	if( modNodeGetSaddrByIndex( nodeIndex, &stG2Ntxt.saddr) == FALSE )
		return FALSE;

	
	modNodeGetMacByIndex(  nodeIndex, stG2Ntxt.frame.pMac );


	aesKey12Get( stG2Ntxt.frame.pBuf + DPACK_OFFSET_PARA );


	//dpackCreate2( DPACK_PORT_ID_SELF, 0, DPACK_PARA_ID_AES_KEY, AES_KEY_12_LEN );
	stG2Ntxt.frame.pBuf[DPACK_OFFSET_LEN]       = DPACK_LEN_CONST_ELE + AES_KEY_12_LEN;
	stG2Ntxt.frame.pBuf[DPACK_OFFSET_PORT_ID]   = DPACK_PORT_ID_SELF;
	stG2Ntxt.frame.pBuf[DPACK_OFFSET_PORT_ADDR] = 0;
	u16splitToByteHL(paraId, stG2Ntxt.frame.pBuf + DPACK_OFFSET_PARA_ID_1);

	
	txtFrameCreateG2N( TXT_FRAME_ACTION_SET, _G2N_SET_AES_KEY_SID, (ST_FRAME  *)&stG2Ntxt.frame );

	
	zgbUartTx( (u8 *)&stG2Ntxt,  stG2Ntxt.frame.len + 2 ); // 

	return TRUE;
}






/*

static void _zigbeeRfTx( u8 *pFrame, u8 *pLen )
{
	if( aesSwitchGet() == FALSE )
	{
		zgbUartTx( pFrame, *pLen );
		return;
	}

	if( aesEnc( pFrame, pLen ) == FALSE )// aes ERR
	{
		modUartDebugTx0("_zigbeeRfTx X1");
		
		zgbUartTx( pFrame, *pLen ); // 加密 出错明文传输 t
	}
	else
	{
		zgbUartTx( pFrame, *pLen ); // aes OK
	}
}
*/

























//========================================================


int modUartZgbG2NonRxMacGetIndex( u8 *pRxMac )
{
	u8 pMac[MAC_ADDR_LEN] = {0};
	
	modNodeGetMacByIndex( _g2nIndex, pMac );

	if( memcmp( pMac, pRxMac, MAC_ADDR_LEN) == 0 )
		return _g2nIndex;

	return -1;
}


static u8 _uartZgbG2N( void )
{
	int index;
	
	
	if( modNodeIsHaveG2Ncmd() == FALSE )
		return FALSE;

	if( modUartZgbG2NstateIsCanTx() == FALSE ) // 
		return FALSE;


	if( _g2nIndex < 0 ) // 没有 要发送命令的节点
	{
		index = modNodeGetMaxActiveNodeIndex(); // 重新查找到要发送命令的节点
		if( index < 0 )
		{
			_g2nIndex = -1;
			return FALSE;
		}

		_g2nIndex = index; // 找到了，更新节点下标
	}
	else // 已经有 要发送命令的节点
	{
		index = _g2nIndex;
	}



	if( modUartZgbG2NstateIsTxAck() )
	{
		_g2nRspAck( index );
		_g2nIndex = -1; // 重新查找到要发送命令的节点
		modUartZgbG2NstateOnEvent( UART_ZGB_G2N_E_TX_ACK );
		return TRUE;
	}

	if( modUartZgbG2NstateIsIdle() )
	{
		if( modNodeIsHaveG2NcmdSetAesSwitch( index ) )
		{
			_g2nAesSwitch( index );
			modUartZgbG2NstateOnEvent( UART_ZGB_G2N_E_TX_TXT);
			return TRUE;
		}	
		
		if( modNodeIsHaveG2NcmdSetKey( index ) )
		{
			_g2nAesKey( index );
			modUartZgbG2NstateOnEvent( UART_ZGB_G2N_E_TX_TXT);
			return TRUE;
		}
	}


	
	/*
	if( modNodeIsHaveG2NcmdRsp( index ) )
	{
		_g2nRspAck( index );
		return TRUE;
	}

	if( modNodeIsHaveG2NcmdSetAesSwitch( index ) )
	{
		_g2nAesSwitch( index );
		return TRUE;
	}	

	if( modNodeIsHaveG2NcmdSetKey( index ) )
	{
		_g2nAesKey( index );
		return TRUE;
	}
	*/

	return FALSE;
	
		
}





#define MOD_UART_ZGB_G2N_GAP_MS  (100)

#define _UART_ZGB_G2N_GAP_CNT  ( MOD_UART_ZGB_G2N_GAP_MS / MOD_UART_ZGB_TX_GAP_MS )



void modUartZgbG2NupdateIndex( void )
{
	_g2nIndex = -1;
}


u8 modUartZgbG2N( void )
{
	static u8 _uartZgbG2NgapCnt = _UART_ZGB_G2N_GAP_CNT ;

	modUartZgbG2NstatePollCB();
	
	if( 0 == --_uartZgbG2NgapCnt )
	{
		_uartZgbG2NgapCnt = _UART_ZGB_G2N_GAP_CNT;
		
		return _uartZgbG2N();
	}

	return FALSE;

}






void zgbG2Ninit( void )
{
	_g2nIndex = -1;
	
}










