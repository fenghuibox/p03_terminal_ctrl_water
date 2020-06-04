/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __AES_KEY_H
#define __AES_KEY_H


#include "com_typedef.h"


#define  AES_UNIT_LEN   (16)
#define  AES_KEY_LEN    (16)


extern u8 aesKeySet( u8 *pKey ) ;


extern void aesKeyGet2(  u8 frameLen, u8 frameVer, u8 frameAct, u8 frameCheck, u8 *pOutKey );

extern void aesKeyGet(  u8 *pFrame, u8 *pOutKey );


extern void aesKeyInit( void );



#endif

