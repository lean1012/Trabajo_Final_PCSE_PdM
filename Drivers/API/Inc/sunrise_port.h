/*
 * sunrise_port.h
 *
 *  Created on: Abr 2, 2023
 *      Author: leandro
 */

#ifndef __sunrise_port_H
#define __sunrise_port_H


/**
 * @brief realiza una copia de la direccion a la configuracion i2c de configuración
 *
 * @param p_i2c puntero a la configuración i2c
 * @return int8_t 0 OK, -1 error
 */
void sunrise_init_port(void* p_i2c);

/**
 * @brief Funcion que permite enviar por I2C
 *
 * @param address direccion del sensor sunrise
 * @param data puntero a los datos a enviar
 * @param data_length largo de los datos a enviar
 * @return int8_t retorna 0 OK -1 error
 */
int8_t sunrise_write(uint16_t address, const uint8_t* data, uint16_t data_length);

/**
 * @brief Funcion que permite leer por I2C
 *
 * @param address direccion dsht4xel sensor sunrise
 * @param data puntero para guardar los datos a recibir
 * @param data_length largo de los datos a enviar
 * @return int8_t retorna 0 OK -1 error
 */
int8_t sunrise_read(uint16_t address, const uint8_t* data, uint16_t data_length);

/**
 * @brief delay bloqueante
 *
 * @param time_delay tiempo de espera en milisegundos
 */
int8_t sunrise_sleep(uint8_t* data);

/**
 * @brief Escritura en consola por medio de UART
 *
 * @param data puntero los datos a enviar, este debe terminar con /0
 */
void sunrise_print(uint8_t* data, uint16_t size);


#endif
