#include "FGPMMOPA6H.h"

void FGPMMOPA6H::serial_event() {
	uint16_t n_bytes = SAL_serial_available();
	if (n_bytes > GPS_PACKET_SIZE) {
		SAL_serial_read(serial_buf, n_bytes);
	}
}