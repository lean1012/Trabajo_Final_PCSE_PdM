#include "sht4x_port.h"
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include <stdint.h>
#include <stdbool.h>

I2C_HandleTypeDef *p_hi2c;

/*
 *HAL_OK       = 0x00U,
  HAL_ERROR    = 0x01U,
  HAL_BUSY     = 0x02U,
  HAL_TIMEOUT  = 0x03U
 *
 *
 */
void sht4x_init_port(void* p_i2c){
	p_hi2c = (I2C_HandleTypeDef*)p_i2c;
}

int8_t sht4x_write(uint8_t address, uint8_t* data, uint16_t data_length){

	  HAL_StatusTypeDef err = HAL_I2C_Master_Transmit (p_hi2c, (uint16_t)(address<<1), data, data_length,HAL_MAX_DELAY);
	  if(err == HAL_OK){
		  return 0;
	  }else{
		  return -1;
	  }
}

int8_t sht4x_read(uint8_t address, uint8_t* data, uint16_t data_length){

	HAL_StatusTypeDef err = HAL_I2C_Master_Receive (p_hi2c, (uint16_t)(address<<1), data, data_length, HAL_MAX_DELAY);
	  if(err == HAL_OK){
			  return 0;
		  }else{
			  return -1;
		  }
}

void sht4x_sleep(uint16_t time_delay){
	HAL_Delay(time_delay);
}

void sht4x_print(uint8_t* data){

}

