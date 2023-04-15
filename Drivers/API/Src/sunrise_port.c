#include "sht4x_port.h"
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include <stdint.h>
#include <stdbool.h>

I2C_HandleTypeDef *p_hi2c_sunrise;

/*
 *HAL_OK       = 0x00U,
  HAL_ERROR    = 0x01U,
  HAL_BUSY     = 0x02U,
  HAL_TIMEOUT  = 0x03U
 *
 *
 */
void sunrise_init_port(void* p_i2c){
	p_hi2c_sunrise = (I2C_HandleTypeDef*)p_i2c;
}

int8_t sunrise_write(uint16_t address, uint8_t* data, uint16_t data_length){

	  HAL_StatusTypeDef err = HAL_I2C_Master_Transmit (p_hi2c_sunrise, (uint16_t)(address<<1), data, data_length,15);
	  if(err == HAL_OK){
		  return 0;
	  }else{
		  return -1;
	  }
}

int8_t sunrise_read(uint16_t address, uint8_t* data, uint16_t data_length){

	HAL_StatusTypeDef err = HAL_I2C_Master_Receive(p_hi2c_sunrise, (uint16_t)(address<<1), data, data_length, 15);
	  if(err == HAL_OK){
			  return 0;
		  }else{
			  return -1;
		  }
}

void sunrise_sleep(uint16_t time_delay){
	HAL_Delay(time_delay);
}

void sunrise_print(uint8_t* data){
}

