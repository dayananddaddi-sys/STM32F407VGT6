#include "stm32f4xx_hal.h"

extern I2C_HandleTypeDef hi2c1; // declared in main.c or i2c.c

// Writes data to I2C OLED
void i2c_write(uint8_t addr, uint8_t* data, uint16_t len) {
    HAL_I2C_Master_Transmit(&hi2c1, addr << 1, data, len, HAL_MAX_DELAY);
}
