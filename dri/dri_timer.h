
#ifndef __DRI_TIMER_H
#define __DRI_TIMER_H


#include "com_typedef.h"






#define DRI_TIMER_UNIT_MS  (2) 



//extern volatile u32 g32TimerCnt;



u32 driTimerCntGet( void );

void driTimerInit( void );


void driTimerStart( FunTimeIrqCB funIrq );


void driTimerStop( void );


void driTimerLoopIrqCB( void );






#endif

