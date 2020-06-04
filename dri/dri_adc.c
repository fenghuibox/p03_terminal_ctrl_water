 
#include "com_typedef.h"
 
#include "com_includes.h"
 
//=========== adc en ==============================================


#define DRI_ADC_EN_PORT  ( GpioPortA )
#define DRI_ADC_EN_PIN   ( GpioPin5 )




void driAdcEnOpen( void )
{
	Gpio_SetIO(DRI_ADC_EN_PORT, DRI_ADC_EN_PIN);
}



void driAdcEnClose( void )
{
	Gpio_ClrIO(DRI_ADC_EN_PORT, DRI_ADC_EN_PIN);
}




static void _driAdcEnInit(void)
{
    stc_gpio_cfg_t stcGpioCfg;

	DDL_ZERO_STRUCT(stcGpioCfg);
	
    
    ///< �˿ڷ�������->���(�������������ϣ����룩���ò���һ��)
    stcGpioCfg.enDir = GpioDirOut;
	
    ///< �˿�����������->����
    stcGpioCfg.enPu = GpioPuDisable;
    stcGpioCfg.enPd = GpioPdDisable;//GpioPdEnable;
    
    driAdcEnClose();
    
    ///< GPIO IO LED�˿ڳ�ʼ��
    Gpio_Init(DRI_ADC_EN_PORT, DRI_ADC_EN_PIN, &stcGpioCfg);
    
}





//============= adc ============================================

#define DRI_ADC_PORT  ( GpioPortA )  //PA06 (AIN6)
#define DRI_ADC_PIN   ( GpioPin6 )
#define DRI_ADC_CH   ( AdcExInputCH6 )



///< ADC �����˿ڳ�ʼ��
static void _AdcPortInit( void )
{    
    Gpio_SetAnalogMode(DRI_ADC_PORT, DRI_ADC_PIN);        //PA06 (AIN6)
}




///< ADCģ�� ��ʼ��
static void _AdcInit( void )
{
    stc_adc_cfg_t  stcAdcCfg;

    DDL_ZERO_STRUCT(stcAdcCfg);
        
    Bgr_BgrEnable();                                        ///< ����BGR
    
    ///< ADC ��ʼ������
    stcAdcCfg.enAdcMode         = AdcSglMode;               ///<����ģʽ-����
    stcAdcCfg.enAdcClkDiv       = AdcMskClkDiv1;            ///<������Ƶ-1
    stcAdcCfg.enAdcSampCycleSel = AdcMskSampCycle12Clk;     ///<����������-12
    stcAdcCfg.enAdcRefVolSel    = AdcMskRefVolSelInBgr1p5;  ///<�ο���ѹѡ��-�ڲ�1.5V
    stcAdcCfg.enAdcOpBuf        = AdcMskBufDisable;         ///<OP BUF����-��
    stcAdcCfg.enInRef           = AdcMskInRefEnable;        ///<�ڲ��ο���ѹʹ��-��
    stcAdcCfg.enAdcAlign        = AdcAlignRight;            ///<ת��������뷽ʽ-��
    Adc_Init(&stcAdcCfg);
}


///< ADC ���β���ģʽ ����
static void _AdcSglCfg( void )
{
#if 0
    ///< ���õ��β���ͨ��
    Adc_CfgSglChannel( DRI_ADC_CH );
    
    ///< ��������һֱ����
    Adc_SGL_Always_Start(); 
#else

	///< ���õ��β���ͨ��
	Adc_CfgSglChannel( DRI_ADC_CH );

	///< ADC �ж�ʹ��
    Adc_EnableIrq();
    EnableNvic(ADC_DAC_IRQn, IrqLevel3, TRUE);
    
    ///< ��������ת������
    //Adc_SGL_Start(); 

#endif
}



 static void _driAdcInit(void)
 {
	 _AdcPortInit();
	 _AdcInit();
	 _AdcSglCfg();
 }


static FunAdcCB _funAdcCB;



 ///< ADC �жϷ������
void Adc_IRQHandler(void)
{    
	u32 val;
	
    if(TRUE == Adc_GetIrqStatus(AdcMskIrqSgl))
    {
        Adc_ClrIrqStatus(AdcMskIrqSgl);   ///< ����жϱ�־λ
        
        
        val = Adc_GetSglResult();   ///< ��ȡ����ֵ
        
		if( _funAdcCB )
			_funAdcCB( val );
        
        Adc_SGL_Stop();                 ///< ADC ����ת��ֹͣ

		
    }
}





void driAdcStart( void )
{	
    ///< ��������ת������
    Adc_SGL_Start(); 
	
}



void driAdcStop( void )
{
    ///< ֹͣ����ת������
    Adc_SGL_Stop(); 
}




void driAdcInit( void )
{
	_driAdcEnInit();

	_driAdcInit();

	_funAdcCB = NULL;
	
}

void driAdcFunSet( FunAdcCB  fun )
{
	_funAdcCB = fun;
}


