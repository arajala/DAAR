#include "FGPMMOPA6H.h"

FGPMMOPA6H::FGPMMOPA6H() {
	current_buf = CURRENT_NONE;
}

void FGPMMOPA6H::serial_event() {
	uint8_t i, k;
	uint8_t this_byte;
	uint16_t n_bytes = SAL_serial_available();
	if (n_bytes >= GPS_RECEIVE_SIZE) {
		while (i++ < n_bytes) {
			this_byte = SAL_serial_read_byte();
			// Serial.print((char)this_byte);
			SAL_delay_us(200);
			switch ((char)this_byte) {
			 case '$':
				char msg_id[5];
				for (k = 0; k < 5; k++) {
					msg_id[k] = SAL_serial_read_byte();
					// Serial.print((char)msg_id[k]);
					SAL_delay_us(500);
				}
				SAL_serial_read_byte(); // comma
				if (!strncmp(msg_id, "GPGGA", 5)) {
					current_buf = CURRENT_GGA;
					i_packet[current_buf] = 0;
				} else if (!strncmp(msg_id, "GPGSA", 5)) {
					current_buf = CURRENT_GSA;
					i_packet[current_buf] = 0;
				} else if (!strncmp(msg_id, "GPGSV", 5)) {
					current_buf = CURRENT_GSV;
					i_packet[current_buf] = 0;
				} else if (!strncmp(msg_id, "GPRMC", 5)) {
					current_buf = CURRENT_RMC;
					i_packet[current_buf] = 0;
				} else if (!strncmp(msg_id, "GPVTG", 5)) {
					current_buf = CURRENT_VTG;
					i_packet[current_buf] = 0;
				} else {
					current_buf = CURRENT_NONE;
					i_packet[current_buf] = 0;
				}
				break;
			 case '\r':
			 	i_packet[current_buf] = 0;
			 	current_buf = CURRENT_NONE;
			 	break;
			 case '\n':
			 	i_packet[current_buf] = 0;
			 	current_buf = CURRENT_NONE;
			 	break;
			 case '*':
			 	i_packet[current_buf] = 0;
			 	current_buf = CURRENT_NONE;
			 	break;
			 default:
			 	packet_buf[current_buf][i_packet[current_buf]] = this_byte;
			 	i_packet[current_buf] += 1;
			 	if (i_packet[current_buf] >= GPS_BUF_SIZE) {
			 		i_packet[current_buf] = 0;
			 		current_buf = CURRENT_NONE;
			 	}
			 	break;
			}
		}
	}
}

float FGPMMOPA6H::read_speed_mph() {
	rmc_t rmc_packet = read_rmc();
	return rmc_packet.speed_knots * 1.15077945f;
}

float FGPMMOPA6H::read_speed_kph() {
	rmc_t rmc_packet = read_rmc();
	return rmc_packet.speed_knots * 1.852f;
}

float FGPMMOPA6H::read_course() {
	rmc_t rmc_packet = read_rmc();
	return rmc_packet.course;
}

float FGPMMOPA6H::read_altitude() {
	gga_t gga_packet = read_gga();
	switch (gga_packet.alt_units) {
		case 'M':
			return gga_packet.altitude;
		default:
			SAL_printf("Altitude error, I only know meters\n");
			return 0.0f;
	}
}

uint8_t* FGPMMOPA6H::read_position() {
	uint8_t position[4];
	rmc_t rmc_packet = read_rmc();
	position[0] = rmc_packet.latitude;
	position[1] = (uint8_t)rmc_packet.north_south;
	position[2] = rmc_packet.longitude;
	position[3] = (uint8_t)rmc_packet.east_west;
	return (uint8_t*)position;
}

uint8_t* FGPMMOPA6H::read_utc_time() {
	uint8_t utc_time[3];
	// rmc_t rmc_packet = read_rmc();
	return (uint8_t*)utc_time;
}

uint8_t* FGPMMOPA6H::read_date() {
	uint8_t date[3];
	// rmc_t rmc_packet = read_rmc();
	return (uint8_t*)date;
}

gga_t FGPMMOPA6H::read_gga() {
	gga_t my_packet;
	return my_packet;
}

gsa_t FGPMMOPA6H::read_gsa() {
	gsa_t my_packet;
	return my_packet;
}

gsv_t FGPMMOPA6H::read_gsv() {
	gsv_t my_packet;
	return my_packet;
}

rmc_t FGPMMOPA6H::read_rmc() {
	uint8_t i, c, offset;

	// for (i = 0; i < GPS_BUF_SIZE; ++i) {
	// 	Serial.print((char)packet_buf[CURRENT_RMC][i]);
	// }
	// Serial.println("");

	// Date
	uint8_t time_buf[10];
	for (i = 0; i < 10; ++i) {
		c = packet_buf[CURRENT_RMC][i];
		if (i != 6 && c >= 48 && c <= 57) { // is digit
			time_buf[i] = c;
		} else if (i == 6 && c == 46) {
			time_buf[i] = c;
		} else {
			return curr_rmc;			
		}
	}
	curr_rmc.utc_time = atof((char*)time_buf);

	// Comma
	c = packet_buf[CURRENT_RMC][i++];
	if (c != 44) {
		return curr_rmc;
	}

	// Status
	c = packet_buf[CURRENT_RMC][i++];
	if (c == 65 || c == 86) {
		curr_rmc.status = (char)c;
	} else {
		return curr_rmc;
	}

	// Comma
	c = packet_buf[CURRENT_RMC][i++];
	if (c != 44) {
		return curr_rmc;
	}

	// Latitude
	uint8_t lat_buf[9];
	offset = i;
	for (i = offset; i < offset+9; ++i) {
		c = packet_buf[CURRENT_RMC][i];
		if (i != offset+4 && c >= 48 && c <= 57) {
			lat_buf[i-offset] = c;
		} else if (i == offset+4 && c == 46) {
			lat_buf[i-offset] = c;
		} else {
			return curr_rmc;
		}
	}
	curr_rmc.latitude = atof((char*)lat_buf);

	// Comma
	c = packet_buf[CURRENT_RMC][i++];
	if (c != 44) {
		return curr_rmc;
	}

	// North-south indicator
	c = packet_buf[CURRENT_RMC][i++];
	if (c == 78 || c == 83) {
		curr_rmc.north_south = (char)c;
	} else {
		return curr_rmc;
	}

	// Comma
	c = packet_buf[CURRENT_RMC][i++];
	if (c != 44) {
		return curr_rmc;
	}

	// Longitude
	uint8_t long_buf[10];
	offset = i;
	for (i = offset; i < offset+10; ++i) {
		c = packet_buf[CURRENT_RMC][i];
		if (i != offset+5 && c >= 48 && c <= 57) {
			long_buf[i-offset] = c;
		} else if (i == offset+5 && c == 46) {
			long_buf[i-offset] = c;
		} else {
			return curr_rmc;
		}
	}
	curr_rmc.longitude = atof((char*)long_buf);

	// Comma
	c = packet_buf[CURRENT_RMC][i++];
	if (c != 44) {
		// Serial.print("Invalid comma: ");
		// Serial.println((char)c);
		return curr_rmc;
	}

	// East-west indicator
	c = packet_buf[CURRENT_RMC][i++];
	if (c == 69 || c == 87) {
		curr_rmc.east_west = (char)c;
	} else {
		// Serial.print("Invalid E/W: ");
		// Serial.println((char)c);
		return curr_rmc;
	}

	// Comma
	c = packet_buf[CURRENT_RMC][i++];
	if (c != 44) {
		return curr_rmc;
	}

	// Speed
	uint8_t speed_buf[7];
	offset = i;
	for (i = offset; i < offset+7; ++i) {
		c = packet_buf[CURRENT_RMC][i];
		if ((c >= 48 && c <= 57) || (c == 46)) {
			speed_buf[i-offset] = c;
		} else if (c == 44) {
			break;
		} else {
			return curr_rmc;
		}
	}
	curr_rmc.speed_knots = atof((char*)speed_buf);

	// Comma
	c = packet_buf[CURRENT_RMC][i++];
	if (c != 44) {
		return curr_rmc;
	}

	// Course
	uint8_t course_buf[6];
	offset = i;
	for (i = offset; i < offset+6; ++i) {
		c = packet_buf[CURRENT_RMC][i];
		if ((c >= 48 && c <= 57) || (c == 46)) {
			course_buf[i-offset] = c;
		} else if (c == 44) {
			break;
		} else {
			return curr_rmc;
		}
	}
	curr_rmc.course = atof((char*)course_buf);

	// Comma
	c = packet_buf[CURRENT_RMC][i++];
	if (c != 44) {
		return curr_rmc;
	}

	// Date
	uint8_t date_buf[6];
	offset = i;
	for (i = offset; i < offset+6; ++i) {
		c = packet_buf[CURRENT_RMC][i];
		if (c >= 48 && c <= 57) {
			date_buf[i-offset] = c;
		} else {
			return curr_rmc;
		}
	}
	curr_rmc.date = atoi((char*)date_buf);

	// Comma
	c = packet_buf[CURRENT_RMC][i++];
	if (c != 44) {
		return curr_rmc;
	}

	// Comma - Magnetic variation value
	c = packet_buf[CURRENT_RMC][i++];
	if (c != 44) {
		return curr_rmc;
	}

	// Comma - Magnetic variation direction
	c = packet_buf[CURRENT_RMC][i++];
	if (c != 44) {
		return curr_rmc;
	}

	// Mode
	c = packet_buf[CURRENT_RMC][i++];
	if (c == 65 || c == 68 || c == 69 || c == 78) {
		curr_rmc.mode = (char)c;
	} else {
		return curr_rmc;
	}

	return curr_rmc;
}

vtg_t FGPMMOPA6H::read_vtg() {
	uint8_t i, c, offset;

	// Course 1
	uint8_t course_buf[6];
	for (i = 0; i < 6; ++i) {
		c = packet_buf[CURRENT_VTG][i];
		if ((c >= 48 && c <= 57) || (c == 46)) {
			course_buf[i] = c;
		} else {
			return curr_vtg;
		}
	}
	curr_vtg.course_1 = atof((char*)course_buf);

	// Comma
	c = packet_buf[CURRENT_VTG][i++];
	if (c != 44) {
		return curr_vtg;
	}

	// Reference 1
	c = packet_buf[CURRENT_VTG][i++];
	if (c == 84 || c == 70) {
		curr_vtg.reference_1 = (char)c;
	} else {
		return curr_vtg;
	}

	// Comma
	c = packet_buf[CURRENT_VTG][i++];
	if (c != 44) {
		return curr_vtg;
	}

	// Comma - course 2
	c = packet_buf[CURRENT_VTG][i++];
	if (c != 44) {
		return curr_vtg;
	}

	// Reference 2
	c = packet_buf[CURRENT_VTG][i++];
	if (c == 77) {
		curr_vtg.reference_2 = (char)c;
	} else {
		return curr_vtg;
	}

	// Comma
	c = packet_buf[CURRENT_VTG][i++];
	if (c != 44) {
		return curr_vtg;
	}

	// Speed 1
	uint8_t speed1_buf[7];
	offset = i;
	for (i = offset; i < offset+7; ++i) {
		c = packet_buf[CURRENT_VTG][i];
		if ((c >= 48 && c <= 57) || (c == 46)) {
			speed1_buf[i-offset] = c;
		} else if (c == 44) {
			break;
		} else {
			return curr_vtg;
		}
	}
	curr_vtg.speed_1 = atof((char*)speed1_buf);

	// Comma
	c = packet_buf[CURRENT_VTG][i++];
	if (c != 44) {
		return curr_vtg;
	}

	// Units 1
	c = packet_buf[CURRENT_VTG][i++];
	if (c == 78) {
		curr_vtg.speed_1_units = (char)c;
	} else {
		return curr_vtg;
	}

	// Comma
	c = packet_buf[CURRENT_VTG][i++];
	if (c != 44) {
		return curr_vtg;
	}

	// Speed 2
	uint8_t speed2_buf[8];
	offset = i;
	for (i = offset; i < offset+8; ++i) {
		c = packet_buf[CURRENT_VTG][i];
		if ((c >= 48 && c <= 57) || (c == 46)) {
			speed2_buf[i-offset] = c;
		} else if (c == 44) {
			break;
		} else {
			return curr_vtg;
		}
	}
	curr_vtg.speed_2 = atof((char*)speed2_buf);

	// Comma
	c = packet_buf[CURRENT_VTG][i++];
	if (c != 44) {
		return curr_vtg;
	}

	// Units 2
	c = packet_buf[CURRENT_VTG][i++];
	if (c == 75) {
		curr_vtg.speed_2_units = (char)c;
	} else {
		return curr_vtg;
	}

	// Comma
	c = packet_buf[CURRENT_VTG][i++];
	if (c != 44) {
		return curr_vtg;
	}

	// Mode
	c = packet_buf[CURRENT_VTG][i++];
	if (c == 65 || c == 68 || c == 69 || c == 78) {
		curr_vtg.mode = (char)c;
	} else {
		return curr_vtg;
	}

	return curr_vtg;
}
