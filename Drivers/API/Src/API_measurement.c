/*
 * API_mensurement.c
 *
 *  Created on: Apr 12, 2023
 *      Author: leandro
 */

#include "API_measurement.h"
#include "API_delay.h"
#include "sht4x.h"
#include "sunrise.h"
#include "API_debounce.h"
#include "API_dobleclick.h"
#include "API_uart.h"
#include <stdlib.h>


typedef enum {
	IDLE, MEASURMENT, CONFIGURATION,
} measurment_state_t;

delay_t measurement_period;
uint16_t period_ms = 500;

struct air {
	uint16_t co2;
	uint16_t temp;
	uint16_t hum;
};

struct air air_p;

static measurment_state_t actual_state;

void measurement_FSM_init();		// debe cargar el estado inicial
void measurement_FSM_update();	// debe leer las entradas, resolver la lógica de
// transición de estados y actualizar las salidas

//delayInit(&led_seq_delay[i],led_delay_seq[i]);
void measurement_FSM_init() {
	actual_state = MEASURMENT;
	delayInit(&measurement_period, period_ms);
	delayRead(&measurement_period);
}

void measurement() {

	sunrise_read_co2(&air_p.co2);
	sht4x_temp_hum_low_presition(&air_p.temp, &air_p.hum);

}

void print_measurement() {

	char buffer[10];

	uint8_t text_co2[] = "CO2: ";
	uartSendString(text_co2);
	itoa(air_p.co2,buffer,10);   // here 2 means binary
	uartSendString(buffer);
	memset(buffer,0, sizeof(buffer));

	uint8_t tab[] = "\t";
	uartSendString(tab);

	uint8_t text_temp[] = "Temp: ";
	uartSendString(text_temp);
	itoa(air_p.temp,buffer,10);   // here 2 means binary
	uartSendString(buffer);
	memset(buffer,0, sizeof(buffer));

	uartSendString(tab);

	uint8_t text_hum[] = "Hum: ";
	uartSendString(text_hum);
	itoa(air_p.hum,buffer,10);   // here 2 means binary
	uartSendString(buffer);
	memset(buffer,0, sizeof(buffer));

	uint8_t text_fin[] = "\r\n";
	uartSendString(text_fin);



}

void measurement_FSM_update() {
	switch (actual_state) {

	case IDLE:
		switch (click()) {
		case 0:
			actual_state = IDLE;
			break;
		case 1:
			actual_state = MEASURMENT;
			break;
		case 2:
			actual_state = CONFIGURATION;
			break;
		}
		break;

	case MEASURMENT:
		if (delayRead(&measurement_period)) {
			measurement();
			print_measurement();
			delayRead(&measurement_period); //disparo el timer
		}
		switch (click()) {
		case 0:
			actual_state = MEASURMENT;
			break;
		case 1:
			actual_state = IDLE;
			break;
		case 2:
			actual_state = CONFIGURATION;
			break;
		}
		break;

	case CONFIGURATION:
		if (click() != 0) {
			actual_state = MEASURMENT;
		}
		break;

	default:
		actual_state = IDLE;
		break;

	}
}

void configuration_FSM() {

	switch (actual_state) {

	case IDLE:
		//nothing
		break;

	case MEASURMENT:

		break;

	case CONFIGURATION:
		//configuration_FSM();
		break;

	default:
		actual_state = IDLE;
		break;

	}
}
