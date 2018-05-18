#include "msp.h"

void delay_us(int time, int clk_freq)
{
	int total_ticks;
	
	if (time == 1)			//if time is 1us, minimize delay
	{
		total_ticks = 1;
		total_ticks --;
		return;
	}
		
  	if (time < 10)											   //time less than 10us
  		total_ticks = (clk_freq/10000000 *time) - 5;            //total ticks
  		
  	else			
		total_ticks = (clk_freq/1000000 *time/10) - 10;         //total ticks
	
    while (total_ticks)		//delay loop
    {
		total_ticks --;
    }
    return;
}