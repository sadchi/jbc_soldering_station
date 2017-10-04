#include "buzzer_periph.h"
#include "cmsis_os.h"
#include "freertos.h"
#include "task.h"

#define START_BIT 1
#define STOP_BIT  2
#define DURATION_MS 250
#define INTERVAL_MS 2000


static TaskHandle_t buzzer_handler;

static void buzzer_task(void* params);

void buzzer_init() {
    buzz_init();
    xTaskCreate(buzzer_task, NULL, configMINIMAL_STACK_SIZE, NULL, 1, &buzzer_handler);
}

void buzzer_start() {
    xTaskNotify(buzzer_handler, START_BIT, eSetBits);
}

void buzzer_stop() {
    xTaskNotify(buzzer_handler, STOP_BIT, eSetBits);
}

static void buzzer_task(void* params) {
    static unsigned short work_request=0;
    static unsigned int notification_val;

    while(1) {
        if (xTaskNotifyWait(0, 0xffff, &notification_val, 0) == pdPASS ) {
            if (notification_val & START_BIT) work_request++;
            if (notification_val & STOP_BIT)  work_request--;
        }
        if(work_request > 0) {
            buzz_on();
            osDelay(DURATION_MS);
            buzz_off();
        }
        osDelay(INTERVAL_MS);
    }

}

