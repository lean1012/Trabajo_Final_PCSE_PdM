/*
 * API_debounce.c
 *
 *  Created on: Mar 28, 2023
 *      Author: leandro
 */

#include "API_debounce.h"
#include "API_delay.h"
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

typedef enum {
	IDLE,
	READY,
} clickState_t;

static delay_t delay_click;
static clickState_t actual_state_click;

/*
 * Incializa la máquina de estados en BUTTON_UP
 */
void clickStateFSM_init() {
	actual_state_click = IDLE;
	delayInit(&delay_click, 500);
}
/*
 * Máquina de estados para resolver los problemas de rebote del botón
 * mediante Software usando retardo no bloqueante definido en DEBOUNCE_TIME
 */

static uint8_t click_count = 0;
void clickFSM_update() {

	switch (actual_state_click) {

	case IDLE:
		if (readKey()) {
			actual_state_click = READY;
			delayRead(&delay_click); //disparo el timer
		}
		break;

	case READY:

		if (delayRead(&delay_click)) {
			if (readKey()) {

				click_count = 2;
			} else {

				click_count = 1;

			}
			actual_state_click = IDLE;
		}

		break;

	default:
		actual_state_click = IDLE;
		break;

	}
}

uint8_t click() {
	uint8_t aux = click_count;
	click_count = 0;
	return aux;
}

