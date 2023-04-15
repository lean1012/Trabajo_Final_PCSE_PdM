#ifndef __API_port_H
#define __API_port_H

#include <stdint.h>
#include <stdbool.h>

void sht4x_init_port(void* p_i2c);
int8_t sht4x_write(uint8_t address, uint8_t* data, uint16_t data_length);
int8_t sht4x_read(uint8_t address, uint8_t* data, uint16_t data_length);
void sht4x_sleep(uint16_t time_delay);
void sht4x_print(uint8_t* data);



#endif
