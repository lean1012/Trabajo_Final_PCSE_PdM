/*
 * sht4x_port.h
 *
 *  Created on: Abr 2, 2023
 *      Author: leandro
 */

#ifndef __sht4x_port_H
#define __sht4x_port_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief realiza una copia de la direccion a la configuracion i2c de configuración
 *
 * @param p_i2c puntero a la configuración i2c
 * @return int8_t 0 OK, -1 error
 */
void sht4x_init_port(void* p_i2c);
/**
 * @brief Funcion que permite enviar por I2C
 * 
 * @param address direccion del sensor sht4x
 * @param data puntero a los datos a enviar
 * @param data_length largo de los datos a enviar
 * @return int8_t retorna 0 OK -1 error
 */
int8_t sht4x_write(uint8_t address, uint8_t* data, uint16_t data_length);
/**
 * @brief Funcion que permite leer por I2C
 * 
 * @param address direccion del sensor sht4x
 * @param data puntero para guardar los datos a recibir
 * @param data_length largo de los datos a enviar
 * @return int8_t retorna 0 OK -1 error
 */
int8_t sht4x_read(uint8_t address, uint8_t* data, uint16_t data_length);

/**
 * @brief delay bloqueante
 * 
 * @param time_delay tiempo de espera en milisegundos
 */
void sht4x_sleep(uint16_t time_delay);
/**
 * @brief Escritura en consola por medio de UART
 * 
 * @param data puntero los datos a enviar, este debe terminar con /0
 */
void sht4x_print(uint8_t* data, uint16_t size);



#endif
