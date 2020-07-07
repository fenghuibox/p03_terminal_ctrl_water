/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#ifndef __DEV_VBATT_H
#define __DEV_VBATT_H


#include "com_typedef.h"



#define _BATT_4D5_ADC   (4072)
#define _BATT_4D4_ADC   (3982)
#define _BATT_4D3_ADC   (3892)
#define _BATT_4D2_ADC   (3802)
#define _BATT_4D1_ADC   (3712)
#define _BATT_4_ADC     (3622) // 常态工作
#define _BATT_3D9_ADC   (3529) // 常态工作
#define _BATT_3D8_ADC   (3439) // 常态工作
#define _BATT_3D7_ADC   (3349) // 常态工作
#define _BATT_3D6_ADC   (3259) // 常态工作
#define _BATT_3D55_ADC   (3210) // calc---
#define _BATT_3D5_ADC   (3166)
#define _BATT_3D4_ADC   (3076) // 电量低警告
#define _BATT_3D3_ADC   (2986)
#define _BATT_3D2_ADC   (2895)
#define _BATT_3D1_ADC   (2805)
#define _BATT_3_ADC     (2712) // 低电
#define _BATT_2D9_ADC   (2622)
#define _BATT_2D8_ADC   (2532)
#define _BATT_2D7_ADC   (2442)
#define _BATT_2D6_ADC   (2349)
#define _BATT_2D5_ADC   (2259)
#define _BATT_2D4_ADC   (2169)
#define _BATT_2D3_ADC   (2089)
#define _BATT_2D2_ADC   (1996)
#define _BATT_2D1_ADC   (1881)




extern void devBattStart( void );

extern u32 devVbattValGet( void );


extern void devVbattInit( void );


//extern  void modVbattCB( void );


extern void devVbattPoll( void ); // 100 ms

#endif

