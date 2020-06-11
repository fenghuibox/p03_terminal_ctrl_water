/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __CTRL_MODE_H
#define __CTRL_MODE_H


#include "com_typedef.h"





typedef enum 
{
	CTRL_MODE_CMD = 0,
	CTRL_MODE_PERIOD,
}EN_CTRL_MODE; // 




extern void ctrlModeSet( EN_CTRL_MODE ctrlMode );


extern u8 ctrlModeIsCmd( void );


extern void ctrlModeInit( void );



#endif

