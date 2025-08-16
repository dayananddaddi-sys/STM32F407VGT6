#include "ssd1306.h"
#include "ssd1306.h"
#include "ssd1306.h"
#include "ssd1306.h"
#include "font.h"       // font data (we'll add later)
#include "i2c_driver.h" // low-level I2C write function

static uint8_t screen_buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

static void ssd1306_send_command(uint8_t command) {
    uint8_t data[2] = {0x00, command};  // 0x00 for command
    i2c_write(SSD1306_I2C_ADDR, data, 2);
}

void ssd1306_init(void) {
    ssd1306_send_command(0xAE); // Display off

    ssd1306_send_command(0xD5); // Set display clock
    ssd1306_send_command(0x80);

    ssd1306_send_command(0xA8); // Set multiplex
    ssd1306_send_command(0x3F);

    ssd1306_send_command(0xD3); // Display offset
    ssd1306_send_command(0x00);

    ssd1306_send_command(0x40); // Start line = 0

    ssd1306_send_command(0x8D); // Charge pump
    ssd1306_send_command(0x14);

    ssd1306_send_command(0x20); // Memory mode
    ssd1306_send_command(0x00);

    ssd1306_send_command(0xA1); // Segment remap

    ssd1306_send_command(0xC8); // COM output scan direction

    ssd1306_send_command(0xDA); // COM pins
    ssd1306_send_command(0x12);

    ssd1306_send_command(0x81); // Contrast
    ssd1306_send_command(0xCF);

    ssd1306_send_command(0xD9); // Pre-charge
    ssd1306_send_command(0xF1);

    ssd1306_send_command(0xDB); // VCOM detect
    ssd1306_send_command(0x40);

    ssd1306_send_command(0xA4); // Resume to RAM content
    ssd1306_send_command(0xA6); // Normal display

    ssd1306_send_command(0xAF); // Display on

    ssd1306_clear();
    ssd1306_update_screen();
}

void ssd1306_clear(void) {
    for (int i = 0; i < sizeof(screen_buffer); i++) {
        screen_buffer[i] = 0x00;
    }
    ssd1306_update_screen();
}

void ssd1306_update_screen(void) {
    for (uint8_t page = 0; page < 8; page++) {
        ssd1306_send_command(0xB0 + page);
        ssd1306_send_command(0x00);
        ssd1306_send_command(0x10);

        uint8_t data[SSD1306_WIDTH + 1];
        data[0] = 0x40;

        for (uint8_t i = 0; i < SSD1306_WIDTH; i++) {
            data[i + 1] = screen_buffer[SSD1306_WIDTH * page + i];
        }
        i2c_write(SSD1306_I2C_ADDR, data, SSD1306_WIDTH + 1);
    }
}

void ssd1306_draw_pixel(uint8_t x, uint8_t y, bool color) {
    if (x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT)
        return;

    if (color)
        screen_buffer[x + (y / 8) * SSD1306_WIDTH] |= (1 << (y % 8));
    else
        screen_buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
}

void ssd1306_set_cursor(uint8_t x, uint8_t y) {
    cursor_x = x;
    cursor_y = y;
}

void ssd1306_write_char(char ch) {
    if (ch < 32 || ch > 127) ch = '?';
    for (uint8_t i = 0; i < 5; i++) {
        uint8_t line = font5x7[ch - 32][i];
        for (uint8_t j = 0; j < 8; j++) {
            ssd1306_draw_pixel(cursor_x + i, cursor_y + j, (line >> j) & 1);
        }
    }
    cursor_x += 6;
}

void ssd1306_write_string(const char* str) {
    while (*str) {
        ssd1306_write_char(*str++);
    }
}
