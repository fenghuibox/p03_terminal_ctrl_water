/******************************************************************************
* Copyright (C) 2017, Huada Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Huada Semiconductor Co.,Ltd ("HDSC").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with HDSC
* components. This software is licensed by HDSC to be adapted only
* for use in systems utilizing HDSC components. HDSC shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. HDSC is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* Disclaimer:
* HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
* WARRANTY OF NONINFRINGEMENT.
* HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
* SAVINGS OR PROFITS,
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
* FROM, THE SOFTWARE.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/
/******************************************************************************/
/** \file adc.h
 **
 ** Header file for AD Converter functions
 ** @link ADC Group Some description @endlink
 **
 **   - 2017-06-28 Alex    First Version
 **
 ******************************************************************************/

#ifndef __ADC_H__
#define __ADC_H__


/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "ddl.h"


/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup AdcGroup AD Converter (ADC)
  **
 ******************************************************************************/
 
//@{

/******************************************************************************
 * Global definitions
 ******************************************************************************/
#define ADC_SCAN_CH0_EN     (0x1u)           /*!< SCANģʽʹ��ADC CH0 */
#define ADC_SCAN_CH1_EN     (0x1u<<1)        /*!< SCANģʽʹ��ADC CH1 */
#define ADC_SCAN_CH2_EN     (0x1u<<2)        /*!< SCANģʽʹ��ADC CH2 */
#define ADC_SCAN_CH3_EN     (0x1u<<3)        /*!< SCANģʽʹ��ADC CH3 */
#define ADC_SCAN_CH4_EN     (0x1u<<4)        /*!< SCANģʽʹ��ADC CH4 */
#define ADC_SCAN_CH5_EN     (0x1u<<5)        /*!< SCANģʽʹ��ADC CH5 */
#define ADC_SCAN_CH6_EN     (0x1u<<6)        /*!< SCANģʽʹ��ADC CH6 */
#define ADC_SCAN_CH7_EN     (0x1u<<7)        /*!< SCANģʽʹ��ADC CH7 */


/******************************************************************************
 ** Global type definitions
 *****************************************************************************/

 /**
 ******************************************************************************
 ** \brief ADCת��ģʽ
 *****************************************************************************/
typedef enum en_adc_mode
{
    AdcSglMode  = 0u,           /*!< ������ͨ������ת��ģʽ */
    AdcScanMode = 1u,           /*!< ������ͨ��˳��/���ɨ��ת��ģʽ*/   
}en_adc_mode_t;

/**
 ******************************************************************************
 ** \brief ADCʱ�ӷ�Ƶѡ��
 *****************************************************************************/
typedef enum en_adc_clk_sel
{
    AdcMskClkDiv1  = 0u<<2,        /*!< PCLK */
    AdcMskClkDiv2  = 1u<<2,        /*!< 1/2 PCLK */
    AdcMskClkDiv4  = 2u<<2,        /*!< 1/4 PCLK */
    AdcMskClkDiv8  = 3u<<2,        /*!< 1/8 PCLK */
} en_adc_clk_div_t;

/**
 ******************************************************************************
 ** \brief ADC�ο���ѹ
 *****************************************************************************/
typedef enum en_adc_ref_vol_sel
{
    AdcMskRefVolSelInBgr1p5 = 0u<<9,        /*!<�ڲ��ο���ѹ1.5V(SPS<=200kHz)*/
    AdcMskRefVolSelInBgr2p5 = 1u<<9,        /*!<�ڲ��ο���ѹ2.5V(avdd>3V,SPS<=200kHz)*/
    AdcMskRefVolSelExtern1  = 2u<<9,        /*!<�ⲿ����(max avdd)   PB01*/
    AdcMskRefVolSelAVDD     = 3u<<9,        /*!<AVDD*/
}en_adc_ref_vol_sel_t;

/**
 ******************************************************************************
 ** \brief ADCת��ͨ��ѡ��
 *****************************************************************************/
typedef enum en_adc_samp_ch_sel
{
    AdcExInputCH0    =  0u,        /*!<ʹ��PA00*/
    AdcExInputCH1    =  1u,        /*!<ʹ��PA01*/
    AdcExInputCH2    =  2u,        /*!<ʹ��PA02*/
    AdcExInputCH3    =  3u,        /*!<ʹ��PA03*/
    AdcExInputCH4    =  4u,        /*!<ʹ��PA04*/
    AdcExInputCH5    =  5u,        /*!<ʹ��PA05*/
    AdcExInputCH6    =  6u,        /*!<ʹ��PA06*/
    AdcExInputCH7    =  7u,        /*!<ʹ��PA07*/
    AdcExInputCH8    =  8u,        /*!<ʹ��PB00*/
    AdcExInputCH9    =  9u,        /*!<ʹ��PB01*/
    AdcExInputCH10   =  10u,       /*!<ʹ��PC00*/
    AdcExInputCH11   =  11u,       /*!<ʹ��PC01*/
    AdcExInputCH12   =  12u,       /*!<ʹ��PC02*/
    AdcExInputCH13   =  13u,       /*!<ʹ��PC03*/
    AdcExInputCH14   =  14u,       /*!<ʹ��PC04*/
    AdcExInputCH15   =  15u,       /*!<ʹ��PC05*/
    AdcExInputCH16   =  16u,       /*!<ʹ��PB02*/
    AdcExInputCH17   =  17u,       /*!<ʹ��PB10*/
    AdcExInputCH18   =  18u,       /*!<ʹ��PB11*/
    AdcExInputCH19   =  19u,       /*!<ʹ��PB12*/
    AdcExInputCH20   =  20u,       /*!<ʹ��PB13*/
    AdcExInputCH21   =  21u,       /*!<ʹ��PB14*/
    AdcExInputCH22   =  22u,       /*!<ʹ��PB15*/
    AdcExInputCH23   =  23u,       /*!<ʹ��PE15*/
    AdcExInputCH24   =  24u,       /*!<ʹ��PE14*/
    AdcExInputCH25   =  25u,       /*!<ʹ��PE13*/

    AdcDacInput      =  26u,       /*!<ʹ��DAC���(����ʹ����������)*/                    
    AdcAVccdiv3Input =  27u,       /*!<ʹ��1/3 AVCC(����ʹ����������)*/
    AdcAiTsInput     =  28u,       /*!<ʹ�������¶ȴ�����BGR_TS(����ʹ����������)*/
    AdcVref1_2Input  =  29u,       /*!<ʹ���ڲ���׼1.2V(����ʹ����������)*/

}en_adc_samp_ch_sel_t;

 /**
 ******************************************************************************
 ** \brief ADC�����źŷŴ�������
 *****************************************************************************/
typedef enum en_adc_op_buf
{
    AdcMskBufEnable  = 1u<<11,          /*!< �򿪷Ŵ���BUF */
    AdcMskBufDisable = 0u,              /*!< �رշŴ���BUF */  
} en_adc_op_buf_t;

/**
 ******************************************************************************
 ** \brief ADC��������ѡ��
 *****************************************************************************/
typedef enum en_adc_samp_cycle_sel
{
    AdcMskSampCycle4Clk  =  0u<<12,        /*!<4������ʱ��*/
    AdcMskSampCycle6Clk  =  1u<<12,        /*!<6������ʱ��*/
    AdcMskSampCycle8Clk  =  2u<<12,        /*!<8������ʱ��*/
    AdcMskSampCycle12Clk =  3u<<12,        /*!<12������ʱ��*/

}en_adc_samp_cycle_sel_t;

 /**
 ******************************************************************************
 ** \brief ADC�ڲ��ο���ѹʹ�ܿ���
 *****************************************************************************/
typedef enum en_adc_in_ref
{
    AdcMskInRefEnable  = 1u<<14,          /*!< �ڲ��ο���ѹʹ�� */
    AdcMskInRefDisable = 0u,              /*!< �ڲ��ο���ѹ�ر� */  
}en_adc_in_ref_t;

/**
 ******************************************************************************
 ** \brief ADC�ܱ�ģ�鷴��Դѡ��
 *****************************************************************************/
typedef enum en_adc_trig_sel
{
    AdcMskTrigTimer0     =  1u<<0,         /*!<ѡ��timer0�ж�Դ���Զ�����ADC����*/
    AdcMskTrigTimer1     =  1u<<1,         /*!<ѡ��timer1�ж�Դ���Զ�����ADC����*/
    AdcMskTrigTimer2     =  1u<<2,         /*!<ѡ��timer2�ж�Դ���Զ�����ADC����*/
    AdcMskTrigTimer3     =  1u<<3,         /*!<ѡ��timer3�ж�Դ���Զ�����ADC����*/
    AdcMskTrigTimer4     =  1u<<4,         /*!<ѡ��timer4�ж�Դ���Զ�����ADC����*/
    AdcMskTrigTimer5     =  1u<<5,         /*!<ѡ��timer5�ж�Դ���Զ�����ADC����*/
    AdcMskTrigTimer6     =  1u<<6,         /*!<ѡ��timer6�ж�Դ���Զ�����ADC����*/
    AdcMskTrigUart0      =  1u<<7,         /*!<ѡ��uart0�ж�Դ���Զ�����ADC����*/
    AdcMskTrigUart1      =  1u<<8,         /*!<ѡ��uart1�ж�Դ���Զ�����ADC����*/
    AdcMskTrigLpuart0    =  1u<<9,         /*!<ѡ��lpuart0�ж�Դ���Զ�����ADC����*/
    AdcMskTrigLpuart1    =  1u<<10,        /*!<ѡ��lpuart1�ж�Դ���Զ�����ADC����*/
    AdcMskTrigVC0        =  1u<<11,        /*!<ѡ��VC0�ж�Դ���Զ�����ADC����*/
    AdcMskTrigVC1        =  1u<<12,        /*!<ѡ��VC1�ж�Դ���Զ�����ADC����*/
    AdcMskTrigRTC        =  1u<<13,        /*!<ѡ��RTC�ж�Դ���Զ�����ADC����*/
    AdcMskTrigPCA        =  1u<<14,        /*!<ѡ��PCA�ж�Դ���Զ�����ADC����*/
    AdcMskTrigSPI0       =  1u<<15,        /*!<ѡ��SPI0�ж�Դ���Զ�����ADC����*/
    AdcMskTrigSPI1       =  1u<<16,        /*!<ѡ��SPI1�ж�Դ���Զ�����ADC����*/
    AdcMskTrigDMA        =  1u<<17,        /*!<ѡ��DMA�ж�Դ���Զ�����ADC����*/
    AdcMskTrigPA03       =  1u<<18,        /*!<ѡ��PA03�ж�Դ���Զ�����ADC����*/
    AdcMskTrigPB03       =  1u<<19,        /*!<ѡ��PB03�ж�Դ���Զ�����ADC����*/
    AdcMskTrigPC03       =  1u<<20,        /*!<ѡ��PC03�ж�Դ���Զ�����ADC����*/
    AdcMskTrigPD03       =  1u<<21,        /*!<ѡ��PD03�ж�Դ���Զ�����ADC����*/
    AdcMskTrigPA07       =  1u<<22,        /*!<ѡ��PA07�ж�Դ���Զ�����ADC����*/
    AdcMskTrigPB07       =  1u<<23,        /*!<ѡ��PB07�ж�Դ���Զ�����ADC����*/
    AdcMskTrigPC07       =  1u<<24,        /*!<ѡ��PC07�ж�Դ���Զ�����ADC����*/
    AdcMskTrigPD07       =  1u<<25,        /*!<ѡ��PD07�ж�Դ���Զ�����ADC����*/
    AdcMskTrigPA11       =  1u<<26,        /*!<ѡ��PA11�ж�Դ���Զ�����ADC����*/
    AdcMskTrigPB11       =  1u<<27,        /*!<ѡ��PB11�ж�Դ���Զ�����ADC����*/
    AdcMskTrigPC11       =  1u<<28,        /*!<ѡ��PC11�ж�Դ���Զ�����ADC����*/
    AdcMskTrigPA15       =  1u<<29,        /*!<ѡ��PA15�ж�Դ���Զ�����ADC����*/
    AdcMskTrigPB15       =  1u<<30,        /*!<ѡ��PB15�ж�Դ���Զ�����ADC����*/
    AdcMskTrigPC15       =  1u<<31,        /*!<ѡ��PC15�ж�Դ���Զ�����ADC����*/
}en_adc_trig_sel_t;

/**
 ******************************************************************************
 ** \brief ADC�ⲿ����Դ�Ĵ���ѡ��
 *****************************************************************************/
typedef enum en_adc_ext_trig_sel
{
    AdcExtTrig0     =  0u,         /*!<���μ�˳��ɨ��ת�� �ⲿ����Դѡ��Ĵ���*/
    AdcExtTrig1     =  1u,         /*!<���ɨ��ת�� �ⲿ����Դѡ��Ĵ���*/
}en_adc_ext_trig_sel_t;

/**
 ******************************************************************************
 ** \brief ADC˳��ת��ͨ��
 *****************************************************************************/
typedef enum en_adc_sqr_chmux
{
    AdcSQRCH0MUX     =  0u,         /*!<˳��ɨ��ģʽת��ͨ��0*/
    AdcSQRCH1MUX     =  1u,         /*!<˳��ɨ��ģʽת��ͨ��1*/
    AdcSQRCH2MUX     =  2u,         /*!<˳��ɨ��ģʽת��ͨ��2*/
    AdcSQRCH3MUX     =  3u,         /*!<˳��ɨ��ģʽת��ͨ��3*/
    AdcSQRCH4MUX     =  4u,         /*!<˳��ɨ��ģʽת��ͨ��4*/
    AdcSQRCH5MUX     =  5u,         /*!<˳��ɨ��ģʽת��ͨ��5*/
    AdcSQRCH6MUX     =  6u,         /*!<˳��ɨ��ģʽת��ͨ��6*/
    AdcSQRCH7MUX     =  7u,         /*!<˳��ɨ��ģʽת��ͨ��7*/
    AdcSQRCH8MUX     =  8u,         /*!<˳��ɨ��ģʽת��ͨ��8*/
    AdcSQRCH9MUX     =  9u,         /*!<˳��ɨ��ģʽת��ͨ��9*/
    AdcSQRCH10MUX    =  10u,        /*!<˳��ɨ��ģʽת��ͨ��10*/
    AdcSQRCH11MUX    =  11u,        /*!<˳��ɨ��ģʽת��ͨ��11*/
    AdcSQRCH12MUX    =  12u,        /*!<˳��ɨ��ģʽת��ͨ��12*/
    AdcSQRCH13MUX    =  13u,        /*!<˳��ɨ��ģʽת��ͨ��13*/
    AdcSQRCH14MUX    =  14u,        /*!<˳��ɨ��ģʽת��ͨ��14*/
    AdcSQRCH15MUX    =  15u,        /*!<˳��ɨ��ģʽת��ͨ��15*/
}en_adc_sqr_chmux_t;

/**
 ******************************************************************************
 ** \brief ADC���ת��ͨ��
 *****************************************************************************/
typedef enum en_adc_jqr_chmux
{
    AdcJQRCH0MUX     =  0u,         /*!<ת��ͨ��0*/
    AdcJQRCH1MUX     =  1u,         /*!<ת��ͨ��1*/
    AdcJQRCH2MUX     =  2u,         /*!<ת��ͨ��2*/
    AdcJQRCH3MUX     =  3u,         /*!<ת��ͨ��3*/
}en_adc_jqr_chmux_t;
/**
 ******************************************************************************
 ** \brief ADC������뷽ʽ
 *****************************************************************************/
typedef enum en_adc_align
{
     AdcAlignRight  = 0u,
     AdcAlignLeft   = 1u,
}en_adc_align_t;

/**
 ******************************************************************************
 ** \brief ADCת������Զ��ۼӹ���
 *****************************************************************************/
typedef enum en_adc_result_acc
{
     AdcResultAccEnable  = 1u,
     AdcResultAccDisable = 0u,
}en_adc_result_acc_t;

/**
 ******************************************************************************
 ** \brief ADC�ж����Ͷ���
 *****************************************************************************/
typedef enum en_adc_irq_type
{
    AdcMskIrqJqr =  1u<<5,        /*!<ADC���ɨ��ת�����*/
    AdcMskIrqSqr =  1u<<4,        /*!<ADC˳��ɨ��ת�����*/
    AdcMskIrqReg =  1u<<3,        /*!<ADCת������Ƚ�������*/
    AdcMskIrqHt  =  1u<<2,        /*!<ADCת���������HT*/
    AdcMskIrqLt  =  1u<<1,        /*!<ADCת���������LT*/
    AdcMskIrqSgl =  1u<<0,        /*!<ADC����ת�����*/

}en_adc_irq_type_t;


/******************************************************************************
 ** Extern type definitions ('typedef')
 ******************************************************************************/

/**
 ******************************************************************************
 ** \brief  ADC��ʼ�����ýṹ��
 *****************************************************************************/
typedef struct stc_adc_cfg
{
    en_adc_mode_t           enAdcMode;                  /*! ADCת��ģʽ*/
    
    en_adc_clk_div_t        enAdcClkDiv;                /*! ADCʱ��ѡ��*/
    en_adc_samp_cycle_sel_t enAdcSampCycleSel;          /*! ADC��������ѡ��*/
    en_adc_ref_vol_sel_t    enAdcRefVolSel;             /*! ADC�ο���ѹѡ��*/
    en_adc_op_buf_t         enAdcOpBuf;                 /*! ADC�����źŷŴ�������ʹ��*/
    en_adc_in_ref_t         enInRef;                    /*! ADC�ڲ��ο���ѹʹ��*/
    
    en_adc_align_t          enAdcAlign;                 /*! ADCת������������*/
}stc_adc_cfg_t;


/**
 ******************************************************************************
 ** \brief  ADC˳��ɨ��ģʽ���ýṹ��
 *****************************************************************************/
typedef struct stc_adc_sqr_cfg
{
    uint8_t                 u8SqrCnt;                   /*! ADC˳��ɨ��ת������*/
    en_adc_result_acc_t     enResultAcc;                /*! ADCת������Զ��ۼӹ���*/
    boolean_t               bSqrDmaTrig;                /*! ADC˳��ɨ��ת�����DMA����ʹ��*/
}stc_adc_sqr_cfg_t;

/**
 ******************************************************************************
 ** \brief  ADC���ɨ��ģʽ���ýṹ��
 *****************************************************************************/
typedef struct stc_adc_jqr_cfg
{
    uint8_t                 u8JqrCnt;                   /*! ADC˳��ɨ��ת������*/
    boolean_t               bJqrDmaTrig;                /*! ADC���ɨ��ת�����DMA����ʹ��*/    
}stc_adc_jqr_cfg_t;


/**
 ******************************************************************************
 ** \brief  ADC�ȽϹ������ýṹ��
 *****************************************************************************/
typedef struct stc_adc_threshold_cfg
{
    boolean_t bAdcRegCmp ;                  /*!ADC����ʹ��*/ 
    boolean_t bAdcHtCmp ;                   /*!ADC�ϳ�������ʹ��*/ 
    boolean_t bAdcLtCmp ;                   /*!ADC�³�������ʹ��*/
    
    uint32_t u32AdcHighThd;                 /*!ADC�Ƚ�����ֵ*/
    uint32_t u32AdcLowThd;                  /*!ADC�Ƚ�����ֵ*/ 
    
    en_adc_samp_ch_sel_t    enSampChSel;    /*!ADC����ͨ��ѡ��*/
    
}stc_adc_threshold_cfg_t;


/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
//ADC ��ʼ��
en_result_t Adc_Init(stc_adc_cfg_t* pstcAdcCfg);

//ADC �ж�ʹ��
void Adc_EnableIrq(void);
//ADC �жϽ�ֹ
void Adc_DisableIrq(void);

//ADC �ж�/�������״̬��ȡ
boolean_t Adc_GetIrqStatus(en_adc_irq_type_t enAdcIrq);
//ADC �ж�/�������״̬���
void Adc_ClrIrqStatus(en_adc_irq_type_t enAdcIrq);

//ADC ʹ��
void Adc_Enable(void);
//ADC ��ֹ
void Adc_Disable(void);

//ADC ˳��ɨ��ģʽ����
en_result_t Adc_SqrModeCfg(stc_adc_sqr_cfg_t* pstcAdcSqrCfg);
//ADC ���ɨ��ģʽ����
en_result_t Adc_JqrModeCfg(stc_adc_jqr_cfg_t* pstcAdcJqrCfg);

//ADC Sgl ����ת��ģʽͨ��ѡ������ 
en_result_t Adc_CfgSglChannel( en_adc_samp_ch_sel_t enstcAdcSampCh);
//ADC SQR ˳��ɨ��ת��ģʽͨ��ѡ������ 
en_result_t Adc_CfgSqrChannel(en_adc_sqr_chmux_t enstcAdcSqrChMux, en_adc_samp_ch_sel_t enstcAdcSampCh);
//ADC JQR ���ɨ��ת��ģʽͨ��ѡ������ 
en_result_t Adc_CfgJqrChannel(en_adc_jqr_chmux_t enstcAdcJqrChMux, en_adc_samp_ch_sel_t enstcAdcSampCh);

///<ADC ����ת���ⲿ����Դ����
void Adc_SglExtTrigCfg(en_adc_trig_sel_t enAdcTrigSel, boolean_t bValue);
///<ADC ˳��ɨ��ת���ⲿ����Դ����
void Adc_SqrExtTrigCfg(en_adc_trig_sel_t enAdcTrigSel, boolean_t bValue);
///<ADC ���ɨ��ת���ⲿ����Դ����
void Adc_JqrExtTrigCfg(en_adc_trig_sel_t enAdcTrigSel, boolean_t bValue);

//ADC ��ֵ�ȽϹ�������
void Adc_ThresholdCfg(stc_adc_threshold_cfg_t* pstcAdcThrCfg);

//ADC ����ת��ģʽ����
void Adc_SGL_Start(void);
//ADC ����ת��ģʽֹͣ
void Adc_SGL_Stop(void);

//ADC ����ת��ģʽһֱת��ģʽ����
void Adc_SGL_Always_Start(void);
//ADC ����ת��ģʽһֱת��ģʽֹͣ
void Adc_SGL_Always_Stop(void);

//ADC ˳��ɨ��ת��ģʽ����
void Adc_SQR_Start(void);
//ADC ˳��ɨ��ת��ģʽֹͣ
void Adc_SQR_Stop(void);

//ADC ���ɨ��ת��ģʽ����
void Adc_JQR_Start(void);
//ADC ���ɨ��ת��ģʽֹͣ
void Adc_JQR_Stop(void);

//��ȡ����ת������ֵ
uint32_t Adc_GetSglResult(void);
//��ȡ˳��ɨ�����ֵ
uint32_t Adc_GetSqrResult(en_adc_sqr_chmux_t enstcAdcSqrChMux);
//��ȡ���ɨ�����ֵ
uint32_t Adc_GetJqrResult(en_adc_jqr_chmux_t enstcAdcJqrChMux);

//��ȡ�ۼӲ���ֵ
uint32_t Adc_GetAccResult(void);
//clear ADC �ۼӼĴ���������
void Adc_ClrAccResult(void);

//@}
#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */
/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/

