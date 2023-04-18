/*
 * sunrise.h
 *
 *  Created on: Abr 2, 2023
 *      Author: leandro
 */

#ifndef __sunrise_H
#define __sunrise_H
#include <stdint.h>
#include <stdbool.h>


/**
 * @brief Inicializa el driver sunrise
 *
 * @param i2c_init Puntero a la configuración i2c
 * @return int8_t 0 OK, -1 error
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
