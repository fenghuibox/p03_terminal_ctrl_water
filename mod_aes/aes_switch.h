/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __AES_SWITCH_H
#define __AES_SWITCH_H


#include "com_typedef.h"



#define AES_SWITCH_DEF (0)



extern void aesSwitchSet( u8 onoff );// 0: off



extern u8 aesSwitchIsEqu( u8 sw );

extern u8 aesSwitchGet( void );



extern void aesSwitchDef( void );


extern void aesSwitchInit( void );



#endif

