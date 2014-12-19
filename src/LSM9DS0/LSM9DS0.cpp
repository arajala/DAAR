#include "LSM9DS0.h"

uint16_t LSM9DS0::read_accel_x_raw() {
	uint8_t x_low = SAL_i2c_read(accel_mag_slave_address, (uint8_t)OUT_X_L_A);
	uint8_t x_high = SAL_i2c_read(accel_mag_slave_address, (uint8_t)OUT_X_H_A);
	return (uint16_t)(x_high << 8 | x_low);
}

uint16_t LSM9DS0::read_accel_y_raw() {
	uint8_t y_low = SAL_i2c_read(accel_mag_slave_address, (uint8_t)OUT_Y_L_A);
	uint8_t y_high = SAL_i2c_read(accel_mag_slave_address, (uint8_t)OUT_Y_H_A);
	return (uint16_t)(y_high << 8 | y_low);
}

uint16_t LSM9DS0::read_accel_z_raw() {
	uint8_t z_low = SAL_i2c_read(accel_mag_slave_address, (uint8_t)OUT_Z_L_A);
	uint8_t z_high = SAL_i2c_read(accel_mag_slave_address, (uint8_t)OUT_Z_H_A);
	return (uint16_t)(z_high << 8 | z_low);
}

uint16_t LSM9DS0::read_rot_x_raw() {
	uint8_t x_low = SAL_i2c_read(gyro_slave_address, (uint8_t)OUT_X_L_G);
	uint8_t x_high = SAL_i2c_read(gyro_slave_address, (uint8_t)OUT_X_H_G);
	return (uint16_t)(x_high << 8 | x_low);
}

uint16_t LSM9DS0::read_rot_y_raw() {
	uint8_t y_low = SAL_i2c_read(gyro_slave_address, (uint8_t)OUT_Y_L_G);
	uint8_t y_high = SAL_i2c_read(gyro_slave_address, (uint8_t)OUT_Y_H_G);
	return (uint16_t)(y_high << 8 | y_low);
}

uint16_t LSM9DS0::read_rot_z_raw() {
	uint8_t z_low = SAL_i2c_read(gyro_slave_address, (uint8_t)OUT_Z_L_G);
	uint8_t z_high = SAL_i2c_read(gyro_slave_address, (uint8_t)OUT_Z_H_G);
	return (uint16_t)(z_high << 8 | z_low);
}

uint16_t LSM9DS0::read_mag_x_raw() {
	uint8_t x_low = SAL_i2c_read(accel_mag_slave_address, (uint8_t)OUT_X_L_M);
	uint8_t x_high = SAL_i2c_read(accel_mag_slave_address, (uint8_t)OUT_X_H_M);
	return (uint16_t)(x_high << 8 | x_low);
}

uint16_t LSM9DS0::read_mag_y_raw() {
	uint8_t y_low = SAL_i2c_read(accel_mag_slave_address, (uint8_t)OUT_Y_L_M);
	uint8_t y_high = SAL_i2c_read(accel_mag_slave_address, (uint8_t)OUT_Y_H_M);
	return (uint16_t)(y_high << 8 | y_low);
}

uint16_t LSM9DS0::read_mag_z_raw() {
	uint8_t z_low = SAL_i2c_read(accel_mag_slave_address, (uint8_t)OUT_Z_L_M);
	uint8_t z_high = SAL_i2c_read(accel_mag_slave_address, (uint8_t)OUT_Z_H_M);
	return (uint16_t)(z_high << 8 | z_low);
}

LSM9DS0::LSM9DS0() {
	// Set state
	gyro_slave_address = 0x6A;
	accel_mag_slave_address = 0x1E;

	// Set measurement scales
	set_accel_scale(A_FS_2);
	set_rot_scale(R_FS_2000);
	set_mag_scale(M_FS_2);

	// Set data rates
	set_accel_rate(A_DR_3);
	set_rot_rate(R_DR_95);
	set_mag_rate(M_DR_3);

	// Turn on
	imu_power_normal();
}

void LSM9DS0::set_accel_scale(AccelScale_t scale, uint8_t update) {
	uint8_t ctrl = SAL_i2c_read(accel_mag_slave_address, (uint8_t)CTRL2_AM);
	uint8_t mask = ~(0x7 << 3);
	uint8_t new_ctrl = (ctrl & mask) | ((uint8_t)scale << 3);
	SAL_i2c_write(accel_mag_slave_address, (uint8_t)CTRL2_AM, new_ctrl);
	switch (scale) {
		case A_FS_2:
			a_factor = 2.0f / (float)(2^15);
			break;
		case A_FS_4:
			a_factor = 4.0f / (float)(2^15);
			break;
		case A_FS_6:
			a_factor = 6.0f / (float)(2^15);
			break;
		case A_FS_8:
			a_factor = 8.0f / (float)(2^15);
			break;
		case A_FS_16:
			a_factor = 16.0f / (float)(2^15);
			break;
		default:
			a_factor = 2.0f / (float)(2^15);
	}
	if (update == 1) {
		a_scale = scale;
	}
}

void LSM9DS0::set_rot_scale(RotScale_t scale, uint8_t update) {
	uint8_t ctrl = SAL_i2c_read(gyro_slave_address, (uint8_t)CTRL4_G);
	uint8_t mask = ~(0x3 << 4);
	uint8_t new_ctrl = (ctrl & mask) | ((uint8_t)scale << 4);
	SAL_i2c_write(gyro_slave_address, (uint8_t)CTRL4_G, new_ctrl);
	switch (scale) {
		case R_FS_245:
			r_factor = 245.0f / (float)(2^15);
			break;
		case R_FS_500:
			r_factor = 500.0f / (float)(2^15);
			break;
		case R_FS_2000:
			r_factor = 2000.0f / (float)(2^15);
			break;
		default:
			r_factor = 245.0f / (float)(2^15);
	}
	if (update == 1) {
		r_scale = scale;
	}
}

void LSM9DS0::set_mag_scale(MagScale_t scale, uint8_t update) {
	uint8_t ctrl = SAL_i2c_read(accel_mag_slave_address, (uint8_t)CTRL6_AM);
	uint8_t mask = ~(0x3 << 5);
	uint8_t new_ctrl = (ctrl & mask) | ((uint8_t)scale << 5);
	SAL_i2c_write(accel_mag_slave_address, (uint8_t)CTRL6_AM, new_ctrl);
	switch (scale) {
		case M_FS_2:
			m_factor = 2.0f / (float)(2^15);
			break;
		case M_FS_4:
			m_factor = 4.0f / (float)(2^15);
			break;
		case M_FS_8:
			m_factor = 8.0f / (float)(2^15);
			break;
		case M_FS_12:
			m_factor = 12.0f / (float)(2^15);
			break;
		default:
			m_factor = 2.0f / (float)(2^15);
	}
	if (update == 1) {
		m_scale = scale;
	}
}

void LSM9DS0::set_accel_rate(AccelDataRate_t rate, uint8_t update) {
	uint8_t ctrl = SAL_i2c_read(accel_mag_slave_address, (uint8_t)CTRL1_AM);
	uint8_t mask = ~(0xF << 4);
	uint8_t new_ctrl = (ctrl & mask) | ((uint8_t)rate << 4);
	SAL_i2c_write(accel_mag_slave_address, (uint8_t)CTRL1_AM, new_ctrl);
	if (update == 1) {
		a_rate = rate;
	}
}

void LSM9DS0::set_rot_rate(RotDataRate_t rate, uint8_t update) {
	uint8_t ctrl = SAL_i2c_read(accel_mag_slave_address, (uint8_t)CTRL1_G);
	uint8_t mask = ~(0x3 << 6);
	uint8_t new_ctrl = (ctrl & mask) | ((uint8_t)rate << 6);
	SAL_i2c_write(gyro_slave_address, (uint8_t)CTRL1_G, new_ctrl);
	if (update == 1) {
		r_rate = rate;
	}
}

void LSM9DS0::set_mag_rate(MagDataRate_t rate, uint8_t update) {
	uint8_t ctrl = SAL_i2c_read(accel_mag_slave_address, (uint8_t)CTRL5_AM);
	uint8_t mask = ~(0x7 << 2);
	uint8_t new_ctrl = (ctrl & mask) | ((uint8_t)rate << 2);
	SAL_i2c_write(accel_mag_slave_address, (uint8_t)CTRL5_AM, new_ctrl);
	if (update == 1) {
		m_rate = rate;
	}
}

float LSM9DS0::read_accel_x() {
	int16_t raw_x = (int16_t)read_accel_x_raw();
	return (float)raw_x * a_factor;
}

float LSM9DS0::read_accel_y() {
	int16_t raw_y = (int16_t)read_accel_y_raw();
	return (float)raw_y * a_factor;
}

float LSM9DS0::read_accel_z() {
	int16_t raw_z = (int16_t)read_accel_z_raw();
	return (float)raw_z * a_factor;
}

float LSM9DS0::read_rot_x() {
	int16_t raw_x = (int16_t)read_rot_x_raw();
	return (float)raw_x * r_factor;
}

float LSM9DS0::read_rot_y() {
	int16_t raw_y = (int16_t)read_rot_y_raw();
	return (float)raw_y * r_factor;
}

float LSM9DS0::read_rot_z() {
	int16_t raw_z = (int16_t)read_rot_z_raw();
	return (float)raw_z * r_factor;
}

float LSM9DS0::read_mag_x() {
	int16_t raw_x = (int16_t)read_mag_x_raw();
	return (float)raw_x * m_factor;
}

float LSM9DS0::read_mag_y() {
	int16_t raw_y = (int16_t)read_mag_y_raw();
	return (float)raw_y * m_factor;
}

float LSM9DS0::read_mag_z() {
	int16_t raw_z = (int16_t)read_mag_z_raw();
	return (float)raw_z * m_factor;
}

void LSM9DS0::accel_power_down() {
	uint8_t power_down = 0x00; // power down data rate, everything off
	SAL_i2c_write(accel_mag_slave_address, (uint8_t)CTRL1_AM, power_down);
	a_power = POWER_DOWN;
}

void LSM9DS0::gyro_power_down() {
	uint8_t power_down = 0x00; // lowest rate/bandwidth, everything off
	SAL_i2c_write(gyro_slave_address, (uint8_t)CTRL1_G, power_down);
	r_power = POWER_DOWN;
}

void LSM9DS0::mag_power_down() {
	uint8_t power_down = 0x07; // low-power mode 1, power-down mode on
	SAL_i2c_write(accel_mag_slave_address, (uint8_t)CTRL7_AM, power_down);
	m_power = POWER_DOWN;
}

void LSM9DS0::imu_power_down() {
	accel_power_down();
	gyro_power_down();
	mag_power_down();
}

void LSM9DS0::accel_power_sleep() {
	uint8_t power_sleep = 0x10; // lowest rate/bandwidth, axis enables 0
	SAL_i2c_write(accel_mag_slave_address, (uint8_t)CTRL1_AM, power_sleep);
	a_power = POWER_SLEEP;
}

void LSM9DS0::gyro_power_sleep() {
	uint8_t power_sleep = 0x08; // lowest rate/bandwidth, PD 1, axis enables 0
	SAL_i2c_write(gyro_slave_address, (uint8_t)CTRL1_G, power_sleep);
	r_power = POWER_SLEEP;
}

void LSM9DS0::mag_power_sleep() {
	uint8_t power_sleep = 0x04; // low-power mode 1, continuous mode on
	SAL_i2c_write(accel_mag_slave_address, (uint8_t)CTRL7_AM, power_sleep);
	m_power = POWER_SLEEP;
}

void LSM9DS0::imu_power_sleep() {
	accel_power_sleep();
	gyro_power_sleep();
	mag_power_sleep();
}

void LSM9DS0::accel_power_normal() {
	uint8_t power_normal = 0x17; // lowest rate, everything on
	SAL_i2c_write(accel_mag_slave_address, (uint8_t)CTRL1_AM, power_normal);
	set_accel_scale(a_scale);
	set_accel_rate(a_rate);
	a_power = POWER_NORMAL;
}

void LSM9DS0::gyro_power_normal() {
	uint8_t power_normal = 0x0F; // lowest rate/bandwidth, everything on
	SAL_i2c_write(gyro_slave_address, (uint8_t)CTRL1_G, power_normal);
	set_rot_scale(r_scale);
	set_rot_rate(r_rate);
	r_power = POWER_NORMAL;
}

void LSM9DS0::mag_power_normal() {
	uint8_t power_normal = 0x00; // low-power mode 0, continuous mode on
	SAL_i2c_write(accel_mag_slave_address, (uint8_t)CTRL7_AM, power_normal);
	set_mag_scale(m_scale);
	set_mag_rate(m_rate);
	m_power = POWER_NORMAL;
}

void LSM9DS0::imu_power_normal() {
	accel_power_normal();
	gyro_power_normal();
	mag_power_normal();
}
