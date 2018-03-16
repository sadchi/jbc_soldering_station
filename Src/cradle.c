#include "FreeRTOS.h"
#include "init.h"
#include "stm32f1xx_hal.h"
#include "thermo_controller.h"
#include "timers.h"

#define DEBOUNCE_MS 10

static volatile TimerHandle_t debounce=NULL;
BaseType_t xHigherPriorityTaskWoken = pdTRUE;


unsigned char is_parked(void) {
    return HAL_GPIO_ReadPin(EXT_INT_GPIO_Port, EXT_INT_Pin) == GPIO_PIN_RESET? 1:0;
}

void cradle_callback(TimerHandle_t timer) {
    if(is_parked()) {
        iron_parked();
    } else {
        iron_left_parking();
    }

}

void cradle_init(void) {
    debounce=xTimerCreate("", pdMS_TO_TICKS(DEBOUNCE_MS), pdFALSE, NULL, cradle_callback);
}

void EXTI2_IRQHandler(void) {
    xTimerStartFromISR(debounce, &xHigherPriorityTaskWoken);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
}


