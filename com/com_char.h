/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __COM_CHAR_H
#define __COM_CHAR_H


#include "com_typedef.h"

//===================================================

/*

*/

#define CHAR_NO_SHOW_MAX    (0x1F)

#define CHAR_RETURN    (0x0D) //  '\r' 13 回车（return）
#define CHAR_NEW_LINE  (0x0A) //  '\n' 10 换行（newline）


/*
0 -- 9 :  0x30  -- 0x39
*/
#define CHAR_MAO_HAO   (0x3A) // 冒号
#define CHAR_DENG_HAO  (0x3D) // 等号
#define CHAR_WEN_HAO   (0x3F) // 问号

/*
A -- Z :  0x41  -- 0x5A
a -- z :  0x61  -- 0x7A

*/


//===================================================
extern u8 isOperator( u8  ch );


extern u8 isFloat( u8  ch );

extern u8 isNumber( u8 ch );


extern u8 isLower( u8 ch );


extern u8 isHexLower( u8 ch );




extern u8 isUpper( u8 ch );



extern u8 isHexUpper( u8 ch );



extern u8 isHex( u8 ch );

extern u8 isPwd( u8 ch );


//===================================================
extern u8 toLower( u8 ch ); 



extern u8 toUpper( u8 ch ); 





#endif

