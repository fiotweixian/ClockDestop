#ifndef __tim_H
#define __tim_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim2;
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

extern void Error_Handler(void);

void TIM3_Init(void);
void TIM4_Init(unsigned short arr,unsigned short psc);
void TIM2_Init(unsigned short arr,unsigned short psc);
/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ tim_H */

