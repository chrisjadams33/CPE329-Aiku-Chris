//

//******************************************************************************
#include "msp.h"
//#include "delay_functions.h"
//#include "convert_data.h"
#include "set_DCO.h"
//#include "min_max_check.h"
//#include "convert_to_frequency.h"
//#include "get_values.h"
#include "display_in_terminal.h"
#include "sqaure_root.h"
#include "terminal_commands.h"
#include "init_DMM.h"

//frequency definitions
#define FREQ_1_5MHz  1500000
#define FREQ_3MHz    3000000
#define FREQ_6MHz    6000000
#define FREQ_12MHz   12000000
#define FREQ_24MHz   24000000
#define FREQ_48MHz   48000000

int global_flag = 0;                    //flag that determines when ADC has samples
//int ms_flag = 0;
uint16_t digital_data;                  //data value returned from ADC
int mode = 0;                           //mode = 0 for AC, 1 for DC
int timer_count = 0;                    //counts overflows on timerA
int cature_count = 0;                   //counts 0-1 for capture index
int capturevalue[2];                    //where capture values are saved
int capture_flag = 0;                   //flag set when 2 rising edges captured
int difference = 0;

int main(void) {
    //volatile unsigned int i;
    //clock speed
    int clk = FREQ_24MHz;

    //RMS, PP, DC raw variables
    int RMS_data = 0;
    int peak2peak = 0;
    int DC_voltage = 0;

    //calibrated data in uV
    int calibrated_RMS, calibrated_pp, calibrated_DC;

    //converted answers sent to terminal
    float pp_answer, RMS_answer, DC_answer;
    float frequency;

    //used in calculations
    int samples = 50000;
    uint64_t squared_sum = 0;
    uint32_t square_avg;
    uint16_t data;
    uint32_t total = 0;
    int maximum = 0;
    int minimum = 16384;

    int RMS_sine;
    int RMS_triangle;
    int RMS_square;
    int wavetype;

    set_DCO(clk);                           //set the system clocks

    WDT_A->CTL = WDT_A_CTL_PW |             // Stop WDT
                 WDT_A_CTL_HOLD;

    init_DMM();                             //initialize (UART, ADC, TIMERS, INTERRUPTS)

    // Enable global interrupt
    __enable_irq();

    while (1)                               //infinite loop
    {
 //       mode = 0;
        while (samples >= 0)                                //still within sampling period
        {
            ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC;  //start/enable new conversion
            if (global_flag == 1)                           //if ADC sampled
            {
                samples --;                                 //decrement sample count
                data = digital_data;                        //save ADC data
                if (mode == 1)                              //DC Mode
                {
                    total += data;                          //running sum
                }
                else                                        //AC mode
                {
                    if (minimum > data)                     //check for min
                        minimum = data;
                    if (maximum < data)                     //check for max
                        maximum = data;

                    total += data;                          //running sum

                    squared_sum = squared_sum + (data*data);    //running squared sum for RMS
                }
                global_flag = 0;                                //clear flag
            }
        }
        maximum = 0;                                            //reset max and min
        minimum = 16384;

        if (mode == 1)                                          //determine sample period based off mode
            samples = 500;
        else
            samples = 50000;

        if (mode == 0)                                          //AC mode
        {
            /*if (capture_flag == 1){
                difference = capturevalue[1] - capturevalue[0];
                difference += timer_count*65535;
                capture_flag = 0;
                timer_count = 0;
            }*/
            //frequency = get_freq();
            /*if (frequency < 20 || frequency >1100)
            {
                previous = 16383;
                while (h_l < 2){
                    cycles ++;
                    if ((digital_data > DC_voltage) && (digital_data > previous)){
                        index[h_l] = cycles;
                        h_l ++;
                    }
                    previous = digital_data;
                    ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC; //start/enable new conversion
                }


                while (P2 -> IN & BIT6 != BIT6);
                while (h_l < 2){
                    current = (P2->IN & BIT6);
                    cycles += 9;
                    if (h_l == 0 && (current == 0))
                    {
                        h_l ++;
                        delay_us(5, clk);
                    }
                    if (h_l == 1 && (current == BIT6))
                        h_l ++;
                }
                h_l = 0;
                difference = index[1]-index[0];
                frequency = difference/24e6;
                cycles = 0;
            }*/
            frequency = difference/375000;                            //frequency in cycles/s
            square_avg = squared_sum/samples;                       //average squared sum
            RMS_data = square_rt(square_avg);                       //take square root
            DC_voltage = total/samples;                             //average sum
            peak2peak = maximum - minimum;                          //obtain raw peak to peak

            RMS_sine = (DC_voltage*DC_voltage) + (peak2peak*peak2peak)/8;
            RMS_sine = square_rt(RMS_sine);

            //reset sums
            total = 0;
            squared_sum = 0;
        }
        else if (mode == 1)                                         //DC modde
        {
            peak2peak = 0;
            RMS_data = 0;
            DC_voltage = total/samples;
            total = 0;
            frequency = 0;
        }

        //calibrated raw data into uV
        calibrated_pp = (189)*peak2peak;
        calibrated_DC = (188)*DC_voltage + 725;
        calibrated_RMS = (189)*RMS_data;

        //covert to Volts
        pp_answer = calibrated_pp/1e6;
        RMS_answer = calibrated_RMS/1e6;
        DC_answer = calibrated_DC/1e6;

        __disable_irq();                                                //disable interrupts
        string_to_terminal(RMS_answer, pp_answer, DC_answer, frequency, mode); //print answers
        __enable_irq();                                                 //enable interrupt

        if (mode > 2)
            mode = 0;
    }
}

// ADC14 interrupt service routine
void ADC14_IRQHandler(void) {

    ADC14->CLRIFGR1 |= ADC14_CLRIFGR1_CLRHIIFG; //clear flag
    digital_data = ADC14->MEM[0];               //read in ADC converted data and store.
    global_flag = 1;                            //set flag
}


//TIMER A interrupt handler (using captures to determine frequency)
void TA0_N_IRQHandler(void){
    //capture counter
    volatile static uint32_t capture_count = 0;

    if (TIMER_A0->CTL & TIMER_A_CTL_IFG)            //check for overflow
        timer_count ++;

    TIMER_A0 -> CTL &=~ TIMER_A_CTL_IFG;            //clear overflow flag

    if (TIMER_A0->CCTL[2] & TIMER_A_CCTLN_CCIFG){   //capture interrupt
        capturevalue[capture_count] = TIMER_A0->CCR[2]; //save capture values
        capture_count ++;
        if (capture_count == 2){                        //after capturing two riding edges
            //calculate total number of ticks on timer clock
            difference = capturevalue[1] - capturevalue[0];
            difference += timer_count*65535;
            capture_flag = 0;
            timer_count = 0;
            capture_count = 0;
        }
        TIMER_A0->CCTL[2] &=~ TIMER_A_CCTLN_CCIFG;

    }
}

// UART interrupt service routine to set Mode between DC and AC
void EUSCIA0_IRQHandler(void)
{
    char received;

    if (EUSCI_A0->IFG & EUSCI_A_IFG_RXIFG)    //receive interrupt flag triggered
    {
        // Check if the TX buffer is empty first
        while(!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG));
        received = EUSCI_A0->RXBUF;     //assign received char to variable

        if (received == ' ')          //if received is a space
        {
           if (mode == 0)
               mode = 1;
           else
               mode = 0;
        }
    }
}
