#include "msp.h"
/*
 * min_max_check.c
 *
 *  Created on: May 15, 2018
 *      Author: Aiku
 */
//minimum maximum checker functions

int min_check(uint16_t data)
{
    static int minimum = 16384;
    if (minimum > data)
        minimum = data;
    return minimum;
}

int max_check(uint16_t data)
{
    static int maximum = 0;
    if (maximum < data)
        maximum = data;
    return maximum;
}



