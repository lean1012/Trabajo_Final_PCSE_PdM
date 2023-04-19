/*
 * sunrise.c
 *
 *  Created on: Abr 2, 2023
 *      Author: leandro
 */

#include "sunrise.h"
#include "sunrise_port.h"
#include <stdint.h>

#define SUNRISE_I2C_ADDRESS 0x68
#define SUNRISE_SERIAL_NUMBER 0xA7

/**
 * @brief Convierte 2 elementos uint8_t en un uint16_t usando MSB
 * 
 * @param bytes puntero al inicio del array
 * @return uint16_t valor en 16bits
 */
static uint16_t buffer_to_uint16_t(const uint8_t* bytes) {
    return (uint16_t)bytes[0] << 8 | (uint16_t)bytes[1];
}

int8_t sunrise_init(void * i2c_init){
	sunrise_init_port(i2c_init);
	return 0;
}

int8_t sunrise_read_co2(uint16_t * co2){
	uint8_t buffer[8];
	int8_t err;
	buffer[0] = 0x00;
	err = sunrise_write(SUNRISE_I2C_ADDRESS,buffer,0);
	err = sunrise_write(SUNRISE_I2C_ADDRESS,buffer,1);
	if (err < 0) {
		return err;
	}
	err = sunrise_read(SUNRISE_I2C_ADDRESS,buffer,sizeof(buffer));
	if (err < 0) {
			return err;
	}
	*co2 = buffer_to_uint16_t(&buffer[6]);
	//controlo que el valor a enviar esté dentro de los parámetros del sensor ()
	if((*co2 > 0) && (*co2 < 10000)){
		return -1;
	}
	return 0;
}



int8_t sunrise_read_co2_low_power(uint16_t * co2){


	/*switch(actual_state){

				case INIT:
					//drive EN PIN
				break;

				case WAIT_35_MS:
					//delay
				break;

				case START_MENSUREMENT:
					//send_co2
				break;

				case WAIT_2_4:
					//delay
				break;

				case READ:
					//read
				break;

				case DISABLED:
					//disabled EN
				break;

				default:PIN
					actual_state=DISABLED;
				break;

			}
			*/
	return 0;
}






