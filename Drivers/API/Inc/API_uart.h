/*
 * API_uart.h
 *
 *  Created on: Apr 3, 2023
 *      Author: leandro
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

#include <stdio.h>
#include <stdbool.h>

typedef bool bool_t;

/**
 * @brief Incialización de UART
 * 
 * @return bool_t retorna  true: si la inicialización es exitosa
 */
bool_t uartInit();

/**
 * @brief Envia un string por UART. El string que se desea enviar debe terminar con caracter ‘\0’
 * 
 * @param pstring puntero a los datos a enviar, el string debe terminar con '\0’
 */
void uartSendString(uint8_t * pstring);


/**
 * @brief Enviar un string por UART. Recibe un puntero a un string que se desea enviar por la UART y 
 * un entero con la cantidad de caracteres que debe enviar
 * 
 * @param pstring  puntero a los datos a enviar
 * @param size largo del string a enviar
 */
void uartSendStringSize(uint8_t * pstring, uint16_t size);

/*
 * Enviar un string por UART. Recibe un puntero a un string donde se desea alojar el mensaje recibido y un entero con la cantidad
 * de caracteres que debe guardar
 */

/**
 * @brief Recibe un string por UART. 
 * 
 * @param pstring puntero donde se desea alojar el mensaje 
 * @param size entero con la cantidad de caracteres que debe guardar
 */
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);

#endif /* API_INC_API_UART_H_ */


