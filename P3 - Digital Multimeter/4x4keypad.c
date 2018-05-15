#include "msp.h"
#include "delay_functions.h"
/*
 * 4x4keypad.c
 *
 *  Created on: Apr 13, 2018
 *      Author: chrisjadams33
 */
int check_column(int clk);
char get_key(int row, int column);

void keypad_init(void)
{
    P5 -> DIR &=~ (BIT0 + BIT1 + BIT2);       //set P5.2-0 as inputs (columns)
    P5 -> REN |= (BIT0 + BIT1 + BIT2);
    P5 -> OUT &=~ (BIT0 + BIT1 + BIT2);       //pull down resistors on P5.2-0
    P4 -> DIR |= (BIT3 + BIT2 + BIT1 + BIT0); //P4.3-0 as outputs (rows)
}

char read_keypad(int clk)
{
    int column = 0;
    int row = 0;
    char key;
    P4 -> OUT &= 0xF0;                      //clear P4.3-0 bits

    P4 -> OUT |= BIT0;                      //power row 1
    row = 1;
    delay_us(40, clk);
    column = check_column(clk);             //check which column is high
    key = get_key(row, column);             //using current row and col value obtained, get key value
    P4 -> OUT &= 0xF0;                      //clear P4.3-0 bits

    if (key != '?')                         //if key has not been pressed return '?'
        return key;

    P4 -> OUT |= BIT1;                      //power row 2 and same procedure
    row = 2;
    delay_us(40, clk);
    column = check_column(clk);
    key = get_key(row, column);
    P4 -> OUT &= 0xF0;

    if (key != '?')
        return key;

    P4 -> OUT |= BIT2;                      //power row 3 and same procedure
    row = 3;
    delay_us(40, clk);
    column = check_column(clk);
    key = get_key(row, column);
    P4 -> OUT &= 0xF0;

    if (key != '?')
        return key;

    P4 -> OUT |= BIT3;                      //power row 4 and same procedure

   /* P5 -> IES =&~ BIT0;                     //set '*' as an interrupt
    P5 -> IE  |= BIT0;                      //enable interrupts
    P5 -> IFG &=~ BIT0;                     //clear interrupt flag
    NVIC -> ISR[0] = 1<<(PORT5_IRQn)&31);   //enable interrupts at NVIC
    __ENABLE_IRQ();                         //enable global interrupts*/

    row = 4;
    delay_us(40, clk);
    column = check_column(clk);
    key = get_key(row, column);
    P4 -> OUT &= 0xF0;

    if (key != '?')
        return key;

    return key;
}

int check_column(int clk)
{
    P5 -> DIR &=~ (BIT0 + BIT1 + BIT2);     //set P1.2-0 as inputs for columns
    int columns = 0x00;
    columns = P5 -> IN;                     //read P1.2-0 and assign to columns

    if ((columns &= BIT0) == BIT0)          //if column 1 bit is high return '1'
        return 1;
    columns = P5 -> IN;                     //"                      return '2'"
    if ((columns &= BIT1) == BIT1)
        return 2;
    columns = P5 -> IN;
    if ((columns &= BIT2) == BIT2)          //"                      return '3'"
        return 3;
    columns = P5 -> IN;
    return 0;
}

char get_key(int row, int column)
{
    if (row == 1)                           //check row 1
    {
        if (column == 1)                    //check each column and return respective key for the row
            return '1';
        if (column == 2)
            return '2';
        if (column == 3)
            return '3';
    }
    if (row == 2)                           //check row 2
    {
        if (column == 1)                    //check each column and return respective key for the row
            return '4';
        if (column == 2)
            return '5';
        if (column == 3)
            return '6';
    }
    if (row == 3)                           //check row 3
    {
        if (column == 1)                    //check each column and return respective key for the row
            return '7';
        if (column == 2)
            return '8';
        if (column == 3)
            return '9';
    }
    if (row == 4)                           //check row 4
    {
        if (column == 1)                    //check each column and return respective key for the row
            return '*';
        if (column == 2)
            return '0';
        if (column == 3)
            return '#';
    }
    return '?';

}


