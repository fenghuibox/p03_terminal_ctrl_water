

#include "com_typedef.h"

#include "com_includes.h"
#include "dri_includes.h"

#include "dri.h"








void driSoftReset( void )
{
	NVIC_SystemReset();
}


//----------------------------------------------------------------

void driInit( void )
{
	driClkInit();

	driFlashEepInit();
	
	driTimerInit();
	
	driUartDebugInit(NULL);
	
	driUartZgbInit(NULL);

	
	driIoZgbInit();

	driAdcInit();

	driIoChInit();
	
	driIoCtrlInit();

	driIoLedInit();
	
	driRtcInit();

	

	
}




