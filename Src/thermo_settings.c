#include "Freertos.h"
#include "cmsis_os.h"
#include "config.h"
#include "task.h"
#include "thermo_controller.h"
#include "thermo_settings_periph.h"
#include "tm1637.h"

#define RANGE 200

static const int presets [] = {
    3500, 2300,
    1830, 300,
    50,    150
};


void thermo_settings_task(void* params) {
    unsigned int val, i;
    volatile static int size = (sizeof(presets) / sizeof(int)) /2 ;

    while(1) {
        val = get_thermo_setting_val();

#if DEBUG_DISPLAY == THERMO_SETTING_DISPLAY
        tm1637_display_dec(val,0);
#endif


        for(i=0; i<size; i++)
            if (val >= (presets[i << 1]-RANGE) && val < (presets[i << 1]+RANGE))
                set_user_temp(presets[(i << 1) + 1]);


        osDelay(1000);
    }
}


void thermo_settings_init(void) {
    xTaskCreate(thermo_settings_task, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);
}


