/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 


#include "com_includes.h"


#include "aes_key4.h"
#include "f_txt_frame.h"

static const u8 constAesKey4[]={'F', 'z', '9', '@'}; //  


/*---------------- hZmY --------------------------
			   16����	  10����	MOD4  ȡֵ	
D1	֡��ʼ	1				                
D2	֡����	1	16	       22	     2	   Z
D3	֡�汾	1	1	       1	     1	   h
D4	֡��Ϊ	1	3	       3	     3	   m
D5	У���	1	29	       41	     1	   h

key4 = Zhmh
*/


void aesKey4Get2( u8 frameLen, u8 frameVer, u8 frameAct, u8 frameCheck, u8 *pOutKey4 )
{
	*pOutKey4 = constAesKey4[ (frameVer + frameCheck ) % 4 ];
	pOutKey4++;
	*pOutKey4 = constAesKey4[ (frameAct + frameCheck ) % 4 ];
	pOutKey4++;
	*pOutKey4 = constAesKey4[ frameCheck % 4 ];
	pOutKey4++;
	*pOutKey4 = constAesKey4[ (frameVer + frameAct + frameCheck ) % 4 ];
}

void aesKey4Get( u8 *pFrame, u8 *pOutKey4 )
{
	*pOutKey4 = constAesKey4[ ( pFrame[ TXT_FRAME_OFFSET_VER ] + pFrame[TXT_FRAME_OFFSET_CHECK] ) % 4 ];
	pOutKey4++;
	*pOutKey4 = constAesKey4[ ( pFrame[TXT_FRAME_OFFSET_ACTION] + pFrame[TXT_FRAME_OFFSET_CHECK] ) % 4 ];
	pOutKey4++;
	*pOutKey4 = constAesKey4[ pFrame[TXT_FRAME_OFFSET_CHECK] % 4 ];
	pOutKey4++;
	*pOutKey4 = constAesKey4[ ( pFrame[TXT_FRAME_OFFSET_VER] + pFrame[TXT_FRAME_OFFSET_ACTION] + pFrame[TXT_FRAME_OFFSET_CHECK] ) % 4 ];
}





void aesKey4Init( void )
{

}




