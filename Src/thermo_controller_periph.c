#include "init.h"
#include "stm32f1xx_hal.h"


void heater_on(void) {
    HAL_GPIO_WritePin(HEATER_GPIO_Port, HEATER_Pin, SET);
}

void heater_off(void) {
    HAL_GPIO_WritePin(HEATER_GPIO_Port, HEATER_Pin, RESET);
}

void temp_stab_on(void) {
    HAL_GPIO_WritePin(TEMP_STAB_LED_GPIO_Port, TEMP_STAB_LED_Pin, SET);
}

void temp_stab_off(void) {
    HAL_GPIO_WritePin(TEMP_STAB_LED_GPIO_Port, TEMP_STAB_LED_Pin, RESET);
}

void get_temp_on(void) {
    HAL_GPIO_WritePin(GET_TEMP_LED_GPIO_Port, GET_TEMP_LED_Pin, SET);
}

void get_temp_off(void) {
    HAL_GPIO_WritePin(GET_TEMP_LED_GPIO_Port, GET_TEMP_LED_Pin, RESET);
}

unsigned int get_current_temp_raw(void) {
    unsigned int adc_val;
    HAL_ADC_Start(&hadc2);
    HAL_ADC_PollForConversion(&hadc2, 100);
    adc_val = HAL_ADC_GetValue(&hadc2);
    HAL_ADC_Stop(&hadc2);
    return adc_val;
}

