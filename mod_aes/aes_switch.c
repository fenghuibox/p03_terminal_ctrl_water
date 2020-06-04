/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 


#include "com_includes.h"

#include "aes_switch.h"

#include "cfg_aes.h"



void aesSwitchSet( u8 onoff )// 0: off
{
	cfgAesSwitchSet( onoff );
}


u8 aesSwitchIsEqu( u8 sw )
{
	if( cfgAesSwitchGet() ) 
	{
		if( sw == 0 )
			return FALSE;
		else
			return TRUE;
	}
	else
	{
		if( sw == 0 )
			return TRUE;
		else
			return FALSE;
	}
}


u8 aesSwitchGet( void )
{
	return  cfgAesSwitchGet();
}

void aesSwitchDef( void )
{	
	cfgAesSwitchDef();
}





