#ifndef SAL_HPP
#define SAL_HPP

uint8_t SAL_i2c_read(uint8_t slave_address, uint8_t reg_address);

void SAL_i2c_write(uint8_t slave_address, uint8_t reg_address, uint8_t data);

#endif // SAL_HPP
