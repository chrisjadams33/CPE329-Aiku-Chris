/*
 * get_values.h
 *
 *  Created on: May 17, 2018
 *      Author: Aiku
 */

#ifndef GET_VALUES_H_
#define GET_VALUES_H_

float get_freq(void);
uint16_t get_rms(uint16_t data, int points);
uint16_t running_avg(uint16_t data);

#endif /* GET_VALUES_H_ */
