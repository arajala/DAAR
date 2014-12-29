#include "DAAR_interface.h"

void setup_hardware(LSM9DS0* imu, GA1A1S202WP* light, LVMAXSONAREZ0* distance) {
	
	// === IMU setup ===

	// Set measurement scales
	imu->set_accel_scale(imu->A_FS_2);
	imu->set_rot_scale(imu->R_FS_2000);
	imu->set_mag_scale(imu->M_FS_2);

	// Set update rates
	imu->set_accel_rate(imu->A_DR_3);
	imu->set_rot_rate(imu->R_DR_95);
	imu->set_mag_rate(imu->M_DR_3);

	// Initialize into lowest power modes
	imu->accel_power_down();
	imu->gyro_power_down();
	imu->mag_power_down();

	// === Light sensor setup ===

	// === Distance sensor setup ===

	// Initialize into lowest power mode
	distance->power_down();

}
