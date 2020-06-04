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


#include "aes_key4.h"
#include "f_txt_frame.h"

static const u8 constAesKey4[]={'F', 'z', '9', '@'}; //  


/*---------------- hZmY --------------------------
			   16进制	  10进制	MOD4  取值	
D1	帧开始	1				                
D2	帧长度	1	16	       22	     2	   Z
D3	帧版本	1	1	       1	     1	   h
D4	帧行为	1	3	       3	     3	   m
D5	校验和	1	29	       41	     1	   h

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




