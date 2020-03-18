#ifndef __RTC_H
#define __RTC_H	  
#include "stm32f1xx_hal.h"
#include "main.h"
	 

extern RTC_HandleTypeDef RTC_Handler;  //RTC���
												    
//ʱ��ṹ��
typedef struct 
{
	volatile unsigned char hour;
	volatile unsigned char min;
	volatile unsigned char sec;			
	//������������
	volatile unsigned short w_year;
	volatile unsigned char  w_month;
	volatile unsigned char  w_date;
	volatile unsigned char  week;	
}_calendar_obj;					 
extern _calendar_obj calendar;				//�����ṹ��
//ʱ��ṹ��
typedef struct _SET_RTCTIME
{		
	//������������
	volatile unsigned short Year;
	volatile unsigned char  Month;
	volatile unsigned char  Date;
	volatile unsigned char Hour;
	volatile unsigned char Min;
	volatile unsigned char Sec;		
} SET_RTCTIME;					 
extern SET_RTCTIME Set_RTCTime;				//���������ṹ��
typedef struct _SET_ALARM
{		
	//������������
	volatile unsigned short Year;
	volatile unsigned char  Month;
	volatile unsigned char  Date;
	volatile unsigned char Hour;
	volatile unsigned char Min;
	volatile unsigned char Sec;		
} SET_ALARM;					 
extern SET_ALARM Set_Alarm;				//���������ṹ��
unsigned char RTC_Init(void);        					//��ʼ��RTC,����0,ʧ��;1,�ɹ�;
unsigned char Is_Leap_Year(unsigned short year);					//ƽ��,�����ж�
unsigned char RTC_Get(void);         					//��ȡʱ��   
unsigned char RTC_Get_Week(unsigned short year,unsigned char month,unsigned char day);
unsigned char RTC_Set(unsigned short syear,unsigned char smon,unsigned char sday,unsigned char hour,unsigned char min,unsigned char sec);		//����ʱ��	
unsigned char RTC_Alarm_Set(unsigned short syear,unsigned char smon,unsigned char sday,unsigned char hour,unsigned char min,unsigned char sec);	//��������	
#endif



















