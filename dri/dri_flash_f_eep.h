/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2020-06-01                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/


#ifndef _DRI_FLASH_F_EEP_H_
#define _DRI_FLASH_F_EEP_H_



#include "com_typedef.h"


// flash size = 128KB


#define FLASH_PAGE_SIZE     (512)
#define FLASH_PAGE_ID_SIZE  (256)


#define FLASH_PAGE_ID_MAX      (255)
#define FLASH_PAGE_VAL_DEC_MAX  (60) // 


#define PAGE_ID_VAL_PAGE_ID   ( FLASH_PAGE_ID_MAX )    // 变量页的地址页ID
#define PAGE_ID_VAL          ( PAGE_ID_VAL_PAGE_ID-1 ) // 变量页ID

#define PAGE_WRITE_CNT_MAX  (98000L)
//#define PAGE_WRITE_CNT_MAX  (3L)

//----------------------------------------------------------------
// FLASH  = 128K   page = 512 B
// pageId : 0 -- (255) ( 512 * 256 = 128KB )
// val    :
extern int driFlashEepClear( u32 pageId,  u8 val );



//----------------------------------------------------------------
// FLASH  = 128K   page = 512 B
// pageId : 0 -- (255) ( 512 * 256 = 128KB )
// index  : 0 -- (128-1) ( 4 * 128 = 512 )
// buf    :
// len    : 32位数的个数
extern int driFlashEepWrite( u32 pageId, u32 index, u32 *pBuf, u32 len );



//----------------------------------------------------------------
// FLASH  = 128K   page = 512 B
// pageId : 0 -- (255) ( 512 * 256 = 128KB )
// index  : 0 -- (128-1) ( 4 * 128 = 512 )
// buf    :
// len    : 32位数的个数
extern int driFlashEepRead( u32 pageId, u32 index, u32 *pOutBuf, u32 len );








 extern u32 *driFlashEepGetPageBuf( void );


 // pageId : 0 -- (255) ( 512 * 256 = 128KB )
 extern void driFlashEepReadPage( u32 pageId, u32 *pOutBuf );













extern void driFlashEepInit( void );




#ifdef TEST_DRI_FLASH_F_EEP

extern void driFlashEepTest( void );
#endif




#endif /* APPLICATIONS_INCLUDE_DRI_FLASH_F_EEP_H_ */
