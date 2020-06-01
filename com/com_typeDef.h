/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __COM_TYPEDEF_H
#define __COM_TYPEDEF_H

#include <assert.h>

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
//#include <malloc.h>


#if 1
typedef signed long s32;
typedef signed short s16;
typedef signed char s8;
typedef signed long const sc32; /* Read Only */
typedef signed short const sc16; /* Read Only */
typedef signed char const sc8; /* Read Only */
typedef volatile signed long vs32;
typedef volatile signed short vs16;
typedef volatile signed char vs8;
typedef volatile signed long const vsc32; /* Read Only */
typedef volatile signed short const vsc16; /* Read Only */
typedef volatile signed char const vsc8; /* Read Only */
typedef unsigned long u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned long const uc32; /* Read Only */
typedef unsigned short const uc16; /* Read Only */
typedef unsigned char const uc8; /* Read Only */
typedef volatile unsigned long vu32;
typedef volatile unsigned short vu16;
typedef volatile unsigned char vu8;
typedef volatile unsigned long const vuc32; /* Read Only */
typedef volatile unsigned short const vuc16; /* Read Only */
typedef volatile unsigned char const vuc8; /* Read Only */

#endif



#if 1

typedef signed long S32;
typedef signed short S16;
typedef signed char S8;
typedef signed long const SC32; /* Read Only */
typedef signed short const SC16; /* Read Only */
typedef signed char const SC8; /* Read Only */
typedef volatile signed long VS32;
typedef volatile signed short VS16;
typedef volatile signed char VS8;
typedef volatile signed long const VSC32; /* Read Only */
typedef volatile signed short const VSC16; /* Read Only */
typedef volatile signed char const VSC8; /* Read Only */
typedef unsigned long U32;
typedef unsigned short U16;
typedef unsigned char U8;
typedef unsigned long const UC32; /* Read Only */
typedef unsigned short const UC16; /* Read Only */
typedef unsigned char const UC8; /* Read Only */
typedef volatile unsigned long VU32;
typedef volatile unsigned short VU16;
typedef volatile unsigned char VU8;
typedef volatile unsigned long const VUC32; /* Read Only */
typedef volatile unsigned short const VUC16; /* Read Only */
typedef volatile unsigned char const VUC8; /* Read Only */


#endif



/*
#define U32 u32
*/




#ifndef NULL
	#define NULL    ((void *)0)
#endif


#ifndef FAIL
	#define FAIL    (-1)
#endif


#if 1
	#ifndef FALSE
		#define FALSE   (0)
	#endif

	#ifndef TRUE
		#define TRUE    (1)
	#endif
#endif


typedef void ( *FunTimeIrqCB)( void );


typedef void ( *FunKeyUpCB)( void );


typedef void ( *LedCB)( void );


typedef  void ( *FunBspRxCB)(u8 *str,u8 len); // bsp_uart.c

typedef  void ( *FunBspRxCB)(u8 *str,u8 len); // 



typedef  void ( *FunBspTxFinishCB)( void ); // bsp_uart.c



typedef  int ( *FunG2sTxCB)( u8 *pBuf, u16 len );



//=====================================================
#define DRI_INIT_USE_GPIO_IO


//====== 模块 测试开关 (一般情况下，只开启一个 )======================

//#define TEST_DRI_TIMER


//#define TEST_COM_DELAY

#define TEST_MOD_TIMER


//#define  TEST_DRI_FLASH_F_EEP

//#define  TEST_MOD_CONFIG


//#define  TEST_MOD_DEBUG_UART

//#define  TEST_MOD_AES

//#define  TEST_ZGB_NODE

//#define TEST_CTRL_OUT


#endif

