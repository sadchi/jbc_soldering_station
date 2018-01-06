#include "buzzer.h"
#include "cmsis_os.h"
#include "freertos.h"
#include "task.h"
#include "init.h"


static void thermo_controller_task(void* params) {
    while(1) {
        
        // buzzer_start();
        HAL_GPIO_WritePin(TEMP_STAB_LED_GPIO_Port, TEMP_STAB_LED_Pin, RESET);
        HAL_GPIO_WritePin(GET_TEMP_LED_GPIO_Port, GET_TEMP_LED_Pin, SET);
        buzz();
        osDelay(3000);
        
        HAL_GPIO_WritePin(TEMP_STAB_LED_GPIO_Port, TEMP_STAB_LED_Pin, SET);
        buzz_x2();
        osDelay(3000);
        HAL_GPIO_WritePin(GET_TEMP_LED_GPIO_Port, GET_TEMP_LED_Pin, RESET);
        osDelay(3000);
    }
}

void thermo_controller_init() {
    xTaskCreate(thermo_controller_task, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);
}

