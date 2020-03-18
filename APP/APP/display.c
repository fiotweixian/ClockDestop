#include "display.h"
#include "oled.h"
#include "delay.h"
#include "key.h"
#include "adc.h"
#include "tim.h"
#include "snake.h"
#include "rtc.h"
#include "led.h"
#include "sht20.h"
#include "string.h"
#include "mp3.h"
uint8_t MoDat_of_Year[12]={31,28,31,30,31,30,31,31,30,31,30,31};
uint8_t a,b,c,d,e,f,m1,m2,m3,m4,m5,m6;
void Boot_Animation(void)
{
		static uint8_t x=0,y=0;
		for(x = 63;x>=18;x--){
				OLED_DrawPoint(108-0.7*x,x,1);
				OLED_DrawPoint(17 +0.7*x,x,1);
				y = 64-x;
				OLED_DrawPoint(64-0.7*y,y,1);
				OLED_DrawPoint(64+0.7*y,y,1);
				delay_ms(2);
			  OLED_Refresh_Gram();
		}
		
		for(x = 30;x <= 94;x++){
				OLED_DrawPoint(125-x,47,1);
				OLED_DrawPoint(x,18,1);
				delay_ms(2);
				OLED_Refresh_Gram();
		}
		delay_ms(3000);
		OLED_Clear();
		OLED_Refresh_Gram();		
}

//出现闪烁,有待解决
#if 0 
void GUI_CLOCK(uint8_t x0,uint8_t y0,uint8_t line,uint8_t with,uint8_t time_t)
{
		int s,c;
		float w;
		OLED_Clear2();
		GUI_Circle(40,30,30,1);
		GUI_Circle(40,30,1,1);
		w = -(time_t+15)*6*3.1415926/180;
		s = -line*cos(w)+x0;
		c = -line*sin(w)+y0;
		GUI_LineWith(x0,y0,s,c,with,1);
		GUI_Exec();	
}
#endif

//显示电池电量相关信息
void ElectricityDisplay(uint8_t rank_t)                    //电量
{
   OLED_P16x16Ch(111,0,rank_t);
}
//显示WIFI
void WifiDisplay()                    		//wifi
{
   OLED_P16x16Ch(0,0,6);
}
//显示蓝牙
void BluetoothDisplay()                  //蓝牙
{
   OLED_P16x16Ch(32,0,5);
}
//显示手电筒相关信息
void FlashlightDisplay()                     //手电筒
{
  OLED_P16x16Ch(16,0,7);
}
void DisplayList(int page_t)
{
  switch(page_t)	
	{
	   case 2:
			OLED_P8x16Str(3*16,0,"Music");
			OLED_P8x16Str(1*16,2,"MP3");
			OLED_P8x16Str(1*16,4,"Mode");	 
			OLED_P8x16Str(1*16,6,"Sort");   
			break;
	   case 3:
			OLED_P8x16Str(3*16,0,"Game");
			OLED_P8x16Str(1*16,2,"Snake");
			OLED_P8x16Str(1*16,4,"."); 
			OLED_P8x16Str(1*16,6,"..");   
			break;
	   case 4:
			OLED_P8x16Str(3*16,0,"Clock");					
			break;
	   case 5:
			OLED_P8x16Str(3*16,0,"Alarm");  
			break;
	   case 6:
			OLED_P8x16Str(3*16,0,"Led");   
			break;
	   case 7:
			OLED_P8x16Str(1*16,2,"00");
			OLED_P8x16Str(1*16,4,"01"); 
			OLED_P8x16Str(1*16,6,"02");   
			break;
	   case 8:
			OLED_P8x16Str(3*16,0,"Set");  
			break;
	   case 9:
			OLED_P8x16Str(3*16,0,"Info");
			OLED_P8x16Str(1*16,2,"User:xxx");
			OLED_P8x16Str(1*16,4,"WX:xxx"); 
			OLED_P8x16Str(1*16,6,"QQ:xxx");	 
			break;
	   case 10:
			OLED_P8x16Str(1*16,2,"00");
			OLED_P8x16Str(1*16,4,"01"); 
			OLED_P8x16Str(1*16,6,"02");   
			break;		 
		 default: 
			break;
	}
}
void indexList(uint8_t page_t,uint8_t index_t)
{
	if(page_t == 2)
	{
		switch(index_t)
		{
			case 2:
				break;
			case 4:
				if(!Mp3_Data.Mode)
					OLED_P8x16Str(4*18,4,">Auto");
				else
					OLED_P8x16Str(4*18,4,">Hard");
				break;
			case 6:
					OLED_ShowNum(4*18,6,Mp3_Data.DisSort,1,12);
				break;
			case 8:
				break;
		}
	}
	else if(page_t == 4)
	{
		switch(index_t)
		{
			case 2:
				OLED_P8x16Str(1*16,2,"Yea");
				OLED_P8x16Str(1*16,4,"Mon"); 
				OLED_P8x16Str(1*16,6,"Dat"); 
				break;
			case 4:
				break;
			case 6:
				break;
			case 8:
				OLED_P8x16Str(1*16,2,"Mon");
				OLED_P8x16Str(1*16,4,"Dat"); 
				OLED_P8x16Str(1*16,6,"Hou"); 
				break;
			case 10:
				OLED_P8x16Str(1*16,2,"Dat");
				OLED_P8x16Str(1*16,4,"Hou"); 
				OLED_P8x16Str(1*16,6,"Min"); 
				break;
			case 12:
				OLED_P8x16Str(1*16,2,"Hou");
				OLED_P8x16Str(1*16,4,"Min"); 
				OLED_P8x16Str(1*16,6,"Sec"); 
				break;
		}	
	}
	else if(page_t == 6)
	{
		switch(index_t)
		{
			case 2:
				OLED_P8x16Str(1*16,2,"OPN");
				OLED_P8x16Str(1*16,4,"OFF"); 
				OLED_P8x16Str(1*16,6,"TOG"); 
				break;
			case 4:
				break;
			case 6:
				break;
			case 8:
				OLED_P8x16Str(1*16,2,"OFF");
				OLED_P8x16Str(1*16,4,"TOG"); 
				OLED_P8x16Str(1*16,6,"BEA"); 
				break;
			case 10:
				OLED_P8x16Str(1*16,2,"TOG");
				OLED_P8x16Str(1*16,4,"BET"); 
				OLED_P8x16Str(1*16,6,"..."); 
				break;
			case 12:
				OLED_P8x16Str(1*16,2,".0.");
				OLED_P8x16Str(1*16,4,".1."); 
				OLED_P8x16Str(1*16,6,".2."); 
				break;
		}		
	}
	else if(page_t == 8)
	{
		switch(index_t)
		{
			case 2:
				OLED_P8x16Str(1*16,2,"01");
				OLED_P8x16Str(1*16,4,"02"); 
				OLED_P8x16Str(1*16,6,"03"); 
				break;
			case 4:
				break;
			case 6:
				break;
			case 8:
				OLED_P8x16Str(1*16,2,"02");
				OLED_P8x16Str(1*16,4,"03"); 
				OLED_P8x16Str(1*16,6,"04"); 
				break;
			case 10:
				OLED_P8x16Str(1*16,2,"03");
				OLED_P8x16Str(1*16,4,"04"); 
				OLED_P8x16Str(1*16,6,"05"); 
				break;
			case 12:
				OLED_P8x16Str(1*16,2,"04");
				OLED_P8x16Str(1*16,4,"05"); 
				OLED_P8x16Str(1*16,6,"06"); 
				break;
		}		
	}
}
void DisplayIcon(int keyvalue_t)
{
   OLED_P16x16Ch(12,3,8);//22+10+48+10=42+48=
	 OLED_P32x32Ch(50,2,keyvalue_t);
	 OLED_P16x16Ch(105,3,9);//127-12=115
	 OLED_P6x8Str(7*16,7,"/");
	 OLED_ShowNum(7.5*16,6,keyvalue_t/2+1,1,12);
}

void OLED_ShowDate(unsigned char x, unsigned char y,unsigned char w1,unsigned char no_week)//显示日期
{
	 
	 OLED_ShowNum(w1*x,y,calendar.w_year/1000,1,12);
	 OLED_ShowNum((w1+1)*x,y,calendar.w_year%1000/100,1,12);
	 OLED_ShowNum((w1+2)*x,y,calendar.w_year%1000%100/10,1,12);
	 OLED_ShowNum((w1+3)*x,y,calendar.w_year%1000%100%10,1,12);
	 OLED_ShowNum((w1+5)*x,y,calendar.w_month/10,1,12);
	 OLED_ShowNum((w1+6)*x,y,calendar.w_month%10,1,12);
	 OLED_ShowNum((w1+8)*x,y,calendar.w_date/10,1,12);
	 OLED_ShowNum((w1+9)*x,y,calendar.w_date%10,1,12);
	 if(no_week)
	 {
		 switch(calendar.week)
			{
				case 1:OLED_ShowString((w1+11)*x,y,"Mon");break;
				case 2:OLED_ShowString((w1+11)*x,y,"Tue");break;
				case 3:OLED_ShowString((w1+11)*x,y,"Wed");break;
				case 4:OLED_ShowString((w1+11)*x,y,"Thu");break;
				case 5:OLED_ShowString((w1+11)*x,y,"Fri");break;
				case 6:OLED_ShowString((w1+11)*x,y,"Sat");break;
				case 7:OLED_ShowString((w1+11)*x,y,"Sun");break;
				default :OLED_ShowString((w1+11)*x,y,"err");break;
			}   
	 }		
}
void OLED_ShowminiDate(unsigned char x, unsigned char y)
{
	 uint8_t w1;
	 w1=0;
	// unsigned char tmp[5]={0};
	 OLED_ShowString(w1*x,y,"<");
	 OLED_ShowNum((w1+1)*x,y,calendar.hour/10,1,12);
	 OLED_ShowNum((w1+2)*x,y,calendar.hour%10,1,12);
	 OLED_ShowNum((w1+3)*x,y,calendar.min/10,1,12);
	 OLED_ShowNum((w1+4)*x,y,calendar.min%10,1,12);
	 OLED_ShowNum((w1+5)*x,y,calendar.sec/10,1,12);
	 OLED_ShowNum((w1+6)*x,y,calendar.sec%10,1,12);
	 OLED_ShowString((w1+7)*x,y,">");
	 #if 0 
	 gSht20Date.Temp = SHT20_GetTempPoll();
	 sprintf(tmp,"%.1f%C",gSht20Date.Temp);
	 OLED_ShowString(0,5,tmp);
	 memset(tmp,0,sizeof(tmp));
	 gSht20Date.Humi = SHT20_GetHumiPoll();
	 sprintf(tmp,"%.1f%%",gSht20Date.Humi);
	 OLED_ShowString(85,5,tmp);
	 #endif
}
void OLED_MainTop(unsigned char mode_t)
{
		unsigned char tmp[5]={0};
		unsigned char Keyvalue = 0;
		static unsigned char bFlag_t = 0;
	 	static unsigned char CollectFre = 0;
		ElectricityDisplay(calendar.sec%5);	
		OLED_ShowDate(6,0,0,1);
		switch(mode_t)
		{
			case 2:
			m1 = calendar.hour/10;
			OLED_DataFlow(0,2,&a,&m1,0);
			m2 = calendar.hour%10;			
			OLED_DataFlow(22,2,&b,&m2,0);	
			OLED_Shownumber11X16(44,3,10); //显示“ : ”
			m3 = calendar.min/10;
			OLED_DataFlow(57,2,&c,&m3,0);	
			m4 = calendar.min%10;			
			OLED_DataFlow(79,2,&d,&m4,0);
			m5 = (calendar.sec/10);
			OLED_DataFlow(103,3,&e,&m5,1);
			m6 = (calendar.sec%10);
			OLED_DataFlow(115,3,&f,&m6,1);
			break;
			case 1:
			m1 = calendar.hour/10;
			OLED_DataFlow(0,2,&a,&m1,0);
			m2 = calendar.hour%10;			
			OLED_DataFlow(22,2,&b,&m2,0);	
			m3 = calendar.min/10;
			OLED_DataFlow(44,2,&c,&m3,0);	
			m4 = calendar.min%10;			
			OLED_DataFlow(66,2,&d,&m4,0);
			m5 = (calendar.sec/10);
			OLED_DataFlow(88,2,&e,&m5,0);
			m6 = (calendar.sec%10);
			OLED_DataFlow(110,2,&f,&m6,0);	
			break;
			case 0:
			m1 = calendar.hour/10;
			OLED_DataFlow(16,3,&a,&m1,1);
			m2 = calendar.hour%10;			
			OLED_DataFlow(28,3,&b,&m2,1);	
			if(bFlag_t)
				OLED_Shownumber11X16(40,3,10); //显示“ : ”
			else
				OLED_Shownumber11X16(40,3,11); //显示“ : ”
			m3 = calendar.min/10;
			OLED_DataFlow(52,3,&c,&m3,1);	
			m4 = calendar.min%10;			
			OLED_DataFlow(64,3,&d,&m4,1);
			if(bFlag_t)
				OLED_Shownumber11X16(76,3,10); //显示“ : ”
			else
				OLED_Shownumber11X16(76,3,11); //显示“ : ”
			m5 = (calendar.sec/10);
			OLED_DataFlow(88,3,&e,&m5,1);
			m6 = (calendar.sec%10);
			OLED_DataFlow(100,3,&f,&m6,1);
			break;
		}
		if(CollectFre == 0)//不影响按键使用
		{
			bFlag_t = !bFlag_t;
			gSht20Date.Temp = SHT20_GetTempPoll();
			sprintf(tmp,"%.1f%C",gSht20Date.Temp);
			OLED_ShowString(0,5,tmp);
			memset(tmp,0,sizeof(tmp));
			gSht20Date.Humi = SHT20_GetHumiPoll();
			sprintf(tmp,"%.1f%% ->>",gSht20Date.Humi);
			OLED_ShowString(50,5,tmp);
			CollectFre = 0;
		}
		CollectFre ++; //采集频率
		if(CollectFre>100)CollectFre = 0;
		OLED_ShowString(0,6,"Menu");
		OLED_ShowString(46,6,"Home");
		OLED_ShowString(96,6,"Exit");
		Keyvalue = KEY_Scan(0);
		switch(Keyvalue)
		{
			case Left:
				if(!Lock_OLED.Lock)
				{
					gOLED_Display.OLED_Page = 1;
					OLED_StartClear();
				}
				break;
			case Determine:
				if(!Lock_OLED.Lock)
				{
					gOLED_Display.OLED_Mode++;
					if(gOLED_Display.OLED_Mode>=3)
						gOLED_Display.OLED_Mode = 0;
					OLED_StartClear();
				}
				break;
			case Right:
				gOLED_Display.OLED_DisplayKey = !gOLED_Display.OLED_DisplayKey;
				if(gOLED_Display.OLED_DisplayKey)
				{
					OLED_Display_Off();
					Lock_OLED.Lock = 1;
				}
				else
				{
					OLED_Display_On();
					Lock_OLED.Lock = 0;
				}
				break;
			case HomeLgPre:
				LED_TOG();
				break;
			default:
				break;
		}
}
void OLED_DeskTop(void)
{
	unsigned char keyvalue = 0;
	OLED_ShowminiDate(6,0);
	ElectricityDisplay(calendar.sec%5);	
	OLED_ShowDate(6,6,0,1);
	keyvalue = KEY_Scan(0);
	if(keyvalue)
	{
		switch(keyvalue)
		{
			case Left:
				gOLED_Display.OLED_Icon -=2;
				if(gOLED_Display.OLED_Icon < 0)
					gOLED_Display.OLED_Icon = 14;
				break;
			case Right:
				gOLED_Display.OLED_Icon +=2;
				if(gOLED_Display.OLED_Icon > 14)
					gOLED_Display.OLED_Icon = 0;
				break;
			case Determine:
				gOLED_Display.OLED_index = 2;
				switch(gOLED_Display.OLED_Icon)
				{
					case 0:
						gOLED_Display.OLED_Page = 2;//mp3	
						break;
					case 2:
						gOLED_Display.OLED_Page = 3;//game
						break;
					case 4:
						gOLED_Display.OLED_Page = 4;//clcok
						break;
					case 6:
						gOLED_Display.OLED_Page = 5;//alarm
						break;
					case 8:
						gOLED_Display.OLED_Page = 6;//led
						break;
					case 10:
						gOLED_Display.OLED_Page = 7;//temp
						break;
					case 12:
						gOLED_Display.OLED_Page = 8;//set
						break;
					case 14:
						gOLED_Display.OLED_Page = 9;//user
						break;
				}
				OLED_StartClear();	
				break;
			case HomeLgPre:
				OLED_StartClear();
				gOLED_Display.OLED_Page = 0;
				gOLED_Display.OLED_Icon = 0;
				a=b=c=d=e=f=0;
				break;
			default:
				break;
		}
	}
	if(keyvalue != Determine && gOLED_Display.OLED_Page != 0)
		DisplayIcon(gOLED_Display.OLED_Icon);
}
void OLED_Mp3Top(unsigned char page_t)
{
	if(gOLED_Display.OLED_index%2==0)	
	{
		if(gOLED_Display.OLED_start == 0)
		{
			OLED_P16x16Ch(0*16,gOLED_Display.OLED_index,10); //选择
			DisplayList(page_t);
			indexList(page_t,gOLED_Display.OLED_index); 
		}
		switch(KEY_Scan(0))	
		{		
			case Left:                     		//上翻
				   OLED_P16x16Ch(0*16,gOLED_Display.OLED_index,11);
				   gOLED_Display.OLED_index+=2;
				   break;
			case Determine:                    //确定
					 switch(gOLED_Display.OLED_index)
					 {
						 case 2:
							OLED_StartClear();               //清除内容栏
							/*启动ADC的DMA传输 配合下面定时器来触发ADC转换*/
							HAL_ADC_Start_DMA(&hadc1, Adc_SourceData, 256);
							/*开启定时器 用溢出事件来触发ADC转换*/
							HAL_TIM_Base_Start(&htim3);		
							OLED_Clear();
							gOLED_Display.OLED_start = 1;
							break;
						 case 4:
								Mp3_Data.Mode = !Mp3_Data.Mode;										
							 break;
						 case 6:
							 Mp3_Data.DisSort ++;
						   if(Mp3_Data.DisSort > SHOW_PAGE)
								 Mp3_Data.DisSort = 0;
							 break;
						 default:
							 break;
					 }
				   break;
			case Right:                       //返回
					 if(gOLED_Display.OLED_start)
					 {
							/*启动ADC的DMA传输 配合下面定时器来触发ADC转换*/
							HAL_ADC_Stop_DMA(&hadc1);
							/*开启定时器 用溢出事件来触发ADC转换*/
							HAL_TIM_Base_Stop(&htim3);
						  gOLED_Display.OLED_Page=2;  
						  gOLED_Display.OLED_start = 0;							 
					 }
					 else
						gOLED_Display.OLED_Page=1;
					 OLED_Clear();				
			     break;
			default : 
				   break;
		}
		
	}	
	if(gOLED_Display.OLED_index>6)gOLED_Display.OLED_index=2;
	if(gOLED_Display.OLED_index<2)gOLED_Display.OLED_index=6;
	if(gOLED_Display.OLED_Page != 1 && gOLED_Display.OLED_start == 0)
	{
		OLED_ShowNum(6*16,6,page_t-1,1,12);
		OLED_P6x8Str(6.5*16,7,"/");
		OLED_ShowNum(7*16,6,gOLED_Display.OLED_index/2,1,12);
	}		
}
void OLED_GameTop(unsigned char page_t)
{
	if(gOLED_Display.OLED_index%2==0)	
	{
		if(gOLED_Display.OLED_start == 0)
		{
			OLED_P16x16Ch(0*16,gOLED_Display.OLED_index,10);              //选择
			DisplayList(page_t);
		}
		switch(KEY_Scan(0))	
		{		
			case Left:                     //上翻
					 if(gOLED_Display.OLED_start == 0){
							OLED_P16x16Ch(0*16,gOLED_Display.OLED_index,11);
							gOLED_Display.OLED_index+=2;
					 }
				   break;
			case Determine:                    //确定
					 switch(gOLED_Display.OLED_index)
					 {
						 case 2:	
								if(gOLED_Display.OLED_start == 0){
									gOLED_Display.OLED_start = 1;
									OLED_StartClear();               //清除内容栏
									OLED_ShowString(20,0,"GreedySnake");
									Snake_Init();
									Frame_Init();	
									runflag=1;
									MoveDirection = RIGHT; 
									HAL_TIM_Base_Start(&htim4);
									HAL_TIM_Base_Start(&htim2);	
								}
							 break;
						 case 4:
							 break;
						 case 6:
							 break;
						 default:
							 break;
					 }
				   break;
			case Right:                       //返回
					 gOLED_Display.OLED_Page=1;
					 OLED_Clear();				
			     break;
			default : 
				   break;
		}
		
	}	
	if(gOLED_Display.OLED_index>6)gOLED_Display.OLED_index=2;
	if(gOLED_Display.OLED_index<2)gOLED_Display.OLED_index=6;
	if(gOLED_Display.OLED_Page != 1 && gOLED_Display.OLED_start == 0)
	{
		OLED_ShowNum(6*16,6,page_t-1,1,12);
		OLED_P6x8Str(6.5*16,7,"/");
		OLED_ShowNum(7*16,6,gOLED_Display.OLED_index/2,1,12);
	}	
	if(gOLED_Display.OLED_start == 1)
	{
		// MoveDirection = KEY_Scan_Snake(1);
		 if(MoveDirection==GAMEOVER)
		 {
				HAL_TIM_Base_Stop_IT(&htim4);
				OLED_Clear();
				OLED_ShowString(32,0,"GAMEOVER");
				OLED_ShowString(20,3,"SCORE:");
				OLED_ShowNum(75,3,SnakeLength-3,4,16);
				while(1)
				{
					switch(KEY_Scan(0))
					{
						case Right:
							OLED_Clear();
						 if(gOLED_Display.OLED_start)
						 { 
							 gOLED_Display.OLED_start = 0;
							 TIM4_Init(4999,7199);
							 HAL_TIM_Base_Stop(&htim4);
							 TIM2_Init(9,7199);
							 HAL_TIM_Base_Stop(&htim2);
							 MoveDirection = RIGHT; 
							 runflag=0;	
							 gOLED_Display.OLED_Page=3;
							 gOLED_Display.OLED_start = 0;						 
						 }
							break;
					}
					if(MoveDirection == RIGHT)
						break;
				}	
		 }	
	}
}
//显示年月日相关信息
void DayAndDayDisplay(void)                  //年月日
{
	OLED_ShowNum(0,1,calendar.w_year,4,12);              //年
  OLED_ShowNum(0,3,calendar.w_month,2,12);           //月
//	OLED_P6x8Str(0.7*16,4,"/");
	OLED_ShowNum(0,4,calendar.w_date,3,12);             //日
}
//显示时分相关形信息
void WhenTheDisplay(unsigned char page_t)                    //时分
{
		if(page_t)
		{
			#if 0
			OLED_P16x32Ch(1.4*18,2,calendar.hour/10);
			OLED_P16x32Ch(2.4*18,2,calendar.hour%10);
			OLED_P16x32Ch(3.4*18,2,10);
			OLED_P16x32Ch(4.4*18,2,calendar.min/10);
			OLED_P16x32Ch(5.4*18,2,calendar.min%10);
			#else
			m1 = calendar.hour/10;
			OLED_DataFlow(52,3,&a,&m1,1);
			m2 = calendar.hour%10;			
			OLED_DataFlow(64,3,&b,&m2,1);	
			OLED_Shownumber11X16(76,3,10); //显示“ : ”
			m3 = calendar.min/10;
			OLED_DataFlow(88,3,&c,&m3,1);	
			m4 = calendar.min%10;			
			OLED_DataFlow(100,3,&d,&m4,1);
			#endif
			OLED_ShowNum(6.4*18,3,calendar.sec,2,12);             //日
		}
		else
		{
		
		}
}
void OLED_SetClockTime(unsigned char x, unsigned char y,unsigned char w1)
{
		 OLED_ShowNum(w1*x,y,Set_RTCTime.Year/1000,1,12);
		 OLED_ShowNum((w1+1)*x,y,Set_RTCTime.Year%1000/100,1,12);
		 OLED_ShowNum((w1+2)*x,y,Set_RTCTime.Year%1000%100/10,1,12);
		 OLED_ShowNum((w1+3)*x,y,Set_RTCTime.Year%1000%100%10,1,12);
		 OLED_ShowNum((w1+5)*x,y,Set_RTCTime.Month/10,1,12);
		 OLED_ShowNum((w1+6)*x,y,Set_RTCTime.Month%10,1,12);
		 OLED_ShowNum((w1+8)*x,y,Set_RTCTime.Date/10,1,12);
		 OLED_ShowNum((w1+9)*x,y,Set_RTCTime.Date%10,1,12);
		 m1 = Set_RTCTime.Hour/10;
		 OLED_DataFlow(52,3,&a,&m1,1);
		 m2 = Set_RTCTime.Hour%10;			
		 OLED_DataFlow(64,3,&b,&m2,1);	
		 OLED_Shownumber11X16(76,3,10); //显示“ : ”
		 m3 = Set_RTCTime.Min/10;
		 OLED_DataFlow(88,3,&c,&m3,1);	
		 m4 = Set_RTCTime.Min%10;			
		 OLED_DataFlow(100,3,&d,&m4,1);
		 OLED_ShowNum(6.4*18,3,Set_RTCTime.Sec,2,12);             //日
}
void OLED_ClockTop(unsigned char page_t)
{
	//unsigned char keyvalue = 0;
	//DayAndDayDisplay();
	unsigned char tmp_t = 0;
	unsigned char ret = 0;
	//WhenTheDisplay(page_t);
	//OLED_ShowDate(6,5,10,0);
	OLED_SetClockTime(6,5,10);
	if(gOLED_Display.OLED_index%2==0)	
	{
		if(gOLED_Display.OLED_start == 0)
		{
			tmp_t = gOLED_Display.OLED_index;
			if(tmp_t > 6)
				OLED_P16x16Ch(0*16,6,10);
			else
				OLED_P16x16Ch(0*16,gOLED_Display.OLED_index,10);              //选择
			DisplayList(page_t);
			indexList(page_t,gOLED_Display.OLED_index);
		}
		switch(KEY_Scan(0))	
		{		
			case Left:                     //上翻
					 if(tmp_t > 6)
						 OLED_P16x16Ch(0*16,6,11);
					 else
						OLED_P16x16Ch(0*16,gOLED_Display.OLED_index,11);
				   gOLED_Display.OLED_index+=2;
				   break;
			case Determine:                    //确定
					 switch(gOLED_Display.OLED_index)
					 {
						 case 2:	
							 Set_RTCTime.Year++;
						   if(Set_RTCTime.Year >= 9999)
								 Set_RTCTime.Year = 0;
							 break;
						 case 4:
							 Set_RTCTime.Month++;
						   if(Set_RTCTime.Month > 12)
								 Set_RTCTime.Month = 1;
							 break;
						 case 6:
							 Set_RTCTime.Date++;
						   //分为30天、31天、29天、28天、
						   MoDat_of_Year[1] = (((Set_RTCTime.Year%4==0)&&(Set_RTCTime.Year%400==0)) || \
																		(Set_RTCTime.Year%400==0) ? 29 : 28);
						   if(Set_RTCTime.Date > MoDat_of_Year[Set_RTCTime.Month - 1])
								 Set_RTCTime.Date = 0;
							 break;
						 case 8:
							 Set_RTCTime.Hour++;
						   if(Set_RTCTime.Hour >= 24)
								 Set_RTCTime.Hour = 0;
							 break;
						 case 10:
							 Set_RTCTime.Min++;
							 if(Set_RTCTime.Min > 60)
								 Set_RTCTime.Min = 0;
							 break;
						 case 12:
							 Set_RTCTime.Sec++;
							 if(Set_RTCTime.Sec >= 60)
								 Set_RTCTime.Sec = 0;
							 break;
						 default:
							 break;
					 }
				   break;
			case Right:                       //返回
					 gOLED_Display.OLED_Page=1;
					 OLED_Clear();				
			     break;
			case HomeLgPre:
					 //长按Home更新时间
					 ret = RTC_Set(Set_RTCTime.Year,Set_RTCTime.Month,Set_RTCTime.Date, \
												 Set_RTCTime.Hour,Set_RTCTime.Min,Set_RTCTime.Sec); //设置日期和时间
					 if(ret == 0)
					 {
							//设置成功
							OLED_ShowChar(80,6,'O');
							OLED_ShowChar(88,6,'K');
					 }
					 else
					 {
							//设置失败
							OLED_ShowChar(80,6,'E');
							OLED_ShowChar(88,6,'R');					 
					 }
					 break;
			default : 
				   break;
		}
	}	
	if(gOLED_Display.OLED_index>12)gOLED_Display.OLED_index=2;
	if(gOLED_Display.OLED_index<2)gOLED_Display.OLED_index=12;
#if 0
	if(gOLED_Display.OLED_Page != 1 && gOLED_Display.OLED_start == 0)
	{
		OLED_ShowNum(6*16,0,page_t-1,1,12);
		OLED_P6x8Str(6.5*16,1,"/");
		OLED_ShowNum(7*16,0,gOLED_Display.OLED_index/2,1,12);
	}		
#endif
}
void OLED_SetAlarmTime(unsigned char x, unsigned char y,unsigned char w1)
{
		 OLED_ShowNum(w1*x,y,Set_Alarm.Year/1000,1,12);
		 OLED_ShowNum((w1+1)*x,y,Set_Alarm.Year%1000/100,1,12);
		 OLED_ShowNum((w1+2)*x,y,Set_Alarm.Year%1000%100/10,1,12);
		 OLED_ShowNum((w1+3)*x,y,Set_Alarm.Year%1000%100%10,1,12);
		 OLED_ShowNum((w1+5)*x,y,Set_Alarm.Month/10,1,12);
		 OLED_ShowNum((w1+6)*x,y,Set_Alarm.Month%10,1,12);
		 OLED_ShowNum((w1+8)*x,y,Set_Alarm.Date/10,1,12);
		 OLED_ShowNum((w1+9)*x,y,Set_Alarm.Date%10,1,12);
		 m1 = Set_Alarm.Hour/10;
		 OLED_DataFlow(52,3,&a,&m1,1);
		 m2 = Set_Alarm.Hour%10;			
		 OLED_DataFlow(64,3,&b,&m2,1);	
		 OLED_Shownumber11X16(76,3,10); //显示“ : ”
		 m3 = Set_Alarm.Min/10;
		 OLED_DataFlow(88,3,&c,&m3,1);	
		 m4 = Set_Alarm.Min%10;			
		 OLED_DataFlow(100,3,&d,&m4,1);
		 OLED_ShowNum(6.4*18,3,Set_Alarm.Sec,2,12);             //日
}
void OLED_AlarmTop(unsigned char page_t)
{
	unsigned char tmp_t = 0;
	OLED_SetAlarmTime(6,5,10);
	if(gOLED_Display.OLED_index%2==0)	
	{
		if(gOLED_Display.OLED_start == 0)
		{
			tmp_t = gOLED_Display.OLED_index;
			if(tmp_t > 6)
				OLED_P16x16Ch(0*16,6,10);
			else
				OLED_P16x16Ch(0*16,gOLED_Display.OLED_index,10);              //选择
			DisplayList(page_t);
			indexList(page_t-1,gOLED_Display.OLED_index);
		}
		switch(KEY_Scan(0))	
		{		
			case Left:                     //上翻
					 if(tmp_t > 6)
						 OLED_P16x16Ch(0*16,6,11);
					 else
						OLED_P16x16Ch(0*16,gOLED_Display.OLED_index,11);
				   gOLED_Display.OLED_index+=2;
				   break;
			case Determine:                    //确定
					 switch(gOLED_Display.OLED_index)
					 {
						 case 2:	
							 Set_Alarm.Year++;
						   if(Set_Alarm.Year >= 9999)
								 Set_Alarm.Year = 0;
							 break;
						 case 4:
							 Set_Alarm.Month++;
						   if(Set_Alarm.Month > 12)
								 Set_Alarm.Month = 1;
							 break;
						 case 6:
							 Set_Alarm.Date++;
						   //分为30天、31天、29天、28天、
						   MoDat_of_Year[1] = (((Set_Alarm.Year%4==0)&&(Set_Alarm.Year%400==0)) || \
																		(Set_Alarm.Year%400==0) ? 29 : 28);
						   if(Set_Alarm.Date > MoDat_of_Year[Set_Alarm.Month - 1])
								 Set_Alarm.Date = 0;
							 break;
						 case 8:
							 Set_Alarm.Hour++;
						   if(Set_Alarm.Hour >= 24)
								 Set_Alarm.Hour = 0;
							 break;
						 case 10:
							 Set_Alarm.Min++;
							 if(Set_Alarm.Min > 60)
								 Set_Alarm.Min = 0;
							 break;
						 case 12:
							 Set_Alarm.Sec++;
							 if(Set_Alarm.Sec >= 60)
								 Set_Alarm.Sec = 0;
							 break;
						 default:
							 break;
					 }
				   break;
			case Right:                       //返回
					 gOLED_Display.OLED_Page=1;
					 OLED_Clear();				
			     break;
			case HomeLgPre:
					 //设置成功
					 OLED_ShowChar(80,6,'O');
					 OLED_ShowChar(88,6,'K');
					 break;
			default : 
				   break;
		}
	}	
	if(gOLED_Display.OLED_index>12)gOLED_Display.OLED_index=2;
	if(gOLED_Display.OLED_index<2)gOLED_Display.OLED_index=12;
#if 1
	if(gOLED_Display.OLED_Page != 1 && gOLED_Display.OLED_start == 0)
	{
		OLED_ShowNum(6*16,0,page_t-1,1,12);
		OLED_P6x8Str(6.5*16,1,"/");
		OLED_ShowNum(7*16,0,gOLED_Display.OLED_index/2,1,12);
	}		
#endif	
}
void LED_MODE(unsigned char mode_t)
{
	switch(mode_t)
	{
		case 1:
			LED_RESET();
			break;
		case 2:
			LED_SET();
			break;
		case 3:
				LED_TOG();
			break;
		case 4:
				LED_TOG();
			break;
		default:break;
	}
}
void OLED_LedTop(unsigned char page_t)
{
	unsigned char tmp_t = 0;
	if(gOLED_Display.OLED_index%2==0)	
	{
		if(gOLED_Display.OLED_start == 0)
		{
			tmp_t = gOLED_Display.OLED_index;
			if(tmp_t > 6)
				OLED_P16x16Ch(0*16,6,10);
			else
				OLED_P16x16Ch(0*16,gOLED_Display.OLED_index,10);              //选择
			DisplayList(page_t);
			indexList(page_t,gOLED_Display.OLED_index);
			if(LED_STATE())
			{
				 OLED_P32x32Ch(70,3,18);		
			}
			else
			{
				 OLED_P32x32Ch(70,3,16);
			}
		}
		switch(KEY_Scan(0))	
		{		
			case Left:                     //上翻
					 if(tmp_t > 6)
						 OLED_P16x16Ch(0*16,6,11);
					 else
						OLED_P16x16Ch(0*16,gOLED_Display.OLED_index,11);
				   gOLED_Display.OLED_index+=2;
				   break;
			case Determine:                    //确定
					 switch(gOLED_Display.OLED_index)
					 {
						 case 2:	
							 Led_Light.Mode = 1;
							 break;
						 case 4:
							 Led_Light.Mode = 2;
							 break;
						 case 6:
							 Led_Light.Mode = 3;
							 break;
						 case 8:
							 Led_Light.Mode = 4;
							 break;
						 case 10:
							 break;
						 case 12:
							 break;
						 default:
							 break;
					 }
				   break;
			case Right:                       //返回
					 gOLED_Display.OLED_Page=1;
					 OLED_Clear();				
			     break;
			case HomeLgPre:
					 //设置成功
					 break;
			default : 
				   break;
		}
	}	
	if(gOLED_Display.OLED_index>12)gOLED_Display.OLED_index=2;
	if(gOLED_Display.OLED_index<2)gOLED_Display.OLED_index=12;
#if 1
	if(gOLED_Display.OLED_Page != 1 && gOLED_Display.OLED_start == 0)
	{
		OLED_ShowNum(6*16,0,page_t-1,1,12);
		OLED_P6x8Str(6.5*16,1,"/");
		OLED_ShowNum(7*16,0,gOLED_Display.OLED_index/2,1,12);
	}		
#endif

}
//显示温湿度
void TEMPDisplay(void)
{
		gSht20Date.Temp = SHT20_GetTempPoll();
	  OLED_P16x32Ch_Delay(3.2*18,2,(int)gSht20Date.Temp/10,3);
		OLED_P16x32Ch_Delay(4.2*18,2,(int)gSht20Date.Temp%10,3);	
		OLED_P8x16Str(5.3*18,4,".");
		OLED_P16x32Ch_Delay(5.7*18,2,(int)(gSht20Date.Temp*10)%10,3);
		OLED_P8x16Str(6.7*18,2,"C");	
}
void HUMIDisplay(void)
{
		gSht20Date.Humi = SHT20_GetHumiPoll();
	  OLED_P16x32Ch_Delay(3.2*18,2,(int)gSht20Date.Humi/10,3);
		OLED_P16x32Ch_Delay(4.2*18,2,(int)gSht20Date.Humi%10,3);	
		OLED_P8x16Str(5.3*18,4,".");
		OLED_P16x32Ch_Delay(5.7*18,2,(int)(gSht20Date.Humi*10)%10,3);
		OLED_P8x16Str(6.7*18,2,"%");	
}
void OLED_TempTop(unsigned char page_t)
{
		unsigned char keyvalue = 0;
	  gOLED_Display.OLED_time++;
		OLED_P32x32Ch(10,2,20);
		if(gOLED_Display.OLED_time >= 50)
			gOLED_Display.OLED_time=0;
		if(gOLED_Display.OLED_time < 25)
			TEMPDisplay();
		else
			HUMIDisplay();
		keyvalue = KEY_Scan(0);
		if(keyvalue == Right)
		{
			 gOLED_Display.OLED_Page=1;
			 OLED_Clear();		
		}
}
void OLED_SetTop(unsigned char page_t)
{
	unsigned char tmp_t = 0;
	if(gOLED_Display.OLED_index%2==0)	
	{
		if(gOLED_Display.OLED_start == 0)
		{
			tmp_t = gOLED_Display.OLED_index;
			if(tmp_t > 6)
				OLED_P16x16Ch(0*16,6,10);
			else
				OLED_P16x16Ch(0*16,gOLED_Display.OLED_index,10);              //选择
			DisplayList(page_t);
			indexList(page_t,gOLED_Display.OLED_index);
		}
		switch(KEY_Scan(0))	
		{		
			case Left:                     //上翻
					 if(tmp_t > 6)
						 OLED_P16x16Ch(0*16,6,11);
					 else
						 OLED_P16x16Ch(0*16,gOLED_Display.OLED_index,11);
				   gOLED_Display.OLED_index+=2;
				   break;
			case Determine:                    //确定
					 switch(gOLED_Display.OLED_index)
					 {
						 case 2:					 
							 break;
						 case 4:
							 break;
						 case 6:
							 break;
						 default:
							 break;
					 }
				   break;
			case Right:                       //返回
					 gOLED_Display.OLED_Page=1;
					 OLED_Clear();				
			     break;
			default : 
				   break;
		}
		
	}	
	if(gOLED_Display.OLED_index>12)gOLED_Display.OLED_index=2;
	if(gOLED_Display.OLED_index<2)gOLED_Display.OLED_index=12;
	if(gOLED_Display.OLED_Page != 1 && gOLED_Display.OLED_start == 0)
	{
		OLED_ShowNum(6*16,6,page_t-1,1,12);
		OLED_P6x8Str(6.5*16,7,"/");
		OLED_ShowNum(7*16,6,gOLED_Display.OLED_index/2,1,12);
	}				
}
void OLED_UserTop(unsigned char page_t)
{
	if(gOLED_Display.OLED_index%2==0)	
	{
		if(gOLED_Display.OLED_start == 0)
		{
			OLED_P16x16Ch(0*16,gOLED_Display.OLED_index,10);              //选择
			DisplayList(page_t);
			OLED_P32x32Ch(90,2,14);	
		}
		switch(KEY_Scan(0))	
		{		
			case Left:                     //上翻
				   OLED_P16x16Ch(0*16,gOLED_Display.OLED_index,11);
				   gOLED_Display.OLED_index+=2;
				   break;
			case Determine:                    //确定
					 switch(gOLED_Display.OLED_index)
					 {
						 case 2:					 
							 break;
						 case 4:
							 break;
						 case 6:
							 break;
						 default:
							 break;
					 }
				   break;
			case Right:                       //返回
					 gOLED_Display.OLED_Page=1;
					 OLED_Clear();				
			     break;
			default : 
				   break;
		}
		
	}	
	if(gOLED_Display.OLED_index>6)gOLED_Display.OLED_index=2;
	if(gOLED_Display.OLED_index<2)gOLED_Display.OLED_index=6;
	if(gOLED_Display.OLED_Page != 1 && gOLED_Display.OLED_start == 0)
	{
		OLED_ShowNum(6*16,6,page_t-1,1,12);
		OLED_P6x8Str(6.5*16,7,"/");
		OLED_ShowNum(7*16,6,gOLED_Display.OLED_index/2,1,12);
	}		
}
void Oled_DisplayPage(void)                          //人机界面
{
	switch(gOLED_Display.OLED_Page)	
	{		
		case 0:
			OLED_MainTop(gOLED_Display.OLED_Mode);
		break;
		case 1:
			OLED_DeskTop();
		break;
		case 2:
			OLED_Mp3Top(gOLED_Display.OLED_Page); 
		break;
		case 3:
			OLED_GameTop(gOLED_Display.OLED_Page);
		break;
		case 4:
			OLED_ClockTop(gOLED_Display.OLED_Page);
		break;
		case 5:
			OLED_AlarmTop(gOLED_Display.OLED_Page);
		break;
		case 6:
			OLED_LedTop(gOLED_Display.OLED_Page);
		break;
		case 7:
			OLED_TempTop(gOLED_Display.OLED_Page);
		break;
		case 8:
			OLED_SetTop(gOLED_Display.OLED_Page);
		break;
		case 9:
			OLED_UserTop(gOLED_Display.OLED_Page);
		break;
		default : break;
	}
	LED_MODE(Led_Light.Mode);
}


