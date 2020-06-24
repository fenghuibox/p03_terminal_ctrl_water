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
#include <time.h>

//#include <malloc.h>


#if 1
typedef signed int s32;
typedef signed short s16;
typedef signed char s8;
typedef signed int const sc32; /* Read Only */
typedef signed short const sc16; /* Read Only */
typedef signed char const sc8; /* Read Only */
typedef volatile signed int vs32;
typedef volatile signed short vs16;
typedef volatile signed char vs8;
typedef volatile signed int const vsc32; /* Read Only */
typedef volatile signed short const vsc16; /* Read Only */
typedef volatile signed char const vsc8; /* Read Only */
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned int const uc32; /* Read Only */
typedef unsigned short const uc16; /* Read Only */
typedef unsigned char const uc8; /* Read Only */
typedef volatile unsigned int vu32;
typedef volatile unsigned short vu16;
typedef volatile unsigned char vu8;
typedef volatile unsigned int const vuc32; /* Read Only */
typedef volatile unsigned short const vuc16; /* Read Only */
typedef volatile unsigned char const vuc8; /* Read Only */

#else
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

typedef signed int S32;
typedef signed short S16;
typedef signed char S8;
typedef signed int const SC32; /* Read Only */
typedef signed short const SC16; /* Read Only */
typedef signed char const SC8; /* Read Only */
typedef volatile signed int VS32;
typedef volatile signed short VS16;
typedef volatile signed char VS8;
typedef volatile signed int const VSC32; /* Read Only */
typedef volatile signed short const VSC16; /* Read Only */
typedef volatile signed char const VSC8; /* Read Only */
typedef unsigned int U32;
typedef unsigned short U16;
typedef unsigned char U8;
typedef unsigned int const UC32; /* Read Only */
typedef unsigned short const UC16; /* Read Only */
typedef unsigned char const UC8; /* Read Only */
typedef volatile unsigned int VU32;
typedef volatile unsigned short VU16;
typedef volatile unsigned char VU8;
typedef volatile unsigned int const VUC32; /* Read Only */
typedef volatile unsigned short const VUC16; /* Read Only */
typedef volatile unsigned char const VUC8; /* Read Only */

#else

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

typedef void ( *irqCB)( void );

typedef  void ( *FunUartPackRxCB)(u8 *str,u32 len); // 
typedef  void ( *FunUartPackTxFinishCB)( void );    // 



typedef  void ( *FunAdcCB)( u32 val );    // 




typedef  int ( *FunN2sTxCB)( u8 *pBuf, u16 len );









//========= 选用 模块 开关 =============================

#if 0
	#define USE_IWDG
#endif


#if 0
	#define AES_128_USE_SW
#else
	#define AES_128_USE_HW
#endif



#define RTC_ARL_USED_PERIOD


//#define DEV_DEBUG_ING


//====== 模块 测试开关 (一般情况下，只开启一个 )======================

//#define TEST_DRI_TIMER

//#define  TEST_DRI_UART_DEBUG


//#define TEST_COM_DELAY

//#define TEST_MOD_TIMER

//#define  TEST_MOD_DBG_UART

//#define  TEST_DRI_FLASH_F_EEP

//#define  TEST_MOD_CONFIG

//#define TEST_AES_128_HW

//#define  TEST_MOD_AES

//#define  TEST_MOD_ZGB_UART



//#define  TEST_COM_TIME


//#define  TEST_MOD_CTRL




#endif

