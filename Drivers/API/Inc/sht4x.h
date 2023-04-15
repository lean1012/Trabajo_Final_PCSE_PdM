#ifndef __API_sht4x_H
#define __API_sht4x_H
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Lecutra del numero de seriel del sensor
 * 
 * @param p_serial_number puntero donde se devolvera el número de serie
 * @return int8_t 0 OK, -1 error
 */
int8_t sht4x_read_serial_number(uint16_t * p_serial_number);
/**
 * @brief Inicializa el driver sht4x
 * 
 * @param i2c_init Puntero a la configuración i2c
 * @return int8_t 0 OK, -1 error
 */
int8_t sht4x_init(void * i2c_init);
/**
 * @brief Lectura de temperatura y humedad con presición baja
 * 
 * @param temperature puntero a donde se devolvera la temperatura
 * @param humidity puntero a donde se devolvera la temperatura
 * @return int8_t 0 OK, -1 error
 */
int8_t sht4x_temp_hum_low_presition(uint16_t * temperature, uint16_t *humidity);
/**
 * @brief Lectura de temperatura y humedad con presición media
 * 
 * @param temperature puntero a donde se devolvera la temperatura
 * @param humidity puntero a donde se devolvera la temperatura
 * @return int8_t 0 OK, -1 error
 */
int8_t sht4x_temp_hum_medium_presition(uint16_t * temperature, uint16_t* humidity);
/**
 * @brief Lectura de temperatura y humedad con presición alta
 * 
 * @param temperature puntero a donde se devolvera la temperatura
 * @param humidity puntero a donde se devolvera la temperatura
 * @return int8_t 0 OK, -1 error
 */
int8_t sht4x_temp_hum_high_presition(uint16_t * temperature, uint16_t* humidity);

#endif
