#include "main.h"
#include "stm32f1xx_hal.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "led.h"
#include "rtc.h" 
#include "myiic.h"
#include "sht20.h"
#include "delay.h"
#include "snake.h"
#include "spi.h"
#include "key.h"
#include "math.h"
#include "oled.h"
#include "config.h"
#include "bg.h"
#include "display.h"
#include "mp3.h"
OLED_Display_t gOLED_Display = {0,2,0,0,0};
SHT20_Date_T gSht20Date = {0,0};
MP3_DATA Mp3_Data = {0,1,0,0};
LOCK_OLED Lock_OLED = {0};
SET_RTCTIME Set_RTCTime = {2020,01,26,15,02,30};
SET_ALARM Set_Alarm = {2020,01,26,30,04,30};
LED_LIGHT	Led_Light = {0};
int main(void)
{
  HAL_Init();
	Stm32_Clock_Init(RCC_PLL_MUL9);
	delay_init(72);
  UART_Init();
	printf("Mcu init start! \r\n \
				  Clock_Init:72MHZ\r\n \
				  Usart1_init's BaudRate is 115200\r\n");
  LED_Init();
	KEY_Init();
  DMA_Init();
  ADC1_Init();
  TIM3_Init();
	while(RTC_Init())
	{ 
		 delay_ms(50);
		 printf("RTC_Initing ! \r\n");		
	}
	printf("RTC_Init succeed! \r\n");
	IIC_Init();
	while(SHT20_Init())
	{
		 delay_ms(50);
		 printf("SHT20_Initing ! \r\n");
	}
	printf("SHT20_Init succeed! \r\n");
	GUI_Initialize();
	printf("GUI_Initialize succeed! \r\n");
	MP3_Init();
	TIM4_Init(4999,7199);
	HAL_TIM_Base_Stop(&htim4);
	TIM2_Init(9,7199);
	HAL_TIM_Base_Stop(&htim2);
	//Boot_Animation();//¿ª»ú¶¯»­
	printf("Mcu init succeed! \r\n");
  while (1)
  { 
		Oled_DisplayPage();	
  }
}
