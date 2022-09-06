#ifndef Slide_H
#define Slide_H

#include "tm4c123gh6pm.h"
#include "PLL.h"

#define Right 1
#define Left 2

#define ADC_Default_Max 2100
#define ADC_Default_Min 2000

void ADC0_InitSWTriggerSeq3_Ch1(void);

//------------ADC0_InSeq3------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
void ADC0_InSeq3(void);

void Slide_init(void);

void Slide_update(void);

int Slide(void);
#endif

