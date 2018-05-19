#include "msp.h"
/*
 * init_DMM.c
 *
 *  Created on: May 18, 2018
 *      Author: chrisjadams33
 */
void init_DMM(void){
    P5->SEL1 |= BIT4;                       // Configure P5.4 for ADC
    P5->SEL0 |= BIT4;
    P1->SEL0 |= BIT2 | BIT3;                // set 2-UART function


    //Configure PIN for sampling frequency measurements
    P2->DIR &=~ (BIT5+ BIT6);   //input
    P2->SEL0 |= BIT5;


    // Configure UART
    EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST;           // Put eUSCI in reset
    EUSCI_A0->CTLW0 = EUSCI_A_CTLW0_SWRST |           // Remain eUSCI in reset
                      EUSCI_B_CTLW0_SSEL__SMCLK;      // Configure eUSCI clock source for SMCLK



    // Baud Rate calculation || 24000000/(16*9600) = 156.25 || Fractional portion = 0.25
        // User's Guide Table 21-4: UCBRSx = 0x10 || UCBRFx = int ( (156.25-156)*16) = 4
    EUSCI_A0->BRW = 13;
    EUSCI_A0->MCTLW = (0 << EUSCI_A_MCTLW_BRF_OFS) | EUSCI_A_MCTLW_OS16;

    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST; // Initialize eUSCI
    EUSCI_A0->IFG &= ~EUSCI_A_IFG_RXIFG;    // Clear eUSCI RX interrupt flag
    EUSCI_A0->IE |= EUSCI_A_IE_RXIE;        // Enable USCI_A0 RX interrupt

    //TIMER_A Initialization
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK    | // SMCLK, continuous mode
                    TIMER_A_CTL_MC__CONTINUOUS| //count in continuous mode
                    TIMER_A_CTL_IE            |
                    TIMER_A_CTL_ID_3          |
                    TIMER_A_CTL_CLR;

    TIMER_A0->CCTL[2] = TIMER_A_CCTLN_CCIE |        // TA0CCR interrupt enabled
                        TIMER_A_CCTLN_SCS  |        //synchronous capture
                        TIMER_A_CCTLN_CAP  |        //capture mode
                        TIMER_A_CCTLN_CM_1 |        //capture on rising edge;
                        TIMER_A_CCTLN_CCIS_0;       //Capture input from CCI register

    //TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE;     // TACCR0 interrupt enabled
    //TIMER_A0->CCTL[3] = TIMER_A_CCTLN_CCIE;     // TACCR1 interrupt enabled

    //TIMER_A0->CCR[3] =  0;                   //when to trigger interrupt
    //TIMER_A0->CCR[0] =  500;                   //when to trigger interrupt




    TIMER_A0->EX0 |= TIMER_A_EX0_TAIDEX_7;

/*    TIMER_A1->CTL = TIMER_A_CTL_SSEL__SMCLK |    // SMCLK, continuous mode
                    TIMER_A_CTL_MC__CONTINUOUS | //count in continuous mode
                    TIMER_A_CTL_CLR;

    TIMER_A1->CCTL[1] = TIMER_A_CCTLN_CCIE;     // TACCR0 interrupt enabled

    TIMER_A1->CCR[1] =  200;                   //when to trigger interrupt*/

    //USE TIMER 1 WITH ACLK FOR 1 SECOND INT (FOR RMS OVER 1 SEC)



    // Enable ADC interrupt in NVIC module
    NVIC->ISER[0] |= 1 << ((ADC14_IRQn) & 31);       //ADC  interrupt, goes in everytime ADC samples
    NVIC->ISER[0] |= 1 << ((TA0_N_IRQn) & 31);       //Timer A0 interrupt for capture mode
    NVIC->ISER[0] |= 1 << ((EUSCIA0_IRQn) & 31);     //UART interrupt, goes off everytime something is receieved by the MSP from the terminal

    //Sample&Hold=16, Sampling time: signal sourced from the sampling timer, ADC14 on
    ADC14->CTL0 = ADC14_CTL0_SHT0_2 | ADC14_CTL0_SHP | ADC14_CTL0_ON;
    ADC14->CTL1 = ADC14_CTL1_RES_3;         // Use sampling timer, 14-bit conversion results
                                            //takes 16 clock cycles

    ADC14->MCTL[0] |= ADC14_MCTLN_INCH_1;   // A1 ADC input select; Vref=AVCC
    ADC14->IER0 |= ADC14_IER0_IE0;          // Enable interrupt to occur after ADC conv. complete

}



