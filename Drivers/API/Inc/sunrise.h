/*
 * sunrise.h
 *
 *  Created on: Abr 2, 2023
 *      Author: leandro
 */

#ifndef __sunrise_H
#define __sunrise_H
#include <stdint.h>

/**
 * @brief Convierte 2 elementos uint8_t en un uint16_t usando MSB
 * 
 * @param bytes puntero al inicio del array
 * @return uint16_t valor en 16bits
 */
int8_t sunrise_init(void * i2c_init);

/**
 * @brief Lecutra del numero de seriel del sensor
 *
 * @param p_serial_number puntero donde se devolvera el número de serie
 * @return int8_t 0 OK, -1 error
 */

/**
 * @brief Lecutra del nivel de Co2
 *
 * @param co2 puntero donde se devolvera la lectura
 * @return int8_t 0 OK, -1 error
 */
int8_t sunrise_read_co2(uint16_t * co2);


#endif
