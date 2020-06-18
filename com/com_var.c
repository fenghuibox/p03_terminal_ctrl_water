/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#include "com_typedef.h"
#include "com_memory.h"

#include "com_var.h"



ST_BOOL gB1 = {0};




void valBitSet1(U32 *pVar, U32 bitMask)
{
	*pVar |= bitMask;
}

void valBitSet0(U32 *pVar, U32 bitMask)
{
	*pVar &= (~bitMask);
}

void valBitReverse(U32 *pVar, U32 bitMask)
{
	*pVar ^= bitMask;
}







/*
���� a = 3,b = 4���뽫a��b��ֵ������������һ�¸�ֵ���ʵ�֣�
 
a = a ^ b��
b = b ^ a��
a = a ^ b��
 
��������ʽ���м�˵����(10���ƻ�Ϊ������)
 
     a = 011
 (^) b = 100
  �� a = 111(a ^ b�Ľ����ֵ��a��a�ѱ����7)
 (^) b = 100
  �� b = 011(b^a�Ľ������b��b�Ѿ������3)
 (^) a = 111
  �� a = 100(a^b�Ľ������a��a�Ѿ������4) 
*/

void comSwapU32( u32 *pD1, u32 *pD2)
{
	#if 0
	u32 d;

	d    = *pD1;
	*pD1 = *pD2;
	*pD2 = d;
	#else

	*pD1 ^= *pD2;
	*pD2 ^= *pD1;
	*pD1 ^= *pD2;
	
	#endif
}


void comSwapU8( u8 *pD1, u8 *pD2)
{
	#if 0
	u32 d;

	d    = *pD1;
	*pD1 = *pD2;
	*pD2 = d;
	#else

	*pD1 ^= *pD2;
	*pD2 ^= *pD1;
	*pD1 ^= *pD2;
	
	#endif
}




void comU8Inc( u8 *pVal )
{
	if( *pVal  != 0xFF )
		(*pVal) ++;
}


void comU8Dec( u8 *pVal )
{
	if( *pVal  != 0 )
		(*pVal) --;
}


void comU32Inc( u32 *pVal )
{
	if( *pVal  != 0xFFFFFFFF )
		(*pVal) ++;
}


void comU32Dec( u32 *pVal )
{
	if( *pVal  != 0 )
		(*pVal) --;
}


//=====================================

u16 byteMergeto16( u8 high, u8 low )
{
	u16 val;
	
	val   = high;
	val <<= 8;
	val  += low;

	return val;
}


// high -> pBuf[0]
void u16splitToByteHL( u16 val, u8 *pBuf ) 
{	
	pBuf[1] = (u8)(val & 0xFF);

	val >>= 8;
	*pBuf  =  (u8)(val & 0xFF);

}

// low -> pBuf[0]
void u16splitToByteLH( u16 val, u8 *pBuf ) 
{	
	pBuf[0] = (u8)(val & 0xFF);

	val >>= 8;
	pBuf[1]  =  (u8)(val & 0xFF);

}



u32 byteMergeto32( u8 highMax, u8 high, u8 low, u8 lowMin )
{
	u32 val;
	
	val   = highMax;
	val <<= 8;
	val  += high;
	val <<= 8;
	val  += low;
	val <<= 8;
	val  += lowMin;	

	return val;
}


// high -> pBuf[0]  
void u32splitToByte( u32 val, u8 *pBuf ) 
{	
	pBuf[3]  = (u8)(val & 0xFF);

	val >>= 8;
	pBuf[2]  = (u8)(val & 0xFF);

	val >>= 8;
	pBuf[1]  = (u8)(val & 0xFF);
	
	val >>= 8;
	pBuf[0]  = (u8)(val & 0xFF);
}





// 0x01020304 --> 0x04030201
void u32Image( u8 *pU32 ) 
{
	comSwapU8( pU32, pU32 + 3 );
	comSwapU8( pU32 + 1, pU32 + 2 );
}


// 0x01020304 --> 0x40302010
void u32Image2( u8 *pU32 ) 
{
	int i;
	u32 val = 0;
	u32 temp;

	temp = *pU32;
	
	for( i = 31; i != 0; i-- )
	{
		if( temp & 1 )
			val |= 1;

		temp >>= 1;
		val  <<= 1;
		
	}

	// ���һλ
	if( temp & 1 )
		val |= 1;

	*pU32 = val;

	
}




