#include "Slide.h"

unsigned int volatile result;

void ADC0_InitSWTriggerSeq3_Ch1(void){ 
	volatile unsigned long delay;  
	SYSCTL_RCGCGPIO_R |= 0x10;     // 1) activate clock for Port E
	while((SYSCTL_PRGPIO_R&0x10) == 0){}; // allow time for clock to start. Wait for status bit to be true
	GPIO_PORTE_DIR_R &= ~0x04;      // 2) make PE2 input
  GPIO_PORTE_AFSEL_R |= 0x04;     // 3) enable alternate function on PE2
  GPIO_PORTE_DEN_R &= ~0x04;      // 4) disable digital I/O on PE2
  GPIO_PORTE_AMSEL_R |= 0x04;     // 5) enable analog function on PE2
	// Changed to new register name SYSCTL_RCGCADC_R. 
  //SYSCTL_RCGC0_R |= 0x00010000;   // 6) activate ADC0 
  //delay = SYSCTL_RCGC2_R;
	SYSCTL_RCGCADC_R |= 0x01;   // 6) activate ADC0
	// These 4 delay statements allow the clock time to stabilize. Simulation did not work without them.
	delay = SYSCTL_RCGCADC_R;       // extra time to stabilize
	delay = SYSCTL_RCGCADC_R;       // extra time to stabilize
	delay = SYSCTL_RCGCADC_R;       // extra time to stabilize
	delay = SYSCTL_RCGCADC_R;				
			
	// Changed to new register name ADC0_PC_R.
	//  SYSCTL_RCGC0_R &= ~0x00000300;  // 7) configure for 125K 		
	ADC0_PC_R = 0x01;               // 7) configure for 125K 
  ADC0_SSPRI_R = 0x0123;          // 8) Sequencer 3 is highest priority
  ADC0_ACTSS_R &= ~0x0008;        // 9) disable sample sequencer 3
  ADC0_EMUX_R &= ~0xF000;         // 10) seq3 is software trigger
  ADC0_SSMUX3_R = (ADC0_SSMUX3_R&0xFFFFFFF0)+1; // 11) channel Ain1 (PE2)
  ADC0_SSCTL3_R = 0x0006;         // 12) no TS0 D0, yes IE0 END0
  ADC0_ACTSS_R |= 0x0008;         // 13) enable sample sequencer 3
}


//------------ADC0_InSeq3------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
void ADC0_InSeq3(void){  
  ADC0_PSSI_R = 0x0008;            // 1) initiate SS3
  while((ADC0_RIS_R&0x08)==0){};   // 2) wait for conversion done
  result = ADC0_SSFIFO3_R&0xFFF;   // 3) read result
  ADC0_ISC_R = 0x0008;             // 4) acknowledge completion
	}
		
		
		volatile unsigned long ADCvalue;
// The digital number ADCvalue is a representation of the voltage on PE2 
// voltage  ADCvalue
// 0.00V     0
// 0.75V    1024
// 1.50V    2048
// 2.25V    3072
// 3.00V    4095

	/*
 void Slide_init(void){
	 ADC0_InitSWTriggerSeq3_Ch1();
 }

 void Slide_update(void){
	 ADC0_InSeq3();
 }
 */
 int Slide(void){
	 if(result > 2100)
		 return Right;
	 else if(result < 2000)
		 return Left;
	 else
		 return 0;
 }
 

 
 

		