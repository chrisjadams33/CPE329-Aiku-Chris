/*
 * convert_to_frequency.c
 *
 *  Created on: May 15, 2018
 *      Author: Aiku
 */

int convert_to_frequency(int captureperiod){

    float micro_seconds = 0;
    float frequency_float = 0;
    int frequency = 0;
    char thousands_place = 0x00;
    char hundreds_place = 0x00;
    char tens_place = 0x00;
    char ones_place = 0x00;
    char tenths_place = 0x00;
    char hundredths_place = 0x00;

    //capture period is the number of ticks of the clock that Timer A is operating at which is
    //SMCLK which is the DCO clock divided by 1 ==> 24M/1 = 24MHz
    //which is then divided by the ID register by 2 ==> 12MHz

    micro_seconds = captureperiod/6;
    frequency_float = 1e6/micro_seconds;

    while(frequency_float > 1000){                   //compare the data(which is in uV) to 1V
        frequency_float = frequency_float - 1000;
        thousands_place += 1;                                //increment value of the ones place
    }
    while(frequency_float > 100){                    //compare the data(which is in uV) to 0.1V
        frequency_float = frequency_float - 100;
        hundreds_place += 1;                              //increment value of the tenths place
    }
    while(frequency_float > 10){                     //compare the data(which is in uV) to 0.01V
        frequency_float = frequency_float - 10;
        tens_place += 1;                          //increment value of the hundredths place
    }
    while(frequency_float > 1){                      //compare the data(which is in uV) to 0.001V
        frequency_float = frequency_float - 1;
        ones_place += 1;                         //increment value of the thousandths place
    }
    while(frequency_float > 0.1){                     //compare the data(which is in uV) to 0.01V
        frequency_float = frequency_float - 0.1;
        tenths_place += 1;                          //increment value of the hundredths place
    }
    while(frequency_float > 0.01){                      //compare the data(which is in uV) to 0.001V
        frequency_float = frequency_float - 0.01;
        hundredths_place += 1;                         //increment value of the thousandths place
    }

    //ones_place |= 0x30;                                 //convert so values are in ASCII form
    //tens_place |= 0x30;
    //hundreds_place |= 0x30;
    //thousands_place |= 0x30;

    frequency |= thousands_place;                         //thousands place in the most significant byte of frequency
    frequency = frequency << 4;
    frequency |= hundreds_place;                         //hundreds place in the 2nd most significant byte of frequency
    frequency = frequency << 4;
    frequency |= tens_place;                            //tens place in the 3rd most significant byte of frequency
    frequency = frequency << 4;
    frequency |= ones_place;                            //ones place in the least significant byte of frequency
    frequency = frequency << 4;
    frequency |= tenths_place;                            //tenths place in the 3rd most significant byte of frequency
    frequency = frequency << 4;
    frequency |= hundredths_place;                            //hundredths place in the least significant byte of frequency

    return frequency;                                //return 0xthousandshundredstensoenestenthshundredths

}



