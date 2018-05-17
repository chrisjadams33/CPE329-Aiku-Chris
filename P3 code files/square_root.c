#include "msp.h"
#include "stdint.h"

int square_rt(uint32_t number){
    int guess = 0x4000;
    int index = 14;
    int guess_sqr = guess*guess;
    while (index >=0){
        if (guess_sqr > number){
            guess &=~ (1 << index);
            index --;
            guess |= (1 << index);
        }
        else{
            index --;
            guess |= (1 << index);
        }
    guess_sqr = guess*guess;
    }
    return guess;
}



