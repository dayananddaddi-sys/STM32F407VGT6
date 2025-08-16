#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include <stdint.h>

void i2c_write(uint8_t addr, uint8_t* data, uint16_t len);

#endif
