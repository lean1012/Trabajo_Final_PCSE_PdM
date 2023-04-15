/*
 * API_debounce.h
 *
 *  Created on: Mar 28, 2023
 *      Author: leandro
 */

#ifndef __API_debounce_H
#define __API_debounce_H

//include uint8_t
#include <stdint.h>
// include bool
#include <stdbool.h>

typedef bool bool_t;

#define DEBOUNCE_TIME 40
#define DEBOUNCE_TIME_LONG 2000

/*
 * Incializa la máquina de estados en BUTTON_UP
 */
void debounceFSM_init();

/*
 * Máquina de estados para resolver los problemas de rebote del botón
 * mediante Software usando retardo no bloqueante definido en DEBOUNCE_TIME
 */
void debounceFSM_update();

bool_t readKey();

#endif
