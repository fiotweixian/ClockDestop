#include "led.h"
void LED_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;
	
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
	
  /*Configure GPIO pins : PB6*/
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6, GPIO_PIN_SET);	
}
