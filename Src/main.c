#include "buzzer.h"
#include "cmsis_os.h"
#include "init.h"
#include "main.h"
#include "stm32f1xx_hal.h"
#include "thermo_controller.h"
#include "thermo_settings.h"
#include "tm1637.h"

osThreadId defaultTaskHandle;


void StartDefaultTask(void const * argument);


int main(void) {

    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();
    MX_ADC1_Init();
    MX_I2C1_Init();
    MX_TIM2_Init();
    MX_ADC2_Init();

    MX_NVIC_Init();


    buzzer_init();
    tm1637_init();
    thermo_settings_init();
    thermo_controller_init();

    osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
    defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

    osKernelStart();

    while (1);
}


void StartDefaultTask(void const * argument) {

    for(;;) {
        osDelay(1);
    }

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM3) {
        HAL_IncTick();
    }
}

void _Error_Handler(char * file, int line) {
    while(1) {
    }
}

#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line) {

}

#endif

