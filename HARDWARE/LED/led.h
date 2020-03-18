#ifndef __LED_H
#define __LED_H
#include "stm32f1xx_hal.h"
#include "main.h"
#ifdef __cplusplus
 extern "C" {
#endif
typedef struct _LED_LIGHT{
	unsigned char Mode;
} LED_LIGHT;
extern LED_LIGHT	Led_Light;
#define LED_RESET() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET)
#define LED_SET() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET)
#define LED_TOG() HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_6)
#define LED_STATE() HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6)

void LED_Init(void);


#ifdef __cplusplus
}
#endif
#endif


