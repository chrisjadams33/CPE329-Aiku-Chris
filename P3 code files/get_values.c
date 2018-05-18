#include "msp.h"
#include "stdint.h"
#include "sqaure_root.h"
/*
 * get_values.c
 *
 *  Created on: May 16, 2018
 *      Author: Aiku
 */
#define max_count   65534

float get_freq(void){
    int start, end, difference = 0;
    float frequency, calibrated_frequency = 0;
    frequency = 0;

    TIMER_A0->CCTL[2] &=~ TIMER_A_CCTLN_COV;                //clear overflow

    while((TIMER_A0->CCTL[2] & 1) == 0);            //wait until capture interrupt flag
    start = TIMER_A0->CCR[2];                       //save starting CCR value
    TIMER_A0->CCTL[2] &=~ 1;                        //clear capture flag

    while((TIMER_A0->CCTL[2] & 1) == 0);             //wait until capture interrupt flag                    //CLOSED THE WHILE LOOP WHEN CALIBRATING;
    end = TIMER_A0->CCR[2];
                       //save ending CCR

    //add and sub end and start to difference count
    difference += end;
    difference -= start;

    if (TIMER_A0->CCTL[2] & TIMER_A_CCTLN_COV)           //check for overflow
    {
        difference += max_count;                //add max timer value
        TIMER_A0->CCTL[2] &=~ TIMER_A_CCTLN_COV;                //clear overflow
    }


    frequency = 1/(difference/(375*1e3));                     //divide # of ticks by Timer A frequency

    calibrated_frequency = 1.008125*(frequency) + 0.011625;

    return calibrated_frequency;
}

uint16_t get_rms(uint16_t data, int points){

    static int i = 0;
    static uint64_t squared_sum = 0;
    static uint16_t answer = 0;
    uint32_t square_avg;
    squared_sum += data*data;
    i++;
    if (i == points){
        square_avg = squared_sum/points;
        answer = square_rt(square_avg);
        i = 0;
    }
    return answer;
}



