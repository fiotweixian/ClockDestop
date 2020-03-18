#ifndef __OLED_H
#define __OLED_H			  	 
#include "stm32f1xx_hal.h"  


extern int Page_Sgin;
extern int Page_index;
//////////////////////////////////////////////////////////////////////////////////	 
//imodule	
//////////////////////////////////////////////////////////////////////////////////	

//OLED模式设置
//0:4线串行模式
//1:并行8080模式
#define OLED_MODE 0

#define DATE_GPIO 	GPIOA
//#define OLED_GPIO_CLK	RCC_APB2Periph_GPIOB
#define OLED_GPIO_CLK	A

#define OLED_SCLK	GPIO_PIN_5
#define OLED_SDIN	GPIO_PIN_7
#define OLED_RST	GPIO_PIN_4
#define OLED_RS		GPIO_PIN_6
#define OLED_CS		GPIO_PIN_3

//-----------------OLED端口定义----------------  					   
#define OLED_SCLK_Clr() HAL_GPIO_WritePin(DATE_GPIO,OLED_SCLK,GPIO_PIN_RESET)
#define OLED_SCLK_Set() HAL_GPIO_WritePin(DATE_GPIO,OLED_SCLK,GPIO_PIN_SET)

#define OLED_SDIN_Clr() HAL_GPIO_WritePin(DATE_GPIO,OLED_SDIN,GPIO_PIN_RESET)
#define OLED_SDIN_Set() HAL_GPIO_WritePin(DATE_GPIO,OLED_SDIN,GPIO_PIN_SET)

#define OLED_RST_Clr() HAL_GPIO_WritePin(DATE_GPIO,OLED_RST,GPIO_PIN_RESET)
#define OLED_RST_Set() HAL_GPIO_WritePin(DATE_GPIO,OLED_RST,GPIO_PIN_SET)

#define OLED_RS_Clr() HAL_GPIO_WritePin(DATE_GPIO,OLED_RS,GPIO_PIN_RESET)
#define OLED_RS_Set() HAL_GPIO_WritePin(DATE_GPIO,OLED_RS,GPIO_PIN_SET)

#define OLED_CS_Clr()  HAL_GPIO_WritePin(DATE_GPIO,OLED_CS,GPIO_PIN_RESET)//CS
#define OLED_CS_Set()  HAL_GPIO_WritePin(DATE_GPIO,OLED_CS,GPIO_PIN_SET)

//PC0~7,作为数据线
//#define DATAOUT(x) GPIO_Write(GPIOC,x);//输出  
//#define DATAOUT(x) GPIO_Write(GPIOC,x);//输出 
//使用4线串行接口时使用 

 		     
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
//snake
#define OLED_PAGE_Address 0xB0
#define OLED_LINE_Address_H 0x10
#define OLED_LINE_Address_L 0x00

//OLED控制用函数
void OLED_WR_Byte(uint8_t dat,uint8_t cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);		   
							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
void OLED_Fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t dot);
//void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size,uint8_t mode);
//void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr);
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len,unsigned char size);
//void OLED_ShowString(uint8_t x,uint8_t y,const uint8_t *p);	 
unsigned char KEY_Scan(unsigned char mode);
void OLED_StartClear(void);
void Status_Bar(void);
void Main_Menu(void);
void Menu_2(void);
void Menu_3(void);
void lnterface(void);
//snake
extern void Draw_Single_Point(uint8_t x,uint8_t y,uint8_t status);
extern void OLED_ShowString(unsigned char x,unsigned char y,unsigned char *chr);
extern void OLED_Clear1(uint8_t data);
extern void Boot_Animation(void);
extern void draw_circle(uint8_t x0,uint8_t y0,uint8_t r);
extern void OLED_Clear2(void);
void Draw_BMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
void LeftDisplay(void);
void OLED_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[]);
void OLED_P8x16Str(unsigned char x,unsigned  char y,unsigned char ch[]);
void OLED_P32x32Ch(unsigned char x,unsigned char y,unsigned int N);
void OLED_P16x32Ch(unsigned char x,unsigned char y,unsigned int N);
void OLED_P16x16Ch(unsigned char x,unsigned char y,unsigned int N);
void OLED_P16x32Ch_Delay(unsigned char x,unsigned char y,unsigned int N,uint8_t mdelay);
extern void OLED_Shownumber11X16(unsigned char x,unsigned char y,unsigned char no);
extern void OLED_DrawBMP(uint8_t x0, uint8_t y0,uint8_t x1, uint8_t y1,unsigned char BMP[]);
extern void secondMove(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,unsigned char num1[],unsigned char num2[]);
extern void OLED_DataFlow(uint8_t x,uint8_t y,uint8_t* SaveData,uint8_t* NowData,uint8_t size);
#endif  
	 



