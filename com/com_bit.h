/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __COM_BIT_H
#define __COM_BIT_H


#include "com_typedef.h"


#if 0


#if 1
	void comBitSet1(volatile U32 *pReg, U32 bitMask);
	void comBitSet0(volatile U32 *pReg, U32 bitMask);
	
	//=============================================================
	// 连续的 bit 段 赋值 
	void comBitsSetVal(volatile U32 *pReg, U32 bitsMask, U32 val);

#else
	#define comBitSet1(pReg, bitMask)  *pReg |= bitMask
	#definecomBitSet0(pReg, bitMask)  *pReg &= (~bitMask)
#endif

#define HIWORD(a)  (U8)(  ( (U16)a ) >>8 )
#define LOWORD(a)  (U8)( (U16)a  )
#define MERGE16(high, low) ( ( ((U16)high ) << 8 ) | (U16)low )


#define HIDWORD(a)  (WORD)(  ( (DWORD)a ) >>16 )
#define LODWORD(a)  (WORD)( (DWORD)a  )
#define MERGE32(high, low) ( ( ((DWORD)high ) << 16 ) | (DWORD)low )


#endif

#endif


