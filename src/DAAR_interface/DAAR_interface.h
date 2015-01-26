#ifndef DAAR_INTERFACE_H
#define DAAR_INTERFACE_H

#include <LiquidCrystal.h>
#include "..\LSM9DS0\LSM9DS0.h"
#include "..\GA1A1S202WP\GA1A1S202WP.h"
#include "..\LVMAXSONAREZ0\LVMAXSONAREZ0.h"
#include "..\FGPMMOPA6H\FGPMMOPA6H.h"

#define LIGHT_INDICATOR_THRESH	0.35
#define LIGHT_OUTPUT_PIN		A0
#define DISTANCE_OUTPUT_PIN		A1
#define DISTANCE_ENABLE_PIN		8

#define LCD_RS_PIN	7
#define LCD_EN_PIN	6
#define LCD_D0_PIN	5
#define LCD_D1_PIN	4
#define LCD_D2_PIN	3
#define LCD_D3_PIN	2

#define LIGHT_INDICATOR_CODE 0x00

#define DRIFT_NONE	0
#define DRIFT_LEFT	1
#define DRIFT_RIGHT	2

struct DisplayInfo_t {
	uint8_t light_on;
	uint8_t distance_on;
	uint8_t drift;
	float target_distance;
	float current_speed;
	float speed_limit;
};

void setup_hardware(LSM9DS0* imu, GA1A1S202WP* light, LVMAXSONAREZ0* distance,
	FGPMMOPA6H* gps, LiquidCrystal* lcd);

void display(DisplayInfo_t display_info, LiquidCrystal* lcd);

#endif // DAAR_INTERFACE_H
