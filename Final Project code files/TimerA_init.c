#include "msp.h"

void TimerA_init(void){

    //Configure PIN for sampling frequency measurements
    P2->DIR &=~ (BIT6);   //input
    P2->SEL0 |= BIT6;

    //TIMER_A Initialization
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__ACLK    | // ACLK
                    TIMER_A_CTL_MC__CONTINUOUS| //count in continuous mode
                    TIMER_A_CTL_IE            | //enable interrupts
                    TIMER_A_CTL_ID_1          | //divide timer clock by 2
                    TIMER_A_CTL_CLR;            //resets TAxR, the timer clock divider logic, and the count direction

    TIMER_A0->CCTL[3] = TIMER_A_CCTLN_CCIE |    //TA0CCR interrupt enabled
                        TIMER_A_CCTLN_SCS  |    //synchronous capture
                        TIMER_A_CCTLN_CAP  |    //capture mode
                        TIMER_A_CCTLN_CM_1 |    //capture on rising edge;
                        TIMER_A_CCTLN_CCIS_0;   //Capture input from CCI register

}

