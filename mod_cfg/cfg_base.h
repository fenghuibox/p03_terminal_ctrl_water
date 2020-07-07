/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/



#ifndef ___CFG_BASE_H
#define ___CFG_BASE_H


#include "com_includes.h"







 
#define CONFIG_DEF_CFG_VER         (0)


#define CONFIG_MAX_SLEEP_SEC      (60*10) // ��������ʱ�� 10����
#define CONFIG_MIN_SLEEP_SEC      (5)     // ��������ʱ�� 5 ��
#define CONFIG_DEF_SLEEP_SEC      (10)    // Ĭ�ϵ�����ʱ�� 10 ��



#define CONFIG_DEF_WORK_SEC     (60*3) // ����ʱ��  ��λ����     5����





//#define CONFIG_DEF_WORK_STATE   (0)



//#define CONFIG_DEF_SG_CH       (5) // Ĭ��ʹ��4G��IPAD   fenghuiw



//======dev cfg ver =====================================
extern u32 cfgCfgVerGet( void ); //

extern void cfgCfgVerSet( u32 cfgVer );

extern void cfgCfgVerDef( void );



//======dev sleep sec =====================================
extern u32 cfgSleepSecGet( void ); //


extern void cfgSleepSecSet( u32 sec );


extern void cfgSleepSecDef( void );


//======dev work sec =====================================
extern u32 cfgWorkSecGet( void ) ;//


extern void cfgWorkSecSet( u32 sec );


extern void cfgWorkSecDef( void );




#endif




