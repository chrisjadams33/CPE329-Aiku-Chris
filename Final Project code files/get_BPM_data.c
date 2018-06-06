#include "msp.h"
/*
 * get_BPM_data.c
 *
 *  Created on: May 30, 2018
 *      Author: Aiku
 */

int get_BPM_data(int avg_cycles){

    int BPM = 0;

    BPM = (128*600/avg_cycles);            //128Hz is the timer clock freq

    //convert digital BPM data to decimal

    //place decimal values into string so prob want this function to return a char

    return BPM;
}


