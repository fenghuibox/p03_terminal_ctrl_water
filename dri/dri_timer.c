

#include "com_includes.h"





//#define DRI_TIMER_ID     TIM0



volatile u32         g32TimerCnt;

static FunTimeIrqCB  _funIrq;
static u8            _isCallIrqFun;


/*******************************************************************************
 ******************************************************************************/





#define TEST_PORT  (GpioPortA)
#define TEST_PIN   (GpioPin2)






u32 driTimerCntGet( void )
{
	return g32TimerCnt;
}



/*******************************************************************************
 * BT1中断服务函数
 ******************************************************************************/
static void _driTimerIntCB(void)
{
    if( TRUE == Bt_GetIntFlag(TIM0, BtUevIrq) )
    {
		g32TimerCnt++;
		
		_isCallIrqFun = 1;

		#ifdef TEST_DRI_TIMER

			if( (g32TimerCnt&1) == 0 )
				Gpio_SetIO(TEST_PORT, TEST_PIN);
			else
				Gpio_ClrIO(TEST_PORT, TEST_PIN);

			//Gpio_ToggleIO( TEST_PORT, TEST_PIN );
		
		#endif

		Bt_ClearIntFlag( TIM0, BtUevIrq );
    }

}



void Tim0_IRQHandler(void)
{
	_driTimerIntCB();
}


void driTimerStart( FunTimeIrqCB funIrq )
{	
	_funIrq = funIrq;
	
	Bt_M0_Run( TIM0 );
}





void driTimerStop( void )
{
    Bt_M0_Stop( TIM0 );
}





void driTimerLoopIrqCB( void )
{
	if( _isCallIrqFun )
	{
		if(_funIrq)
		{
			_funIrq();
		}
		
		_isCallIrqFun = 0;
	}
}






/*******************************************************************************
 * BT定时功能测试 （重载模式）
 ******************************************************************************/
void driTimerInit(void)
{
	#define _48M_2MS_TIMER_LOAD_VAL	 (0xE890)
	#define _2MS_TIMER_LOAD_VAL      (_48M_2MS_TIMER_LOAD_VAL)
	
    u16                  u16ArrValue;
    u16                  u16CntValue;
    stc_bt_mode0_cfg_t   stcBtBaseCfg;
	

    //结构体初始化清零
    DDL_ZERO_STRUCT( stcBtBaseCfg );
    
    stcBtBaseCfg.enWorkMode = BtWorkMode0;                  //定时器模式
    stcBtBaseCfg.enCT       = BtTimer;                      //定时器功能，计数时钟为内部PCLK
    stcBtBaseCfg.enPRS      = BtPCLKDiv16;                  //PCLK/16
    stcBtBaseCfg.enCntMode  = Bt16bitArrMode;               //自动重载16位计数器/定时器
    stcBtBaseCfg.bEnTog     = FALSE;
    stcBtBaseCfg.bEnGate    = FALSE;
    stcBtBaseCfg.enGateP    = BtGatePositive;
    
    //stcBtBaseCfg.pfnTim0Cb  = _driTimerIntCB;//Tim0Int;   //中断函数入口
    
    Bt_Mode0_Init(TIM0, &stcBtBaseCfg);                     //TIM0 的模式0功能初始化
    
    u16ArrValue = _2MS_TIMER_LOAD_VAL;
    
    Bt_M0_ARRSet(TIM0, u16ArrValue);                        //设置重载值(周期 = 0x10000 - ARR)
    
    u16CntValue = _2MS_TIMER_LOAD_VAL;
    
    Bt_M0_Cnt16Set(TIM0, u16CntValue);                      //设置计数初值
    
    Bt_ClearIntFlag(TIM0,BtUevIrq);                         //清中断标志   
    Bt_Mode0_EnableIrq(TIM0);                               //使能TIM0中断(模式0时只有一个中断)
    EnableNvic(TIM0_IRQn, IrqLevel3, TRUE);                 //TIM0中断使能





	//Bt_M0_Run(TIM0);										//TIM0 运行。

	
	_isCallIrqFun = 0;

	g32TimerCnt  = 0;

	_funIrq      = NULL; 


    
}





//----------sleep and wakeup---------------------------------------------------------

void driTimerToSleep( void )
{
	 Bt_M0_Stop( TIM0 );                      // 1:  stop timer
	 EnableNvic(TIM0_IRQn, IrqLevel3, FALSE); // 2: close irq	
	                                          // 3: close clk	
}

void driTimerOnWakeup( void )
{
	                                          // 1: open clk
	 EnableNvic(TIM0_IRQn, IrqLevel3, TRUE); // 2: open irq	 
	Bt_M0_Run( TIM0 );                        // 3: start timer

	
}




#if 0

void Tim3_IRQHandler(void)
{
    static uint8_t i;
    
    //Timer3 模式0 计时溢出中断
    if(TRUE == Tim3_GetIntFlag(Tim3UevIrq))
    {
        if(0 == i)
        {
            Gpio_WriteOutputIO(STK_LED_PORT, STK_LED_PIN, TRUE);  //LED翻转
            i++;
        }
        else
        {
            Gpio_WriteOutputIO(STK_LED_PORT, STK_LED_PIN, FALSE);  //LED翻转
            i = 0;
        }
        
        Tim3_ClearIntFlag(Tim3UevIrq);  //Timer3模式0 中断标志清除
    }
}


//Timer3 配置
void App_Timer3Cfg(uint16_t u16Period)
{
    uint16_t                    u16ArrValue;
    uint16_t                    u16CntValue;
    stc_tim3_mode0_cfg_t     stcTim3BaseCfg;
    
    //结构体初始化清零
    DDL_ZERO_STRUCT(stcTim3BaseCfg);
    
    Sysctrl_SetPeripheralGate(SysctrlPeripheralTim3, TRUE); //Base Timer外设时钟使能
    
    stcTim3BaseCfg.enWorkMode = Tim3WorkMode0;              //定时器模式
    stcTim3BaseCfg.enCT       = Tim3Timer;                  //定时器功能，计数时钟为内部PCLK
    stcTim3BaseCfg.enPRS      = Tim3PCLKDiv16;              //PCLK/16
    stcTim3BaseCfg.enCntMode  = Tim316bitArrMode;           //自动重载16位计数器/定时器
    stcTim3BaseCfg.bEnTog     = FALSE;
    stcTim3BaseCfg.bEnGate    = FALSE;
    stcTim3BaseCfg.enGateP    = Tim3GatePositive;
    
    Tim3_Mode0_Init(&stcTim3BaseCfg);                       //TIM3 的模式0功能初始化
        
    u16ArrValue = 0x10000 - u16Period ;
    
    Tim3_M0_ARRSet(u16ArrValue);                            //设置重载值(ARR = 0x10000 - 周期)
    
    u16CntValue = 0x10000 - u16Period;
    
    Tim3_M0_Cnt16Set(u16CntValue);                          //设置计数初值
    
    Tim3_ClearIntFlag(Tim3UevIrq);                          //清中断标志
    Tim3_Mode0_EnableIrq();                                 //使能TIM3中断(模式0时只有一个中断)
    EnableNvic(TIM3_IRQn, IrqLevel3, TRUE);                 //TIM3 开中断 
}


#endif


