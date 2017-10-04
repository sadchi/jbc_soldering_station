#include "buzzer.h"
#include "cmsis_os.h"
#include "freertos.h"
#include "task.h"


static void thermo_controller_task(void* params) {
    while(1) {
        buzzer_start();
        osDelay(5000);
        buzzer_stop();
        osDelay(2000);
    }
}

void thermo_controller_init() {
    xTaskCreate(thermo_controller_task, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);
}

