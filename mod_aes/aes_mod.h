/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __AES_MOD_H
#define __AES_MOD_H


#include "com_typedef.h"


#include "aes_128.h"

#include "aes_switch.h"
#include "aes_key12.h"
#include "aes_key4.h"
#include "aes_key.h"





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
// pFrame: in/out
// pLen:   in/out
extern u8 aesEnc( u8 *pFrame, u8 *pLen );











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
// pFrame: in/out
// pLen:   in/out
extern u8 aesDec( u8 *pFrame, u8 *pLen );



extern void aesEepDef( void );



extern void aesInit( void );



#ifdef TEST_MOD_AES

extern void testModAes( void );

#endif


#endif

