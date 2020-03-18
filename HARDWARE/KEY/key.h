#ifndef __KEY_H
#define __KEY_H
#include "stm32f1xx_hal.h"
#ifdef __cplusplus
 extern "C" {
#endif
#define KEY0 							HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)
#define KEY1 							HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12)
#define KEY2 							HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)
#define Left_KEY       		KEY0	
#define Right_KEY      		KEY2
#define Determine_KEY     KEY1	 
 #define Upper      			2  //上
 #define Left       			3  //左
 #define Right      			4  //右 
 #define Lower      			5  //下
 #define Determine  			6  //确定
 #define Return     			7  //返回
#define	 HomeLgPre        8	 //长按
void KEY_Init(void);
extern unsigned char KEY_Scan(unsigned char mode);	 
extern unsigned char KEY_Scan_Snake(unsigned char mode);
#ifdef __cplusplus
}
#endif
#endif



