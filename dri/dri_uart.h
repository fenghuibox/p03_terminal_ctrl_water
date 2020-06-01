
#ifndef __DRI_UART_H
#define __DRI_UART_H


#include "com_typedef.h"

#if 0
//=============================================================================
#define     UART_CHECK_PORT                (GpioPortA)
#define     UART_CHECK_PIN                  (GpioPin1)

#define     UART_CHECK_PORT_NVIC           (PORTA_IRQn)

//=============================================================================

void driUartInit( void );


void driUartSend( u8 *pData, u32 len );

void driUartSendNum( u16 val, u8 isEnter );




//=============================================================================

void driUartCheckSleepIn( void );
void driUartCheckSleepOut( void );

void driUartCheckInitIn( void );


void driUartCheckInit( void );


//u8  driUartCheckRead( void );

#define driUartCheckRead()  Gpio_GetInputIO(UART_CHECK_PORT, UART_CHECK_PIN)

#else


//=============================================================================
#define     UART_CHECK_PORT                (GpioPortA)
#define     UART_CHECK_PIN                  (GpioPin1)

//=============================================================================

void driUartInit( void );


void driUartSend( u8 *pData, u32 len );

void driUartSendNum( u16 val, u8 isEnter );




//=============================================================================

//void driUartCheckSleepIn( void );
//void driUartCheckSleepOut( void );

void driUartCheckInitIn( void );


void driUartCheckInit( void );


//u8  driUartCheckRead( void );

#define driUartCheckRead()  Gpio_GetInputIO(UART_CHECK_PORT, UART_CHECK_PIN)

#endif


#endif

