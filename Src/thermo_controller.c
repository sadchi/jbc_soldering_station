#include "buzzer.h"
#include "cmsis_os.h"
#include "config.h"
#include "freertos.h"
#include "init.h"
#include "task.h"
#include "tm1637.h"

#define MEASURE_INTERVAL 100

static TaskHandle_t thermo_controller_handler;

void set_user_temp(unsigned long t) {
    xTaskNotify(thermo_controller_handler, t & 0xFFFF, eSetBits);
}


void set_target_temp(unsigned long t) {
    set_user_temp( t << 16);
}



static void thermo_controller_task(void* params) {
    static unsigned int notification_val;
    static unsigned short user_temp=0, target_temp=150;





    while(1) {

        if (xTaskNotifyWait(0, 0xFFFFFFFF, &notification_val, 0) == pdPASS) {
            user_temp   = (notification_val & 0xFFFF) ? (notification_val & 0xFFFF): user_temp;
            target_temp = (notification_val >> 16) ? (notification_val >> 16)      : target_temp;
        }



#if DEBUG_DISPLAY == THERMO_CONTROLLER_DISPLAY
        tm1637_display_dec(user_temp,0);
#endif

        osDelay(MEASURE_INTERVAL);

        // buzzer_start();
        // HAL_GPIO_WritePin(TEMP_STAB_LED_GPIO_Port, TEMP_STAB_LED_Pin, RESET);
        // HAL_GPIO_WritePin(GET_TEMP_LED_GPIO_Port, GET_TEMP_LED_Pin, SET);
        // buzz();
        // osDelay(3000);

        // HAL_GPIO_WritePin(TEMP_STAB_LED_GPIO_Port, TEMP_STAB_LED_Pin, SET);
        // buzz_x2();
        // osDelay(3000);
        // HAL_GPIO_WritePin(GET_TEMP_LED_GPIO_Port, GET_TEMP_LED_Pin, RESET);
        // osDelay(3000);
    }
}

void thermo_controller_init() {
    xTaskCreate(thermo_controller_task, NULL, configMINIMAL_STACK_SIZE, NULL, 1, &thermo_controller_handler);
}

