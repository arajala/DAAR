#ifndef LVMAXSONAREZ0_H
#define LVMAXSONAREZ0_H

#include "..\DAAR_common\DAAR_common.h"
#include "..\DAAR_sal\DAAR_sal.h"

// Output mode options
#define ANALOG 	1
#define PWM		2
#define SERIAL	3

class LVMAXSONAREZ0 {

 private:

 	// Voltage supply
 	float v_cc;

 	// Distance conversion factors
 	float analog_factor;
 	float pwm_factor;

 	// Output mode
 	uint8_t mode;

 	// Pin assignments
 	uint8_t output_pin;
 	uint8_t enable_pin;

 	// Distance thresholds (increasing order)
 	float* thresholds;
 	uint8_t n_thresholds;

 	// Data reading abstraction
 	float read_distance_by_mode();

 public:

 	// === Setup methods ===

 	// Constructor, sets output pin and enable pin
 	LVMAXSONAREZ0(uint8_t output_pin_assignment,
 			uint8_t enable_pin_assignment, uint8_t output_mode, float v_in);
 	// Sets threshold buckets at any time
 	void set_thresholds(float* new_thresholds, uint8_t n_new_thresholds);

 	// === Data methods ===

 	// Raw distance reading (PWM or Analog mode)
 	float read_distance_analog();
 	// Distance separated into arbitrary discrete values
 	// Returns 0 for less than thresholds[0], 1 for thresholds[1], ...
 	uint8_t read_distance_digital();

 	// === Power methods ===

 	// Power down the device to stop ranging
 	void power_down();
 	// Return device to normal ranging operation
 	// Causes 20 us delay
 	// Warning: causes recalibration
 	void power_normal();

};

#endif // LVMAXSONAREZ0_H
