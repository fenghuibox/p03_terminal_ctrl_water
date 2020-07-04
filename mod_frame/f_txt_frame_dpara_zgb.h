/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#if 1

#ifndef __F_TXT_FRAME_DPARA_ZGB_H
#define __F_TXT_FRAME_DPARA_ZGB_H


#include "com_typedef.h"


#include "f_frame_comm.h"


#include "zgb_cmd.h"






//---------------- reset ---------------------------------------
extern u8 para_zigbee_to_reset_exe( ST_FRAME *pstFrame );



//---------------- def ---------------------------------------
extern u8 para_zigbee_to_def_exe( ST_FRAME *pstFrame );




//---------------- auto net ---------------------------------------
extern u8 paraZigbeeAutoNetGet( void );

extern u8 para_zigbee_auto_net_exe( ST_FRAME *pstFrame );


//---------------- LQI ---------------------------------------

extern u8 paraZigbeeLqiGet( void );

extern u8 para_zigbee_lqi_exe( ST_FRAME *pstFrame );



//---------------- zigbee work state ---------------------------------------
extern u8 paraZigbeeWorkStateGet( void );

extern u8 para_zigbee_state_exe( ST_FRAME *pstFrame );




//---------------- zigbee dev info  ---------------------------------------
extern void paraZigbeeInfoGet( ST_ZIGBEE_DEV_INFO_RF *pstInfoRf );

extern u8 para_zigbee_info_exe( ST_FRAME *pstFrame );









#endif



#endif





