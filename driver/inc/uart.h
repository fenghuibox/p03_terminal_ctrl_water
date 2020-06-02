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
/** \file uart.h
 **
 ** Headerfile for UART functions
 **  
 **
 ** History:
 **   - 2017-05-10   Cathy     First Version
 **
 *****************************************************************************/

#ifndef __UART_H__
#define __UART_H__
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
 ** \defgroup UartGroup Universal Asynchronous Receiver/Transmitter (UART)
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
 **\brief uartͨ��ѡ��
 ******************************************************************************/

/**
 ******************************************************************************
 ** \brief uart���ģʽ��ַ֡/����֡������żУ��
 ******************************************************************************/
typedef enum en_uart_mmdorck
{
    UartMskDataOrAddr = 0u,     ///<���ģʽʱ��ͨ����дSBUF[8]����֡Ϊ����֡���ַ֡
    UartMskEven       = 0x4u,   ///<�Ƕ��ģʽżУ��   
    UartMskOdd        = 0x8u,   ///<�Ƕ��ģʽ��У��    
}en_uart_mmdorck_t;

/**
 ******************************************************************************
 ** \brief uart���ģʽ���ӻ���ַ�͵�ַ��������
 ******************************************************************************/
typedef struct stc_uart_multimode
{
    uint8_t             u8SlaveAddr;    ///<�ӻ���ַ
    uint8_t             u8SaddEn;       ///<�Ӽ���ַ����
}stc_uart_multimode_t;

/**
 ******************************************************************************
 ** \brief uart ���ֹ���ģʽѡ��
 ******************************************************************************/

typedef enum en_uart_mode
{
    UartMskMode0 = 0x00u, ///<ģʽ0    
    UartMskMode1 = 0x40u, ///<ģʽ1
    UartMskMode2 = 0x80u, ///<ģʽ2
    UartMskMode3 = 0xc0u, ///<ģʽ3
} en_uart_mode_t;
/**
 ******************************************************************************
 ** \brief uart stop����ѡ��
 ******************************************************************************/

typedef enum en_uart_stop
{
    UartMsk1bit   = 0x0000u, ///<1λֹͣλ 
    UartMsk1_5bit = 0x4000u, ///<1.5λֹͣλ
    UartMsk2bit   = 0x8000u, ///<2λֹͣλ
} en_uart_stop_t;
/**
 ******************************************************************************
 ** \brief uart ����ʹ��
 ******************************************************************************/
typedef enum en_uart_func
{
    UartRenFunc    = 4u,    ///<0-TX; ///<1-��mode0ģʽ����RX&TX ,mode0ģʽ����RX;       
    UartDmaRxFunc  = 16u,   ///<DMA���չ���   
    UartDmaTxFunc  = 17u,   ///<DMA���͹���
    UartRtsFunc    = 18u,   ///<Ӳ����RTS����
    UartCtsFunc    = 19u,   ///<Ӳ����CTS����
    UartHdFunc     = 22u,   ///<���߰�˫������    
}en_uart_func_t;
/**
 ******************************************************************************
 ** \brief uart�ж�ʹ�ܿ���
 ******************************************************************************/
typedef enum en_uart_irq_sel
{
    UartRxIrq  = 0u,    ///<�����ж�ʹ��
    UartTxIrq  = 1u,    ///<�����ж�ʹ��        
    UartTxEIrq = 8u,    ///<TX���ж�ʹ��
    UartPEIrq  = 13u,   ///<��żУ���ж�ʹ��
    UartCtsIrq = 20u,   ///<CTS�źŷ�ת�ж�ʹ��    
    UartFEIrq  = 21u,   ///<֡�����ж�ʹ�� 
}en_uart_irq_sel_t;

/**
 ******************************************************************************
 ** \brief uart ״̬��־λ
 ******************************************************************************/
typedef enum en_uart_status
{
    UartRC    = 0u,  ///<����������ɱ��
    UartTC    = 1u,  ///<����������ɱ��
    UartFE    = 2u,  ///<֡������
    UartTxe   = 3u,  ///<TXbuff�ձ��    
    UartPE    = 4u,  ///<��żУ�������
    UartCtsIf = 5u,  ///<CTS�жϱ��
    UartCts   = 6u,  ///<CTS�źű��
}en_uart_status_t;

/**
 ******************************************************************************
 ** \brief uart ͨ��������Ƶ����
 ******************************************************************************/
typedef enum en_uart_clkdiv
{
    UartMsk16Or32Div = 0u,      ///<ģʽ0��Ч��ģʽ1/3Ϊ16��Ƶ��ģʽ2Ϊ32��Ƶ
    UartMsk8Or16Div  = 0x200u,  ///<ģʽ0��Ч��ģʽ1/3Ϊ8��Ƶ��ģʽ2Ϊ16��Ƶ
}en_uart_clkdiv_t;
/**
 ******************************************************************************
 ** \brief uart ͨ��Mode1��Mode3�����ʼ������
 ******************************************************************************/
typedef struct stc_uart_baud
{
    en_uart_clkdiv_t     enClkDiv;      ///<������Ƶ
    uint32_t             u32Pclk;       ///<pclk
    uint32_t             u32Baud;       ///<������
} stc_uart_baud_t;
/**
 ******************************************************************************
 ** \uart ��������
 ******************************************************************************/

typedef struct stc_uart_cfg
{
    en_uart_mode_t       enRunMode;     ///<����ģʽ����
    en_uart_mmdorck_t    enMmdorCk;     ///<У��ģʽ
    en_uart_stop_t       enStopBit;     ///<ֹͣλ����
    stc_uart_baud_t      stcBaud;       ///<Mode1/3����������
} stc_uart_cfg_t;

//UART��ʼ��
en_result_t Uart_Init(M0P_UART_TypeDef* UARTx, stc_uart_cfg_t* pstcCfg);

///< UART ����ģʽʹ��/��ֹ
void Uart_HdModeEnable(M0P_UART_TypeDef* UARTx);
void Uart_HdModeDisable(M0P_UART_TypeDef* UARTx);

//UARTģ����ģʽ���ú���
en_result_t Uart_SetMultiMode(M0P_UART_TypeDef* UARTx,stc_uart_multimode_t* pstcMultiCfg);

//TB8��������
void Uart_SetTb8(M0P_UART_TypeDef* UARTx, boolean_t bTB8Value);
//RB8���ݻ�ȡ
boolean_t Uart_GetRb8(M0P_UART_TypeDef* UARTx);

//�ж�������ú���
en_result_t Uart_EnableIrq(M0P_UART_TypeDef* UARTx, en_uart_irq_sel_t enIrqSel);
en_result_t Uart_DisableIrq(M0P_UART_TypeDef* UARTx, en_uart_irq_sel_t enIrqSel);
                             
//����ʹ�ܺͽ�ֹ
en_result_t Uart_EnableFunc(M0P_UART_TypeDef* UARTx, en_uart_func_t enFunc);
en_result_t Uart_DisableFunc(M0P_UART_TypeDef* UARTx, en_uart_func_t enFunc);

//״̬λ�Ļ�ȡ����� 
uint8_t Uart_GetIsr(M0P_UART_TypeDef* UARTx);
boolean_t Uart_GetStatus(M0P_UART_TypeDef* UARTx,en_uart_status_t enStatus);
en_result_t Uart_ClrIsr(M0P_UART_TypeDef* UARTx);
en_result_t Uart_ClrStatus(M0P_UART_TypeDef* UARTx,en_uart_status_t enStatus);

//�����շ�����
///< ���ݲ�ѯģʽ����
en_result_t Uart_SendDataPoll(M0P_UART_TypeDef* UARTx, uint8_t u8Data);
///< �����ж�ģʽ����
en_result_t Uart_SendDataIt(M0P_UART_TypeDef* UARTx, uint8_t u8Data);
uint8_t Uart_ReceiveData(M0P_UART_TypeDef* UARTx);

//@} // UartGroup

#ifdef __cplusplus
#endif

#endif /* __UART_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/




