#ifndef __usart_H
#define __usart_H
#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f1xx_hal.h"
#include "main.h"


extern UART_HandleTypeDef huart1;
extern void Error_Handler(void);
extern void UART_Init(void);

#ifdef __cplusplus
}
#endif
#endif




