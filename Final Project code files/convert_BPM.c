#include "msp.h"

uint32_t convert_data(uint32_t calibrated_data){

    char hundreds_place = 0x00;
    char tens_place = 0x00;
    char ones_place = 0x00;
    uint32_t num_return = 0;

    while(calibrated_data > 1000){                   //compare the data(which is in uV) to 1V
        calibrated_data = calibrated_data - 1000;
        hundreds_place += 1;                                //increment value of the ones place
    }
    while(calibrated_data > 100){                    //compare the data(which is in uV) to 0.1V
        calibrated_data = calibrated_data - 100;
        tens_place += 1;                              //increment value of the tenths place
    }
    while(calibrated_data > 10){                     //compare the data(which is in uV) to 0.01V
        calibrated_data = calibrated_data - 10;
        ones_place += 1;                          //increment value of the hundredths place
    }
    if (calibrated_data >= 5)
        ones_place += 1;

    ones_place |= 0x30;                                 //convert so values are in ASCII form
    tens_place |= 0x30;
    hundreds_place |= 0x30;

    num_return |= hundreds_place;                           //ones place in the most significant byte of num_return
    num_return = num_return << 8;
    num_return |= tens_place;                         //tenths place in the 2nd most significant byte of num_return
    num_return = num_return << 8;
    num_return |= ones_place;                     //hundredths place in the 3rd most significant byte of num_return

    return num_return;                                  //return 0x3_3_3_3_
}





