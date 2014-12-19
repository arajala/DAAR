#ifndef DAAR_SAL_H
#define DAAR_SAL_H

#include <Arduino.h>
#include <Wire.h>

uint8_t SAL_i2c_read(uint8_t slave_address, uint8_t reg_address);

void SAL_i2c_write(uint8_t slave_address, uint8_t reg_address, uint8_t data);

float SAL_analog_read(uint8_t pin);

#endif // DAAR_SAL_H
