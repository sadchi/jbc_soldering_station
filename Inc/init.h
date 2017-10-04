#ifndef __INIT_H
#define __INIT_H


#define ONBOARD_LED_Pin GPIO_PIN_13
#define ONBOARD_LED_GPIO_Port GPIOC
#define EXTRA_OUT1_Pin GPIO_PIN_0
#define EXTRA_OUT1_GPIO_Port GPIOA
#define EXTRA_OUT2_Pin GPIO_PIN_1
#define EXTRA_OUT2_GPIO_Port GPIOA
#define EXT_INT_Pin GPIO_PIN_2
#define EXT_INT_GPIO_Port GPIOA
#define EXT_INT_EXTI_IRQn EXTI2_IRQn
#define THERMO_COUPLE_Pin GPIO_PIN_0
#define THERMO_COUPLE_GPIO_Port GPIOB
#define THERMO_SETTING_Pin GPIO_PIN_1
#define THERMO_SETTING_GPIO_Port GPIOB
#define TM1637_CLK_Pin GPIO_PIN_14
#define TM1637_CLK_GPIO_Port GPIOB
#define TM1637_IO_Pin GPIO_PIN_15
#define TM1637_IO_GPIO_Port GPIOB
#define HEATER_Pin GPIO_PIN_10
#define HEATER_GPIO_Port GPIOA
#define TEMP_STAB_LED_Pin GPIO_PIN_11
#define TEMP_STAB_LED_GPIO_Port GPIOA
#define GET_TEMP_LED_Pin GPIO_PIN_12
#define GET_TEMP_LED_GPIO_Port GPIOA
#define BUZZ_Pin GPIO_PIN_15
#define BUZZ_GPIO_Port GPIOA
#define TOF_SCL_Pin GPIO_PIN_6
#define TOF_SCL_GPIO_Port GPIOB
#define TOF_SDA_Pin GPIO_PIN_7
#define TOF_SDA_GPIO_Port GPIOB


#include "stm32f1xx_hal.h"

extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim1;

void SystemClock_Config(void);
void MX_NVIC_Init(void);
void MX_I2C1_Init(void);
void MX_ADC1_Init(void);
void MX_ADC2_Init(void);
void MX_TIM2_Init(void);
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
void MX_GPIO_Init(void);

#endif

