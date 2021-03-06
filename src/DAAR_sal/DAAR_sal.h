#ifndef DAAR_SAL_H
#define DAAR_SAL_H

#include <Arduino.h>
#include <Wire.h>

#define SAL_INPUT	INPUT
#define SAL_OUTPUT	OUTPUT

uint8_t SAL_i2c_read(uint8_t slave_address, uint8_t reg_address);

void SAL_i2c_write(uint8_t slave_address, uint8_t reg_address, uint8_t data);

float SAL_analog_read(uint8_t pin);

uint8_t SAL_digital_read(uint8_t pin);

void SAL_digital_write(uint8_t pin, uint8_t val);

void SAL_pin_mode(uint8_t pin, uint8_t mode);

void SAL_delay_us(uint16_t n_delay);

void SAL_printf(char* msg);

uint16_t SAL_serial_available();

void SAL_serial_read(uint8_t* buf, uint16_t n_bytes);

uint8_t SAL_serial_read_byte();

uint8_t SAL_serial_find(uint8_t* target);

#endif // DAAR_SAL_H
