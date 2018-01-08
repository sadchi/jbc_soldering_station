#include "buzzer_periph.h"
#include "cmsis_os.h"
#include "freertos.h"
#include "task.h"

#define DURATION_MS 100
#define INTERVAL_MS 100


static TaskHandle_t buzzer_handler;

static void buzzer_task(void* params);

void buzzer_init() {
    buzz_init();
    xTaskCreate(buzzer_task, NULL, configMINIMAL_STACK_SIZE, NULL, 1, &buzzer_handler);
}

void buzz() {
    xTaskNotify(buzzer_handler, 0, eIncrement);
}

void buzz_x2() {
    buzz();
    buzz();
}

static void buzzer_task(void* params) {
    static unsigned short buzz_quantity=0;
    static unsigned int notification_val;

    while(1) {
        if (xTaskNotifyWait(0, 0xFFFFFFFF, &notification_val, 0) == pdPASS && notification_val > 0)
            buzz_quantity = buzz_quantity + notification_val;

        for(;buzz_quantity>0;buzz_quantity--){
            buzz_on();
            osDelay(DURATION_MS);
            buzz_off();
            osDelay(INTERVAL_MS);
        }
    }
}

