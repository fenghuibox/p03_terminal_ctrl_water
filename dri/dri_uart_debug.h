
#ifndef __DRI_UART_DEBUG_H
#define __DRI_UART_DEBUG_H


#include "com_typedef.h"



#define DBG_UART_HANDLE         M0P_LPUART0


extern void driUartDebugIrqCBset( irqCB funIrqCB );

extern void driUartDebugInit( irqCB funIrqCB  );




//----------sleep and wakeup---------------------------------------------------------

void driUartDbgToSleep( void );


void driUartDbgOnWakeup( void );





#endif

