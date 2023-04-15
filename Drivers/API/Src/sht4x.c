
#include <stdint.h>
#include <stdbool.h>

#include "sht4x.h"
#include "sht4x_port.h"

#define SHT4X_I2C_ADDRESS 0x44
#define SHT4X_SLEEP 100
#define SHT4X_CRC_POLY		0x31
#define SHT4X_CRC_INIT		0xFF
#define STATUS_OK 0
#define STATUS_ERR_BAD_DATA (-1)
#define STATUS_CRC_FAIL (-2)
#define STATUS_UNKNOWN_DEVICE (-3)
#define SHT4X_SERIAL_NUMBER 0x89
#define SHT4X_CMD_MEASURE_HPM 0xFD
#define SHT4X_CMD_MEASURE_MPM 0xFD
#define SHT4X_CMD_MEASURE_LPM 0xE0
#define SHT4X_MEASUREMENT_DURATION_USEC 10000 /* 10ms "high repeatability" */
#define SHT4X_MEASUREMENT_DURATION_LPM_USEC 2500 /* 2.5ms "low repeatability" */

#define RESPONSE_LENGHT 6




static uint16_t buffer_to_uint16_t(const uint8_t* bytes) {

    return (uint16_t)bytes[0] << 8 | (uint16_t)bytes[1];
}

static int16_t convert_ticks_to_celsius(uint16_t ticks) {
	/**
	 * Temperature = 175 * S_T / 65535 - 45
	 */
    return ((ticks * 175) / 65535) - 45;
}

static int16_t convert_ticks_to_percent_rh(uint16_t ticks) {
	/**
	 * Relative Humidity = 125 * (S_RH / 65535) - 6
	 */
    return (((ticks * 125)) / 65535) - 6;
}


static int16_t sht4x_measure_ticks(uint8_t precision, uint16_t* temperature_ticks, uint16_t* humidity_ticks){
	uint8_t buffer[RESPONSE_LENGHT];
	int8_t err;
	buffer[0] = precision;
	err = sht4x_write(SHT4X_I2C_ADDRESS,buffer,1);
	if (err < 0) {
		sht4x_print("Error en la escritura. \n");
		return err;
	}
	sht4x_sleep(100);

	err = sht4x_read(SHT4X_I2C_ADDRESS,buffer,sizeof(buffer));
	if (err < 0) {
		sht4x_print("Error en la lectura.\n");
		return err;
	}


	//uint16_t temp = 0;
	//uint16_t checksum_temp = 0;
	//uint16_t hum = 0;
	//uint16_t checksum_hum = 0;

	*temperature_ticks = buffer_to_uint16_t(&buffer[0]);
	//checksum_temp = buffer[2];
	*humidity_ticks = buffer_to_uint16_t(&buffer[3]);
	//checksum_hum = buffer[5];
	if(*temperature_ticks == 0 && *humidity_ticks == 0){
		return -1;
	}
	return 0;


}

int8_t sht4x_init(void * i2c_init){
	sht4x_init_port(i2c_init);
	uint16_t serial_number_sht4x = 0;
	if(sht4x_read_serial_number(&serial_number_sht4x)){
		if(serial_number_sht4x!=0)
			return 0;
	}
	return -1;
}


int8_t sht4x_read_serial_number(uint16_t * p_serial_number){
	uint8_t buffer[RESPONSE_LENGHT];
	int8_t err;
	buffer[0] = SHT4X_SERIAL_NUMBER;
	err = sht4x_write(SHT4X_I2C_ADDRESS,buffer,1);
	if (err < 0) {
		return err;
	}
	sht4x_sleep(100);
	err = sht4x_read(SHT4X_I2C_ADDRESS,buffer,sizeof(buffer));

	if (err < 0) {
			return err;
	}
	*p_serial_number = buffer[0]*256 + buffer[1];
	return 0;
}



int8_t sht4x_temp_hum_low_presition(uint16_t * temperature, uint16_t* humidity){

	uint16_t temp_ticks = 0;
	uint16_t hum_ticks = 0;
	int8_t err = sht4x_measure_ticks(SHT4X_CMD_MEASURE_LPM, &temp_ticks, &hum_ticks);
	if(err<0){
		return err;
	}
	*temperature = convert_ticks_to_celsius(temp_ticks);
	*humidity = convert_ticks_to_percent_rh(hum_ticks);

	return 0;
}

int8_t sht4x_temp_hum_medium_presition(uint16_t * temperature, uint16_t* humidity){

	uint16_t temp_ticks = 0;
	uint16_t hum_ticks = 0;
	sht4x_measure_ticks(SHT4X_CMD_MEASURE_MPM, &temp_ticks, &hum_ticks);
	*temperature = convert_ticks_to_celsius(temp_ticks);
	*humidity = convert_ticks_to_percent_rh(hum_ticks);

	return 0;
}

int8_t sht4x_temp_hum_high_presition(uint16_t * temperature, uint16_t* humidity){

	uint16_t temp_ticks = 0;
	uint16_t hum_ticks = 0;
	sht4x_measure_ticks(SHT4X_CMD_MEASURE_HPM, &temp_ticks, &hum_ticks);
	*temperature = convert_ticks_to_celsius(temp_ticks);
	*humidity = convert_ticks_to_percent_rh(hum_ticks);

	return 0;
}




