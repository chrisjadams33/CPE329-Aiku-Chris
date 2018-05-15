//  MSP432P401 Demo - ADC14, Sample A1, AVcc Ref, Set P1.0 if A1 > 0.5*AVcc
//
//   Description: A single sample is made on A1 with reference to AVcc.
//   Software sets ADC14_CTL0_SC to start sample and conversion - ADC14_CTL0_SC
//   automatically cleared at EOC. ADC14 internal oscillator times sample (16x)
//   and conversion. In Mainloop MSP432 waits in LPM0 to save power until ADC14
//   conversion complete, ADC14_ISR will force exit from LPM0 in Mainloop on
//   reti. If A0 > 0.5*AVcc, P1.0 set, else reset. The full, correct handling of
//   and ADC14 interrupt is shown as well.
//
//
//                MSP432P401x
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//        >---|P5.4/A1      P1.0|-->LED
//
//   William Goh
//   Texas Instruments Inc.
//   June 2016 (updated) | November 2013 (created)
//   Built with CCSv6.1, IAR, Keil, GCC
//******************************************************************************
#include "msp.h"
#include "delay_functions.h"
#include "convert_data.h"
#include "set_DCO.h"

#define FREQ_1_5MHz  1500000
#define FREQ_3MHz    3000000
#define FREQ_6MHz    6000000
#define FREQ_12MHz   12000000
#define FREQ_24MHz   24000000
#define FREQ_48MHz   48000000

int global_flag = 0;
uint16_t digital_data;
int captureflag = 0;
int captureperiod = 0;

int main(void) {
    volatile unsigned int i;
    int clk = FREQ_12MHz;
    static uint32_t calibrated_data;
    uint32_t num_return = 0;
    char answer[] = "0.000";
    int frequency
    int x = 0;

    //SMCLK has been divided by 128
    set_DCO(clk);

    WDT_A->CTL = WDT_A_CTL_PW |             // Stop WDT
                 WDT_A_CTL_HOLD;

    P5->SEL1 |= BIT4;                       // Configure P5.4 for ADC
    P5->SEL0 |= BIT4;
    P1->SEL0 |= BIT2 | BIT3;                // set 2-UART function


    //Configure PIN for sampling frequency measurements
    P6->DIR &=~ BIT5;   //input
    P6->IE |= BIT5;     //enable interrupt on pin
    P6->IES &=~ BIT5;    //set up for interrupt trigger on low-to-high transition


    // Configure UART
    EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST;           // Put eUSCI in reset
    EUSCI_A0->CTLW0 = EUSCI_A_CTLW0_SWRST |           // Remain eUSCI in reset
                      EUSCI_B_CTLW0_SSEL__SMCLK;      // Configure eUSCI clock source for SMCLK

    // Baud Rate calculation || 12000000/(16*9600) = 78.125 || Fractional portion = 0.125
    // User's Guide Table 21-4: UCBRSx = 0x10 || UCBRFx = int ( (78.125-78)*16) = 2
    EUSCI_A0->BRW = 78;
    EUSCI_A0->MCTLW = (2 << EUSCI_A_MCTLW_BRF_OFS) | EUSCI_A_MCTLW_OS16;

    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST; // Initialize eUSCI
    EUSCI_A0->IFG &= ~EUSCI_A_IFG_RXIFG;    // Clear eUSCI RX interrupt flag

    //TIMER_A Initialization
    TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE |        // TACCR0 interrupt enabled
                        TIMER_A_CCTLN_SCS  |        //synchronous capture
                        TIMER_A_CCTLN_CM_1 |        //capture on rising edge;
                        TIMER_A_CCTLN_CCIS_0;       //Capture input from CCI register

    //TIMER_A0->CCR[0] =  1000;                   //when to trigger interrupt
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK |    // SMCLK, continuous mode
                    TIMER_A_CTL_MC__CONTINUOUS | //count in continuous mode
                    TIMER_A_CTL_ID_1;            //divide SMCLK by 2


    // Enable global interrupt
    __enable_irq();

    // Enable ADC interrupt in NVIC module
    NVIC->ISER[0] = 1 << ((ADC14_IRQn) & 31);
    NVIC->ISER[1] = 1 << ((PORT6_IRQn) & 31);
    NVIC->ISER[2] = 1 << ((TA0_0_IRQn) & 31);

    //Sample&Hold=16, Sampling time: signal sourced from the sampling timer, ADC14 on
    ADC14->CTL0 = ADC14_CTL0_SHT0_2 | ADC14_CTL0_SHP | ADC14_CTL0_ON;
    ADC14->CTL1 = ADC14_CTL1_RES_3;         // Use sampling timer, 14-bit conversion results
                                            //takes 16 clock cycles

    ADC14->MCTL[0] |= ADC14_MCTLN_INCH_1;   // A1 ADC input select; Vref=AVCC
    ADC14->IER0 |= ADC14_IER0_IE0;          // Enable interrupt to occur after ADC conv. complete

    // Start sampling/conversion, interrupt is triggered after this
    ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC;  //start/enable new conversion

    while (1)
    {
        if (capture_flag == 1)
        {
            __disable_irq();
            captureperiod = capturevalue[1] - capturevalue[0];
            __enable_irq();

            frequency = convert_to_frequency(int captureperiod);


        }
        /*if (global_flag == 1)                              //check if value has been updated
        {
            //calibrated_data result is in uV!!!
            calibrated_data = (196)*digital_data + (725);  //slope = 196, y-int = 725
            num_return = convert_data(calibrated_data);    //num_return returns a 32 bit int. with four characters within it

            answer[0] = num_return >> 24;       //ones place
            answer[2] = num_return >> 16;       //tenths place
            answer[3] = num_return >> 8;        //hundredths place
            answer[4] = num_return;             //thousandths place

            while (x<5)                         //Display 5 ASCII characters to the Serial Terminal
            {
                EUSCI_A0->TXBUF = answer[x];    //Transmit character to TXBUF
                x ++;
                delay_ms(1, clk);               //Delay since sending to TXBUF takes cycles
            }
            x = 0;

            EUSCI_A0->TXBUF = 0x0D;                        //enter, new line

            delay_ms(500,clk);                             //delay before next sample
            ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC; //start/enable new conversion
            global_flag = 0;                               //clear flag
            delay_ms(1, clk);                              // Delay so that digital_data can get updated
        }*/
    }
}

// ADC14 interrupt service routine
void ADC14_IRQHandler(void) {

    ADC14->CLRIFGR1 |= ADC14_CLRIFGR1_CLRHIIFG; //clear flag
    digital_data = ADC14->MEM[0];               //read in ADC converted data and store.
    global_flag = 1;                            //set flag

}

//Frequency Sampling Interrupts
void PORT6_IRQHandler(void){

    static int capturecount = 0;

    P6->IFG &=~ BIT5; //clear flag

    if (TIMER_A0 -> CCTL[0] & TIMER_A_CCTLN_CCIFG)
    {
        capturevalue[capturecount] = TIMER_A0 -> CCR[0];
        capturecount ++;
        if (capturecount == 2)
        {
            capturecount = 0;
            capture_flag = 1;
        }
    }



}

//Timer A Interrupt Handler
void TA0_0_IRQHandler(void){


    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;  //clear flag

}
