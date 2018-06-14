#include "msp.h"

void ADC_init(void){

    P5->SEL1 |= BIT0;                       // Configure P5.4 for ADC
    P5->SEL0 |= BIT0;

    //Sample&Hold=16, Sampling time: signal sourced from the sampling timer, ADC14 on, ADC14 clock is SMCLK, Divide ADC clock source by 64
    ADC14->CTL0 = ADC14_CTL0_SHT0_2 | ADC14_CTL0_SHP | ADC14_CTL0_ON | ADC14_CTL0_SSEL_4 | ADC14_CTL0_PDIV_3;

    ADC14->CTL1 = ADC14_CTL1_RES_3;         //Use sampling timer, 14-bit conversion results
                                            //takes 16 clock cycles

    ADC14->MCTL[0] |= ADC14_MCTLN_INCH_5;   // A5 ADC input select; Vref=AVCC
    ADC14->IER0 |= ADC14_IER0_IE0;          // Enable interrupt to occur after ADC conv. complete

}

