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
 * @brief Lecutra del nivel de Co2 filtrada
 *
 * @param co2 puntero donde se devolvera la lectura
 * @return int8_t 0 OK, -1 error
 */
int8_t sunrise_read_co2_filtered(uint16_t * co2);

/**
 * @brief Lecutra del nivel de Co2 sin filtrar
 *
 * @param co2 puntero donde se devolvera la lectura
 * @return int8_t 0 OK, -1 error
 */
int8_t sunrise_read_co2_unfiltered(uint16_t * co2);

/**
 * @brief Lee si está activada la calibración ABC
 * 
 * @param ABC_status puntero donde devuelve el estado ABC, 0 si está activada 1 desactivada
 * @return int8_t 0 OK, -1 error
 */
int8_t read_ABC_status(uint8_t *ABC_status);

/**
 * @brief Activa la calibración ABC
 * 
 * @return int8_t 0 OK, -1 error
 */
int8_t enable_ABC();

/**
 * @brief Desactiva la calibración ABC
 * 
 * @return int8_t OK, -1 error
 */
int8_t disable_ABC();

/**
 * @brief Lee el estado del sensor
 * 
 * @param mode puntero donde devuelvo el modo, CONTINUO = 1 , SIMPLE = 0.
 * @param period puntero donde se devuelve el período de muestreo en segundos
 * @param number_samples puntero donde se devuelve la cantidad de muestras que se realizan en una medida
 * @return int8_t OK, -1 error
 */
int8_t read_measurement_mode(uint8_t *mode, uint16_t *period, uint16_t *number_samples);

/**
 * @brief Seteo el número de muestras a tomar
 * 
 * @param value_sample numeros de muestras a tomar
 * @return int8_t OK, -1 error
 */
int8_t set_number_samples(uint16_t value_sample);

/**
 * @brief seteo el período de muestreo
 * 
 * @param value_period período de muestreo a configurar
 * @return int8_t OK, -1 error
 */
int8_t set_period(uint16_t value_period);

#endif
