/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __COM_STR_H
#define __COM_STR_H


#include "com_typedef.h"

//返回值：
//成功时，函数返回成功填充的参数列表中的项目数。 这个计数可以匹配预期的项目数量，或者在匹配失败的情况下可以小于 - 甚至为零。
// 在任何数据可被成功解释之前输入失败的情况下，返回EOF(-1)。
extern int strScanf(const char *pStr, const char *pFormat, ...);







extern void strPrintfBuf(u8 *pOutBuf, u32 bufLen, const char *pFormat, ...);



#endif

