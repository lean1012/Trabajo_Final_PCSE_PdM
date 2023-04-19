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

/**
 * @brief Estructura de datos a muestrear co2 mediante el sensor sunrise
 * temperatura y humedad mediante el sensor sht4x
 * 
 */
struct air {
	uint16_t co2;
	uint16_t temp;
	uint16_t hum;
};

/**
 * @brief Inicializa los drivers sht4x y sunrise
 * 
 * @param i2c_init puntero a la configuración i2c
 */
void init_sensors(void * i2c_init);

/**
 * @brief Realiza una muestra de air (co2,temp y hum)
 * 
 * @param p_air puntero a la estructura donde se alojaran los datos
 */
void measurement(struct air * p_air);


#endif /* API_INC_API_SENSORS_H_ */
