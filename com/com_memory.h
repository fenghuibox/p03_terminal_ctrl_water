/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __COM_MEMORY_H
#define __COM_MEMORY_H


#include "com_typedef.h"

#define COM_MEM_PARA_ERROR  (-199999)

extern void comMallocEr( void );


extern void* comMemcpy(void *dest, void *src, u32 n);

extern int comMemcmp(const u8 *pBuf1, const u8 *pBuf2, u32 cnt);

extern u8 *comMemset( u8 *pBuf, u8 ch, u32 n);

#endif

