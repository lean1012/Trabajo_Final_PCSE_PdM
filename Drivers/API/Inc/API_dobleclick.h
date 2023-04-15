/*
 * API_dobleclick.h
 *
 *  Created on: Apr 13, 2023
 *      Author: leandro
 */

#ifndef API_INC_API_DOBLECLICK_H_
#define API_INC_API_DOBLECLICK_H_



//include uint8_t
#include <stdint.h>
// include bool
#include <stdbool.h>

typedef bool bool_t;

/*
 * Incializa la máquina de estados en BUTTON_UP
 */
void clickStateFSM_init();

/*
 * Máquina de estados para resolver los problemas de rebote del botón
 * mediante Software usando retardo no bloqueante definido en DEBOUNCE_TIME
 */
void clickFSM_update();


uint8_t click();


#endif /* API_INC_API_DOBLECLICK_H_ */
