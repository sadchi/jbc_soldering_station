#include "init.h"
#include "main.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"




osThreadId defaultTaskHandle;

void StartDefaultTask(void const * argument);


int main(void) {

    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_ADC1_Init();
    MX_TIM1_Init();

    MX_NVIC_Init();

    osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
    defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

    osKernelStart();

    while (1) {
    }

}

void StartDefaultTask(void const * argument) {
    for(;;) {
        osDelay(1);
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM2) {
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

