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





#ifdef AES_128_USE_SW

// AES128 ECB 加密  无填充



// foreward sbox
const unsigned char sbox[256] =   {
//0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, //0
0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, //1
0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, //2
0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, //3
0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, //4
0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, //5
0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, //6
0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, //7
0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, //8
0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, //9
0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, //A
0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, //B
0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, //C
0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, //D
0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, //E
0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 }; //F

// inverse sbox
const unsigned char rsbox[256] =
{ 0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb
, 0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb
, 0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e
, 0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25
, 0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92
, 0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84
, 0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06
, 0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b
, 0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73
, 0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e
, 0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b
, 0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4
, 0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f
, 0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef
, 0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61
, 0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };

// round constant
const unsigned char Rcon[10] = {
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
	};


// multiply by 2 in the galois field
static unsigned char galois_mul2(unsigned char value)
{
	signed char temp;
	// cast to signed value
	temp = (signed char) value;
	// if MSB is 1, then this will signed extend and fill the temp variable with 1's
	temp = temp >> 7;
	// AND with the reduction variable
	temp = temp & 0x1b;
	// finally shift and reduce the value
	return ((value << 1)^temp);
}



/*------------------------------------------------------------------------------
                   AES_128 加密 和 解密
--------------------------------------------------------------------------------
state : in/out | 要加密或解密的文本
key:    in| 密匙
dir:    in| 0:加密   非0: 解密
---------------------------------------------------------------------------------*/
void aesEncDec( unsigned char *state, unsigned char *key, unsigned char dir )
{
	unsigned char buf1, buf2, buf3, buf4, round, i;

	// In case of decryption
	if (dir) 
	{
		// compute the last key of encryption before starting the decryption
		for (round = 0 ; round < 10; round++) 
		{
			//key schedule
			key[0] = sbox[key[13]]^key[0]^Rcon[round];
			key[1] = sbox[key[14]]^key[1];
			key[2] = sbox[key[15]]^key[2];
			key[3] = sbox[key[12]]^key[3];
			for (i=4; i<16; i++) 
			{
				key[i] = key[i] ^ key[i-4];
			}
		}

		//first Addroundkey
		for (i = 0; i <16; i++)
		{
			state[i]=state[i] ^ key[i];
		}
	}

	// main loop
	for (round = 0; round < 10; round++)
	{
		if (dir)
		{
			//Inverse key schedule
			for (i=15; i>3; --i)
			{
				key[i] = key[i] ^ key[i-4];
			}  
			key[0] = sbox[key[13]]^key[0]^Rcon[9-round];
			key[1] = sbox[key[14]]^key[1];
			key[2] = sbox[key[15]]^key[2];
			key[3] = sbox[key[12]]^key[3]; 
		} 
		else 
		{
			for (i = 0; i <16; i++)
			{
				// with shiftrow i + 5 mod 16
				state[i]=sbox[state[i] ^ key[i]];
			}
			
			//shift rows
			buf1 = state[1];
			state[1] = state[5];
			state[5] = state[9];
			state[9] = state[13];
			state[13] = buf1;

			buf1 = state[2];
			buf2 = state[6];
			state[2] = state[10];
			state[6] = state[14];
			state[10] = buf1;
			state[14] = buf2;

			buf1 = state[15];
			state[15] = state[11];
			state[11] = state[7];
			state[7] = state[3];
			state[3] = buf1;
		}
		
		//mixcol - inv mix
		if ((round > 0 && dir) || (round < 9 && !dir)) 
		{
			for (i=0; i <4; i++)
			{
				buf4 = (i << 2);
				if (dir)
				{
					// precompute for decryption
					buf1 = galois_mul2(galois_mul2(state[buf4]^state[buf4+2]));
					buf2 = galois_mul2(galois_mul2(state[buf4+1]^state[buf4+3]));
					state[buf4] ^= buf1; state[buf4+1] ^= buf2; state[buf4+2] ^= buf1; state[buf4+3] ^= buf2; 
				}
				// in all cases
				buf1 = state[buf4] ^ state[buf4+1] ^ state[buf4+2] ^ state[buf4+3];
				buf2 = state[buf4];
				buf3 = state[buf4]^state[buf4+1]; buf3=galois_mul2(buf3); state[buf4] = state[buf4] ^ buf3 ^ buf1;
				buf3 = state[buf4+1]^state[buf4+2]; buf3=galois_mul2(buf3); state[buf4+1] = state[buf4+1] ^ buf3 ^ buf1;
				buf3 = state[buf4+2]^state[buf4+3]; buf3=galois_mul2(buf3); state[buf4+2] = state[buf4+2] ^ buf3 ^ buf1;
				buf3 = state[buf4+3]^buf2;     buf3=galois_mul2(buf3); state[buf4+3] = state[buf4+3] ^ buf3 ^ buf1;
			}
		}
    
		if (dir) 
		{
			//Inv shift rows
			// Row 1
			buf1 = state[13];
			state[13] = state[9];
			state[9] = state[5];
			state[5] = state[1];
			state[1] = buf1;
			//Row 2
			buf1 = state[10];
			buf2 = state[14];
			state[10] = state[2];
			state[14] = state[6];
			state[2] = buf1;
			state[6] = buf2;
			//Row 3
			buf1 = state[3];
			state[3] = state[7];
			state[7] = state[11];
			state[11] = state[15];
			state[15] = buf1;         
	           
			for (i = 0; i <16; i++)
			{
				// with shiftrow i+5 mod 16
				state[i]=rsbox[state[i]] ^ key[i];
			} 
		} 
		else 
		{
			//key schedule
			key[0] = sbox[key[13]]^key[0]^Rcon[round];
			key[1] = sbox[key[14]]^key[1];
			key[2] = sbox[key[15]]^key[2];
			key[3] = sbox[key[12]]^key[3];
			for (i=4; i<16; i++) 
			{
				key[i] = key[i] ^ key[i-4];
			}
		}
	}

	if (!dir)
	{
		//last Addroundkey
		for (i = 0; i <16; i++)
		{
			// with shiftrow i+5 mod 16
			state[i]=state[i] ^ key[i];
		} // enf for
	} // end if (!dir)
} // end function




//==== start test ========================================================================================

#if 0
#define _TEST_CNT 100

#include "hal_led.h"
int aes_test( void )
{
  //WDTCTL = WDTPW + WDTHOLD;             // Stop watchdog timer
  
  unsigned char state[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 
                               0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
  //unsigned char ciphertext[] = {0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30,
  //                              0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a};
  unsigned char key1[]   = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                           0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

  unsigned char key2[]   = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                           0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

  unsigned char i;

  while(1)
  {
	  HalLedSet(HAL_LED_1, HAL_LED_MODE_ON);

	  //for( i = _TEST_CNT; i != 0; i-- )
	  	aes_enc_dec(state,key1,0); // 100 次 用时 330.4 ms
	  
	  HalLedSet(HAL_LED_1, HAL_LED_MODE_OFF);
	 // for( i = _TEST_CNT; i != 0; i-- )
	  	aes_enc_dec(state,key2,1);// 100 次 用时 458.4 ms
  }

  return 0;
}
#endif
//===== end test =======================================================================================

 


void aes128Init( void )
{
	
}


#endif






#ifdef AES_128_USE_HW

#include "dbg_uart.h"

static void _aesEnc( u8 *pInTxt, u8 *pInKey ) // 加密
{	
	u32 pKey[4]    = {0};
	u32 pTxt[4]    = {0};
	u32 pEncTxt[4] = {0};//< 存放加密后的数据
		
    stc_aes_cfg_t stcAesCfg;                                  
 
    
    ///< 打开AES外设门控时钟
    Sysctrl_SetPeripheralGate(SysctrlPeripheralAes, TRUE);

	memcpy( pTxt, pInTxt, 16 );
	
	memcpy( pKey, pInKey, 16 );


    ///<KEY 128
    stcAesCfg.pu32Plaintext = pTxt;       ///< AES 明文指针
    stcAesCfg.pu32Cipher    = pEncTxt;           ///< AES 密文指针
    stcAesCfg.pu32Key       = pKey;     ///< AES 密钥指针
    stcAesCfg.enKeyLen      = AesKey128;         ///< AES 密钥长度类型

	
    ///< AES 加密
    AES_Encrypt(&stcAesCfg);

	memcpy( pInTxt, pEncTxt, 16 );
	
	//dprintfBuf( "hwEnc=", (u8 *)pEncTxt, 16, 1 );
	
    Sysctrl_SetPeripheralGate(SysctrlPeripheralAes, FALSE);

}



static void _aesDec( u8 *pInEncTxt, u8 *pInKey )
{
	
	u32 pKey[4]     = {0};
	u32 pEncTxt[4]  = {0};
	u32 pDecTxt[4]  = {0};//< 存放解密后的数据
	

    stc_aes_cfg_t stcAesCfg;                                  
 
    
    ///< 打开AES外设门控时钟
    Sysctrl_SetPeripheralGate(SysctrlPeripheralAes, TRUE);
	
	memcpy( pKey,    pInKey,    16 );
	memcpy( pEncTxt, pInEncTxt, 16 );


    ///<KEY 128
    stcAesCfg.pu32Plaintext = pDecTxt;       ///< AES 明文指针
    stcAesCfg.pu32Cipher    = pEncTxt;       ///< AES 密文指针
    stcAesCfg.pu32Key       = pKey;        ///< AES 密钥指针
    stcAesCfg.enKeyLen      = AesKey128;            ///< AES 密钥长度类型

	
    ///< AES 解密
    AES_Decrypt(&stcAesCfg);

	memcpy( pInEncTxt, pDecTxt, 16 );
	
	//dprintfBuf( "hwDec=", (u8 *)pDecTxt, 16, 1 );
	
	
    Sysctrl_SetPeripheralGate(SysctrlPeripheralAes, FALSE);

}




/*------------------------------------------------------------------------------
                   AES_128 加密 和 解密
--------------------------------------------------------------------------------
state : in/out | 要加密或解密的文本
key:    in| 密匙
dir:    in| 0:加密   非0: 解密
---------------------------------------------------------------------------------*/
void aesEncDec( u8 *pTxt, u8 *pKey, u8 dir )
{
	if( dir == 0 )
		_aesEnc( pTxt, pKey );
	else
		_aesDec( pTxt, pKey );
}






#ifdef TEST_AES_128_HW


#include "timer.h"
#include "dbg_uart.h"


void testAesGetKey( U8 *pKey )
{
	u8 key[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

	memcpy( pKey, key, 16 );
}

void testAesGetData( U8 *pData )
{
	u8 data[16] = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26 };

	memcpy( pData, data, 16 );
}



void aesTimerCB( void )
{
	static int _cnt = 0;

	static u8 _pKey[16] = {0};
	static u8 _pData[16] = {0};


	if(_cnt == 0 )
	{
		testAesGetKey( _pKey );
		testAesGetData( _pData );
		
		aesEncDec( _pData, _pKey, 0 );
		dprintfBuf( "hwEnc=", _pData, 16, 1 );
	}
	else
	{
		aesEncDec( _pData, _pKey, 1 );
		dprintfBuf( "hwDec=", _pData, 16, 1 );
	}

	_cnt++;
}

void testAesHw( void )
{
	timerStart( 500, 2, aesTimerCB );
}

#endif


#endif









#if 0


void testAesGetKey( U8 *pKey )
{
	u8 key[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

	memcpy( pKey, key, 16 );
}

void testAesGetData( U8 *pData )
{
	u8 data[16] = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26 };

	memcpy( pData, data, 16 );
}


void testSwAes( void )
{
	#include "aes_128.h"
	
	u8 pKey[16] = {0};
	u8 pData[16] = {0};


	testAesGetKey(pKey);
	testAesGetData(pData);
	aesEncDec( pData, pKey, 0 );

	dprintfBuf( "swEnc=", pData, 16, 1 );


	testAesGetKey(pKey);
	aesEncDec( pData, pKey, 1 );

	dprintfBuf( "swDec=", pData, 16, 1 );
}

void testHwAes( void )
{
	//< AEC密匙
	u32 pKey[4]  = {0};
	
	//< 存放待加密的数据
	u32 pTestData[4] = {0};
	
	
	//< 存放加密后的数据
	u32 pTestDataEnc[4] = {0};
	
	//< 存放解密后的数据
	u32 pTestDataDec[4]  = {0};
	

    stc_aes_cfg_t stcAesCfg;                                  
 
    
    ///< 打开AES外设门控时钟
    Sysctrl_SetPeripheralGate(SysctrlPeripheralAes, TRUE);

	
	testAesGetKey( (u8 *)pKey );
	testAesGetData( (u8 *)pTestData );
    
    ///<KEY 128
    stcAesCfg.pu32Plaintext = pTestData;       ///< AES 明文指针
    stcAesCfg.pu32Cipher    = pTestDataEnc;       ///< AES 密文指针
    stcAesCfg.pu32Key       = pKey;        ///< AES 密钥指针
    stcAesCfg.enKeyLen      = AesKey128;            ///< AES 密钥长度类型
    ///< AES 加密
    AES_Encrypt(&stcAesCfg);

	dprintfBuf( "hwEnc=", (u8 *)pTestDataEnc, 16, 1 );
	
    ///< AES 解密
    stcAesCfg.pu32Plaintext = pTestDataDec;
    AES_Decrypt(&stcAesCfg);

	dprintfBuf( "hwDec=", (u8 *)pTestDataDec, 16, 1 );
	
    Sysctrl_SetPeripheralGate(SysctrlPeripheralAes, FALSE);

}


void aesTimerCB( void )
{
	static int _cnt = 0;

	if(_cnt == 0 )
		testSwAes();
	else
		testHwAes();

	_cnt++;
}

static void _testAes( void )
{
	timerStart( 1000, 10, aesTimerCB );
}




#endif



