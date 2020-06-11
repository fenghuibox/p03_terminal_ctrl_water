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

#ifndef __F_TXT_FRAME_DPARA_BASE_H
#define __F_TXT_FRAME_DPARA_BASE_H


#include "com_typedef.h"

#include "f_frame_comm.h"

#include "cfg_base.h"




// ------------- config ver -----------------------------------------
//extern void paraCfgVerSet( u8 *pPara );


extern void paraCfgVerGet( u8 *pPara );


extern u8 para_config_ver_exe( ST_FRAME *pstFrame );






// ------------- def -----------------------------------------

extern u8 para_def_exe( ST_FRAME *pstFrame );








// ------------- aes switch -----------------------------------------

extern u8 paraAesSwitchGet( void );

extern u8 para_aes_switch_exe( ST_FRAME *pstFrame );




// ------------- aes key -----------------------------------------

extern u8 paraAesKeyGet( u8 *pPara );

extern u8 para_aes_key_exe( ST_FRAME *pstFrame );



// ------------- reboot -----------------------------------------

extern u8 para_reboot_exe( ST_FRAME *pstFrame );



// ------------- sleep sec  -----------------------------------------
void paraSleepSecSet( u8 *pPara );


void paraSleepSecGet( u8 *pPara );


u8 para_sleep_sec_exe( ST_FRAME *pstFrame );



// ------------- work sec  -----------------------------------------
void paraWorkSecSet( u8 *pPara );

void paraWorkSecGet( u8 *pPara );

u8 para_work_sec_exe( ST_FRAME *pstFrame );



// ------------- ver -----------------------------------------


extern u8 paraVerGet( void );

extern u8 para_ver_exe( ST_FRAME *pstFrame );



// ------------- dev type -----------------------------------------

// 设备的类型   1：网关	2：路由 3：采集终端  4：控制终端

// 修改为: 1网络设备，2采集设备，3传感器，4摄像头，5控制设备

typedef enum
{
	DEV_TYPE_NOT_DEF   = 0,
	DEV_TYPE_GATEWAY   = 1,
	DEV_TYPE_COLLECTOR = 2, // collector
	
	//DEV_TYPE_ROUTER  = 3,
	DEV_TYPE_SENSOR    = 3,
	
	DEV_TYPE_CAMERA    = 4,
	DEV_TYPE_CTRL      = 5,
}EN_DEV_TYPE;

extern EN_DEV_TYPE paraDevTypeGet( void );





extern u8 para_dev_type_exe( ST_FRAME *pstFrame );


// ------------- Heartbeat -----------------------------------------
extern u8 para_heartbeat_exe( ST_FRAME *pstFrame );



// ------------- battery -----------------------------------------
extern void paraBatteryGet( u8 *pPara );

extern u8 para_battery_exe( ST_FRAME *pstFrame );











#endif

#endif


