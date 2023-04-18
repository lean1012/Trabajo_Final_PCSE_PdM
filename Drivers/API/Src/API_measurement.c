/*
 * API_mensurement.c
 *
 *  Created on: Apr 12, 2023
 *      Author: leandro
 */

#include <API_doubleclick.h>
#include "API_measurement.h"
#include "API_delay.h"
#include "API_sensors.h"
#include "API_debounce.h"
#include "API_uart.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

//logica de la aplicación

typedef enum {
	IDLE, MEASURMENT, WAIT, CONFIGURATION,
} measurment_state_t;

static struct air air_p;

delay_t measurement_period;
uint16_t period_ms = 500;

#define ZERO_CLICK 0
#define ONE_CLICK 1
#define TWO_CLICK 2

static measurment_state_t actual_state;

void measurement_FSM_init();		// debe cargar el estado inicial
void measurement_FSM_update();	// debe leer las entradas, resolver la lógica de
// transición de estados y actualizar las salidas

static void configuration_s();

void print_measurement() {

	char buffer[10];

	uint8_t text_co2[] = "CO2: ";
	uartSendString(text_co2);
	itoa(air_p.co2, buffer, 10);   // here 2 means binary
	uartSendString((uint8_t*)buffer);
	memset(buffer, 0, sizeof(buffer));

	uint8_t tab[] = "\t";
	uartSendString(tab);

	uint8_t text_temp[] = "Temp: ";
	uartSendString(text_temp);
	itoa(air_p.temp, buffer, 10);   // here 2 means binary
	uartSendString((uint8_t*)buffer);
	memset(buffer, 0, sizeof(buffer));

	uartSendString(tab);

	uint8_t text_hum[] = "Hum: ";
	uartSendString(text_hum);
	itoa(air_p.hum, buffer, 10);   // here 2 means binary
	uartSendString((uint8_t*)buffer);
	memset(buffer, 0, sizeof(buffer));

	uint8_t text_fin[] = "\r\n";
	uartSendString(text_fin);

}

void print_text_conf() {
	uint8_t send_text[] =
			"Configuración... Ingrese la frecuencia de muestreo en segundos con el siguiente formato MXX\r\n";
	uartSendString(send_text);
}

void print_text_meansurement() {
	uint8_t send_text[] = "Midiendo... \r\n";
	uartSendString(send_text);
}


void measurement_FSM_init() {
	actual_state = WAIT;
	print_text_meansurement();
	delayInit(&measurement_period, period_ms);
	delayRead(&measurement_period);
}


void print_text_idle() {
	uint8_t send_text[] = "Pausa... \r\n";
	uartSendString(send_text);
}

void measurement_FSM_update() {
	switch (actual_state) {

	case IDLE:
		switch (click()) {
		case ZERO_CLICK:
			actual_state = IDLE;
			//no hay salida
			break;
		case ONE_CLICK:
			print_text_meansurement();
			delayRead(&measurement_period); //disparo el timer
			actual_state = WAIT;

			break;
		case TWO_CLICK:
			actual_state = CONFIGURATION;
			print_text_conf();
			break;
		default:
			print_text_idle();
			actual_state = IDLE;
		}
		break;

	case WAIT:
		switch (click()) {
		case ZERO_CLICK:
			if (delayRead(&measurement_period)) {
				measurement(&air_p);
				print_measurement();
				delayRead(&measurement_period); //disparo el timer
			}
			break;
		case ONE_CLICK:
			print_text_idle();
			actual_state = IDLE;
			break;
		case TWO_CLICK:
			print_text_conf();
			actual_state = CONFIGURATION;
			break;
		default:
			print_text_idle();
			actual_state = IDLE;
		}
		break;
	case MEASURMENT:
		actual_state = WAIT;

	case CONFIGURATION:
		configuration_s();
		if (click() != 0) {
			delayRead(&measurement_period); //disparo el timer
			print_text_meansurement();
			actual_state = MEASURMENT;
		}
		break;

	default:
		print_text_idle();
		actual_state = WAIT;
	}
}

static uint8_t datos[5];
void configuration_s() {
	static uint8_t conf[5];
	memset(conf, 0, sizeof(conf));
	uartReceiveStringSize(conf, 5);
	if (strcmp((char*)conf, (char*)"\000\000\000\000\000")) {
		if (conf[0] == 'M') {
			uint8_t text_err[] =
					"Se ha cambiado la frecuencia correctamente\r\n";

			uartSendString(text_err);
			memcpy(datos, &conf[1], 2);
			uint16_t val = 1000*atoi((char*)datos);
			delayWrite(&measurement_period, val);

		} else {
			uint8_t text_err[] = "Comando no válido\r\n";
			uartSendString(text_err);
		}
	}

}
