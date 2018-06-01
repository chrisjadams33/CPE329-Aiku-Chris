#include "msp.h"
#include "set_DCO.h"
#include "ADC_init.h"
#include "TimerA_init.h"
#include "get_sat_level.h"
#include "get_BPM_data.h"
#include "delay_functions.h"
#include "LCD_start.h"
#include "LCD_CMD.h"

//frequency definitions
#define FREQ_1_5MHz  1500000
#define FREQ_3MHz    3000000
#define FREQ_6MHz    6000000
#define FREQ_12MHz   12000000
#define FREQ_24MHz   24000000
#define FREQ_48MHz   48000000

int global_flag = 0;                    //flag that determines when ADC has samples
uint16_t digital_data;                  //data value returned from ADC
int timer_count = 0;                    //counts overflows on timerA
int cature_count = 0;                   //counts 0-1 for capture index
int capturevalue[2];                    //where capture values are saved
int difference[5];
int capture_done = 0;
int freq_done = 0;
int measure_flag = 0;
int RED = 0;

void main(void)
{
    //used in calculations
    int maximum = 0;
    int minimum = 16384;
    int REDp2p = 0;
    int IRp2p = 0;
    float sat_level = 0;
    //int period = ____;          // need to figure out how many samples
    //int samples = period;
    uint16_t data;
    int avg_cycles;

    //calibrated data in uV
    int REDcalibrated_pp, IRcalibrated_pp;

    //converted answers sent to terminal
    float SPO;
    int BPM;

    //just in case
    //P2->DS |= BIT3;       //high drive enable

    //configure control bits for LEDs
    P5->DIR |= BIT1 + BIT2;                 //Red: Bit1, IR: Bit2
    P5->OUT &=~ (BIT1 + BIT2);              //initialize low

    //stop watchdog timer
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

	//MCLK, SMCLK freq
	int clk = FREQ_24MHz;

	//ACLK freq is set to REF0CLK which is 32.768kHz
	set_DCO(clk);
	//CS->KEY = CS_KEY_VAL;                   //unlock CS register
	//CS->CTL1 |= CS_CTL1_DIVA_7;             //divide ACLK by 128 ==> new ACLK freq = 32.768k/128 = 256Hz
    //CS->KEY = 0;                            //lock CS register

/*    //button input set up: P2.5 is input
    button_init();

	//ADC init and interrupt set up
	ADC_init();

	//TimerA init and interrupt set up
	TimerA_init();

	//LCD init
    LCD_start(clk);
    char Measuring[] = "Measuring...";
    char Sat_display[] = "SPO2: ";
    char BPM_display[] = "BPM: ";*/


    //Enable global interrupt
    __enable_irq();

    //T-gate testing
	while(1){
	    P5->OUT |= BIT1;
	    delay_ms(1000, clk);
	    P5->OUT &=~ BIT1;
	    delay_ms(1000, clk);

	}
}



/*    while (1)                               //infinite loop
    {
        if (measure_flag == 1)
        {
            //TURN ON IR LED
            P5->OUT |= BIT2;                //let T-gate turn on IR LED

            // DISPLAY "MEASURING..." ON LCD
            LCD_CMD(clear_display, clk);         //set ddram address top left
            delay_ms(2, clk);
            LCD_CMD(return_home, clk);           //return cursor to home
            delay_us(50, clk);
            write_string(Measuring, clk);
            delay_us(50, clk);

            //consider slowing down sampling, probably would have to use another timer

            while (samples >= 0)                                //still within sampling period
            {
                ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC;  //start/enable new conversion
                if (global_flag == 1)                           //if ADC sampled
                {
                    samples --;                                 //decrement sample count
                    data = digital_data;                        //save ADC data

                    if (minimum > data)                         //check for min
                        minimum = data;
                    if (maximum < data)                         //check for max
                        maximum = data;

                    global_flag = 0;                            //clear flag
                }

                if (samples == (period/2))
                {
                    //TURN OFF IR LED AND TURN ON RED LED
                    P5->OUT &=~ BIT2;               //turn off IR LED
                    P5->OUT |= BIT1;                //let T-gate turn on RED LED

                    IRp2p = maximum - minimum;                  //obtain raw peak to peak
                    maximum = 0;                                //reset max and min
                    minimum = 16384;
                    RED = 1;
                }
            }

            REDp2p = maximum - minimum;                         //obtain raw peak to peak
            maximum = 0;                                        //reset max and min
            minimum = 16384;

            samples = period;                                   //reset samples

            while(freq_done == 0){
                ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC;  //start/enable new conversion
            }

            //TURN OFF RED LED
            P5->OUT &=~ BIT1;               //turn off RED LED

            freq_done = 0;
            avg_cycles = (difference[0] + difference[1] +
                         difference[2] + difference[3] +
                         difference[4])/5;

            //CALCULATION FUNCTION FOR SPO AND BPM
            sat_level = get_sat_level(REDp2p, IRp2p);
            BPM_data = get_BPM_data(avg_cycles);

            //PRINT MEASURED VALUES ON LCD
            LCD_CMD(clear_display, clk);         //set ddram address top left
            delay_ms(2, clk);
            LCD_CMD(return_home, clk);           //return cursor to home
            delay_us(50, clk);
            write_string(Sat_display, clk);
            delay_us(50, clk);
            //WRITE SPO2 value
            delay_us(50,clk);
            LCD_CMD(bottom_row, clk);            //set ddram address to bottom row
            delay_us(50, clk);
            write_string(BPM_display, clk);
            delay_us(50, clk);
            //WRITE BPM value
            delay_us(50, clk);

        }
        //if (__button is triggered high__)       //check whatever pin the button is on
        if ((P2->IN &= BIT5) == BIT5)             //check whatever pin the button is on
            measure_flag = 1;
        else
            measure_flag = 0;

    }

}


// ADC14 interrupt service routine
void ADC14_IRQHandler(void) {

    ADC14->CLRIFGR1 |= ADC14_CLRIFGR1_CLRHIIFG; //clear flag
    digital_data = ADC14->MEM[0];               //read in ADC converted data and store.
    global_flag = 1;                            //set flag

    if (RED == 1)
    {
        //SAVE DIGITAL DATA ON EEPROM
    }
}

//TIMER A interrupt handler (using captures to determine frequency)
void TA0_N_IRQHandler(void){
    //capture counter
    static uint32_t capture_count = 0;
    static int i = 0;

    if (RED == 1)
    {
        if (TIMER_A0->CTL & TIMER_A_CTL_IFG){            //check for overflow
            timer_count ++;
            TIMER_A0 -> CTL &=~ TIMER_A_CTL_IFG;            //clear overflow flag
        }
        if ((TIMER_A0->CCTL[2] & TIMER_A_CCTLN_CCIFG)&& capture_done == 0){//capture interrupt
            capturevalue[capture_count] = TIMER_A0->CCR[2];           //save capture values
            capture_count ++;
            if (capture_count == 1)
                timer_count = 0;
        }
        if (capture_count == 2){                        //after capturing two riding edges
            //calculate total number of ticks on timer clock
            difference[i] = capturevalue[1] - capturevalue[0];
            difference[i] += timer_count*65535;
            capture_count = 0;
            i++;
        }
        if (i == 5){
            i = 0;
            freq_done = 1;
            measure_flag = 0;
            RED = 0;
        }
    }
    TIMER_A0->CCTL[2] &=~ TIMER_A_CCTLN_CCIFG;
}*/


