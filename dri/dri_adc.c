 
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
	
    
    ///< 端口方向配置->输出(其它参数与以上（输入）配置参数一致)
    stcGpioCfg.enDir = GpioDirOut;
	
    ///< 端口上下拉配置->下拉
    stcGpioCfg.enPu = GpioPuDisable;
    stcGpioCfg.enPd = GpioPdDisable;//GpioPdEnable;
    
    driAdcEnClose();
    
    ///< GPIO IO LED端口初始化
    Gpio_Init(DRI_ADC_EN_PORT, DRI_ADC_EN_PIN, &stcGpioCfg);
    
}





//============= adc ============================================

#define DRI_ADC_PORT  ( GpioPortA )  //PA06 (AIN6)
#define DRI_ADC_PIN   ( GpioPin6 )
#define DRI_ADC_CH   ( AdcExInputCH6 )



///< ADC 采样端口初始化
static void _AdcPortInit( void )
{    
    Gpio_SetAnalogMode(DRI_ADC_PORT, DRI_ADC_PIN);        //PA06 (AIN6)
}




///< ADC模块 初始化
static void _AdcInit( void )
{
    stc_adc_cfg_t  stcAdcCfg;

    DDL_ZERO_STRUCT(stcAdcCfg);
        
    Bgr_BgrEnable();                                        ///< 开启BGR
    
    ///< ADC 初始化配置
    stcAdcCfg.enAdcMode         = AdcSglMode;               ///<采样模式-单次
    stcAdcCfg.enAdcClkDiv       = AdcMskClkDiv1;            ///<采样分频-1
    stcAdcCfg.enAdcSampCycleSel = AdcMskSampCycle12Clk;     ///<采样周期数-12
    stcAdcCfg.enAdcRefVolSel    = AdcMskRefVolSelInBgr1p5;  ///<参考电压选择-内部1.5V
    stcAdcCfg.enAdcOpBuf        = AdcMskBufDisable;         ///<OP BUF配置-关
    stcAdcCfg.enInRef           = AdcMskInRefEnable;        ///<内部参考电压使能-开
    stcAdcCfg.enAdcAlign        = AdcAlignRight;            ///<转换结果对齐方式-右
    Adc_Init(&stcAdcCfg);
}


///< ADC 单次采样模式 配置
static void _AdcSglCfg( void )
{
#if 0
    ///< 配置单次采样通道
    Adc_CfgSglChannel( DRI_ADC_CH );
    
    ///< 启动单次一直采样
    Adc_SGL_Always_Start(); 
#else

	///< 配置单次采样通道
	Adc_CfgSglChannel( DRI_ADC_CH );

	///< ADC 中断使能
    Adc_EnableIrq();
    EnableNvic(ADC_DAC_IRQn, IrqLevel3, TRUE);
    
    ///< 启动单次转换采样
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



 ///< ADC 中断服务程序
void Adc_IRQHandler(void)
{    
	u32 val;
	
    if(TRUE == Adc_GetIrqStatus(AdcMskIrqSgl))
    {
        Adc_ClrIrqStatus(AdcMskIrqSgl);   ///< 清除中断标志位
        
        
        val = Adc_GetSglResult();   ///< 获取采样值
        
		if( _funAdcCB )
			_funAdcCB( val );
        
        Adc_SGL_Stop();                 ///< ADC 单次转换停止

		
    }
}





void driAdcStart( void )
{	
    ///< 启动单次转换采样
    Adc_SGL_Start(); 
	
}



void driAdcStop( void )
{
    ///< 停止单次转换采样
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


