/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/



#if 0
#include "com_typedef.h"
#include "com_bit.h"

void comBitSet1(volatile U32 *pReg, U32 bitMask)
{
	*pReg |= bitMask;
}

void comBitSet0(volatile U32 *pReg, U32 bitMask)
{
	*pReg &= (~bitMask);
}


//=============================================================
// ������ bit �� ��ֵ 
void comBitsSetVal(volatile U32 *pReg, U32 bitsMask, U32 val)
{
	U32 i;
	U32 v;

	if(bitsMask == 0)
		return;

	comBitSet0(pReg, bitsMask); // ���� ������ bit ��

	for(i = 0; 1; i++)
	{
		if( ( (bitsMask >> i) & 1 ) == 1 )
			break;
	}

	v = val << i;

	
	comBitSet1(pReg, v ); // ��ֵ ������ bit ��
	
}

//end common
//============================================   



#endif





