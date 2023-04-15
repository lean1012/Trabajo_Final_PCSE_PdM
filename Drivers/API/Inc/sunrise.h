#ifndef __API_sunrise_H
#define __API_sunrise_H
#include <stdint.h>
#include <stdbool.h>

#define SUNRISE_I2C_ADDRESS 0x68

#define SUNRISE_SERIAL_NUMBER 0xA7

int8_t sunrise_read_co2(uint16_t * co2);
int8_t sunrise_init(void * i2c_init);


#endif
