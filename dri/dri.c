

#include "com_typedef.h"

#include "com_includes.h"
#include "dri_includes.h"

#include "dri.h"





//----------------------------------------------------------------

void driInit( void )
{


	driClkInit();

	driFlashEepInit();
	
	driTimerInit();
	
	driUartDebugInit(NULL);

	//driAdcInit();


	

	
}




