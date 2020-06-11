/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/

#include "cfg_aes.h"
#include "cfg_com.h"


//====== aes switch  =====================================
u8 cfgAesSwitchGet( void ) //
{
    if( _stAppConfig.aes_switch == 0 )
		return 0;

	return 1;
}

u8 cfgAesSwitchSet( u8 s )
{
    if( _stAppConfig.aes_switch == s )
        return s;

    _cfgModify = 1;

    return _stAppConfig.aes_switch = s;
}

u32 cfgAesSwitchDef( void )
{
    return cfgAesSwitchSet( CONFIG_DEF_AES_SWITCH );
}


//====== aes key =====================================
void cfgAesKeyGet( u8 *pAesKey )
{
    if(pAesKey == NULL )
		return;

    memcpy(pAesKey, _stAppConfig.aes_key, EEP_LEN_CFG_AES_KEY );
}



void cfgAesKeySet(u8 *pAesKey)
{
    if(pAesKey == NULL)
		return;

    if (memcmp(pAesKey, _stAppConfig.aes_key, EEP_LEN_CFG_AES_KEY) == 0)
        return;

    _cfgModify = 1;

    memcpy(_stAppConfig.aes_key, pAesKey, EEP_LEN_CFG_AES_KEY);
}

void cfgAesKeyDef( void )
{
    u8 pKey[] = CONFIG_DEF_AES_KEY;

    cfgAesKeySet( pKey );
}


