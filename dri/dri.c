

#include "com_typedef.h"

#include "com_includes.h"
#include "dri_includes.h"

#include "dri.h"





//----------------------------------------------------------------

void driInit( void )
{


	driClkInit();
	
	driTimerInit();
	
	driUartDebugInit(NULL);

	//driAdcInit();


	

	
}




