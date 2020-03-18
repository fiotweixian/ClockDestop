#include "key.h"
#include "delay.h"
#include "snake.h"
void KEY_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pins : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;   //高速
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0, GPIO_PIN_RESET);
	
  /*Configure GPIO pins : PB5 PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;   //高速
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);	
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5 | GPIO_PIN_12, GPIO_PIN_SET);
	
}
unsigned char KEY_Scan(unsigned char mode)
{	 
	static unsigned char key_up=1;//按键标志
	unsigned char count = 0;
	if(mode)key_up=1;  //支持连按	
  //检测按键是否按下	
	if(key_up&&(KEY0==0||KEY1==0||KEY2==1))
	{
		//delay_ms(2);//去抖动 
		key_up=0;
		if(KEY0== 0)           			return Left;
		else if(KEY2== 1)						return Right;
		else if(KEY1== 0)
		{
			while(KEY1 == 0)
			{
				count++;
				delay_ms(20);
				if(count > 50)
					return HomeLgPre;			
			}
			return Determine;
		}
	}
	//检测按键是否松开
	else if(KEY0==1 && KEY1==1 && KEY2==0)
	key_up=1; 	return 0;//无按键按下
}
unsigned char KEY_Scan_Snake(unsigned char mode)
{	
  static unsigned char temp=RIGHT;	
	static unsigned char key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==1))
	{
		delay_ms(10);//去抖动 
		if((KEY0==0)&&(MoveDirection!=RIGHT)) { runflag=1; temp=LEFT; }
		else if((KEY1==0)&&(MoveDirection!=DOWN)) { runflag=1; temp=DOWN; }
		else if((KEY2==1)&&(MoveDirection!=LEFT)) { runflag=1; temp=RIGHT; }
		//else if((KEY3==0)&&(MoveDirection!=UP)) { runflag=1; temp=DOWN; }
	}
	  return temp;
}


