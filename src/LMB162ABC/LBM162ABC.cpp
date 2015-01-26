#include "LBM162ABC.h"

uint8_t LBM162ABC::read_bf_addr() {
	uint8_t dummy;
	return dummy;
}

void LBM162ABC::send_command(uint8_t command) {
	uint8_t i;
	for (i = 0; i < (bits_8 ? 8 : 4); ++i) {
		SAL_pin_mode(DB_pins[i], SAL_OUTPUT);
	}
	if (bits_8) {
		for (i = 0; i < 8; ++i) {
			SAL_digital_write(DB_pins[i], (command >> i) & 0x01);
		}
		enable();
	} else {
		for (i = 0; i < 4; ++i) {
			SAL_digital_write(DB_pins[i], (command >> i) & 0x01);
		}
		enable();
		for (i = 0; i < 4; ++i) {
			SAL_digital_write(DB_pins[i], ((command << 4) >> i) & 0x01);
		}
		enable();
	}
}

void LBM162ABC::write_data(uint8_t data) {
	SAL_digital_write(RS_pin, 1);
	SAL_digital_write(RW_pin, 0);
	send_command(data);
}

uint8_t LBM162ABC::read_data() {
	uint8_t dummy;
	return dummy;
}

void LBM162ABC::enable() {
	SAL_digital_write(EN_pin, 1);
	SAL_delay_us(1);
	SAL_digital_write(EN_pin, 0);
	SAL_delay_us(150);
}

void LBM162ABC::init(uint8_t set_bits_8) {
	SAL_delay_us(1000*50);
	SAL_digital_write(RS_pin, 0);
	SAL_digital_write(RW_pin, 0);
	send_command(0x30);
	SAL_delay_us(1000*5);
	send_command(0x30);
	SAL_delay_us(150);
	send_command(0x30);
	if (set_bits_8) {
		send_command(0x38);
	} else {
		send_command(0x04);
		bits_8 = set_bits_8;
		send_command(0x28);
	}
	send_command(0x08);
	send_command(0x01);
	send_command(0x06);
}

LBM162ABC::LBM162ABC(uint8_t RS_assign, uint8_t RW_assign, uint8_t EN_assign, uint8_t set_bits_8) {
	RS_pin = RS_assign;
	RW_pin = RW_assign;
	EN_pin = EN_assign;
	SAL_pin_mode(RS_pin, SAL_OUTPUT);
	SAL_pin_mode(RW_pin, SAL_OUTPUT);
	SAL_pin_mode(EN_pin, SAL_OUTPUT);
	bits_8 = 1;
	init(set_bits_8);
}

void LBM162ABC::set_data_pins(uint8_t DB_assign[8]) {
	uint8_t i;
	for (i = 0; i < 8; ++i) {
		DB_pins[i] = DB_assign[i];
	}
}

void LBM162ABC::set_auto_shift(uint8_t shift, uint8_t inc) {
	SAL_digital_write(RS_pin, 0);
	SAL_digital_write(RW_pin, 0);
	send_command(0x04 | ((inc & 0x01) << 1) | (shift & 0x01));
}

void LBM162ABC::display_on() {
	SAL_digital_write(RS_pin, 0);
	SAL_digital_write(RW_pin, 0);
	send_command(0x0C);
}

void LBM162ABC::display_off() {
	SAL_digital_write(RS_pin, 0);
	SAL_digital_write(RW_pin, 0);
	send_command(0x08);
}

void LBM162ABC::cursor_on() {
	SAL_digital_write(RS_pin, 0);
	SAL_digital_write(RW_pin, 0);
	send_command(0x0E);
}

void LBM162ABC::cursor_off() {
	display_on();
}

void LBM162ABC::cursor_blink_on() {
	SAL_digital_write(RS_pin, 0);
	SAL_digital_write(RW_pin, 0);
	send_command(0x0F);
}

void LBM162ABC::cursor_blink_off() {
	cursor_on();
}

void LBM162ABC::set_mode(uint8_t set_bits_8, uint8_t lines_2, uint8_t font_5x11) {
	bits_8 = set_bits_8 & 0x01;
	SAL_digital_write(RS_pin, 0);
	SAL_digital_write(RW_pin, 0);
	send_command(0x20 | (bits_8 << 4) | ((lines_2 & 0x01) << 3) | ((font_5x11 & 0x01) << 2));
}

void LBM162ABC::create_character(uint8_t code, uint8_t pattern[8]) {
	uint8_t i;
	SAL_digital_write(RS_pin, 0);
	SAL_digital_write(RW_pin, 0);
	send_command(0x40 | (code & 0x07));
	SAL_digital_write(RS_pin, 1);
	for (i = 0; i < 8; ++i) {
		send_command(pattern[i]);
	}
	display_clear();
}

void LBM162ABC::set_cursor(uint8_t line, uint8_t col) {
	uint8_t addr;
	addr = 0x40 * line + col;
	SAL_digital_write(RS_pin, 0);
	SAL_digital_write(RW_pin, 0);
	send_command(0x80 | addr);
}

void LBM162ABC::shift_screen_right(uint8_t n) {
	uint8_t i;
	SAL_digital_write(RS_pin, 0);
	SAL_digital_write(RW_pin, 0);
	for (i = 0; i < n; ++i) {
		send_command(0x1C);
	}
}

void LBM162ABC::shift_screen_left(uint8_t n) {
	uint8_t i;
	SAL_digital_write(RS_pin, 0);
	SAL_digital_write(RW_pin, 0);
	for (i = 0; i < n; ++i) {
		send_command(0x18);
	}
}

void LBM162ABC::shift_cursor_right(uint8_t n) {
	uint8_t i;
	SAL_digital_write(RS_pin, 0);
	SAL_digital_write(RW_pin, 0);
	for (i = 0; i < n; ++i) {
		send_command(0x14);
	}
}

void LBM162ABC::shift_cursor_left(uint8_t n) {
	uint8_t i;
	SAL_digital_write(RS_pin, 0);
	SAL_digital_write(RW_pin, 0);
	for (i = 0; i < n; ++i) {
		send_command(0x10);
	}
}

void LBM162ABC::display_msg(char* msg) {
	uint8_t i, len, len_line_1, len_line_2;
	len = strlen(msg);
	if (len > 32) {
		len = 32;
	}
	if (len > 16) {
		len_line_1 = 16;
		len_line_2 = len - len_line_1;
	} else {
		len_line_1 = len;
		len_line_2 = 0;
	}
	set_cursor(0, 0);
	for (i = 0; i < len_line_1; ++i) {
		write_data(msg[i]);
	}
	set_cursor(1, 0);
	for (i = 0; i < len_line_2; ++i) {
		write_data(msg[i+16]);
	}
}

void LBM162ABC::display_msg_at_position(char* msg, uint8_t line, uint8_t col) {
	uint8_t i, len, len_line_1, len_line_2, col_1, col_2;
	len = strlen(msg);
	if (len > 32 - line*16 - col) {
		len = line*16 - col;
	}
	if (line == 1) {
		len_line_1 = 0;
		len_line_2 = len;
		col_1 = 0;
		col_2 = col;
	} else if (len > 16 - col) {
		len_line_1 = 16 - col;
		len_line_2 = len - len_line_1;
		col_1 = col;
		col_2 = 0;
	} else {
		len_line_1 = len;
		len_line_2 = 0;
		col_1 = col;
		col_2 = 0;
	}
	set_cursor(0, col_1);
	for (i = 0; i < len_line_1; ++i) {
		write_data(msg[i]);
	}
	set_cursor(1, col_2);
	for (i = 0; i < len_line_2; ++i) {
		write_data(msg[i+len_line_1]);
	}
}

void LBM162ABC::display_clear() {
	SAL_digital_write(RS_pin, 0);
	SAL_digital_write(RW_pin, 0);
	send_command(0x01);
}

void LBM162ABC::display_clear_line(uint8_t line) {
	uint8_t i;
	set_cursor(line, 0);
	for (i = 0; i < 16; ++i) {
		write_data((uint8_t)' ');
	}
}

void LBM162ABC::display_clear_position(uint8_t line, uint8_t col) {
	set_cursor(line, col);
	write_data((uint8_t)' ');
}
