/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#include "com_includes.h"

#include "dri_io_ch.h"




#define CH_IO_PORT  ( GpioPortF )
#define CH_IO_PIN   ( GpioPin5 )
#define CH_IO_AF    ( GpioAf0 )





//---------ACK----------------------------------------------------------


u8 driIoChRead( void )
{
	if( Gpio_ReadOutputIO(CH_IO_PORT, CH_IO_PIN) == 0 )
		return 0;

	return 1;
}

static void _ioChInit(void)
{
	stc_gpio_cfg_t stcGpioCfg;
	
	DDL_ZERO_STRUCT(stcGpioCfg);
	
	
	///< �˿ڷ�������
	stcGpioCfg.enDir = GpioDirIn;
	
	///< �˿�����������
	stcGpioCfg.enPu = GpioPuDisable;
	stcGpioCfg.enPd = GpioPdDisable;
	
	
	///< �˿ڳ�ʼ��
	Gpio_Init( CH_IO_PORT, CH_IO_PIN, &stcGpioCfg);

}


//-------------------------------------------------------------------

void driIoChInit( void )
{
	_ioChInit();
	
}




