/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __DRI_IO_CTRL_H
#define __DRI_IO_CTRL_H


#include "com_typedef.h"




//--------- 12V switch ----------------------------------------------------------
extern void driCtrl12VswitchH( void );

extern void driCtrl12VswitchL( void );


//--------- 12V en ----------------------------------------------------------
extern void driCtrl12VenH( void );

extern void driCtrl12VenL( void );


//--------- open or close ----------------------------------------------------------
extern void driCtrlOpen( void );

extern void driCtrlClose( void );

extern void driCtrlFinish( void );


//--------- init ----------------------------------------------------------



extern void driIoCtrlInit( void );



#endif

