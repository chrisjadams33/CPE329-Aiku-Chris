#include "msp.h"

uint32_t convert_data(uint32_t calibrated_data){

    char ones_place = 0x00;
    char tenths_place = 0x00;
    char hundredths_place = 0x00;
    char thousandths_place = 0x00;
    uint32_t num_return = 0;

    while(calibrated_data > 1000000){                   //compare the data(which is in uV) to 1V
        calibrated_data = calibrated_data - 1000000;
        ones_place += 1;                                //increment value of the ones place
    }
    while(calibrated_data > 100000){                    //compare the data(which is in uV) to 0.1V
        calibrated_data = calibrated_data - 100000;
        tenths_place += 1;                              //increment value of the tenths place
    }
    while(calibrated_data > 10000){                     //compare the data(which is in uV) to 0.01V
        calibrated_data = calibrated_data - 10000;
        hundredths_place += 1;                          //increment value of the hundredths place
    }
    while(calibrated_data > 1000){                      //compare the data(which is in uV) to 0.001V
        calibrated_data = calibrated_data - 1000;
        thousandths_place += 1;                         //increment value of the thousandths place
    }

    ones_place |= 0x30;                                 //convert so values are in ASCII form
    tenths_place |= 0x30;
    hundredths_place |= 0x30;
    thousandths_place |= 0x30;

    num_return |= ones_place;                           //ones place in the most significant byte of num_return
    num_return = num_return << 8;
    num_return |= tenths_place;                         //tenths place in the 2nd most significant byte of num_return
    num_return = num_return << 8;
    num_return |= hundredths_place;                     //hundredths place in the 3rd most significant byte of num_return
    num_return = num_return << 8;
    num_return |= thousandths_place;                    //thousandths place in the least significant byte of num_return

    return num_return;                                  //return 0x3_3_3_3_
}




