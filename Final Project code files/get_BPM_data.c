#include "msp.h"
/*
 * get_BPM_data.c
 *
 *  Created on: May 30, 2018
 *      Author: Aiku
 */

float get_BPM_data(int avg_cycles){

    float BPM = 0;

    BPM = (128/avg_cycles)*60;            //128Hz is the timer clock freq

    //convert digital BPM data to decimal

    //place decimal values into string so prob want this function to return a char


}


