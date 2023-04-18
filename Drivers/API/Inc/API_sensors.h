/*
 * API_sensors.h
 *
 *  Created on: Apr 17, 2023
 *      Author: leandro
 */

#ifndef API_INC_API_SENSORS_H_
#define API_INC_API_SENSORS_H_

//include uint8_t
#include <stdint.h>
// include bool
#include <stdbool.h>

struct air {
	uint16_t co2;
	uint16_t temp;
	uint16_t hum;
};

void init_sensors();

void measurement(struct air * p_air);


#endif /* API_INC_API_SENSORS_H_ */
