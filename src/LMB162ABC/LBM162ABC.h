#ifndef LBM162ABC_H
#define LBM162ABC_H

#include "..\DAAR_common\DAAR_common.h"
#include "..\DAAR_sal\DAAR_sal.h"

class LBM162ABC {
 
 private:

	// === Configuration methods ===

	uint8_t bits_8;
	uint8_t RS_pin;
	uint8_t RW_pin;
	uint8_t EN_pin;
	uint8_t DB_pins[8];

 	// Set address in address counters
 	void set_cgram_addr(uint8_t addr);
 	void set_ddram_addr(uint8_t addr);

 	// === Data methods ===

 	// Reads busy flag and current address counter
 	uint8_t read_bf_addr();

 	// Send commands
 	void send_command(uint8_t command);

 	// Writes data to RAM
 	void write_data(uint8_t data);

 	// Reads data to RAM
 	uint8_t read_data();

 	// Complete a transaction and pause
 	void enable();

 	// Write one character to screen at cursor
 	void display_char(char c);

	// Initialization sequence
	void init(uint8_t set_bits_8);

 public:

 	// === Setup methods ===

 	// Constructor
	LBM162ABC(uint8_t RS_assign, uint8_t RW_assign, uint8_t EN_assign, uint8_t set_bits_8);

 	// Set data pin array
 	void set_data_pins(uint8_t DB_assign[8]);

 	// Screen configurtion
 	void set_auto_shift(uint8_t shift, uint8_t inc);
 	void display_on();
 	void display_off();
 	void cursor_on();
 	void cursor_off();
 	void cursor_blink_on();
 	void cursor_blink_off();
 	void set_mode(uint8_t set_bits_8, uint8_t lines_2, uint8_t font_5x11);

 	// Create a custom character
 	void create_character(uint8_t code, uint8_t pattern[8]);

 	// Set the cursor location
 	void set_cursor(uint8_t line, uint8_t col);

 	// === Display methods ===

 	// Shift screen n times
 	void shift_screen_right(uint8_t n);
 	void shift_screen_left(uint8_t n);

 	// Shift cursor n times
 	void shift_cursor_right(uint8_t n);
 	void shift_cursor_left(uint8_t n);

 	// Write buffer to screen, beginning at start, wrapping lines
 	void display_msg(char* msg);

 	// Write message to location
 	void display_msg_at_position(char* msg, uint8_t line, uint8_t col);

 	// Clear entire display
 	void display_clear();

 	// Clear one line
 	void display_clear_line(uint8_t line);

 	// Clear one character at location
 	void display_clear_position(uint8_t line, uint8_t col);

};

#endif // LBM162ABC_H
