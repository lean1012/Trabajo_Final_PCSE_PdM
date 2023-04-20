
#include <stdint.h>
#include "sht4x.h"
#include "sht4x_port.h"

#define SHT4X_I2C_ADDRESS 0x44
#define SHT4X_SLEEP 10

//registros sht4x
#define SHT4X_SERIAL_NUMBER 0x89
#define SHT4X_CMD_MEASURE_HPM 0xFD
#define SHT4X_CMD_MEASURE_MPM 0xFD
#define SHT4X_CMD_MEASURE_LPM 0xE0
//tamaño en byte de la respuesta i2c
#define RESPONSE_LENGHT 6


/**
 * @brief Convierte un array de 2 elementos uint_8 en el forma uint_16 usando MSB
 * 
 * @param bytes puntero al inicio del array
 * @return uint16_t valor en 16bits
 */

static uint16_t buffer_to_uint16_t(const uint8_t* bytes) {

    return (uint16_t)bytes[0] << 8 | (uint16_t)bytes[1];
}

/**
 * @brief Convierte los ticks devueltos por el registro de temperatura a un valor de grados celsius
 * 
 * @param bytes ticks
 * @return uint16_t valor de temperatura
 */
static int16_t convert_ticks_to_celsius(uint16_t ticks) {
	/**
	 * Temperature = 175 * S_T / 65535 - 45
	 */
    return ((ticks * 175) / 65535) - 45;
}

/**
 * @brief Convierte los ticks devueltos por el registro de humedad a un valor de grados celsius
 * 
 * @param bytes ticks
 * @return uint16_t valor de humedad
 */
static int16_t convert_ticks_to_percent_rh(uint16_t ticks) {
	/**
	 * Relative Humidity = 125 * (S_RH / 65535) - 6
	 */
    return (((ticks * 125)) / 65535) - 6;
}

/**
 * @brief Lectura de los datos de temperatura y humedad segun la presición indicada. Los datos son devueltos en ticks
 * 
 * @param precision presición a realizar la medida
 * @param temperature_ticks puntero donde se alojará la temperatura en ticks
 * @param humidity_ticks puntero a donde se alojará la humedad en ticks
 * @return int16_t 0 OK, -1 error
 */
static int16_t sht4x_measure_ticks(uint8_t precision, uint16_t* temperature_ticks, uint16_t* humidity_ticks){
	uint8_t buffer[RESPONSE_LENGHT];
	int8_t err;
	buffer[0] = precision;
	err = sht4x_write(SHT4X_I2C_ADDRESS,buffer,1);
	if (err < 0) {
		uint8_t msg[] = "Error en la escritura. \r\n";
		sht4x_print(msg,sizeof(msg));
		return err;
	}
	sht4x_sleep(SHT4X_SLEEP);
	err = sht4x_read(SHT4X_I2C_ADDRESS,buffer,sizeof(buffer));
	if (err < 0) {
		uint8_t msg[] = "Error en la lectura.\r\n";
		sht4x_print(msg,sizeof(msg));
		return err;
	}
	*temperature_ticks = buffer_to_uint16_t(&buffer[0]);
	*humidity_ticks = buffer_to_uint16_t(&buffer[3]);
	//checkeo que los ticks sean mayores que 0
	if(*temperature_ticks == 0 && *humidity_ticks == 0){
		return -1;
	}
	return 0;


}

int8_t sht4x_init(void * i2c_init){
	sht4x_init_port(i2c_init);
	uint16_t serial_number_sht4x = 0;
	if(sht4x_read_serial_number(&serial_number_sht4x)==0){
		if(serial_number_sht4x!=0){
			uint8_t msg[] = "Inicialización correcta del sensor sht4x. \r\n";
			sht4x_print(msg,sizeof(msg));
			return 0;
		}
	}
	uint8_t msg[] = "Error en la inicialización del sensor sht4x. \r\n";
	sht4x_print(msg,sizeof(msg));
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
	sht4x_sleep(SHT4X_SLEEP);
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
	int8_t err = sht4x_measure_ticks(SHT4X_CMD_MEASURE_MPM, &temp_ticks, &hum_ticks);
	if(err<0){
		return err;
	}
	*temperature = convert_ticks_to_celsius(temp_ticks);
	*humidity = convert_ticks_to_percent_rh(hum_ticks);
	return 0;
}

int8_t sht4x_temp_hum_high_presition(uint16_t * temperature, uint16_t* humidity){

	uint16_t temp_ticks = 0;
	uint16_t hum_ticks = 0;
	int8_t err = sht4x_measure_ticks(SHT4X_CMD_MEASURE_HPM, &temp_ticks, &hum_ticks);
	if(err<0){
		return err;
	}
	*temperature = convert_ticks_to_celsius(temp_ticks);
	*humidity = convert_ticks_to_percent_rh(hum_ticks);
	return 0;
}




