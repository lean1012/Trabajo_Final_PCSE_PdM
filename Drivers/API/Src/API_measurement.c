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


typedef enum {
	IDLE, MEASURMENT, WAIT, CONFIGURATION,
} measurment_state_t;

/*Estructura donde se almancena la última muestra tomada*/
static struct air air_p;

delay_t measurement_period;
uint16_t period_init_ms = 500;

#define ZERO_CLICK 0
#define ONE_CLICK 1
#define TWO_CLICK 2

static measurment_state_t actual_state;
/*Imprimo los valores de Co2, humedad y temperatura en consola separados con un tabulador, al final se agrega salto de linea*/
static void print_measurement() {
	char buffer[10];
	uint8_t text_co2[] = "CO2: ";
	uartSendString(text_co2);
	itoa(air_p.co2, buffer, 10);   
	uartSendString((uint8_t*) buffer);
	memset(buffer, 0, sizeof(buffer));

	uint8_t tab[] = "\t";
	uartSendString(tab);

	uint8_t text_temp[] = "Temp: ";
	uartSendString(text_temp);
	itoa(air_p.temp, buffer, 10);   
	uartSendString((uint8_t*) buffer);
	memset(buffer, 0, sizeof(buffer));

	uartSendString(tab);

	uint8_t text_hum[] = "Hum: ";
	uartSendString(text_hum);
	itoa(air_p.hum, buffer, 10);   
	uartSendString((uint8_t*) buffer);
	memset(buffer, 0, sizeof(buffer));

	uint8_t text_fin[] = "\r\n";
	uartSendString(text_fin);

}
/*Imprimo en consola que entre en modo configuración*/
static void print_text_conf() {
	uint8_t send_text[] =
			"Configuración... Ingrese la frecuencia de muestreo con el siguiente formato MXX, donde XX es la frecuencia en segundos\r\n";
	uartSendString(send_text);
}
/*Imprimo en consola que comienzo a tomar muestras*/
static void print_text_meansurement() {
	uint8_t send_text[] = "Midiendo... \r\n";
	uartSendString(send_text);
}
/*Imprimo en consola que entre en pausa*/
static void print_text_idle() {
	uint8_t send_text[] = "Pausa... \r\n";
	uartSendString(send_text);
}
/*Modifico el período de muestreo por medio de la consola*/
static void frequency_configuration() {
	uint8_t conf[5];
	memset(conf, 0, sizeof(conf));
	uartReceiveStringSize(conf, 6);
	/*Si se cumple que el comando ingresado es distinto de nulo realizo un control
	 * de los parametros que comienzo con M y termino con /r
	 * Luego convertir los caracteres XX a números (uso atoi)*/
	if (strcmp((char*) conf, (char*) "\000\000\000\000\000")) {
		if (conf[0] == 'M') {
			uint8_t text_err[] =
					"Se ha cambiado la frecuencia correctamente\r\n";
			uartSendString(text_err);
			uint8_t datos[5];
			memcpy(datos, &conf[1], 2);
			uint16_t val = 1000 * atoi((char*) datos);
			delayWrite(&measurement_period, val);
		} else {
			uint8_t text_err[] = "Comando no válido\r\n";
			uartSendString(text_err);
		}
	}

}

void measurement_FSM_init() {
	actual_state = WAIT;
	print_text_meansurement();
	delayInit(&measurement_period, period_init_ms);
	delayRead(&measurement_period);
}

/* ESTADO IDLE: no realiza mediciones ni configuraciones. 1 click empieza a medir, 2 clicks va a configuración
 * ESTADO WAIT: empezo a tomar medidas, espera X segundos para luego ir al estado MEASURMENT y tomar una medida 1 click va a IDLE
 * 2 click va a configuración
 * ESTADO MEASURMENT: toma una medida de co2, humedad y temperatura e imprime por UART. Luego vuelve a WAIT
 * ESTADO CONFIGURATION: modifica el período en el cual se toman muestra, se ingresa por UART mediante el siguiente formato MXX 
 * donde XX son los segundos. Para volver a tomar medidas se realiza 1 o 2 click
 */
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

		if (click() == 0) {
			frequency_configuration();
		} else {
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

