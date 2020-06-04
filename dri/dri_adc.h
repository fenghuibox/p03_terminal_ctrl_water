
#ifndef __DRI_ADC_H
#define __DRI_ADC_H


#include "com_typedef.h"



void driAdcEnOpen( void );

void driAdcEnClose( void );




void driAdcStart( void );



void driAdcStop( void );






void driAdcInit( void );


void driAdcFunSet( FunAdcCB  fun );


#endif

