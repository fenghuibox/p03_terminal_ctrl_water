/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef ___DBG_CMD_AES_H
#define ___DBG_CMD_AES_H


#include "com_typedef.h"

extern const char strCmdAesHead[];

#define DEBUG_AES_HEAD_LEN   (3)




// str = switchget / keyget ...
extern u8 debugCmdAes( u8 *str,  u8 len );



#endif

