#ifndef __MP3_H
#define __MP3_H
#include "stm32f1xx_hal.h"
#ifdef __cplusplus
 extern "C" {
#endif
//采样率计算
//分辨率：Fs/NPT 
#define NEX 256
#define PI2 6.28318530717959
#define Fs	9984	
#define SHOW_PAGE 		7				//显示函数的个数	 
typedef struct _MP3_DATA{
	unsigned char Auto;
	unsigned char Count;
	unsigned char	Mode;
	unsigned char	DisSort;
} MP3_DATA;	 
extern MP3_DATA Mp3_Data;
extern uint32_t Adc_SourceData[256];
void MP3_Init(void);//初始化 
void FFT_GetDcComponent(void);//获取FFT之后的直流分量
void Mp3_UnColuDisplay(void);//单边显示
void Mp3_MiniUnColuDisplay(void);//迷你单边显示
void Mp3_MiddleColuDisplay(void);//中间对称
void Mp3_Mi2ddleColuDisplay(void);//mini中间对此
void Mp3_SMiddleColuDisplay(void);
void Mp3_RMiddleColuDisplay(void);
void Mp3_TMiddleColuDisplay(void);	 
#ifdef __cplusplus
}
#endif
#endif
