/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#if 0

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



//---------------- zigbee allow join  ---------------------------------------

extern void paraZigbeeAllowJoinGet( u8 *pPara );


extern u8 para_zigbee_allow_join_exe( ST_FRAME *pstFrame );



//---------------- zigbee del by mac---------------------------------------

extern u8 para_zigbee_del_by_mac_addr_exe( ST_FRAME *pstFrame );





//---------------- zigbee child info ---------------------------------------

/*
------pNodeBuf----------------------------------
         nodeCnt  startId   getCnt  pNodeMac
------------------------------------------------
  len:    1byte    1byte    1byte   8byte * n 
------------------------------------------------
  value:  1- n     1- n     0- n
------------------------------------------------
返回值: 总的字节数
*/
extern u8 paraZigbeeChildInfoGet( u8 *pPara ); // 


extern u8 para_zigbee_child_info_exe( ST_FRAME *pstFrame );










//---------------- zigbee work state ---------------------------------------
extern u8 paraZigbeeWorkStateGet( void );

extern u8 para_zigbee_work_state_exe( ST_FRAME *pstFrame );




//---------------- zigbee dev info  ---------------------------------------
extern void paraZigbeeInfoGet( ST_ZIGBEE_DEV_INFO_RF *pstInfoRf );

extern u8 para_zigbee_info_exe( ST_FRAME *pstFrame );









#endif



#endif





