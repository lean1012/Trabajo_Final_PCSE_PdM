/*
 * API_sensors.c
 *
 *  Created on: Apr 17, 2023
 *      Author: leandro
 */

#include "API_sensors.h"
#include "sht4x.h"
#include "sunrise.h"
#include "API_uart.h"

void init_sensors(void *i2c_init)
{

	int8_t err = sht4x_init(i2c_init);
	if (err < 0)
	{
		uint8_t msg[] = "Error en la inicialización del sensor sht4x. \r\n";
		uartSendStringSize(msg, sizeof(msg));
	}
	err = sunrise_init(i2c_init);
	if (err < 0)
	{
		uint8_t msg[] = "Error en la inicialización del sensor sunrise. \r\n";
		uartSendStringSize(msg, sizeof(msg));
	}
	// set_period(2);
	// set_number_samples(1);
}

void measurement(struct air *p_air)
{
	// si las lecturas dan con error grabo 0
	int8_t err = sunrise_read_co2_filtered(&p_air->co2);
	if (err < 0)
	{
		p_air->co2 = 0;
	}
	err = sht4x_temp_hum_low_presition(&p_air->temp, &p_air->hum);
	if (err < 0)
	{
		p_air->temp = 0;
		p_air->hum = 0;
	}
}
