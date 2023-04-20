/*
 * API_sensors.c
 *
 *  Created on: Apr 17, 2023
 *      Author: leandro
 */

#include "API_sensors.h"
#include "sht4x.h"
#include "sunrise.h"



void init_sensors(void * i2c_init){
	 sht4x_init(i2c_init);
	 sunrise_init(i2c_init);

}

void measurement(struct air * p_air) {
	//si las lecturas dan con error grabo 0
	int8_t err = sunrise_read_co2_filtered(&p_air->co2);
	if(err<0){
		p_air->co2=0;
	}
	err = sht4x_temp_hum_low_presition(&p_air->temp, &p_air->hum);
	if(err<0){
			p_air->temp=0;
			p_air->hum=0;
		}

}
