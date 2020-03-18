#ifndef __RTC_H
#define __RTC_H	  
#include "stm32f1xx_hal.h"
#include "main.h"
	 

extern RTC_HandleTypeDef RTC_Handler;  //RTC句柄
												    
//时间结构体
typedef struct 
{
	volatile unsigned char hour;
	volatile unsigned char min;
	volatile unsigned char sec;			
	//公历日月年周
	volatile unsigned short w_year;
	volatile unsigned char  w_month;
	volatile unsigned char  w_date;
	volatile unsigned char  week;	
}_calendar_obj;					 
extern _calendar_obj calendar;				//日历结构体
//时间结构体
typedef struct _SET_RTCTIME
{		
	//公历日月年周
	volatile unsigned short Year;
	volatile unsigned char  Month;
	volatile unsigned char  Date;
	volatile unsigned char Hour;
	volatile unsigned char Min;
	volatile unsigned char Sec;		
} SET_RTCTIME;					 
extern SET_RTCTIME Set_RTCTime;				//设置日历结构体
typedef struct _SET_ALARM
{		
	//公历日月年周
	volatile unsigned short Year;
	volatile unsigned char  Month;
	volatile unsigned char  Date;
	volatile unsigned char Hour;
	volatile unsigned char Min;
	volatile unsigned char Sec;		
} SET_ALARM;					 
extern SET_ALARM Set_Alarm;				//设置日历结构体
unsigned char RTC_Init(void);        					//初始化RTC,返回0,失败;1,成功;
unsigned char Is_Leap_Year(unsigned short year);					//平年,闰年判断
unsigned char RTC_Get(void);         					//获取时间   
unsigned char RTC_Get_Week(unsigned short year,unsigned char month,unsigned char day);
unsigned char RTC_Set(unsigned short syear,unsigned char smon,unsigned char sday,unsigned char hour,unsigned char min,unsigned char sec);		//设置时间	
unsigned char RTC_Alarm_Set(unsigned short syear,unsigned char smon,unsigned char sday,unsigned char hour,unsigned char min,unsigned char sec);	//设置闹钟	
#endif



















