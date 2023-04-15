/*
 * API_uart.h
 *
 *  Created on: Apr 3, 2023
 *      Author: leandro
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

#include <stdio.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include <stdbool.h>

typedef bool bool_t;
/*Inicialización de UART,devuelve true: si la inicialización es exitosa,
 *false: si la inicialización no es exitosa.
 */
bool_t uartInit();
/*
 * Envia un string por UART. El string que se desea enviar debe terminar con caracter ‘\0’
 */
void uartSendString(uint8_t * pstring);
/*
 * Enviar un string por UART. Recibe un puntero a un string que se desea enviar por la UART y un entero con la cantidad de caracteres que debe enviar
 */
void uartSendStringSize(uint8_t * pstring, uint16_t size);

/*
 * Enviar un string por UART. Recibe un puntero a un string donde se desea alojar el mensaje recibido y un entero con la cantidad
 * de caracteres que debe guardar
 */
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);

#endif /* API_INC_API_UART_H_ */


