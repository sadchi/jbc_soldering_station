#include "init.h"
#include "stm32f1xx_hal.h"

unsigned int get_thermo_setting_val(void) {
    unsigned int adc_val;
    // HAL_ADC_Start(&hadc1);
    // HAL_ADC_PollForConversion(&hadc1, 100);
    adc_val = HAL_ADC_GetValue(&hadc1);
    // HAL_ADC_Stop(&hadc1);
    return adc_val;
}


