#include "msp.h"

void delay_ms(int time, int clk_freq)
{
    int i;                              //initialize counter i

    int n_clk = clk_freq / 10000;       //divide clock to get cycles per ms
    int total_ticks = n_clk * time;     //total ticks for the given time

    if (set_DCO(clk_freq) == -1)
            return -1;                  //not using an available clock

    while (total_ticks)				   //delay loop
    {
		total_ticks -- ;
    }
    return;
}