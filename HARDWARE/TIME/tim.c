#include "tim.h"
#include "snake.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim2;
/* TIM3 init function */
void TIM3_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 72;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 100;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

}
/* TIM4 init function */
void TIM4_Init(unsigned short arr,unsigned short psc)
{
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = psc;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = arr;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
   HAL_TIM_Base_Start_IT(&htim4); //使能定时4和定时器4更新中断：TIM_IT_UPDATE   

}
/* TIM3 init function */
void TIM2_Init(unsigned short arr,unsigned short psc)
{
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = psc;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = arr;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
   HAL_TIM_Base_Start_IT(&htim2); //使能定时4和定时器4更新中断：TIM_IT_UPDATE   

}
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspInit 0 */

  /* USER CODE END TIM3_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM3_CLK_ENABLE();
  /* USER CODE BEGIN TIM3_MspInit 1 */

  /* USER CODE END TIM3_MspInit 1 */
  }
  if(tim_baseHandle->Instance==TIM4)
  {
  /* USER CODE BEGIN TIM3_MspInit 0 */

  /* USER CODE END TIM3_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM4_CLK_ENABLE();
  /* USER CODE BEGIN TIM3_MspInit 1 */
		HAL_NVIC_SetPriority(TIM4_IRQn,1,3);    //设置中断优先级，抢占优先级1，子优先级3
		HAL_NVIC_EnableIRQ(TIM4_IRQn);          //开启ITM3中断   
  /* USER CODE END TIM3_MspInit 1 */
  }
  if(tim_baseHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM3_MspInit 0 */

  /* USER CODE END TIM3_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();
  /* USER CODE BEGIN TIM3_MspInit 1 */
		HAL_NVIC_SetPriority(TIM2_IRQn,0,3);    //设置中断优先级，抢占优先级1，子优先级3
		HAL_NVIC_EnableIRQ(TIM2_IRQn);          //开启ITM3中断   
  /* USER CODE END TIM3_MspInit 1 */
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspDeInit 0 */

  /* USER CODE END TIM3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM3_CLK_DISABLE();
  }
  if(tim_baseHandle->Instance==TIM4)
  {
  /* USER CODE BEGIN TIM3_MspDeInit 0 */

  /* USER CODE END TIM3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM4_CLK_DISABLE();
  }
  if(tim_baseHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM3_MspDeInit 0 */

  /* USER CODE END TIM3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM2_CLK_DISABLE();
  }
  /* USER CODE BEGIN TIM3_MspDeInit 1 */

  /* USER CODE END TIM3_MspDeInit 1 */
} 

/* USER CODE BEGIN 1 */
//定时器4中断服务函数
void TIM4_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&htim4);
}
void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&htim2);
}
//回调函数，定时器中断服务函数调用
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
		uint16_t count;
    if(htim==(&htim4))
    {
      SnakeCoordinate_x = MoveCoordinate[0]>>8;
		  SnakeCoordinate_y = MoveCoordinate[0]&0x00ff;	 
      if(Border_Check(SnakeCoordinate_x,SnakeCoordinate_y)==-1)
				    MoveDirection = GAMEOVER;	
      for(count=1;count<SnakeLength;count++)//清空CheckBuffer
         CheckBuffer[count] = 0;			
      Direction_Process();	
      for(count=1;count<SnakeLength;count++)//除蛇头外所有坐标存入CheckBuffer
         CheckBuffer[MoveCoordinate[count]>>8] = MoveCoordinate[count]&0x00ff;			
		 // TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
//		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_6);
    }
    else if(htim==(&htim2))
    {
      Counter_x++;
		  Counter_y++;
		  if(Counter_x==5000) Counter_x = 166;
		  if(Counter_y==5000) Counter_y = 1785;
		  //TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
    }
}


