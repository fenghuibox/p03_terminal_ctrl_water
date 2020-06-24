/*
 * Copyright (c) 2006-2020
 * hunan Central China Seedlings Cloud Tech. Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-04-21     fenghui      the first version
 */


#include "com_includes.h"

#include "dri_flash_f_eep.h"









#define _FLASH_TEMP_BUF_U32_CNT  (  FLASH_PAGE_SIZE/4 )


u32 _flashTempBuf[ _FLASH_TEMP_BUF_U32_CNT ];// 512





u32 *driFlashEepGetPageBuf( void )
{
    return _flashTempBuf;
}


// pageId : 0 -- (255) 
void driFlashEepReadPage( u32 pageId, u32 *pOutBuf )
{
    u32 i;
    VU32 *pFlash, *pBuf;

	
    if( pageId > FLASH_PAGE_ID_MAX )
        return;

    pBuf = pOutBuf;
    pFlash = (vu32 *)( FLASH_PAGE_SIZE * pageId);

    for( i = _FLASH_TEMP_BUF_U32_CNT; i != 0; i-- )
    {
        *pBuf++ =  *pFlash++;
    }
}





// pageId : 0 -- (255) 
static int _driFlashEepWritePage( u32 pageId, u32 *pInBuf )
{
#if 1
    u32 pFlash;
    
    pFlash = FLASH_PAGE_SIZE * pageId;


    ///< FLASH目标扇区擦除
    while( Ok != Flash_SectorErase(pFlash) )
    {
        ;
    }


	if( Flash_WritePage( pageId, pInBuf ) == Ok )
		return TRUE;

	return FALSE;
	
#else
    u32 i;
    VU32 *pFlash, *pBuf;

    pFlash = ( VU32 *)(FLASH_PAGE_SIZE * pageId);

    pBuf = pInBuf;

    for( i = _FLASH_TEMP_BUF_U32_CNT; i != 0; i--, pFlash++, pBuf++ )
    {
        if ( Flash_WriteWord( (U32)pFlash, *pBuf) == Ok )
        {

        }
        else
        {
            //LOG_E( (const char *)"driFlashEepWritePage err" );
            return FALSE;
        }
    }

    return TRUE;
#endif
}



//----------------------------------------------------------------
// FLASH  = 128K   page = 512 B
// pageId : 0 -- (255) ( 512 * 256 = 128KB )
// index  : 0 -- (128-1) ( 4 * 128 = 512 )
// buf    :
// len    : 32位数的个数
static int _driFlashEepWrite( u32 pageId, u32 index, u32 *pBuf, u32 len )
{
    if( pageId > FLASH_PAGE_ID_MAX )
        return FALSE;

    driFlashEepReadPage( pageId, _flashTempBuf );


    memcpy( _flashTempBuf + index, pBuf, len * 4);


    if( _driFlashEepWritePage( pageId, _flashTempBuf ) == FALSE )
    {
        return FALSE;
    }

    return TRUE;
}


//----------------------------------------------------------------
// FLASH  = 128K   page = 512 B
// pageId : 0 -- (255) ( 512 * 256 = 128KB )
// index  : 0 -- (128-1) ( 4 * 128 = 512 )
// buf    :
// len    : 32位数的个数
int driFlashEepWrite( u32 pageId, u32 index, u32 *pBuf, u32 len )
{
	#include "dbg_uart.h"

    int i;

    for( i = 4; i != 0; i-- )
    {
        if( _driFlashEepWrite(pageId, index, pBuf, len) != FALSE )
            return TRUE;
    }

	if(gB1.inited == 1)
		dprintf("\r\nflash write ERR");

    return FALSE;
}



int driFlashEepClear( u32 pageId,  u8 val )
{
    if( pageId > FLASH_PAGE_ID_MAX )
        return FALSE;

    memset(  _flashTempBuf, val, FLASH_PAGE_SIZE );

    if( _driFlashEepWritePage( pageId, _flashTempBuf ) == FALSE )
    {
        return FALSE;
    }

    return TRUE;
}



//----------------------------------------------------------------
// FLASH  = 128K   page = 512 B
// pageId : 0 -- (255) ( 512 * 256 = 128KB )
// index  : 0 -- (128-1) ( 4 * 128 = 512 )
// buf    :
// len    : 32位数的个数
int driFlashEepRead( u32 pageId, u32 index, u32 *pOutBuf, u32 len )
{
    u32 i;
    VU32 *pFlash, *pBuf;

    pBuf = pOutBuf;

    pFlash = (u32 *)(FLASH_PAGE_SIZE * pageId);

    pFlash += index;

    for( i = len; i != 0; i-- )
    {
        *pBuf++ =  *pFlash++;
    }

    return TRUE;
}



void driFlashEepInit( void )
{
    ///< 确保初始化正确执行后方能进行FLASH编程操作，FLASH初始化（编程时间,休眠模式配置）
    while( Ok != Flash_Init( 12, TRUE) )
    {
        ;
    }
}


#ifdef TEST_DRI_FLASH_F_EEP

void driFlashEepTest( void )
{

    //u32 pTxt[] = {1, 2, 3, 4, 5, 11, 12, 13, 14, 15};

    u32 pTxtOut[64] = {0};


    u8  pageId = 100;
    u16 index  = 100;
    u8  len    = 10;


    //driFlashEepWrite( pageId, index, pTxt, len );

    len *= 2;
    driFlashEepRead( pageId, index, pTxtOut, len );

    //LOG_HEX( "pTxtOut", 10, (U8 *)pTxtOut,len );


}


#endif


