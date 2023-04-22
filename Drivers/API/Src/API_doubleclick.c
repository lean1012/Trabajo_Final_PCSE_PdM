/*
 * API_debounce.c
 *
 *  Created on: Mar 28, 2023
 *      Author: leandro
 */

#include "API_delay.h"
#include "API_doubleclick.h"
#include "API_debounce.h"
/*Tiempo de espera para considerar próximo click como doble*/
#define WAIT_SECOND_CLICK 1000

typedef enum {
	WAIT_1CLICK, WAIT_2CLICK,
} clickState_t;

static delay_t delay_click;
static clickState_t actual_state_click;
static uint8_t click_count = 0;

/**
 * @brief Incializa la máquina de estados en WAIT_1CLICK
 * 
 */
void clickStateFSM_init() {
	actual_state_click = WAIT_1CLICK;
	delayInit(&delay_click, WAIT_SECOND_CLICK);
}

/**
 * @brief Máquina de estados para agregar la opción de doble click
 * La máquina comienza esperando el primer click, una vez sucedido empieza a correr un
 * un timer no bloqueante. Al finalizar se verifica si se dió otro click, en caso que si
 * el resultado es doble click, caso contrario un solo click
 */
void clickFSM_update() {

	switch (actual_state_click) {

	case WAIT_1CLICK:
		if (readKey()) {
			actual_state_click = WAIT_2CLICK;
			delayRead(&delay_click); //disparo el timer
		}
		break;

	case WAIT_2CLICK:
		if (readKey()) {
			click_count = 2;
			actual_state_click = WAIT_1CLICK;
		}else{
			if (delayRead(&delay_click)) {
				click_count = 1;
				actual_state_click = WAIT_1CLICK;
			}
		}
		break;
	default:
		actual_state_click = WAIT_1CLICK;
		break;

	}
}
/**
 * @brief Pregunta si se ha realizo un click y cúantos
 * 
 * @return uint8_t retorna 0 si no se ha realizado ningun click, 1 si se realizó 1 click y 2 si se realizaron 2 click
 */
uint8_t click() {
	// click solamente vale 0, 1 o 2, caso contrario devuelvo 0.
	if(click_count <0 || click_count >2){
		click_count = 0;
	}
	uint8_t aux = click_count;
	click_count = 0;
	return aux;
}

