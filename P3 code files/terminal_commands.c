#include "msp.h"

void choose_address(int horiz, int vert);
void move_left(int move);
void move_down(int move);
void move_down(int move);
void move_topleft(void);
void transmit_char(char data);
void move_right(int move);
void hide_cursor(void);


void choose_address(int horiz, int vert){
    int count = 0;

    while(horiz >= 9)
    {
        horiz -= 9;
        count ++;
    }
    transmit_char(27); //ESC
    transmit_char(91); //[
    transmit_char(48+horiz); //spaces to move cursor horizontally
    transmit_char(59);      //spaces to move cursor vertically
    transmit_char(48+vert);
    while(count > 0)
    {
        move_right(48 + 9);
    }
    transmit_char(72); //direction: right
    }

void move_right(int move){
    transmit_char(27); //ESC
    transmit_char(91); //[
    transmit_char(48+move); //spaces to move
    transmit_char(67); //direction: right
}

void move_left(int move){
    transmit_char(27); //ESC
    transmit_char(91); //[
    transmit_char(48+move); //spaces to move
    transmit_char(68); //direction: left
}

void move_down(int move){
    transmit_char(27); //ESC
    transmit_char(91); //[
    transmit_char(48+move); //spaces to move
    transmit_char(66); //direction: down
}

void move_topleft(void){
    transmit_char(27); //ESC
    transmit_char(91); //[
    transmit_char(72); //moves cursor to top left of terminal
}

void transmit_char(char data){

    // Check if the TX buffer is empty first
    while(!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG));
        //send characters on the TXBUF
        EUSCI_A0->TXBUF = data;
}

void hide_cursor(void){
    transmit_char(27); //ESC
    transmit_char(91); //[
    transmit_char(63);
    transmit_char(50);
    transmit_char(53);
    transmit_char(73);
}

