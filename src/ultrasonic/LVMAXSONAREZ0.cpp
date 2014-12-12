#include "LVMAXSONAREZ0.h"

float LVMAXSONAREZ0::read_distance_by_mode() {
	if (mode == SERIAL) {
		//return SAL_serial_read(pin);
		printf("You don goofed\n");
		return 0.0f;
	} else {
		return SAL_analog_read(pin);
	}
}

LVMAXSONAREZ0::LVMAXSONAREZ0(uint8_t pin_assignment, OutputMode_t output_mode) {
	pin = pin_assignment;
	mode = output_mode;
}

void LVMAXSONAREZ0::set_thresholds(float* new_thresholds, uint8_t n_new_thresholds) {
	thresholds = new_thresholds;
	n_thresholds = n_new_thresholds;
}

float LVMAXSONAREZ0::read_distance_analog() {
	return read_distance_by_mode();
}

uint8_t LVMAXSONAREZ0::read_distance_digital() {
	float analog_reading = read_distance_analog();
	uint8_t i_bucket;
	uint8_t bucket = 0;
	for (i_bucket = 0; i_bucket < n_new_thresholds; ++i) {
		if (analog_reading > thresholds[i_bucket]) {
			++bucket;
			continue;
		} else {
			return bucket;
		}
	}

}
