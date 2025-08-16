#ifndef SSD1306_H
#define SSD1306_H

#include <stdint.h>
#include <stdbool.h>

#define SSD1306_I2C_ADDR      0x3C
#define SSD1306_WIDTH         128
#define SSD1306_HEIGHT        64

void ssd1306_init(void);
void ssd1306_clear(void);
void ssd1306_update_screen(void);
void ssd1306_draw_pixel(uint8_t x, uint8_t y, bool color);
void ssd1306_set_cursor(uint8_t x, uint8_t y);
void ssd1306_write_char(char ch);
void ssd1306_write_string(const char* str);

#endif
