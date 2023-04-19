/*
 * API_dobleclick.h
 *
 *  Created on: Apr 13, 2023
 *      Author: leandro
 */

#ifndef API_INC_API_DOUBLECLICK_H_
#define API_INC_API_DOUBLECLICK_H_

//include uint8_t
#include <stdint.h>


/**
 * @brief Incializa la máquina de estados en WAIT_1CLICK
 * 
 */
void clickStateFSM_init();

/**
 * @brief Máquina de estados para agregar la opción de doble click
 * La máquina comienza esperando el primer click, una vez sucedido empieza a correr un
 * un timer no bloqueante. Al finalizar se verifica si se dió otro click, en caso que si
 * el resultado es doble click, caso contrario un solo click
 * 
 */
void clickFSM_update();

/**
 * @brief Pregunta si se ha realizo un click y cúantos
 * 
 * @return uint8_t retorna 0 si no se ha realizado ningun click, 1 si se realizó 1 click y 2 si se realizaron 2 click
 */
uint8_t click();


#endif /* API_INC_API_DOUBLECLICK_H_ */
