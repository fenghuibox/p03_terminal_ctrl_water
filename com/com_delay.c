/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/




#include "com_typedef.h"
#include "com_delay.h"

#include "ddl.h"



//==================================
// start common
void comDelay(u32 a) 
{
	while(a) a--;
}



//==================================

/*
void comDelay1Us(void) 
{
	u8 us = 40; 
	
	while(us--)
		;
}

*/

//#define _comDelay1Us() {; }
void comDelay12Us(u32 us)
{
	//while(us--)
	//	comDelay1Us();

	delay10us( 1 * us );

}

//==================================
void comDelayMs(u32 ms)
{

	//comDelay(ms * 7000); 

	delay1ms( ms );

}


//==================================

void comDelayS(u32 s)
{
	while(s--)
		comDelayMs(1000);
}
//-------------------------------------




//=============================================
//=============================================


#ifdef TEST_COM_DELAY

#include "com_includes.h"

void testDelay( void )
{
	while(1)
	{
		comDelayS(1);
		Gpio_SetIO(GpioPortA, GpioPin2);


		comDelayS(1);
		Gpio_ClrIO(GpioPortA, GpioPin2);

	}
}


#endif

