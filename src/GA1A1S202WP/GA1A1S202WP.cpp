#include "GA1A1S202WP.h"

GA1A1S202WP::GA1A1S202WP(uint8_t pin_assignment) {
	pin = pin_assignment;
}

void GA1A1S202WP::set_thresholds(float* new_thresholds, uint8_t n_new_thresholds) {
	thresholds = new_thresholds;
	n_thresholds = n_new_thresholds;
}

float GA1A1S202WP::read_light_analog() {
	return SAL_analog_read(pin);
}

uint8_t GA1A1S202WP::read_light_digital() {
	float analog_reading = read_light_analog();
	uint8_t i_bucket;
	uint8_t bucket = 0;
	for (i_bucket = 0; i_bucket < n_thresholds; ++i_bucket) {
		if (analog_reading > thresholds[i_bucket]) {
			++bucket;
			continue;
		} else {
			return bucket;
		}
	}
}
