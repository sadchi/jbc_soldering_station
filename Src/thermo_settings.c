#include "Freertos.h"
#include "cmsis_os.h"
#include "task.h"
#include "thermo_settings_periph.h"
#include "tm1637.h"
#include "config.h"


void thermo_settings_task(void* params) {
    unsigned int val;
    while(1) {
        val = get_thermo_setting_val();
        #if DEBUG_DISPLAY == THERMO_SETTING_DISPLAY
        tm1637_display_dec(val,0);
        #endif
        osDelay(200);
    }
}


void thermo_settings_init(void) {
    xTaskCreate(thermo_settings_task, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);
}


