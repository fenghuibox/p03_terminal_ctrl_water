/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __AES_KEY12_H
#define __AES_KEY12_H


#include "com_typedef.h"


#define  AES_KEY_12_LEN    (12)






extern u8 aesKey12Set( u8 *pKey );


extern void aesKey12Get( u8 *pKey );

extern u8 aesKey12isEqu( u8 *pKey );


extern u8 * _aesKey12Get( void );

extern void aesKey12Def( void );


extern void aesKey12Load( void );





extern void aesKey12Init( void );



#endif

