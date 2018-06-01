#include "math.h"

/*
 * get_sat_level.c
 *
 *  Created on: May 29, 2018
 *      Author: Aiku
 */

//inputs are integers rn bc assuming digital value (not calibrated yet)
float get_sat_level(int REDp2p, int IRp2p){

    float digital_sat_level = 0;

    //wavelength of red: 626nm, of IR: 940nm //ratio so e-9 doesnt matter
    digital_sat_level = (log10(REDp2p)*626)/(log10(IRp2p)*940);

    //convert digital sat level to decimal

    //place decimal values into string so prob want this function to return a char

}



