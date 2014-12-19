#include "DAAR_sal.h"

uint8_t SAL_i2c_read(uint8_t slave_address, uint8_t reg_address) {
	Wire.beginTransmission(slave_address);
	Wire.send(reg_address);
	volatile int wait = 0;
	while (!Wire.available()) {
		++wait;
	}
	uint8_t result = Wire.read();
	Wire.endTransmission();
}

void SAL_i2c_write(uint8_t slave_address, uint8_t reg_address, uint8_t data) {
	Wire.beginTransmission(slave_addres);
	Wire.send(reg_address);
	Wire.send(data);
	Wire.endTransmission;
}


float SAL_analog_read(uint8_t pin) {
	uint16_t val = analogRead(pin);
	float float_val = (float)val / 1023.0f;
	return float_val;
}
