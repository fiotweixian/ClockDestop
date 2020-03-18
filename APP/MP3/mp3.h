#ifndef __MP3_H
#define __MP3_H
#include "stm32f1xx_hal.h"
#ifdef __cplusplus
 extern "C" {
#endif
//�����ʼ���
//�ֱ��ʣ�Fs/NPT 
#define NEX 256
#define PI2 6.28318530717959
#define Fs	9984	
#define SHOW_PAGE 		7				//��ʾ�����ĸ���	 
typedef struct _MP3_DATA{
	unsigned char Auto;
	unsigned char Count;
	unsigned char	Mode;
	unsigned char	DisSort;
} MP3_DATA;	 
extern MP3_DATA Mp3_Data;
extern uint32_t Adc_SourceData[256];
void MP3_Init(void);//��ʼ�� 
void FFT_GetDcComponent(void);//��ȡFFT֮���ֱ������
void Mp3_UnColuDisplay(void);//������ʾ
void Mp3_MiniUnColuDisplay(void);//���㵥����ʾ
void Mp3_MiddleColuDisplay(void);//�м�Գ�
void Mp3_Mi2ddleColuDisplay(void);//mini�м�Դ�
void Mp3_SMiddleColuDisplay(void);
void Mp3_RMiddleColuDisplay(void);
void Mp3_TMiddleColuDisplay(void);	 
#ifdef __cplusplus
}
#endif
#endif
