/*
 * keypad.h
 *
 *  Created on: Apr 13, 2018
 *      Author: chrisjadams33
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

void keypad_init(void);
char read_keypad(int clk);
int check_column(int clk);
char get_key(int row, int column);



#endif /* KEYPAD_H_ */
