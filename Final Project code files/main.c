#include "msp.h"
#include "set_DCO.h"
#include "ADC_init.h"
#include "TimerA_init.h"
#include "delay_functions.h"
#include "LCD_start.h"
#include "LCD_CMD.h"
#include "convert_data.h"

//frequency definitions
#define FREQ_24MHz   24000000

#define clear_display 0x01             //LCD Commands
#define function_set  0x28             //set up LCD mode of operation
#define display_on 0x0F                //turn on LCD
#define display_off 0x08               //turn off LCD
#define entry_set 0x06                 //configurations
#define return_home 0x02               //return home
#define top_row  0x80                  //ddram address for top left
#define bottom_row 0xC0                //ddram address for bottom left

int global_flag = 0;                    //flag that determines when ADC has samples
uint16_t digital_data;                  //data value returned from ADC
int timer_count = 0;                    //counts overflows on timerA
int cature_count = 0;                   //counts 0-1 for capture index
int capturevalue[2];                    //where capture values are saved
int capture_done = 0;                   //capture count variable
int freq_done = 0;                      //to see when freq meas are done
int measure_flag = 0;                   //set when button is pressed
int RED = 0;
int capturecount = 0;

void main(void)
{
    //variables used throughout code
    int maximum = 0;            //used to compare to ADC samples
    int minimum = 16384;        //used to compare to ADC samples
    int REDp2p = 0;             //stores p2p value for RED LED
    int IRp2p = 0;              //stores p2p value for IR LED
    float sat_level = 0;        //to store SpO2 level
    int BPM_data;               //raw BPM data
    int period = 50000;         //25,000 samples for RED, 25,000 samples for IR
    int samples = period;
    uint16_t data;              //used to store ADC data
    int avg_cycles;             //used to store avergaed frequency measurement
    uint32_t BPM_LCD, SPO_LCD;  //SpO2 and BPM data to display on LCD
    int button_check;           //used to poll for button press

    //Messages to Display on LCD
    char Measuring[] = "Measuring...";
    char Sat_display[] = "SPO2: ";
    char BPM_display[] = "BPM: ";
    char Startup1[] = "  Press Button";
    char Startup2[] = "   To Measure";

    //stop watchdog timer
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

	//MCLK, SMCLK freq
	int clk = FREQ_24MHz;

	//ACLK freq is set to REF0CLK which is 32.768kHz
	set_DCO(clk);

    //button input set up: P2.4 is input (checking for transition high)
    P2->DIR &=~ BIT4;     //set P2.4 as input
    P2->REN |= BIT4;
    P2->OUT &=~ BIT4;     //pull down resistor on P2.4
    //RED and IR LED Control Bit Configurations in High Drive
    P1->DIR|=BIT0;        //RED LED CTL
    P1->OUT|=BIT0;
    P2->DIR|=BIT0;        //IR LED CTL
    P2->OUT&=~BIT0;
    P1->DS |= BIT0;       //high drive enable
    P2->DS |= BIT0;       //high drive enable

	//ADC init
	ADC_init();

	//TimerA init
	TimerA_init();

	//LCD init
    LCD_start(clk);

    //Enable global interrupt
    __enable_irq();

    //Initial Message to Display Upon Start-up
    LCD_CMD(clear_display, clk);         //set ddram address top left
    delay_ms(2, clk);
    LCD_CMD(return_home, clk);           //return cursor to home
    delay_us(50, clk);
    write_string(Startup1, clk);         //display "Press Button"
    delay_us(50, clk);
    LCD_CMD(bottom_row, clk);            //set ddram address to bottom row
    delay_us(50, clk);
    write_string(Startup2, clk);         //display "To Measure"
    delay_us(50, clk);

    while (1){

        //check if button has been pressed to initialize measurements
        if (measure_flag == 1)
         {
             __enable_irq();                 //enable interrupts

             P2->OUT |= BIT0;                //turn on IR LED
             P1->OUT &=~ BIT0;               //turn off RED LED
             delay_ms(500, clk);

             LCD_CMD(clear_display, clk);         //set ddram address top left
             delay_ms(2, clk);
             LCD_CMD(return_home, clk);           //return cursor to home
             delay_us(50, clk);
             write_string(Measuring, clk);        //diaplay "Measuring..."
             delay_us(50, clk);

             NVIC->ISER[0] |= 1 << ((ADC14_IRQn) & 31);       //ADC  interrupt enable

             while (samples >= 0)                                //still within sampling period
             {
                 ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC;  //start/enable new conversion
                 if (global_flag == 1)                           //if ADC sampled
                 {
                     RED = 0;
                     samples --;                                 //decrement sample count
                     data = digital_data;                        //save ADC data

                     if (minimum > data)                         //check for min
                         minimum = data;
                     if (maximum < data)                         //check for max
                         maximum = data;

                     global_flag = 0;                            //clear flag
                 }

                 if (samples == (period/2))          //RED LED testing
                 {
                     P2->OUT &=~ BIT0;               //turn off IR LED
                     P1->OUT |= BIT0;                //turn on RED LED
                     delay_ms(500, clk);

                     IRp2p = maximum - minimum;      //obtain raw peak to peak
                     maximum = 0;                    //reset max and min
                     minimum = 16384;
                     RED = 1;
                 }
                 delay_us(50, clk);                  //delay loop speed
             }

             REDp2p = maximum - minimum;             //obtain raw peak to peak
             maximum = 0;                            //reset max and min
             minimum = 16384;

             samples = period;                      //reset samples
             freq_done = 0;
             NVIC->ISER[0] |= 1 << ((TA0_N_IRQn) & 31);  //Enable TA0 interrupts in order to measure frequency

             while(!freq_done);
             NVIC->ICER[0] |= 1 << ((TA0_N_IRQn) & 31);  //Disable TA0 interrupts since its only for frequency
             __disable_irq();                            //disable interrupts

             avg_cycles = (difference[0] + difference[1] +      //take average of 5 frequency measurements
                          difference[2] + difference[3] +
                          difference[4])/5;

             sat_level = (log10(REDp2p)*915)/(log10(IRp2p)*940)*100;    //Beer-Lambert Law to calculate SpO2 level
             if (sat_level > 99)
                 sat_level = 99;
             SPO_LCD = convert_SPO(sat_level);              //convert SpO2 value to ascii
             BPM_data = (16384*600/avg_cycles);             //16384Hz is the timer clock freq
             BPM_LCD = convert_BPM(BPM_data);               //convert BPM value to ascii

             //PRINT MEASURED VALUES ON LCD
             LCD_CMD(clear_display, clk);         //set ddram address top left
             delay_ms(2, clk);
             LCD_CMD(return_home, clk);           //return cursor to home
             delay_us(50, clk);
             write_string(Sat_display, clk);      //Display "SpO2:"
             delay_us(50, clk);

             //WRITE SPO2 value
             LCD_write((SPO_LCD >> 8), clk);      //display tens place
             delay_us(50, clk);
             LCD_write(SPO_LCD, clk);             //display hundreds place
             delay_us(50, clk);
             LCD_write('%', clk);                 //display % sign
             delay_us(50,clk);

             LCD_CMD(bottom_row, clk);            //set ddram address to bottom row
             delay_us(50, clk);
             write_string(BPM_display, clk);      //Display "BPM:"
             delay_us(50, clk);

             //WRITE BPM value
             if (BPM_data > 999)
                 LCD_write((BPM_LCD >> 16), clk); //display hundreds place
             delay_us(50, clk);
             LCD_write((BPM_LCD >> 8), clk);       //display tens place
             delay_us(50, clk);
             LCD_write(BPM_LCD, clk);              //display ones place
             delay_us(50, clk);

             button_check = 0;                     //reset button check

         }
         //if (__button is triggered high__)       //check pin the button is on
         button_check = P2 -> IN;
         if ((button_check &= BIT4) == BIT4)       //check pin the button is on
             measure_flag = 1;                     //start measurements
         else
             measure_flag = 0;

         P1->OUT &=~ BIT0;                          //turn off red LED
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
    static uint32_t capture_count = 0;
    static int i = 0;
    if (freq_done == 0){
        if (TIMER_A0->CTL & TIMER_A_CTL_IFG){               //check for overflow
            timer_count ++;
            TIMER_A0 -> CTL &=~ TIMER_A_CTL_IFG;            //clear overflow flag
        }
        if ((TIMER_A0->CCTL[3] & TIMER_A_CCTLN_CCIFG)&& capture_done == 0){   //capture interrupt
            capturevalue[capture_count] = TIMER_A0->CCR[3];                   //save capture values
            capture_count ++;
            if (capture_count == 1)
                 timer_count = 0;
        }
        if (capture_count == 2){                                     //after capturing two riding edges
                 difference[i] = capturevalue[1] - capturevalue[0];  //calculate difference b/w rising edges
                 difference[i] += timer_count*65535;                 //add overflow
                 capture_count = 0;                                  //ready for new freq measurement sequence

             if ((difference[i] < 9000) || (difference[i] > 40960)){ //unreasonable freq measurements
                 i--;
             }
             i++;
         }
         if (i == 5){                                                //if 5 frequency measurements acquired
             i = 0;
             freq_done = 1;
             measure_flag = 0;
         }
     TIMER_A0->CCTL[3] &=~ TIMER_A_CCTLN_CCIFG;                      //clear caputre interrupt flag
     }
}
