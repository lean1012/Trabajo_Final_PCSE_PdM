#ifndef __API_delay_H
#define __API_delay_H

//include uint8_t
#include <stdint.h>
// include bool
#include <stdbool.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */


typedef uint32_t tick_t;

typedef bool bool_t;

/*Struct to Non-blocking delays. It requires a previous time variable, duration and if the delay is running*/
typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;

/*
 * @brief Init delay
 * @param [in] delay: pointer to struct delay
 * @param [in] duration: duration in ms
 */
void delayInit( delay_t * delay, tick_t duration );

/*
 * @brief Read a delay to know if the time has passed
 * @param [in] delay: pointer to struct delay
 * @param [in] duration: duration in ms
 * @return true if time ended.
 */
bool_t delayRead( delay_t * delay );

/*
 * @brief Modifies the duration of a delay
 * @param [in] delay: pointer to struct delay
 * @param [in] duration: new duration in ms
 */
void delayWrite( delay_t * delay, tick_t duration );


#endif
