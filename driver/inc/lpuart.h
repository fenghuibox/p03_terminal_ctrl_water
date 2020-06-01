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
/*****************************************************************************/
/** \file lpuart.h
 **
 ** Headerfile for LPUART functions
 **  
 **
 ** History:
 **   - 2017-05-10   Cathy     First Version
 **
 *****************************************************************************/

#ifndef __LPUART_H__
#define __LPUART_H__
/*****************************************************************************
 * Include files
 *****************************************************************************/
#include "ddl.h"


#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup LPUartGroup Universal Asynchronous Receiver/Transmitter (LPUART)
 **
 ******************************************************************************/
//@{

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/

/******************************************************************************
 * Global type definitions
 ******************************************************************************/
 /**
 ******************************************************************************
 **\brief LPuartͨ��ѡ��
 ******************************************************************************/

/**
 ******************************************************************************
 ** \brief lpuart ��sclkʱ��Դѡ��
 ******************************************************************************/

typedef enum en_lpuart_sclk_sel
{
    LPUartMskPclk   = 0u<<11, ///<pclk
    LPUartMskXtl    = 2u<<11, ///<�ⲿ���پ���
    LPUartMskRcl    = 3u<<11, ///<�ڲ����پ���
} en_lpuart_sclksel_t;

/**
 ******************************************************************************
 ** \brief lpuart���ģʽ��ַ֡/����֡������żУ��
 ******************************************************************************/
typedef enum en_lpuart_mmdorck
{
    LPUartDataOrAddr = 0u, ///<���ģʽʱ��ͨ����дSBUF[8]����֡Ϊ����֡���ַ֡
    LPUartEven       = 0x4u, ///<�Ƕ��ģʽżУ��   
    LPUartOdd        = 0x8u, ///<�Ƕ��ģʽ��У��    
}en_lpuart_mmdorck_t;

/**
 ******************************************************************************
 ** \brief lpuart���ģʽ���ӻ���ַ�͵�ַ��������
 ******************************************************************************/

typedef struct stc_lpuart_multimode
{
    uint8_t             u8SlaveAddr;  ///<�ӻ���ַ
    uint8_t             u8SaddEn;  ///<�Ӽ���ַ����
}stc_lpuart_multimode_t;

/**
 ******************************************************************************
 ** \brief lpuart ���ֹ���ģʽѡ��
 ******************************************************************************/

typedef enum en_lpuart_mode
{
    LPUartMskMode0 = 0x00u, ///<ģʽ0    
    LPUartMskMode1 = 0x40u, ///<ģʽ1
    LPUartMskMode2 = 0x80u, ///<ģʽ2
    LPUartMskMode3 = 0xc0u, ///<ģʽ3
} en_lpuart_mode_t;
/**
 ******************************************************************************
 ** \brief lpuart stop����ѡ��
 ******************************************************************************/

typedef enum en_lpuart_stop
{
    LPUart1bit  = 0x0000u,  ///<1λֹͣλ 
    LPUart1_5bit = 0x4000u, ///<1.5λֹͣλ
    LPUart2bit  = 0x8000u,  ///<2λֹͣλ
} en_lpuart_stop_t;
/**
 ******************************************************************************
 ** \brief lpuart ����ʹ��
 ******************************************************************************/
typedef enum en_lpuart_func
{
    LPUartRenFunc    = 4u,    ///<0-TX; ///<1-��mode0ģʽ����RX&TX ,mode0ģʽ����RX;       
    LPUartDmaRxFunc  = 16u,   ///<DMA���չ���   
    LPUartDmaTxFunc  = 17u,   ///<DMA���͹���
    LPUartRtsFunc    = 18u,   ///<Ӳ����RTS����
    LPUartCtsFunc    = 19u,   ///<Ӳ����CTS����
    LPUartHdFunc     = 22u,   ///<���߰�˫������    
}en_lpuart_func_t;
/**
 ******************************************************************************
 ** \brief lpuart�ж�ʹ�ܿ���
 ******************************************************************************/
typedef enum en_lpuart_irq_sel
{
    LPUartRxIrq  = 0u,    ///<�����ж�ʹ��
    LPUartTxIrq  = 1u,    ///<�����ж�ʹ��        
    LPUartTxEIrq = 8u,    ///<TX���ж�ʹ��
    LPUartPEIrq  = 13u,   ///<��żУ���ж�ʹ��
    LPUartCtsIrq = 20u,   ///<CTS�źŷ�ת�ж�ʹ��    
    LPUartFEIrq  = 21u,   ///<֡�����ж�ʹ�� 
}en_lpuart_irq_sel_t;

/**
 ******************************************************************************
 ** \brief lpuart ״̬��־λ
 ******************************************************************************/
typedef enum en_lpuart_status
{
    LPUartRC    = 0u,  ///<����������ɱ��
    LPUartTC    = 1u,  ///<����������ɱ��
    LPUartFE    = 2u,  ///<֡������
    LPUartTxe   = 3u,  ///<TXbuff�ձ��    
    LPUartPE    = 4u,  ///<��żУ�������
    LPUartCtsIf = 5u,  ///<CTS�жϱ��
    LPUartCts   = 6u,  ///<CTS�źű��
}en_lpuart_status_t;

/**
 ******************************************************************************
 ** \brief lpuart ͨ��������Ƶ����
 ******************************************************************************/
typedef enum en_lpuart_clkdiv
{
    LPUartMsk16Or32Div = 0u,        ///<ģʽ0��Ч��ģʽ1/3Ϊ16��Ƶ��ģʽ2Ϊ32��Ƶ
    LPUartMsk8Or16Div  = 0x200u,    ///<ģʽ0��Ч��ģʽ1/3Ϊ8��Ƶ��ģʽ2Ϊ16��Ƶ
    LPUartMsk4Or8Div   = 0x400u,    ///<ģʽ0��Ч��ģʽ1/3Ϊ4��Ƶ��ģʽ2Ϊ8��Ƶ
}en_lpuart_clkdiv_t;

/**
 ******************************************************************************
 ** \brief lpuart ͨ��Mode1��Mode3�����ʼ������
 ******************************************************************************/
typedef struct stc_lpuart_baud
{
    en_lpuart_sclksel_t  enSclkSel;      ///<����ʱ��Դѡ��
    en_lpuart_clkdiv_t   enSclkDiv;     ///<������Ƶѡ�� 
    uint32_t             u32Sclk;        ///<sclk
    uint32_t             u32Baud;        ///< ������
} stc_lpuart_baud_t;
/**
 ******************************************************************************
 ** \lpuart ��������
 ******************************************************************************/
typedef struct stc_lpuart_cfg
{
    en_lpuart_mode_t       enRunMode;      ///<����ģʽ����
    en_lpuart_mmdorck_t    enMmdorCk;      ///<У��ģʽ
    en_lpuart_stop_t       enStopBit;      ///<ֹͣλ����    
    stc_lpuart_baud_t      stcBaud;        ///<Mode1/3����������                                                        
} stc_lpuart_cfg_t;

// �ܳ�ʼ������
en_result_t LPUart_Init(M0P_LPUART_TypeDef* LPUARTx, stc_lpuart_cfg_t* pstcCfg);

// LPUART ����ģʽʹ��/��ֹ
void LPUart_HdModeEnable(M0P_LPUART_TypeDef* LPUARTx);
void LPUart_HdModeDisable(M0P_LPUART_TypeDef* LPUARTx);


//TB8��������
void LPUart_SetTb8(M0P_LPUART_TypeDef* LPUARTx, boolean_t bTB8Value);

//���ݼĴ���bit8λ��ȡ
boolean_t LPUart_GetRb8(M0P_LPUART_TypeDef* LPUARTx);

//�ж�������ú���ʹ�ܺͽ�ֹ
en_result_t LPUart_EnableIrq(M0P_LPUART_TypeDef* LPUARTx, en_lpuart_irq_sel_t enIrqSel);
en_result_t LPUart_DisableIrq(M0P_LPUART_TypeDef* LPUARTx, en_lpuart_irq_sel_t enIrqSel);

//���⹦��ʹ�ܺͽ�ֹ
en_result_t LPUart_EnableFunc(M0P_LPUART_TypeDef* LPUARTx, en_lpuart_func_t enFunc);
en_result_t LPUart_DisableFunc(M0P_LPUART_TypeDef* LPUARTx, en_lpuart_func_t enFunc);

//״̬λ��ȡ����
boolean_t LPUart_GetStatus(M0P_LPUART_TypeDef* LPUARTx,en_lpuart_status_t enStatus);
//״̬λ�����
en_result_t LPUart_ClrStatus(M0P_LPUART_TypeDef* LPUARTx,en_lpuart_status_t enStatus);
//����״̬�Ĵ�����ȡ
uint8_t LPUart_GetIsr(M0P_LPUART_TypeDef* LPUARTx);
//����״̬�Ĵ������
en_result_t LPUart_ClrIsr(M0P_LPUART_TypeDef* LPUARTx);

//���ݲ�ѯ��ʽ�ķ���
en_result_t LPUart_SendData(M0P_LPUART_TypeDef* LPUARTx, uint8_t u8Data);
//�����жϷ�ʽ�ķ���
en_result_t LPUart_SendDataIt(M0P_LPUART_TypeDef* LPUARTx, uint8_t u8Data);
//���ݽ���
uint8_t LPUart_ReceiveData(M0P_LPUART_TypeDef* LPUARTx);

//LPUARTxͨ���ţ�enClk ʱ��Դѡ��
en_result_t LPUart_SelSclk(M0P_LPUART_TypeDef* LPUARTx, en_lpuart_sclksel_t enSclk);

//LPUARTͨ��������ģʽ����
en_result_t LPUart_SetMultiMode(M0P_LPUART_TypeDef* LPUARTx, stc_lpuart_multimode_t* pstcMultiCfg);

//LPUARTͨ��������ģʽ�ӻ���ַ���ú���
en_result_t LPUart_SetSaddr(M0P_LPUART_TypeDef* LPUARTx,uint8_t u8Addr);

//@} // LPUartGroup

#ifdef __cplusplus
#endif

#endif /* __UART_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/




