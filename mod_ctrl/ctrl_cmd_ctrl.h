/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __CTRL_CMD_CTRL_H
#define __CTRL_CMD_CTRL_H


#include "com_typedef.h"







extern void ctrlCmdCtrlClose( void );


extern void ctrlCmdCtrlOpen( void );


extern u8 ctrlCmdCtrlStateIsOpen( void );


extern  void ctrlCmdCtrlInit( void );







#ifdef TEST_MOD_CTRL


extern void testCtrlCmdCtrl( void );


#endif




#endif

