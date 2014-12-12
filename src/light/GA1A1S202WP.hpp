#ifndef GA1A1S202WP_H
#define GA1A1S202WP_H

#include "standards.hpp"
#include "comms.hpp"

class GA1A1S202WP {

 private:

 	// Analog pin assignment
 	uint8_t pin;

 	// Ambient light threshold (increasing order)
 	float* thresholds;
 	uint8_t n_thresholds;

 public:

 	// === Setup methods ===

 	// Constructor, sets analog pin
 	GA1A1S202WP(uint8_t pin_assignment);
 	// Sets threshold buckets
 	void set_thresholds(float* new_thresholds, uint8_t n_new_thresholds);

 	// === Data methods ===

 	// Raw ambient light reading
 	float read_light_analog();
 	// Ambient light separated into arbitrary discrete values
 	// Returns 0 for less than thresholds[0], 1 for thresholds[1], ...
 	uint8_t read_light_digital();

};

#endif // GA1A1S202WP_H
