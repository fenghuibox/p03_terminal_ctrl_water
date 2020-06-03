/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/



#ifndef ___CFG_AES_H
#define ___CFG_AES_H


#include "com_includes.h"




#define EEP_LEN_CFG_AES_KEY           ( 3 * 4 ) // 12



#define CONFIG_DEF_AES_KEY_ONE  (88)
#define CONFIG_DEF_AES_KEY      {88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88}
#define CONFIG_DEF_AES_SWITCH   (0)





//====== aes switch  =====================================
extern u8 cfgAesSwitchGet( void ); //

extern u8 cfgAesSwitchSet( u8 s );

extern u32 cfgAesSwitchDef( void );





//====== aes key =====================================
extern void cfgAesKeyGet( u8 *pAesKey );


extern void cfgAesKeySet(u8 *pAesKey);

extern void cfgAesKeyDef( void );






#endif

