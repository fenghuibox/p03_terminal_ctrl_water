
#ifndef __DRI_UART_ZGB_H
#define __DRI_UART_ZGB_H


#include "com_typedef.h"



#define ZGB_UART_HANDLE         M0P_UART0


extern void driUartZgbIrqCBset( irqCB funIrqCB );

extern void driUartZgbInit( irqCB funIrqCB  );









#endif

