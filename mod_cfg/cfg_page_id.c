/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/

#include "dri_flash_f_eep.h"

#include "cfg_com.h"
#include "cfg_page_id.h"
#include "dbg_uart.h"


static u32 _cfgPageId;




u32 cfgPageIdIsOk( u32 id )
{
	if( id < PAGE_ID_VAL_PAGE_ID && id > (PAGE_ID_VAL_PAGE_ID - FLASH_PAGE_VAL_DEC_MAX) )
		return TRUE;

	return FALSE;
}



u32 cfgPageIdGet( void )
{
	return _cfgPageId;
}




int cfgPageIdSet( u32 pageId )
{
	if( _cfgPageId == pageId )
		return 0;
	

	_cfgPageId = pageId;
	
	if(gB1.inited == 1)
    	dprintf("cfgPageIdSet=%d", _cfgPageId); // 

    return driFlashEepWrite( PAGE_ID_VAL_PAGE_ID, 0, &_cfgPageId, 1);
}




int cfgPageIdDef( void )
{
	if(gB1.inited == 1)
    	dprintf("\r\ncfgPageIdDef" ); // 
    
	_cfgPageId = 0;
	
    return cfgPageIdSet( PAGE_ID_VAL );
}


void cfgPageIdLoad( void )
{
    driFlashEepRead( PAGE_ID_VAL_PAGE_ID, 0, &_cfgPageId, 1 );
}



void cfgPageIdInit( void )
{
    cfgPageIdLoad();

    if( _cfgPageId > PAGE_ID_VAL_PAGE_ID  )// 第一次使用
    {
    	cfgPageIdDef();
    }
    else
    {
    }
}





