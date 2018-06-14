#include "LCD_CMD.h"
#include "delay_functions.h"

#define top_row 0x80                      //LCD to top row

void LCD_start(int clk){

    delay_ms(50, clk);                    //delay for LCD power up
    LCD_init(clk);                        //initialize LCD
    delay_us(50, clk);
    LCD_CMD(top_row, clk);                //set ddram address top left
    delay_us(50, clk);
}


