#ifndef FGPMMOPA6H_H
#define FGPMMOPA6H_H

#include "..\DAAR_common\DAAR_common.h"
#include "..\DAAR_sal\DAAR_sal.h"

#define GPS_RECEIVE_SIZE	30

#define GPS_BUF_SIZE	82

#define CURRENT_GGA		0
#define CURRENT_GSA		1
#define CURRENT_GSV		2
#define CURRENT_RMC		3
#define CURRENT_VTG		4
#define CURRENT_NONE	5

#define GGA_FIX_NONE				0
#define GGA_FIX_GPS					1
#define GGA_FIX_DIFFERENTIAL_GPS	2

#define GSA_MODE_MANUAL	M
#define GSA_MODE_AUTO	A
#define GSA_NO_FIX	1
#define GSA_2D_FIX	2
#define GSA_3D_FIX	3

#define RMC_STATUS_VALID	A
#define RMC_STATUS_INVALID	V
#define RMC_MODE_AUTO			A
#define RMC_MODE_DIFFERENTIAL	D
#define RMC_MODE_ESTIMATED		E

#define VTG_MODE_AUTO			A
#define VTG_MODE_DIFFERENTIAL	D
#define VTG_MODE_ESTIMATED		E

// === Data types ===

// GGA
struct gga_t {
	float utc_time;
	float latitude;
	char north_south;
	float longitude;
	char east_west;
	uint8_t fix;
	uint8_t n_satellites;
	float hdop;
	float altitude;
	char alt_units;
	float geoidal_sep;
	char geo_units;
};
// GSA
struct gsa_t {
	char mode_1;
	uint8_t mode_2;
	uint8_t n_satellites[12];
	float pdop;
	float hdop;
	float vdop;
};
// GSV
struct gsv_t {
	uint8_t n_messages;
	uint8_t message_num;
	uint8_t n_satellites;
	uint8_t satellite_id[4];
	uint8_t elevation[4];
	uint8_t azimuth[4];
	uint8_t snr[4];
};
// RMC
struct rmc_t {
	float utc_time;
	char status;
	float latitude;
	char north_south;
	float longitude;
	char east_west;
	float speed_knots;
	float course;
	uint32_t date;
	float mag_var_val;
	char mag_var_dir;
	char mode;
};
// VTG
struct vtg_t {
	float course_1;
	char reference_1;
	float course_2;
	char reference_2;
	float speed_1;
	char speed_1_units;
	float speed_2;
	char speed_2_units;
	char mode;
};

class FGPMMOPA6H {

 private:

 	// === Data storage ===

 	// All-purpose serial buffer
 	uint8_t serial_buf[GPS_BUF_SIZE];
 	// Identifier for current buffer
 	uint8_t current_buf;
 	// Packet buffers
 	uint8_t packet_buf[6][GPS_BUF_SIZE];
 	uint8_t i_packet[6];
 	// Current packet data
 	gga_t curr_gga;
 	gsa_t curr_gsa;
 	gsv_t curr_gsv;
 	rmc_t curr_rmc;
 	vtg_t curr_vtg;

 public:

 	// === Constructor ===

 	FGPMMOPA6H();

 	// === Data methods ===

 	// Serial available callback
 	void serial_event();

 	// Read specific data
 	float read_speed_mph();
 	float read_speed_kph();
 	float read_course();
 	float read_altitude();
 	uint8_t* read_position();
 	uint8_t* read_utc_time();
 	uint8_t* read_date();

 	// === Packet methods ===

 	// Packet for time, position, and fix type data
 	gga_t read_gga();
 	// Packet for GPS receiver operating mode, active satellites 
 	// used in the position solution, and DOP values
 	gsa_t read_gsa();
	// Packet for the number of GPS satellites in view, satellite
 	// ID numbers, elevation, azimuth, and SNR values
 	gsv_t read_gsv();
 	// Packet for time, date, position, course, and speed data
 	// Recommended Minimum Navigation Information
 	rmc_t read_rmc();
 	// Packet for course and speed information relative to ground
 	vtg_t read_vtg();

};

#endif // FGPMMOPA6H_H
