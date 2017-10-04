#include "init.h"


void buzz_init(void) {
    TIM_OC_InitTypeDef sConfigOC;

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 1000;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
}


void buzz_on(void) {
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
}

void buzz_off(void) {
    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
}


