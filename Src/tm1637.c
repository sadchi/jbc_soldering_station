#include "stm32f1xx_hal.h"
#include "tm1637.h"
#include "tm1637_periph.h"


static const char segment_map[] = {
    0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, // 0-7
    0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, // 8-9, A-F
    0x00
};


static void tm1637_start(void) {
    tm1637_clk_high();
    tm1637_dio_high();
    HAL_Delay(2);
    tm1637_dio_low();
}

static void tm1637_stop(void) {
    tm1637_clk_low();
    HAL_Delay(2);
    tm1637_dio_low();
    HAL_Delay(2);
    tm1637_clk_high();
    HAL_Delay(2);
    tm1637_dio_high();
}

static void tm1637_read_result(void) {
    tm1637_clk_low();
    HAL_Delay(5);
    tm1637_clk_high();
    HAL_Delay(2);
    tm1637_clk_low();
}

void tm1637_write_byte(unsigned char b) {
    for (int i = 0; i < 8; ++i) {
        tm1637_clk_low();
        if (b & 0x01) tm1637_dio_high();
        else tm1637_dio_low();

        HAL_Delay(3);
        b >>= 1;
        tm1637_clk_high();
        HAL_Delay(3);
    }
}

void tm1637_set_brightness(char brightness) {
    tm1637_start();
    tm1637_write_byte(0x87 + brightness);
    tm1637_read_result();
    tm1637_stop();
}

void tm1637_init(void) {
    tm1637_set_brightness(TM1637_BRIGHTNESS);
}

void tm1637_display_dec(int v, int separator) {

    unsigned char digit[4];

    for (int i = 0; i < 4; ++i) {
        digit[i] = segment_map[v % 10];
        if (i == 2 && separator) {
            digit[i] |= 1 << 7;
        }
        v /= 10;
    }

    tm1637_start();
    tm1637_write_byte(0x40);
    tm1637_read_result();
    tm1637_stop();

    tm1637_start();
    tm1637_write_byte(0xc0);
    tm1637_read_result();

    for (int i = 0; i < 4; ++i) {
        tm1637_write_byte(digit[3 - i]);
        tm1637_read_result();
    }

    tm1637_stop();
}

