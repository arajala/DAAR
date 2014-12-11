#ifndef GA1A1S202WP_H
#define GA1A1S202WP_H

#include "standards.hpp"
#include "comms.hpp"

class LightSensor {

 private:

 	// Analog pin assignment
 	uint8_t pin;

 	// Ambient light threshold
 	float threshold;

 public:

 	// === Setup methods ===

 	// Minimum constructor, sets analog pin
 	LightSensor(uint8_t pin_assignment);
 	// Optional constructor, sets analog pin and digital threshold bins
 	LightSensor(uint8_t pin_assignment, float* new_threshold, uint8_t n_thresholds);
 	// Re-sets threshold bins at any time
 	void set_threshold(float* new_threshold, uint8_t n_thresholds);

 	// === Data methods ===

 	// Raw ambient light reading
 	float read_light_analog();
 	// Ambient light separated into discrete values
 	uint8_t read_light_digital();

};

#endif // GA1A1S202WP_H
