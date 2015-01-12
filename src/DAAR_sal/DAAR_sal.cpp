#include "DAAR_sal.h"

uint8_t SAL_i2c_read(uint8_t slave_address, uint8_t reg_address) {
	Wire.beginTransmission(slave_address);
	Wire.write(reg_address);
	volatile int wait = 0;
	while (!Wire.available()) {
		++wait;
	}
	uint8_t result = Wire.read();
	Wire.endTransmission();
}

void SAL_i2c_write(uint8_t slave_address, uint8_t reg_address, uint8_t data) {
	Wire.beginTransmission(slave_address);
	Wire.write(reg_address);
	Wire.write(data);
	Wire.endTransmission();
}

float SAL_analog_read(uint8_t pin) {
	uint16_t val = analogRead(pin);
	float float_val = (float)val / 1023.0f;
	return float_val;
}

uint8_t SAL_digital_read(uint8_t pin) {
	uint8_t val = digitalRead(pin);
	return val;
}

void SAL_digital_write(uint8_t pin, uint8_t val) {
	digitalWrite(pin, val ? HIGH : LOW);
}

void SAL_pin_mode(uint8_t pin, uint8_t mode) {
	pinMode(pin, mode);
}

void SAL_delay_us(uint16_t n_delay) {
	delayMicroseconds(n_delay);
}

void SAL_printf(char* msg) {
	Serial.print(msg);
}

uint16_t SAL_serial_available() {
	uint16_t bytes = Serial.available();
	return bytes;
}

void SAL_serial_read(uint8_t* buf, uint16_t n_bytes) {
	Serial.readBytes((char*)buf, n_bytes);
}

uint8_t SAL_serial_read_byte() {
	uint8_t byte = Serial.read();
	return byte;
}

uint8_t SAL_serial_find(uint8_t* target) {
	uint8_t found = (uint8_t)Serial.find((char*)target);
	return found;
}