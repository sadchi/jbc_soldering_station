#include "buzzer.h"
#include "cmsis_os.h"
#include "config.h"
#include "cradle.h"
#include "freertos.h"
#include "init.h"
#include "task.h"
#include "thermo_controller_periph.h"
#include "tm1637.h"

#define MEASURE_INTERVAL_REGULAR 5
#define MEASURE_INTERVAL_STANDBY 20

#define PARKED        1
#define UNPARKED      2
#define PARKING_SHIFT 24
#define STANDBY_TEMP  1000

static TaskHandle_t thermo_controller_handler;
static unsigned char stand_by, temp_latch = 1;
static unsigned short user_temp = 0, target_temp=STANDBY_TEMP;

void set_user_temp(unsigned long t) {
    xTaskNotify(thermo_controller_handler, t & 0xFFF, eSetBits);
}


void set_target_temp(unsigned long t) {
    set_user_temp((t & 0xFFF) << 12);
}

void iron_parked(void) {
    xTaskNotify(thermo_controller_handler, PARKED << PARKING_SHIFT, eSetBits);
}

void iron_left_parking(void) {
    xTaskNotify(thermo_controller_handler, UNPARKED << PARKING_SHIFT, eSetBits);
}

void switch_to_stand_by(void) {
    stand_by = 1;
    target_temp = STANDBY_TEMP;
}

void switch_to_regular(void) {
    stand_by = 0;
    target_temp = user_temp;
}

static void thermo_controller_task(void* params) {
    static unsigned int notification_val;
    static unsigned long raw_temp, current_temp;

    while(1) {

        buzz();
        temp_stab_on();

        if (xTaskNotifyWait(0, 0xFFFFFFFF, &notification_val, 0) == pdPASS) {
            user_temp   = (notification_val  &  0xFFF)       ? (notification_val &  0xFFF)        : user_temp;
			
			if (! stand_by) target_temp = user_temp;
			
            target_temp = ((notification_val >> 12) & 0xFFF) ? ((notification_val >> 12) & 0xFFF) : target_temp;

            if ((notification_val >> PARKING_SHIFT) == PARKED)   switch_to_stand_by();
            if ((notification_val >> PARKING_SHIFT) == UNPARKED) switch_to_regular();
        }





        get_temp_on();
        heater_off();
        // osDelay(5);
        raw_temp = get_current_temp_raw();
        current_temp =raw_temp;
        heater_on();
        get_temp_off();



        if (stand_by) {
            if(current_temp < target_temp) heater_on();
            else heater_off();
            osDelay(MEASURE_INTERVAL_STANDBY);
        } else {

            if((!temp_latch) && (current_temp < ( target_temp - 400))) {
                temp_latch = 1;
                // buzz();
                // temp_stab_off();
            }

            if (current_temp < target_temp) heater_on();

            if (current_temp >= target_temp) {
                heater_off();
                // temp_stab_on();
                if(temp_latch) {
                    // buzz_x2();
                    temp_latch =0;
                }

            }

            osDelay(MEASURE_INTERVAL_REGULAR);
        }




#if DEBUG_DISPLAY == THERMO_CONTROLLER_MODE
        tm1637_display_dec(stand_by,0);
#endif

#if DEBUG_DISPLAY == THERMO_CONTROLLER_RAW_TEMP
        tm1637_display_dec(raw_temp,0);
#endif

#if DEBUG_DISPLAY == THERMO_CONTROLLER_TARGET_TEMP
        tm1637_display_dec(target_temp,0);
#endif

#if DEBUG_DISPLAY == THERMO_CONTROLLER_CURRENT_TEMP
        tm1637_display_dec(current_temp,0);
#endif

#if DEBUG_DISPLAY == THERMO_CONTROLLER_USER_TEMP
        tm1637_display_dec(user_temp,0);
#endif

    }
}

void thermo_controller_init() {
    xTaskCreate(thermo_controller_task, NULL, configMINIMAL_STACK_SIZE, NULL, 1, &thermo_controller_handler);
    stand_by = is_parked();
}

