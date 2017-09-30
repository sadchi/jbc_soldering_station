#include "init.h"
#include "stm32f1xx_hal.h"


void tm1637_clk_high(void) {
    HAL_GPIO_WritePin(TM1637_CLK_GPIO_Port, TM1637_CLK_Pin, SET);
}

void tm1637_clk_low(void) {
    HAL_GPIO_WritePin(TM1637_CLK_GPIO_Port, TM1637_CLK_Pin, RESET);
}

void tm1637_dio_high(void) {
    HAL_GPIO_WritePin(TM1637_IO_GPIO_Port, TM1637_IO_Pin, SET);
}

void tm1637_dio_low(void) {
    HAL_GPIO_WritePin(TM1637_IO_GPIO_Port, TM1637_IO_Pin, RESET);
}

