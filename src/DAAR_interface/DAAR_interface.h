#ifndef DAAR_INTERFACE_H
#define DAAR_INTERFACE_H

#include <LiquidCrystal.h>
#include "..\LSM9DS0\LSM9DS0.h"
#include "..\GA1A1S202WP\GA1A1S202WP.h"
#include "..\LVMAXSONAREZ0\LVMAXSONAREZ0.h"

#define LIGHT_OUTPUT_PIN		A1
#define DISTANCE_OUTPUT_PIN		A0
#define DISTANCE_ENABLE_PIN		2

#define DRIFT_NONE	0
#define DRIFT_LEFT	1
#define DRIFT_RIGHT	2

struct DisplayInfo_t {
	uint8_t light_on;
	uint8_t distance_on;
	uint8_t drift;
	float current_speed;
	float speed_limit;
};

void setup_hardware(LSM9DS0* imu, GA1A1S202WP* light, LVMAXSONAREZ0* distance,
	FGPMMOPA6H* gps, LiquidCrystal* lcd);

#endif // DAAR_INTERFACE_H
