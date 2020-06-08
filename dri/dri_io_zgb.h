/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __DRI_IO_ZGB_H
#define __DRI_IO_ZGB_H


#include "com_typedef.h"

//---------sleep----------------------------------------------------------

#define DRI_ZIGBEE_TO_SLEEP_KEEP_L_MS (20) // �������ţ��͵�ƽ��Ч������ 10ms ���ϵ͵�ƽ���� ����ģʽ

extern void driZgbSleepH( void );


extern void driZgbSleepL( void );





//---------reset----------------------------------------------------------
#define DRI_ZIGBEE_TO_RESET_KEEP_L_MS (100)

extern void driZgbResetH( void );


extern void driZgbResetL( void );



//---------wakeup----------------------------------------------------------
#define DRI_ZIGBEE_TO_WAKEUP_KEEP_L_MS (20)

extern void driZgbWakeupH( void );

extern void driZgbWakeupL( void );



//---------detect----------------------------------------------------------
#define DRI_ZIGBEE_TO_DETECT_KEEP_L_MS (100)

extern void driZgbDetectH( void );


extern void driZgbDetectL( void );






//---------ACK----------------------------------------------------------
extern u8 driZgbAckGet( void );


//-------------------------------------------------------------------


extern void driIoZgbInit( void );



#endif

