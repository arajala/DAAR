#ifndef LSM9DS0_H
#define LSM9DS0_H

#include "..\DAAR_common\DAAR_common.h"
#include "..\DAAR_sal\DAAR_sal.h"

class LSM9DS0 {

 private:

 	// === Registers and addresses ===

 	enum GyroRegister_t {
 		CTRL1_G 	= 0x20,
 		CTRL2_G 	= 0x21,
 		CTRL3_G 	= 0x22,
 		CTRL4_G 	= 0x23,
 		CTRL5_G 	= 0x24,
 		REF_G 		= 0x25,
 		STATUS_G 	= 0x27,
 		OUT_X_L_G 	= 0x28,
 		OUT_X_H_G 	= 0x29,
 		OUT_Y_L_G 	= 0x2A,
 		OUT_Y_H_G 	= 0x2B,
 		OUT_Z_L_G 	= 0x2C,
 		OUT_Z_H_G 	= 0x2D,
 	};
 	uint8_t gyro_slave_address;

 	enum AccelMagRegister_t {
 		STATUS_M 	= 0x07,
 		OUT_X_L_M	= 0x08,
 		OUT_X_H_M	= 0x09,
 		OUT_Y_L_M 	= 0x0A,
 		OUT_Y_H_M 	= 0x0B,
 		OUT_Z_L_M 	= 0x0C,
 		OUT_Z_H_M 	= 0x0D,
 		OFF_X_L_M 	= 0x16,
 		OFF_X_H_M 	= 0x17,
 		OFF_Y_L_M 	= 0x18,
 		OFF_Y_H_M 	= 0x19,
 		OFF_Z_L_M 	= 0x1A,
 		OFF_Z_H_M 	= 0x1B,
 		REF_A_X 	= 0x1C,
 		REF_A_Y 	= 0x1D,
 		REF_A_Z 	= 0x1E,
 		CTRL0_AM 	= 0x1F,
 		CTRL1_AM 	= 0x20,
 		CTRL2_AM 	= 0x21,
 		CTRL3_AM 	= 0x22,
 		CTRL4_AM 	= 0x23,
 		CTRL5_AM 	= 0x24,
 		CTRL6_AM 	= 0x25,
 		CTRL7_AM 	= 0x26,
 		STATUS_A	= 0x27,
 		OUT_X_L_A	= 0x28,
 		OUT_X_H_A	= 0x29,
 		OUT_Y_L_A	= 0x2A,
 		OUT_Y_H_A	= 0x2B,
 		OUT_Z_L_A	= 0x2C,
 		OUT_Z_H_A	= 0x2D
 	};
 	uint8_t accel_mag_slave_address;

 	// === Setup methods ===

 	// Accelerometer
 	enum AccelScale_t {
 		A_FS_2,
 		A_FS_4,
 		A_FS_6,
 		A_FS_8,
 		A_FS_16
 	};
 	AccelScale_t a_scale;
 	float a_factor;

 	enum AccelDataRate_t {
 		A_DR_3,
 		A_DR_6,
 		A_DR_12,
 		A_DR_25,
 		A_DR_50,
 		A_DR_100,
 		A_DR_200,
 		A_DR_400,
 		A_DR_800,
 		A_DR_1600
 	};
 	AccelDataRate_t a_rate;

 	// Gyroscope
 	enum RotScale_t {
 		R_FS_245,
 		R_FS_500,
 		R_FS_2000,
 	};
 	RotScale_t r_scale;
 	float r_factor;

 	enum RotDataRate_t {
 		R_DR_95,
 		R_DR_190,
 		R_DR_380,
 		R_DR_760
 	};
 	RotDataRate_t r_rate;

 	// Magnetometer
 	enum MagScale_t {
 		M_FS_2,
 		M_FS_4,
 		M_FS_8,
 		M_FS_12
 	};
 	MagScale_t m_scale;
 	float m_factor;

 	enum MagDataRate_t {
 		M_DR_3,
 		M_DR_6,
 		M_DR_12,
 		M_DR_25,
 		M_DR_50,
 		M_DR_100
 	};
 	MagDataRate_t m_rate;

 	// === Data methods ===

 	// Reads uncalibrated acceleration from each axis
 	uint16_t read_accel_x_raw();
 	uint16_t read_accel_y_raw();
 	uint16_t read_accel_z_raw();

 	// Reads uncalibrated rotation from each axis
 	uint16_t read_rot_x_raw();
 	uint16_t read_rot_y_raw();
 	uint16_t read_rot_z_raw();

 	// Reads uncalibrated magnetic field strength from each axis
 	uint16_t read_mag_x_raw();
 	uint16_t read_mag_y_raw();
 	uint16_t read_mag_z_raw();

 public:

 	// === Setup methods ===

 	// Constructor
 	LSM9DS0();

 	// Set output scales
 	void set_accel_scale(AccelScale_t scale);
 	void set_rot_scale(RotScale_t scale);
 	void set_mag_scale(MagScale_t scale);

 	// Set data rates
 	void set_accel_rate(AccelDataRate_t rate);
 	void set_rot_rate(RotDataRate_t rate);
 	void set_mag_rate(MagDataRate_t rate);

 	// === Data methods ===

 	// --- Accelerometer ---

 	// Reads acceleration in G's from each axis
 	float read_accel_x();
 	float read_accel_y();
 	float read_accel_z();

 	// --- Gyroscope ---

 	// Reads rotation in DPS from each axis
 	float read_rot_x();
 	float read_rot_y();
 	float read_rot_z();

 	// --- Magnetometer ---

 	// Reads magnetic field strength in Gauss from each axis
 	float read_mag_x();
 	float read_mag_y();
 	float read_mag_z();

 	// === Power methods ===

 	// Turn device off completely
 	void accel_power_down();
 	void gyro_power_down();
 	void mag_power_down();

 	// Puts device in low power mode
 	void accel_power_sleep();
 	void gyro_power_sleep();
 	void mag_power_sleep();

 	// Puts device at full operation power
 	void accel_power_normal();
 	void gyro_power_normal();
 	void mag_power_normal();

};

#endif // LSM9DS0_H
