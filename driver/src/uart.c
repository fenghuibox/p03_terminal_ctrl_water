/*************************************************************************************
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
/** \file uart.c
 **
 ** UART function driver API.
 ** @link SampleGroup Some description @endlink
 **
 **   - 2017-05-17  1.0  CJ First version for Device Driver Library of Module.
 **
 ******************************************************************************/

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "uart.h"
/**
 ******************************************************************************
 ** \addtogroup UartGroup
 ******************************************************************************/
//@{
/******************************************************************************/
/* Local pre-processor symbols/macros ('#define')                             */
/******************************************************************************/

/******************************************************************************/
/* Local function prototypes ('static')                                       */
/******************************************************************************/

/******************************************************************************/
/* Local variable definitions ('static')                                       */
/******************************************************************************/

/**
 ******************************************************************************
 ** \brief  UARTͨ���ж�ʹ�ܺ�������
 **
 ** \param [in] UARTxͨ���ţ�enIrqSel����or�����ж�ʹ��
 **
 ** \retval OK���óɹ�
 ** \retval ErrorInvalidParameter����ʧ��
 ******************************************************************************/
en_result_t Uart_EnableIrq(M0P_UART_TypeDef* UARTx, en_uart_irq_sel_t enIrqSel)
{
    SetBit((uint32_t)(&(UARTx->SCON)), enIrqSel, TRUE);

    return Ok;
}
/**
 ******************************************************************************
 ** \brief  UARTͨ���жϽ�ֹ��������
 **
 ** \param [in] UARTxͨ���ţ�enIrqSel����or�����жϽ�ֹ
 **
 ** \retval OK���óɹ�
 ** \retval ErrorInvalidParameter����ʧ��
 ******************************************************************************/
en_result_t Uart_DisableIrq(M0P_UART_TypeDef* UARTx, en_uart_irq_sel_t enIrqSel)
{
    SetBit((uint32_t)(&(UARTx->SCON)), enIrqSel, FALSE);
    
    return Ok;
}

/**
 ******************************************************************************
 ** \brief  UARTͨ��������ģʽ����
 **
 ** \param [in] UARTxͨ���ţ�stcMultiCfg������ģʽ�ṹ
 **
 ** \retval OK���óɹ�
 ** \retval ErrorInvalidParameter����ʧ��
 ******************************************************************************/
en_result_t Uart_SetMultiMode(M0P_UART_TypeDef* UARTx, stc_uart_multimode_t* pstcMultiCfg)
{
    if(NULL != pstcMultiCfg)
    {
        UARTx->SCON_f.ADRDET = TRUE;   
        UARTx->SADDR = pstcMultiCfg->u8SlaveAddr;
        UARTx->SADEN = pstcMultiCfg->u8SaddEn;

    }
    else
    {
        return ErrorInvalidParameter;
    }
    
    return Ok;
}

/**
 ******************************************************************************
 ** \brief  UART���߰�˫��ģʽʹ��
 **
 ** \param [in] UARTx ͨ����
 **
 ** \retval Null
 ******************************************************************************/
void Uart_HdModeEnable(M0P_UART_TypeDef* UARTx)
{
    UARTx->SCON_f.HDSEL = TRUE;
}

/**
 ******************************************************************************
 ** \brief  UART���߰�˫��ģʽ�ر�
 **
 ** \param [in] UARTx ͨ����
 **
 ** \retval Null
 ******************************************************************************/
void Uart_HdModeDisable(M0P_UART_TypeDef* UARTx)
{
    UARTx->SCON_f.HDSEL = FALSE;
}

/**
 ******************************************************************************
 ** \brief  UARTͨ�����ģʽ��������/��ַ֡����TB8
 **
 ** \param [in] UARTx ͨ����
 ** \param [in] TRUE-TB8Ϊ��ַ֡��־��FALSE-TB8Ϊ����֡��־��
 **
 ** \retval Null
 ******************************************************************************/
void Uart_SetTb8(M0P_UART_TypeDef* UARTx, boolean_t bTB8Value)
{
    UARTx->SCON_f.B8CONT = bTB8Value;
    
}

/**
 ******************************************************************************
 ** \brief ��ȡRB8��ֵ
 **
 ** \param [in] UARTxͨ����
 **
 ** \retval RB8
 ******************************************************************************/
boolean_t Uart_GetRb8(M0P_UART_TypeDef* UARTx)
{
    return (UARTx->SBUF_f.DATA8);
}

/**
 ******************************************************************************
 ** \brief  UARTͨ��������ģʽ�ӻ���ַ���ú���
 **
 ** \param [in] UARTxͨ���ţ�addr��ַ
 **
 ** \retval OK���óɹ�
 ** \retval ErrorInvalidParameter����ʧ��
 ******************************************************************************/
en_result_t Uart_SetSaddr(M0P_UART_TypeDef* UARTx,uint8_t u8Addr)
{
    UARTx->SADDR = u8Addr;
    
    return Ok;
}

/**
 ******************************************************************************
 ** \brief  UARTͨ�����ͻ���յȹ���ʹ������
 **
 ** \param [in] UARTxͨ���ţ�enFunc����
 **
 ** \retval OK���óɹ�
 ** \retval ErrorInvalidParameter����ʧ��
 ******************************************************************************/
en_result_t Uart_EnableFunc(M0P_UART_TypeDef* UARTx, en_uart_func_t enFunc)
{    
    SetBit((uint32_t)(&(UARTx->SCON)), enFunc, TRUE);
    
    return Ok;
}
/**
 ******************************************************************************
 ** \brief  UARTͨ�����ͻ���յȹ��ܽ�ֹ����
 **
 ** \param [in] UARTxͨ���ţ�enFunc����
 **
 ** \retval OK���óɹ�
 ** \retval ErrorInvalidParameter����ʧ��
 ******************************************************************************/
en_result_t Uart_DisableFunc(M0P_UART_TypeDef* UARTx, en_uart_func_t enFunc)
{
    SetBit((uint32_t)(&(UARTx->SCON)), enFunc, FALSE);
    
    return Ok;
}
/**
 ******************************************************************************
 ** \brief  UARTͨ��ͨ��״̬��ȡ
 **
 ** \param [in] UARTxͨ����
 **
 ** \retval ״ֵ̬
 ******************************************************************************/
uint8_t Uart_GetIsr(M0P_UART_TypeDef* UARTx)
{
    return (UARTx->ISR);
}

/**
 ******************************************************************************
 ** \brief  UARTͨ��ͨ��״̬��ȡ
 **
 ** \param [in] UARTxͨ���ţ�enStatus��ȡ�ĸ�״̬
 **
 ** \retval ״ֵ̬
 ******************************************************************************/
boolean_t Uart_GetStatus(M0P_UART_TypeDef* UARTx, en_uart_status_t enStatus)
{
    boolean_t bStatus = FALSE;

     
    ASSERT(IS_VALID_STATUS(enStatus));

    bStatus =  GetBit((uint32_t)(&(UARTx->ISR)), enStatus);
    
    return bStatus;
}
/**
 ******************************************************************************
 ** \brief  UARTͨ��ͨ��״̬���
 **
 ** \param [in] UARTxͨ����
 **
 ** \retval OK
 ** \retval ErrorInvalidParameter���ʧ��
 ******************************************************************************/
en_result_t Uart_ClrIsr(M0P_UART_TypeDef* UARTx)
{
    UARTx->ICR = 0u;
    return Ok;
}
/**
 ******************************************************************************
 ** \brief  UARTͨ��ͨ��״̬���
 **
 ** \param [in] UARTxͨ���ţ�enStatus����ĸ�״̬
 **
 ** \retval OK
 ** \retval ErrorInvalidParameter���ʧ��
 ******************************************************************************/
en_result_t Uart_ClrStatus(M0P_UART_TypeDef* UARTx,en_uart_status_t enStatus)
{
    ASSERT(IS_VALID_STATUS(enStatus));

    SetBit((uint32_t)(&(UARTx->ICR)), enStatus, FALSE);
    
    return Ok;
}
/**
 ******************************************************************************
 ** \brief  UARTͨ���������ݺ���,��ѯ��ʽ���ô˺������жϷ�ʽ���Ͳ�����
 **
 ** \param [in] UARTxͨ���ţ�Data��������
 **
 ** \retval Ok���ͳɹ�
 ** \retval ErrorInvalidParameter����ʧ��
 ******************************************************************************/
en_result_t Uart_SendDataPoll(M0P_UART_TypeDef* UARTx, uint8_t u8Data)
{
    while(FALSE == Uart_GetStatus(UARTx,UartTxe))
    {}
    UARTx->SBUF_f.DATA = u8Data;
    while(FALSE == Uart_GetStatus(UARTx,UartTC))
    {}
    Uart_ClrStatus(UARTx,UartTC);       
    return Ok;
}

/**
 ******************************************************************************
 ** \brief  UARTͨ���������ݺ���,�жϷ�ʽ���ô˺���
 **
 ** \param [in] UARTxͨ���ţ�Data��������
 **
 ** \retval Ok���ͳɹ�
 ** \retval ErrorInvalidParameter����ʧ��
 ******************************************************************************/
en_result_t Uart_SendDataIt(M0P_UART_TypeDef* UARTx, uint8_t u8Data)
{ 
    UARTx->SBUF_f.DATA = u8Data; 
    
    return Ok;
}

/**
 ******************************************************************************
 ** \brief  UARTͨ���������ݺ���
 **
 ** \param [in] UARTxͨ����
 **
 ** \retval ��������
 ******************************************************************************/
uint8_t Uart_ReceiveData(M0P_UART_TypeDef* UARTx)
{
    return (UARTx->SBUF_f.DATA);
}

/**
 ******************************************************************************
 ** \brief  UARTͨ����ʼ������
 **
 ** \param [in] UARTxͨ���ţ�pstcCfg��ʼ���ṹ�� @ref stc_uart_cfg_t
 **
 ** \retval OK���óɹ�
 ** \retval ErrorInvalidParameter����ʧ��
 ******************************************************************************/
en_result_t Uart_Init(M0P_UART_TypeDef* UARTx, stc_uart_cfg_t* pstcCfg)
{
    en_result_t enRet = Error;
    uint32_t u32Over[2] = {0x4, 0x3};
    uint16_t u16OverShift;
    
    if(NULL == pstcCfg)
    {
        return ErrorInvalidParameter;
    }
    
    UARTx->SCON = 0;
    
    UARTx->SCON = (uint32_t)pstcCfg->enStopBit |
                  (uint32_t)pstcCfg->enMmdorCk |
                  (uint32_t)pstcCfg->stcBaud.enClkDiv |
                  (uint32_t)pstcCfg->enRunMode;
    
    if((UartMskMode1 == pstcCfg->enRunMode) || (UartMskMode3 == pstcCfg->enRunMode))
    {
        u16OverShift = u32Over[pstcCfg->stcBaud.enClkDiv/UartMsk8Or16Div];
        UARTx->SCNT = pstcCfg->stcBaud.u32Pclk/(pstcCfg->stcBaud.u32Baud<<u16OverShift);
        Uart_EnableFunc(UARTx,UartRenFunc);       ///<ʹ���շ�
    }
    
    
 
    enRet = Ok;
    return enRet;
}
//@} // UartGroup      

