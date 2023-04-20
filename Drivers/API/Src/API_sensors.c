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

     uint8_t hola1;
     uint16_t hola2;
     uint16_t hola3;
     read_measurement_mode(&hola1,&hola2,&hola3);
     set_number_samples(6);
     read_measurement_mode(&hola1,&hola2,&hola3);



}

void measurement(struct air * p_air) {
	sunrise_read_co2_filtered(&p_air->co2);
	sht4x_temp_hum_low_presition(&p_air->temp, &p_air->hum);
}
