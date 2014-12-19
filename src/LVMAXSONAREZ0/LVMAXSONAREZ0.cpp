#include "LVMAXSONAREZ0.h"

float LVMAXSONAREZ0::read_distance_by_mode() {
	if (mode == ANALOG) {
		float float_val = SAL_analog_read(output_pin);
		float meters = float_val * v_cc * analog_factor;
		return meters;
	} else if (mode == PWM) {
		float float_val = SAL_analog_read(output_pin);
		float meters = float_val * v_cc * pwm_factor;
		return meters;
	} else { // SERIAL mode or typo - either is bad
		SAL_printf("You don goofed\n");
		return 0.0f;
	}
}

LVMAXSONAREZ0::LVMAXSONAREZ0(uint8_t output_pin_assignment, 
		uint8_t enable_pin_assignment, uint8_t output_mode, float v_in) {
	output_pin = output_pin_assignment;
	enable_pin = enable_pin_assignment;
	mode = output_mode;
	v_cc = v_in;
	analog_factor = 1.0f / (v_cc / 512.0f / 0.0254f); // 1 divided by volts per meter
	pwm_factor = 1.0f / 5787.40157f; // 1 divded by microsecond per meter
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
	for (i_bucket = 0; i_bucket < n_thresholds; ++i_bucket) {
		if (analog_reading > thresholds[i_bucket]) {
			++bucket;
			continue;
		} else {
			return bucket;
		}
	}
}

void LVMAXSONAREZ0::power_down() {
	SAL_digital_write(enable_pin, 0);
}

void LVMAXSONAREZ0::power_normal() {
	SAL_digital_write(enable_pin, 1);
	SAL_delay_us(20);
}
