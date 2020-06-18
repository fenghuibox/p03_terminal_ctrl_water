
#ifndef __DRI_H
#define __DRI_H


#include "com_typedef.h"



extern void driSoftReset( void );


extern void driInit( void );


//----------sleep and wakeup---------------------------------------------------------

void driToSleep( void );
void driOnWakeup( void );




#endif

