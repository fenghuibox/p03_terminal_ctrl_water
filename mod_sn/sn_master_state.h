/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __SN_MASTER_STATE_H
#define __SN_MASTER_STATE_H


#include "com_typedef.h"


typedef enum
{
	MASTER_STATE_NOT_DEF = 0,
	MASTER_STATE_OK  = 1,
	MASTER_STATE_NG = 2,
}EN_MASTER_STATE;




extern void modMasterStateSet( EN_MASTER_STATE s );

extern EN_MASTER_STATE modMasterStateGet( void );



extern void modMasterStatePoll( void );



extern void snMasterStateInit( void );



#endif

