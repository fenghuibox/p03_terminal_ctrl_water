/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#if 1

#ifndef __COM_MAC_H
#define __COM_MAC_H


#include "com_typedef.h"


#define MAC_ADDR_LEN (8)


//===========================================================
extern void macCopy( u8 *dstMac, u8 *srcMac );



extern u8 macIsEqual( u8* pMac1, u8* pMac2 );



extern int macIsGateway00( u8 *pMac );



extern int macIsNodeFF( u8 *pMac );






//===========================================================
extern void macSetToGateway00( u8 *pMac );


extern void macSetToNodeFF( u8 *pMac );








#endif

#endif


