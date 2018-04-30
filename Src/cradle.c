#include "FreeRTOS.h"
#include "init.h"
#include "stm32f1xx_hal.h"
#include "thermo_controller.h"
#include "timers.h"



unsigned char is_parked(void) {
    return HAL_GPIO_ReadPin(EXT_INT_GPIO_Port, EXT_INT_Pin) == GPIO_PIN_RESET? 1:0;
}


void EXTI2_IRQHandler(void) {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
}


