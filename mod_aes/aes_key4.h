/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __AES_KEY4_H
#define __AES_KEY4_H


#include "com_typedef.h"





extern void aesKey4Get2( u8 frameLen, u8 frameVer, u8 frameAct, u8 frameCheck, u8 *pOutKey4 );

extern void aesKey4Get( u8 *pFrame, u8 *pOutKey4 );

extern void aesKey4Init( void );



#endif

