/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/

// sn: Server and node communication	服务器和节点通信

#include "com_includes.h"

#include "timer.h"
#include "dbg_uart.h"

#include "frame.h"

#include "sn_rx.h"
#include "sn_n2s.h"
#include "sn_rx_queue.h"


#define SG_RX_BUF_LEN ( 256 * 2 )

static u16 _index;
static u16 _start;
static u16 _unPaserLen;


static u8 _pBuf[SG_RX_BUF_LEN];



// ok: return frame len;
// ng: return 0;
static u16 _paserFrame( void )
{
	u8 *pCh;
	u16 i;
	u8 frameLen;
	//u8 frameVer;
	u8 start;
	u8 headNgLen;

	// 1 ----- check frame Head ------
	start = _start;
	
	pCh = _pBuf + start;

	for( i = 1; *pCh != TXT_FRAME_START; pCh++, i++ ) // RSP_FRAME_START == TXT_FRAME_START
	{
		if(  i >= _unPaserLen )
			return 0;

		start++;
	}

	headNgLen = start - _start;

	if( headNgLen != 0 ) // 前缀有误
	{
		dprintfBuf("snrx _paserFrame head NG: ", _pBuf + _start, headNgLen, 1 );

		_start       = start;
		_unPaserLen -= headNgLen;
	}



	// 2  ----- check frame len ----- 
	frameLen = _pBuf[ start + 1];
	
	if( frameLen > _unPaserLen )
		return 0; // 长度不够


	// 3  ----- check frame ver ----- 
	//frameVer = _pBuf[ start + 2];
	//if( frameVer & 0x3F > 5 )
		

	
	// 4  ----- check frame tail (is aes not do ) ----- 
	//if( txtFrameVerIsEnc( ) )
	
	
	return frameLen;
}


static int _snRx( u8 *pBuf, u8 len )
{
	u16 frameLen;
	u8 *pFrame;
	
	memcpy( _pBuf + _index, pBuf, len );
	_index += len;
	
	_unPaserLen += len;
	

	for( ; _unPaserLen > 0; )
	{
		frameLen = _paserFrame();

		
		if( frameLen == 0 )// 没有 OK 的 FRAME
		{
			if( _start == 0 )
				return TRUE;
			
			// 将没有处理的数据移到BUF头 start=0
			memcpy( _pBuf, _pBuf + _start, _unPaserLen );
			_index = _unPaserLen;

			_start = 0;

			return TRUE;
		}
		

		// 有 OK 的 FRAME

		pFrame = _pBuf + _start;
		
		if( rspFrameLenIsOk( pFrame[RSP_FRAME_OFFSET_LEN]) == FALSE) // 不是应答帧
		{
			snRxQueueEn( pFrame, frameLen );
		}
		else// 是应答帧
		{
			if( rspFrameUnpack( pFrame, frameLen, 0 ) != FRAME_UNPACK_OK ) // 不是网关的ACK
			{
				snRxQueueEn( pFrame, frameLen );
			}
			else
			{
				if( snN2sIsRspCurTxCmdSid(pFrame[RSP_FRAME_OFFSET_SID]) == FALSE )// 不是当前命令的ACK
				{
					dprintfBuf("sid NG: ", pFrame, frameLen, 1 );
				}
				else
				{
					// 是网关当前命令的ACK
					n2sTxCmdOnRxOkRsp();
				}
			}
		}

		_start      += frameLen;
		_unPaserLen -= frameLen;
		
		// 将没有处理的数据移到BUF头 start=0
		if( _unPaserLen != 0 )
		{
			memcpy( _pBuf, _pBuf + _start, _unPaserLen );
		}
		_index = _unPaserLen;
		_start = 0;
		
	}

	return TRUE;
}









/*
static u16 _canPaserLenGet( void )
{
	return SG_RX_BUF_LEN - _index;
}
*/

static u16 _PaserLenGet( u16 len )
{
	u16 canPaserLen;

	//canPaserLen = _canPaserLenGet();
	canPaserLen = SG_RX_BUF_LEN - _index;
	
	if( len < canPaserLen )
		return len;

	return canPaserLen;
}



int snRx( u8 *pBuf, u8 len )
{
	u16 paserLen;
	u16 unPaserLen;
	u8 *pPaserBuf;

	if( len == 0 || pBuf == NULL )
		return FALSE;

	
	pPaserBuf  = pBuf;
	paserLen   = _PaserLenGet( len );
	unPaserLen = len - paserLen;

	for( ; paserLen != 0; )
	{
		_snRx( pPaserBuf, paserLen);
		
		if( unPaserLen == 0 )
			return TRUE;
		
		pPaserBuf  += paserLen;
		paserLen    = _PaserLenGet( unPaserLen );
		unPaserLen -= paserLen;		
	}
	
	return TRUE;
}





void _snRxTimerCB( void )
{
	static u8 _pFrame[256];
	static u32 _len;
	
	if( snRxQueueIsEmpty() )
		return;

	if( snN2sIsIng() )
		return;

	snRxQueueDe(_pFrame, &_len );

	snOnRx( _pFrame, _len );
	
}



void snRxInit( void )
{
	_index = 0;
	_start = 0;
	_unPaserLen = 0;

	timerStart( 4/TIMER_UNIT_MS, TIMER_REPEAT_FOREVER,_snRxTimerCB);

}



