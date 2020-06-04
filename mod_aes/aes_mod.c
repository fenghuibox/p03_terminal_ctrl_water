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


#include "aes_mod.h"



#include "f_txt_frame.h"

#define TXT_HEAD_LEN  (13)



/*-----------------------------------------------------------------------------------------------
                                 加密帧
-------------------------------------------------------------------------------------------------
明文     |AA 16 01 03 29 04 A8 08 68 00 15 8D 00 00 01 06 00 00 00 15 03 88 

                                                 -----------加密内容 -------
加密内容 |AA 16 01 03 29 04 A8 08 68 00 15 8D 00 |00 01 06 00 00 00 15 03 88 

            长度                                 -----------加密内容 -------|--------补0----------
补0      |AA 1D 01 03 29 04 A8 08 68 00 15 8D 00 |00 01 06 00 00 00 15 03 88| 00 00 00 00 00 00 00

            版本                                 -----------加密内容 -------|--------补0----------
修改版本 |AA 1D 02 03 29 04 A8 08 68 00 15 8D 00 |00 01 06 00 00 00 15 03 88| 00 00 00 00 00 00 00

   							                     ---------------------加密 -----------------------
加密     |AA 1D 02 03 29 04 A8 08 68 00 15 8D 00 |CD EA 15 55 66 59 15 36 58 15 28 65 15 48 96 AD

-------------------------------------------------------------------------------------------------*/
// --- ver set enc bit ----
// pFrame: in/out
// pLen:   in/out
u8 aesEnc( u8 *pFrame, u8 *pLen )
{
	u8 key[AES_KEY_LEN];
	u8 key2[AES_KEY_LEN];
	u8 encLen;
	u8 zeroLen;
	u8 i;

	if( txtFrameHeadIsOk( pFrame[TXT_FRAME_OFFSET_HEAD] ) == FALSE  )
	{
		dprintf("aesEnc X1");
		return FALSE;
	}

	if(txtFrameLenIsOk( *pLen ) == FALSE )
	{
		dprintf("aesEnc X2");
		return FALSE;
	}
	
	if( pFrame[TXT_FRAME_OFFSET_LEN] != *pLen )
	{
		dprintf("aesEnc X3");
		return FALSE;
	}

	if( txtFrameVerIsOk( pFrame[TXT_FRAME_OFFSET_VER] ) == FALSE  )
	{
		dprintf("aesEnc X4");
		return FALSE;
	}

	if( txtFrameVerIsEnc( pFrame[TXT_FRAME_OFFSET_VER] ) == TRUE )
	{
		dprintf("aesEnc X5");
		return FALSE;
	}

	txtFrameEncBitSet( pFrame + TXT_FRAME_OFFSET_VER );
	
	
	aesKeyGet( pFrame, key );

	//dprintf("ek:");
	//modUartDebugTxU8buf( key, 16 );
	//dprintf("\r\n");

	encLen = *pLen - TXT_HEAD_LEN; // 加密内容长度

	zeroLen = encLen % AES_UNIT_LEN;

	if( zeroLen != 0 )
	{
		zeroLen = AES_UNIT_LEN - zeroLen;
	}

	if( zeroLen != 0 )
	{
		comMemset( pFrame + *pLen, 0, zeroLen ); // 补0
	}

	*pLen += zeroLen;

	for( i = TXT_HEAD_LEN; i < *pLen; i += AES_UNIT_LEN  )
	{
		memcpy( key2, key, AES_KEY_LEN);
		aesEncDec( pFrame + i, key2, 0 );
	}

	
	pFrame[TXT_FRAME_OFFSET_LEN] = *pLen;

	return TRUE;
	
	
}




/*-----------------------------------------------------------------------------------------------
                                 解密帧
-------------------------------------------------------------------------------------------------

   							                     --------------------- 密文 ---------------------
密文     |AA 1D 02 03 29 04 A8 08 68 00 15 8D 00 |CD EA 15 55 66 59 15 36 58 15 28 65 15 48 96 AD

                                                 --------------------- 明文 ----------------------
解密     |AA 1D 02 03 29 04 A8 08 68 00 15 8D 00 |00 01 06 00 00 00 15 03 88 00 00 00 00 00 00 00

            长度                                 -------------明文 ---------|
去掉0    |AA 16 02 03 29 04 A8 08 68 00 15 8D 00 |00 01 06 00 00 00 15 03 88| 

               版本 
改版本   |AA 16 01 03 29 04 A8 08 68 00 15 8D 00 00 01 06 00 00 00 15 03 88 


-------------------------------------------------------------------------------------------------*/
	// --- ver clear enc bit ----
// pFrame: in/out
// pLen:   in/out
u8 aesDec( u8 *pFrame, u8 *pLen )
{
	u8 key[AES_KEY_LEN];
	u8 key2[AES_KEY_LEN];
	u8 len;
	// u8 zeroLen;
	u8 encLen;
	u8 i;
	u8 *p;

	if( txtFrameHeadIsOk( pFrame[TXT_FRAME_OFFSET_HEAD] ) == FALSE  )
	{
		dprintf("aesDec X1");
		return FALSE;
	}

	if(txtFrameLenIsOk( *pLen ) == FALSE )
	{
		dprintf("aesDec X2");
		return FALSE;
	}

	if( pFrame[TXT_FRAME_OFFSET_LEN] != *pLen )
	{
		dprintf("aesEnc X3");
		return FALSE;
	}

	if( txtFrameVerIsOk( pFrame[TXT_FRAME_OFFSET_VER] ) == FALSE  )
	{
		dprintf("aesDec X4");
		return FALSE;
	}

	if( txtFrameVerIsEnc( pFrame[TXT_FRAME_OFFSET_VER] ) == FALSE )
	{
		dprintf("aesEnc X5");
		return FALSE;
	}


	encLen = *pLen - TXT_HEAD_LEN;

	if( (encLen % AES_UNIT_LEN ) != 0 )
	{
		dprintf("aesDec X6");
		return FALSE;
	}

	

	aesKeyGet( pFrame, key );

	//dprintf("dk:");
	//modUartDebugTxU8buf( key, 16 );
	//dprintf("\r\n");

	len = *pLen;
	
	for( i = TXT_HEAD_LEN; i < len; i += AES_UNIT_LEN  )
	{
		memcpy( key2, key, AES_KEY_LEN);
		aesEncDec( pFrame + i, key2, 1 );
	}
	
	
	for( p = pFrame + len - 1; *p == 0; p-- ) // 去掉0
	{
	
	}

	len  = p - pFrame + 1;

	
	pFrame[TXT_FRAME_OFFSET_LEN] = len;
	
	txtFrameEncBitClear( pFrame + TXT_FRAME_OFFSET_VER );

	*pLen = len;

	return TRUE;
	
	
	
}





void aesEepDef( void )
{
	aesSwitchDef();  
	aesKey12Def();
}





void aesInit( void )
{

}




#ifdef TEST_MOD_AES


const u8 pConstFrameSetWorkStateTo0[] = {
//设置工作状态为 0
0xAA, 0x16, 0x01, 0x01, 0x84, 0x04, 0xA8, 0x08, 0x68, 0x00, 0x15, 0x8D, 0x00, // head 13 byte
0xD4, 0x01, 0x06, 0x00, 0x00, 0x00, 0xA1, 0x00, 0x88
};
/*
Enc:
AA 1D 81 01 84 04 A8 08 68 00 15 8D 00 
56 E7 19 3C DE E5 C8 D6 27 C7 1E 1A B1 03 62 70

Dec: 
AA 16 01 01 84 04 A8 08 68 00 15 8D 00 
D4 01 06 00 00 00 A1 00 88

*/

const u8 pConstFrameAddPtlCfg[] = {
//添加一个协议配置 
0xAA, 0x21, 0x01, 0x01, 0x35, 0x04, 0xA8, 0x08, 0x68, 0x00, 0x15, 0x8D, 0x00, 
0xD5, 0x01, 0x11, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x0C, 0x04, 0x01, 0x01, 0xFF, 0x00, 
0x00, 0x00, 0x06, 0x88

};

/*
Enc:
AA 2D 81 01 35 04 A8 08 68 00 15 8D 00 
96 B9 E7 85 41 84 E0 FD 9D E2 E0 7A 3F F2 50 26 
55 61 DD 6C A9 E8 DE F7 5C 32 B8 25 D6 36 70 2B

Dec: 
AA 21 01 01 35 04 A8 08 68 00 15 8D 00 
D5 01 11 00 00 00 24 00 00 00 0C 04 01 01 FF 00 
00 00 06 88
*/

static u8 _pFrame[50];


#include "dri_timer.h"
#include "timer.h"


static void _aesTestCB( void )
{
	static u8 _cnt = 0;
	u8 len, len2;
	u32 t1, t2;

	int i;

	static u8 _pFrameMs[10][32] = {0};


	if( _cnt == 0 )
	{
		len = pConstFrameSetWorkStateTo0[ TXT_FRAME_OFFSET_LEN ];

	
		memcpy( _pFrame, pConstFrameSetWorkStateTo0, len);
		
		//dprintfBuf( "\r\ntt1:", _pFrame, len, 1 );

		aesEnc( _pFrame, &len);

		dprintfBuf( "Enc:", _pFrame, len, 1 );
	}
	else if( _cnt == 1 )
	{
		len = _pFrame[ TXT_FRAME_OFFSET_LEN ];

		aesDec( _pFrame, &len);
		
		dprintfBuf( "Dec:", _pFrame, len, 1 );

	}
	else if( _cnt == 2 )
	{
		len = pConstFrameAddPtlCfg[TXT_FRAME_OFFSET_LEN];
		
		memcpy( _pFrame, pConstFrameAddPtlCfg, len);

		dprintfBuf( "tt2:", _pFrame, len, 1 );
		
		aesEnc( _pFrame, &len );
		
		dprintfBuf( "Enc:", _pFrame, len, 1 );

	}
	else if( _cnt == 3 )
	{
		len = _pFrame[TXT_FRAME_OFFSET_LEN];

		aesDec( _pFrame, &len);
		
		dprintfBuf( "Dec:", _pFrame, len, 1 );
	}
	#if 1
	else if( _cnt == 4 )
	{
		len = 0x16;
	
		memcpy( _pFrameMs[0], pConstFrameSetWorkStateTo0, len);
		memcpy( _pFrameMs[1], pConstFrameSetWorkStateTo0, len);
		memcpy( _pFrameMs[2], pConstFrameSetWorkStateTo0, len);
		memcpy( _pFrameMs[3], pConstFrameSetWorkStateTo0, len);
		memcpy( _pFrameMs[4], pConstFrameSetWorkStateTo0, len);
		memcpy( _pFrameMs[5], pConstFrameSetWorkStateTo0, len);
		memcpy( _pFrameMs[6], pConstFrameSetWorkStateTo0, len);
		memcpy( _pFrameMs[7], pConstFrameSetWorkStateTo0, len);
		memcpy( _pFrameMs[8], pConstFrameSetWorkStateTo0, len);
		memcpy( _pFrameMs[9], pConstFrameSetWorkStateTo0, len);

		t1 = driTimerCntGet();
		
		aesEnc( _pFrameMs[0], &len );
		len = 0x16;
		aesEnc( _pFrameMs[1], &len );
		len = 0x16;
		aesEnc( _pFrameMs[2], &len );
		len = 0x16;
		aesEnc( _pFrameMs[3], &len );
		len = 0x16;
		aesEnc( _pFrameMs[4], &len );
		len = 0x16;
		aesEnc( _pFrameMs[5], &len );
		len = 0x16;
		aesEnc( _pFrameMs[6], &len );
		len = 0x16;
		aesEnc( _pFrameMs[7], &len );
		len = 0x16;
		aesEnc( _pFrameMs[8], &len );
		len = 0x16;
		aesEnc( _pFrameMs[9], &len );

		t2 = driTimerCntGet();

		t2 -= t1;
		
		dprintf( "Enc10 ms=%d:", t2 * TIMER_UNIT_MS );

	}
	else if( _cnt == 5 )
	{
		len2 = len = _pFrameMs[0][ TXT_FRAME_OFFSET_LEN ];
		
		t1 = driTimerCntGet();
		aesDec( _pFrameMs[0], &len);
		len = len2;
		aesDec( _pFrameMs[1], &len);
		len = len2;
		aesDec( _pFrameMs[2], &len);
		len = len2;
		aesDec( _pFrameMs[3], &len);
		len = len2;
		aesDec( _pFrameMs[4], &len);
		len = len2;
		aesDec( _pFrameMs[5], &len);
		len = len2;
		aesDec( _pFrameMs[6], &len);
		len = len2;
		aesDec( _pFrameMs[7], &len);
		len = len2;
		aesDec( _pFrameMs[8], &len);
		len = len2;
		aesDec( _pFrameMs[9], &len);
		t2 = driTimerCntGet();

		t2 -= t1;
		
		dprintf( "Dec10 ms=%d:", t2 * TIMER_UNIT_MS  );
	}
	else if( _cnt == 6 )
	{
		t1 = driTimerCntGet();
		for( i = 0; i < 1000; i++ )
		{
			len = 0x16;
			memcpy( _pFrameMs[0], pConstFrameSetWorkStateTo0, len);
			aesEnc( _pFrameMs[0], &len );
		}

		t2 = driTimerCntGet();
		t2 -= t1;
		dprintf( "Enc1000 ms=%d:", t2 * TIMER_UNIT_MS );

		memcpy( _pFrameMs[1], _pFrameMs[0], 32);
	}
	else
	{
		len2 = len = _pFrameMs[0][ TXT_FRAME_OFFSET_LEN ];
		
		t1 = driTimerCntGet();
		for( i = 0; i < 1000; i++ )
		{
			len = len2;
			memcpy( _pFrameMs[0], _pFrameMs[1], len);
			aesDec( _pFrameMs[0], &len );
		}

		t2 = driTimerCntGet();
		t2 -= t1;
		dprintf( "Dec1000 ms=%d:", t2 * TIMER_UNIT_MS );
	}

	

	#endif

	_cnt ++;
	
}




void testModAes( void )
{
	timerStartSec(1, 8, _aesTestCB );
}



#endif






