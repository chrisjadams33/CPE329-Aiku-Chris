//

//******************************************************************************
#include "msp.h"
#include "delay_functions.h"
#include "convert_data.h"
#include "set_DCO.h"
#include "min_max_check.h"
#include "convert_to_frequency.h"
#include "get_values.h"
#include "display_in_terminal.h"


#define FREQ_1_5MHz  1500000
#define FREQ_3MHz    3000000
#define FREQ_6MHz    6000000
#define FREQ_12MHz   12000000
#define FREQ_24MHz   24000000
#define FREQ_48MHz   48000000

int global_flag = 0;
int ms_flag = 0;
uint16_t digital_data;
int capture_flag = 0;
int captureperiod = 0;
int mode = 0;                           //mode = 0 for AC, 1 for DC
int timer_count = 0;
int capturevalue[2];
int capturecount = 0;


int main(void) {
    volatile unsigned int i;
    int clk = FREQ_24MHz;
    int calibrated_RMS, calibrated_average, calibrated_pp, calibrated_DC;
    char display_frequency[] = "0000.00";
    float frequency;
    int x = 0;
    int n = 0;
    int total, average, maximum, minimum, RMS_data, peak2peak, DC_voltage;
    //int timer_max = 65535;
    //char answer[5] = "0.000";

    //SMCLK = DCO
    set_DCO(clk);

    WDT_A->CTL = WDT_A_CTL_PW |             // Stop WDT
                 WDT_A_CTL_HOLD;

    P5->SEL1 |= BIT4;                       // Configure P5.4 for ADC
    P5->SEL0 |= BIT4;
    P1->SEL0 |= BIT2 | BIT3;                // set 2-UART function


    //Configure PIN for sampling frequency measurements
    P2->DIR &=~ BIT5;   //input
    P2->SEL0 |= BIT5;
    //P6->OUT &=~ BIT5;
    //P2->IE |= BIT5;     //enable interrupt on pin
    //P2->IES &=~ BIT5;    //set up for interrupt trigger on low-to-high transition


    // Configure UART
    EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST;           // Put eUSCI in reset
    EUSCI_A0->CTLW0 = EUSCI_A_CTLW0_SWRST |           // Remain eUSCI in reset
                      EUSCI_B_CTLW0_SSEL__SMCLK;      // Configure eUSCI clock source for SMCLK


    // Baud Rate calculation || 12000000/(16*9600) = 78.125 || Fractional portion = 0.125                       ///////MAKE SURE TO CHECK THIS IF DCO/SMCLK IS ADJSUTED
    // User's Guide Table 21-4: UCBRSx = 0x10 || UCBRFx = int ( (78.125-78)*16) = 2
    //EUSCI_A0->BRW = 78;
    //EUSCI_A0->MCTLW = (2 << EUSCI_A_MCTLW_BRF_OFS) | EUSCI_A_MCTLW_OS16;


    // Baud Rate calculation || 24000000/(16*9600) = 156.25 || Fractional portion = 0.25
        // User's Guide Table 21-4: UCBRSx = 0x10 || UCBRFx = int ( (156.25-156)*16) = 4
    EUSCI_A0->BRW = 156;
    EUSCI_A0->MCTLW = (4 << EUSCI_A_MCTLW_BRF_OFS) | EUSCI_A_MCTLW_OS16;

    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST; // Initialize eUSCI
    EUSCI_A0->IFG &= ~EUSCI_A_IFG_RXIFG;    // Clear eUSCI RX interrupt flag
    EUSCI_A0->IE |= EUSCI_A_IE_RXIE;        // Enable USCI_A0 RX interrupt

    //TIMER_A Initialization
    TIMER_A0->CCTL[2] = TIMER_A_CCTLN_CCIE |        // TA0CCR interrupt enabled
                        TIMER_A_CCTLN_SCS  |        //synchronous capture
                        TIMER_A_CCTLN_CAP  |        //capture mode
                        TIMER_A_CCTLN_CM_1 |        //capture on rising edge;
                        TIMER_A_CCTLN_CCIS_0;       //Capture input from CCI register

    TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE;     // TACCR0 interrupt enabled
    //TIMER_A0->CCTL[1] = TIMER_A_CCTLN_CCIE;     // TACCR0 interrupt enabled

    TIMER_A0->CCR[0] =  6000;                   //when to trigger interrupt
    //TIMER_A0->CCR[1] =  6000;                   //when to trigger interrupt                                   //USE THIS FOR SAMPLE RATE

    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK |    // SMCLK, continuous mode
                    TIMER_A_CTL_MC__CONTINUOUS | //count in continuous mode
                    TIMER_A_CTL_ID_2           |            //divide SMCLK by 4
                    TIMER_A_CTL_CLR;

    //USE TIMER 1 WITH ACLK FOR 1 SECOND INT (FOR RMS OVER 1 SEC)



    // Enable ADC interrupt in NVIC module
    NVIC->ISER[0] |= 1 << ((ADC14_IRQn) & 31);       //ADC  interrupt, goes in everytime ADC samples
    //NVIC->ISER[1] |= 1 << ((PORT6_IRQn) & 31);       //P6.5 interrupt, goes in everytime L-to-H transition
    NVIC->ISER[0] |= 1 << ((TA0_0_IRQn) & 31);       //TA0  interrupt,
    //NVIC->ISER[0] |= 1 << ((TA0_N_IRQn) & 31);       //TA1  interrupt, goes every 1ms of time
    NVIC->ISER[0] |= 1 << ((EUSCIA0_IRQn) & 31);     //UART interrupt, goes off everytime something is receieved by the MSP from the terminal

    //Sample&Hold=16, Sampling time: signal sourced from the sampling timer, ADC14 on
    ADC14->CTL0 = ADC14_CTL0_SHT0_2 | ADC14_CTL0_SHP | ADC14_CTL0_ON;
    ADC14->CTL1 = ADC14_CTL1_RES_3;         // Use sampling timer, 14-bit conversion results
                                            //takes 16 clock cycles

    ADC14->MCTL[0] |= ADC14_MCTLN_INCH_1;   // A1 ADC input select; Vref=AVCC
    ADC14->IER0 |= ADC14_IER0_IE0;          // Enable interrupt to occur after ADC conv. complete

    // Start sampling/conversion, interrupt is triggered after this
    //ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC;  //start/enable new conversion

    /*float freq = 1011.11;
    float DC = 2.78;                                  //USED these 4 lines to make sure floats are displayed on Terminal
    float RMS_voltage = 3.30;
    string_to_terminal(RMS_voltage, DC, freq);*/

    //string_to_terminal(RMS_voltage, DC_voltage, frequency); //MAKE SURE TO DISABLE INTERRUPTS WHEN PRINTING HERE AND ENABLE THEM AFTER

    // Enable global interrupt
    __enable_irq();

    while (1)
    {
        frequency = get_freq();
        /*if (capture_flag == 1)
        {

            while (timer_count > 0)            //# of times that the timer has been maxed out
            {
                captureperiod += timer_max;
                timer_count --;
            }
            captureperiod += capturevalue[1];
            captureperiod -= capturevalue[0];

            frequency = convert_to_frequency(captureperiod);
            captureperiod = 0;

            display_frequency[0] = (frequency >> 28) & 0x30;       //thousands place
            display_frequency[1] = (frequency >> 24) & 0x30;       //hundreds place
            display_frequency[2] = (frequency >> 20) & 0x30;       //tens place
            display_frequency[3] = (frequency >> 16) & 0x30;       //ones place
            display_frequency[5] = (frequency >> 12) & 0x30;       //tenths place
            display_frequency[6] = (frequency >> 8) & 0x30;       //hundredths place

            while (x<7)                         //Display 5 ASCII characters to the Serial Terminal
            {
                EUSCI_A0->TXBUF = display_frequency[x];    //Transmit character to TXBUF
                x ++;
                delay_ms(1, clk);               //Delay since sending to TXBUF takes cycles
            }
            x = 0;

            EUSCI_A0->TXBUF = 0x0D;                        //enter, new line

            delay_ms(500,clk);                             //delay before next sample
            ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC; //start/enable new conversion
            global_flag = 0;                               //clear flag
            delay_ms(1, clk);                              // Delay so that digital_data can get updated
            __enable_irq();
        }*/
        if (global_flag == 1)
        {
            if (mode == 1)                                     //DC Mode
            {
                total += digital_data;
                n++;
                if (ms_flag == 1)                              //DC mode needs 1ms update of DC value
                {
                    average = total/n;
                    calibrated_average = (196)*average + (725);  //slope = 196, y-int = 725
                    ms_flag = 0;
                    n = 0;
                }
            }
            else if (mode == 0)                                  //AC mode
            {
                minimum = min_check(digital_data);
                maximum = max_check(digital_data);
                peak2peak = maximum - minimum;
                DC_voltage = (maximum + minimum)/2;

                //RMS_data = get_rms(digital_data, samples);                                                          //NEED TO DETERMINE NUMBER OF SAMPLES

                calibrated_pp = (196)*peak2peak + (725);  //slope = 196, y-int = 725
                calibrated_DC = (196)*DC_voltage + (725);  //slope = 196, y-int = 725
                calibrated_RMS = (196)*RMS_data + (725);  //slope = 196, y-int = 725
            }

          /*  while (x<5)                         //Display 5 ASCII characters to the Serial Terminal
            {
                EUSCI_A0->TXBUF = answer[x];    //Transmit character to TXBUF
                x ++;
                delay_ms(1, clk);               //Delay since sending to TXBUF takes cycles
            }
            x = 0;

            EUSCI_A0->TXBUF = 0x0D;                        //enter, new line

            delay_ms(500,clk);                             //delay before next sample*/

            ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC; //start/enable new conversion                            //PUT IN TIMER INTR WITH CCR FOR SAMPLE RATE
            global_flag = 0;                               //clear flag


            //delay_ms(1, clk);                              // Delay so that digital_data can get updated

            //CONVERT ALL VALUES TO FLOATS AND PRINT
        }
    }
}

// ADC14 interrupt service routine
void ADC14_IRQHandler(void) {

    ADC14->CLRIFGR1 |= ADC14_CLRIFGR1_CLRHIIFG; //clear flag
    digital_data = ADC14->MEM[0];               //read in ADC converted data and store.
    global_flag = 1;                            //set flag
}

//Frequency Sampling Interrupts
void TA0_0_IRQHandler(void){

    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;  //clear flag
    TIMER_A0->CCR[0] += 6000;                    //increment CCR by 384

}

//Timer A Interrupt Handler (use for DC 1ms intervals)
//only thing this will do is turn on ms_flag
/*
void TA0_N_IRQHandler(void){

    TIMER_A0->CCTL[1] &= ~TIMER_A_CCTLN_CCIFG;
    ms_flag = 1;
    TIMER_A0->CCR[1] += 12000;                  //12000 ticks of TimerA clock in order to get 1ms
}
*/


//Timer A Interrupt Handler to count how many times CCR max's out
/*void TA0_0_IRQHandler(void){

    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;  //clear flag
    if (capturecount > 0)
        timer_count ++;                         //# of times that the timer has been maxed out
    TIMER_A0->CCR[0] += 65534;                  //12000 ticks of TimerA clock in order to get 1ms
}*/

// UART interrupt service routine to set Mode between DC and AC
/*void EUSCIA0_IRQHandler(void)
{
    char received;

    if (EUSCI_A0->IFG & EUSCI_A_IFG_RXIFG)
    {
        // Check if the TX buffer is empty first
        while(!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG));

        received = EUSCI_A0->RXBUF;     //assign received char to variable

        //check
        if (received == 0x41)          //if received is a
        {
           mode = 1;
        }
        if (received == 0x44)         //if received is d
        {
            mode = 0;
        }
    }
}*/
