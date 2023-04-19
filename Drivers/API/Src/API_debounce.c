/*
 * API_debounce.c
 *
 *  Created on: Mar 28, 2023
 *      Author: leandro
 */


#include "API_debounce.h"
#include "API_delay.h"
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

/*Estados para resolver el rebote del botón
 * ver https://docs.google.com/presentation/d/19-_3vYQWjhZznpSB0fJqiIfhxkiMoVlrsakPLtWlMUE/edit#slide=id.g10118059909_0_38
 */
typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
} debounceState_t;


static delay_t delay;
static debounceState_t actual_state;
static bool_t key_press;

/*
 * Incializa la máquina de estados en BUTTON_UP
 */
void debounceFSM_init(){
	actual_state = BUTTON_UP;
	delayInit(&delay, DEBOUNCE_TIME);
}
/*
 * Máquina de estados para resolver los problemas de rebote del botón
 * mediante Software usando retardo no bloqueante definido en DEBOUNCE_TIME
 */
void debounceFSM_update(){

	switch(actual_state){

		case BUTTON_UP:
			if(BSP_PB_GetState(BUTTON_USER)){
				actual_state = BUTTON_FALLING;
				delayRead(&delay); //disparo el timer para irme al proximo estado con el timer activo;
			}else{
				actual_state = BUTTON_UP;
			}

		break;
		case BUTTON_FALLING:
			//espero 40milisegundos y pregunto como está el botón
			if(delayRead(&delay)){
				if(BSP_PB_GetState(BUTTON_USER)){
					actual_state = BUTTON_DOWN;
					key_press = true;
				}else{
					actual_state = BUTTON_UP;
				}
			}
		break;
		case BUTTON_DOWN:
			if(BSP_PB_GetState(BUTTON_USER)){
				actual_state = BUTTON_DOWN;
			}else{
				actual_state = BUTTON_RAISING;
				delayRead(&delay); //disparo el timer para irme al proximo estado con el timer activo;
			}
		break;
		case BUTTON_RAISING:
			//espero 40milisegundos y pregunto como está el botón
			if(delayRead(&delay)){
				if(BSP_PB_GetState(BUTTON_USER)){
					actual_state = BUTTON_DOWN;
				}else{
					actual_state = BUTTON_UP;
				}
			}
		break;
		default:
			actual_state=BUTTON_UP;
		break;

	}

}

bool_t readKey(){
	if(key_press){
		key_press = false;
		return true;
	}else{
		return false;
	}
}

