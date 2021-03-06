#include "DAAR_interface.h"

void setup_hardware(LSM9DS0* imu, GA1A1S202WP* light, LVMAXSONAREZ0* distance,
	FGPMMOPA6H* gps, LiquidCrystal* lcd) {

	
	// === IMU setup ===

	// // Set measurement scales
	// imu->set_accel_scale(imu->A_FS_2);
	// imu->set_rot_scale(imu->R_FS_2000);
	// imu->set_mag_scale(imu->M_FS_2);

	// // Set update rates
	// imu->set_accel_rate(imu->A_DR_3);
	// imu->set_rot_rate(imu->R_DR_95);
	// imu->set_mag_rate(imu->M_DR_3);

	// // Initialize into lowest power modes
	// imu->accel_power_down();
	// imu->gyro_power_down();
	// imu->mag_power_down();

	// // === Light sensor setup ===

	// // === Distance sensor setup ===

	// // Initialize into lowest power mode
	// distance->power_down();

	// === LCD setup ===
	uint8_t map_light_indicator[8] = {2, 20, 8, 15, 8, 20, 2, 0};
	lcd->createChar(LIGHT_INDICATOR_CODE, map_light_indicator);
	lcd->begin(16, 2);

}

void display(DisplayInfo_t display_info, LiquidCrystal* lcd) {
	static float prev_speed = 0.0f;
	static float prev_target_distance = 0.0f;
	static uint8_t prev_light = 9999;
	static uint8_t init_display = 1;

	if ((prev_speed != display_info.current_speed) || init_display) {
		lcd->setCursor(0, 0);
		lcd->print(display_info.current_speed);
		prev_speed = display_info.current_speed;
	}

	if ((prev_target_distance != display_info.target_distance) || init_display) {
		lcd->setCursor(0, 1);
		lcd->print(display_info.target_distance);
		prev_target_distance = display_info.target_distance;
	}

	if ((prev_light != display_info.light_on) || init_display) {
		lcd->setCursor(15, 1);
		display_info.light_on ? lcd->write((uint8_t)LIGHT_INDICATOR_CODE) : lcd->print(' ');
		prev_light = display_info.light_on;
	}
	
	init_display = 0;

}
