#include "oled.h"
#include "oledfont.h" 
#include "rtc.h"  
#include "led.h"
#include "key.h"
#include "delay.h"
#include "adc.h"  
#include "dma.h"
#include "tim.h"
#include "config.h"
#include "snake.h"
#include "math.h"

//OLED���Դ�
//��Ÿ�ʽ����.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   
uint16_t OLED_GRAM[128][8];	 
//�����Դ浽LCD		 
void OLED_Refresh_Gram(void)
{
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA); 
	}   
}
#if OLED_MODE==1
//��SSD1306д��һ���ֽڡ�
//dat:Ҫд�������/����
//cmd:����/�����־ 0,��ʾ����;1,��ʾ����;
void OLED_WR_Byte(uint8_t dat,uint8_t cmd)
{
	//DATAOUT(dat);	    
	if(cmd)
	  OLED_RS_Set();
	else 
	  OLED_RS_Clr();		   
	OLED_CS_Clr();
	OLED_WR_Clr();	 
	OLED_WR_Set();
	OLED_CS_Set();	  
	OLED_RS_Set();	 
} 	    	    
#else
//��SSD1306д��һ���ֽڡ�
//dat:Ҫд�������/����
//cmd:����/�����־ 0,��ʾ����;1,��ʾ����;
void OLED_WR_Byte(uint8_t dat,uint8_t cmd)
{	
	uint8_t i;	
	if(cmd)
	  OLED_RS_Set();
	else 
	  OLED_RS_Clr();
#if 1	
	OLED_CS_Clr();
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();
		if(dat&0x80)
		   OLED_SDIN_Set();
		else 
		   OLED_SDIN_Clr();
		OLED_SCLK_Set();
		dat<<=1;   
	}				 		  
	OLED_CS_Set();
	OLED_RS_Set();
#else
	OLED_CS_Clr();
  HAL_SPI_Transmit(&hspi1,&dat,1, 1000);
	OLED_CS_Set();
#endif	
} 
#endif
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD); 
} 	  	  
//����OLED��ʾ    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//�ر�OLED��ʾ     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		  
//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!	  
void OLED_Clear(void)  
{  
	uint8_t i,n;  
	for(i=0;i<8;i++)for(n=0;n<128;n++)OLED_GRAM[n][i]=0X00;  
	OLED_Refresh_Gram();//������ʾ
}
void OLED_Clear2(void)  
{  
	uint8_t i,n;  
	for(i=0;i<8;i++)for(n=0;n<75;n++)OLED_GRAM[n][i]=0X00;  
	OLED_Refresh_Gram();//������ʾ
}
//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!	  
void OLED_StartClear(void)  
{  
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x02,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //������ʾ
}
//���� 
//x:0~127
//y:0~63
//t:1 ��� 0,���				   
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t)
{
	uint8_t pos,bx,temp=0;
	if(x>131||y>63)return;//������Χ��.
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)OLED_GRAM[x][pos]|=temp;
	else OLED_GRAM[x][pos]&=~temp;	    
}
//x1,y1,x2,y2 �������ĶԽ�����
//ȷ��x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63	 	 
//dot:0,���;1,���	  
void OLED_Fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t dot)  
{  
	uint8_t x,y;  
	for(x=x1;x<=x2;x++)
	{
		for(y=y1;y<=y2;y++)OLED_DrawPoint(x,y,dot);
	}													    
	OLED_Refresh_Gram();//������ʾ
}
//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ				 
//size:ѡ������ 16/12 
#if 0
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size,uint8_t mode)
{      			    
	uint8_t temp,t,t1;
	uint8_t y0=y;
	chr=chr-' ';//�õ�ƫ�ƺ��ֵ				   
    for(t=0;t<size;t++)
    {   
		if(size==12)temp=oled_asc2_1206[chr][t];  //����1206����
		else temp=oled_asc2_1608[chr][t];		 //����1608���� 	                          
        for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)OLED_DrawPoint(x,y,mode);
			else OLED_DrawPoint(x,y,!mode);
			temp<<=1;
			y++;
			if((y-y0)==size)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
    }          
}
#else
#define Max_Column	128
#define SIZE 1
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr)
{      	
	 unsigned char c=0,i=0;	
		c=chr-' ';//�õ�ƫ�ƺ��ֵ			
		if(x>Max_Column-1){x=0;y=y+2;}
		if(SIZE==0)
			{
				OLED_Set_Pos(x,y);	
				for(i=0;i<8;i++)
				OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
				OLED_Set_Pos(x,y+1);
				for(i=0;i<8;i++)
				OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
			}
			else {	
				OLED_Set_Pos(x,y+1);
				for(i=0;i<6;i++)
				OLED_WR_Byte(F6x8[c][i],OLED_DATA);
				
			}
}
#endif
//m^n����
uint32_t oled_pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//��ʾ2������
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);
#if 0
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size/2)*t,y,' ',size,1);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0',size,1); 
	}	
} 
#else
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len,unsigned char size)
{         	
	unsigned char t,temp;
	unsigned char enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size/2)*t,y,' ');
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0'); 
	}
} 
#endif
//��ʾ�ַ���
//x,y:�������  
//*p:�ַ�����ʼ��ַ
//��16����
#if 0
void OLED_ShowString(uint8_t x,uint8_t y,const uint8_t *p)
{
// #define MAX_CHAR_POSX 122
 #define MAX_CHAR_POSX 126
#define MAX_CHAR_POSY 58          
    while(*p!='\0')
    {       
        if(x>MAX_CHAR_POSX){x=0;y+=16;}
        if(y>MAX_CHAR_POSY){y=x=0;OLED_Clear();}
        OLED_ShowChar(x,y,*p,16,1);	 
        x+=8;
        p++;
    } 
}	   
#endif
void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
#if OLED_GPIO_CLK == A
  __HAL_RCC_GPIOA_CLK_ENABLE();
#endif
	#if OLED_GPIO_CLK == B
  __HAL_RCC_GPIOB_CLK_ENABLE();
#endif
	#if OLED_GPIO_CLK == C
  __HAL_RCC_GPIOC_CLK_ENABLE();
#endif
  GPIO_InitStruct.Pin = OLED_SCLK|OLED_SDIN|OLED_RST|OLED_RS|OLED_CS;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DATE_GPIO, &GPIO_InitStruct);
	HAL_GPIO_WritePin(DATE_GPIO,OLED_SCLK|OLED_SDIN|OLED_RST|OLED_RS|OLED_CS,GPIO_PIN_SET);	
}
void OLED_Init(void)
{
	GPIO_Config();
	OLED_RST_Set(); 
	HAL_Delay(200);
	OLED_RST_Clr();
	HAL_Delay(200);
	OLED_RST_Set(); 
	
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x02,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	
	OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
	OLED_StartClear();
	OLED_Set_Pos(0,0); 
}
/*****************������������ʾ16*16����  ��ʾ�����꣨x,y����yΪҳ��Χ0��7****************************/
void OLED_P8x16Ch(unsigned char x,unsigned char y,unsigned int N)
{
	unsigned char wm=0;
	unsigned int adder=32*N;
	OLED_Set_Pos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WR_Byte(F16x16[adder],OLED_DATA); 
		adder += 1;
	}	  	
}
void OLED_P16x16Ch(unsigned char x,unsigned char y,unsigned int N)
{
	unsigned char wm=0;
	unsigned int adder=32*N;
	OLED_Set_Pos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WR_Byte(F16x16[adder],OLED_DATA); 
		adder += 1;
	}
	OLED_Set_Pos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WR_Byte(F16x16[adder],OLED_DATA);
		adder += 1;
	} 	  	
}
void OLED_P16x32Ch(unsigned char x,unsigned char y,unsigned int N)
{
	unsigned char wm=0;
	unsigned int adder=64*N;
	OLED_Set_Pos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WR_Byte(F16x32[adder],OLED_DATA); 
		adder += 1;
	}
	OLED_Set_Pos(x,y+1 );
	for(wm = 0;wm <16;wm++)
	{
		OLED_WR_Byte(F16x32[adder],OLED_DATA);
		adder += 1;
	} 
	OLED_Set_Pos(x , y+2);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WR_Byte(F16x32[adder],OLED_DATA); 
		adder += 1;
	}
	OLED_Set_Pos(x,y+3 );
	for(wm = 0;wm <16;wm++)
	{
		OLED_WR_Byte(F16x32[adder],OLED_DATA);
		adder += 1;
	} 	 		
}
void OLED_P32x32Ch(unsigned char x,unsigned char y,unsigned int N)
{
	unsigned char wm=0;
	unsigned int adder=64*N;
	OLED_Set_Pos(x , y);
	for(wm = 0;wm < 32;wm++)
	{
		OLED_WR_Byte(F32x32[adder],OLED_DATA); 
		adder += 1;
	}
	delay_ms(50);
	OLED_Set_Pos(x,y+1 );
	for(wm = 0;wm <32;wm++)
	{
		OLED_WR_Byte(F32x32[adder],OLED_DATA);
		adder += 1;
	}
	delay_ms(50);	
	OLED_Set_Pos(x , y+2);
	for(wm = 0;wm < 32;wm++)
	{
		OLED_WR_Byte(F32x32[adder],OLED_DATA); 
		adder += 1;
	}	delay_ms(50);
	OLED_Set_Pos(x,y+3 );
	for(wm = 0;wm <32;wm++)
	{
		OLED_WR_Byte(F32x32[adder],OLED_DATA);
		adder += 1;
	} 		delay_ms(50); 		
}
void OLED_P16x32Ch_Delay(unsigned char x,unsigned char y,unsigned int N,uint8_t mdelay)
{
	unsigned char wm=0;
	unsigned int adder=64*N;
	OLED_Set_Pos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WR_Byte(F16x32[adder],OLED_DATA); 
		adder += 1;
		delay_ms(mdelay);
	}
	OLED_Set_Pos(x,y+1 );
	for(wm = 0;wm <16;wm++)
	{
		OLED_WR_Byte(F16x32[adder],OLED_DATA);
		adder += 1;
		delay_ms(mdelay);
	} 
	OLED_Set_Pos(x , y+2);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WR_Byte(F16x32[adder],OLED_DATA); 
		adder += 1;
		delay_ms(mdelay);
	}
	OLED_Set_Pos(x,y+3 );
	for(wm = 0;wm <16;wm++)
	{
		OLED_WR_Byte(F16x32[adder],OLED_DATA);
		adder += 1;
		delay_ms(mdelay);
	} 	 		
}
/***************������������ʾ6*8һ���׼ASCII�ַ���	��ʾ�����꣨x,y����yΪҳ��Χ0��7****************/
void OLED_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[])
{
	unsigned char c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>126){x=0;y++;}
		OLED_Set_Pos(x,y);
		for(i=0;i<6;i++)
		OLED_WR_Byte(F6x8[c][i],OLED_DATA);
		x+=6;
		j++;
	}
}
#if 0
void OLED_P128x48Ch(unsigned char x,unsigned char y,unsigned int N)
{
	unsigned char wm=0;
	unsigned int adder=768*N;
	OLED_Set_Pos(x , y);
	for(wm = 0;wm < 128;wm++)
	{
		OLED_WR_Byte(F128x48[adder],OLED_DATA); 
		adder += 1;
	}
	OLED_Set_Pos(x,y+1);
	for(wm = 0;wm <128;wm++)
	{
		OLED_WR_Byte(F128x48[adder],OLED_DATA);
		adder += 1;
	} 
	OLED_Set_Pos(x , y+2);
	for(wm = 0;wm < 128;wm++)
	{
		OLED_WR_Byte(F128x48[adder],OLED_DATA); 
		adder += 1;
	}
	OLED_Set_Pos(x,y+3 );
	for(wm = 0;wm <128;wm++)
	{
		OLED_WR_Byte(F128x48[adder],OLED_DATA);
		adder += 1;
	}  
	OLED_Set_Pos(x,y+4 );
	for(wm = 0;wm <128;wm++)
	{
		OLED_WR_Byte(F128x48[adder],OLED_DATA);
		adder += 1;
	}
	OLED_Set_Pos(x,y+5 );
	for(wm = 0;wm <128;wm++)
	{
		OLED_WR_Byte(F128x48[adder],OLED_DATA);
		adder += 1;
	}  	
}
#endif
/*******************������������ʾ8*16һ���׼ASCII�ַ���	 ��ʾ�����꣨x,y����yΪҳ��Χ0��7****************/
void OLED_P8x16Str(unsigned char x,unsigned  char y,unsigned char ch[])
{
	unsigned char c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>120){x=0;y++;}
		OLED_Set_Pos(x,y);
		for(i=0;i<8;i++)
		OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
		OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
		x+=8;
		j++;
	}
}
/******************************�Թ̶�ʾ11X16��second[]*********************************************************************************/
void OLED_Shownumber11X16(unsigned char x,unsigned char y,unsigned char no)
{                                  
  unsigned char t, i;
  for (i = 0; i < 2; i++)
  {
    OLED_Set_Pos(x, y + i);
    for(t = 0; t < 11; t++)
    {
			OLED_WR_Byte(second[no][11 * i + t],OLED_DATA);
    }
  }
}
/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
void OLED_DrawBMP(uint8_t x0, uint8_t y0,uint8_t x1, uint8_t y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
	    }
	}
} 
/************************������ʾ:���õ�***11X16****************************************************************************************************************/
void secondMove(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,unsigned char num1[],unsigned char num2[])//x1��y1��Ӧ��������ʾ�ֵó���ƥ��
{
	uint8_t i=0,j=0,k=16;//k����λ��
	unsigned char tempArr[44];//������ģ��������
	for(i=0;i<22;i++)
	{
		tempArr[i]=num1[i];
	}
	for(i=0;i<22;i++)//�޸�i<__������
	{
		tempArr[i+22]=num2[i];//�޸�i+__������
	}
	while(k--) 
	{
			for(j=0;j<4;j++)//
			{
				for(i=j*11;i<(j+1)*11;i++)//j*�ֿ�(j+1)*�ֿ�
				{
					tempArr[i]=tempArr[i]>>1;  //ÿ���ƶ�1��
					tempArr[i]|=((tempArr[i+11]&0x01)<<7);
					delay_us(150);
				}
			}
		OLED_DrawBMP(x0,y0,x1,y1,tempArr);			
	}
}
/************************������ʾ:���õ� mid[] 20X32*******************************************************************************************************************/
/**
*���������������ƶ�
*ÿ���ƶ�2λ
*ԭ����������ģ���һ��ͼƬ��Ȼ����λ��ʾ
**/
void BnumUpMove(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,unsigned char num1[],unsigned char num2[])//x1��y1��Ӧ��������ʾ�ֵó���ƥ��
{
	uint8_t i=0,j=0,k=32;//k����λ��
	unsigned char tempArr[160];//������ģ��������
	for(i=0;i<80;i++)
	{
		tempArr[i]=num1[i];
	}
	for(i=0;i<80;i++)//�޸�i<__������
	{
		tempArr[i+80]=num2[i];//�޸�i+__������
	}
	while(k--)
	{
			for(j=0;j<8;j++)
			{
				for(i=j*20;i<(j+1)*20;i++)//j*�ֿ�(j+1)*�ֿ�
				{
					tempArr[i]=tempArr[i]>>1;  //ÿ���ƶ�1��
					tempArr[i]|=((tempArr[i+20]&0x01)<<7);
					delay_us(50);
				}
			}
		OLED_DrawBMP(x0,y0,x1,y1,tempArr);
			
	}
}
/*******************************�̶���ʾ20X32��mid[]**************************************************************************************/
void OLED_Shownumber(unsigned char x,unsigned char y,unsigned char no)
{                                  
  unsigned char t, i;
  for (i = 0; i < 4; i++)
  {
    OLED_Set_Pos(x, y + i);
    for(t = 0; t < 20; t++)
    {
			OLED_WR_Byte(mid[no][20 * i + t],OLED_DATA);
    }
  }
}
/*****************************���λ��m2��ʾ*************************************************/
void OLED_DataFlow(uint8_t x,uint8_t y,uint8_t* SaveData,uint8_t* NowData,uint8_t size)
{
	if(*SaveData==*NowData) 	
	{
		if(size)
		{
			OLED_Shownumber11X16(x,y,*NowData);
		}
		else
		{
			OLED_Shownumber(x,y,*NowData);
		}
		*SaveData=*NowData;
	}
	else
	{
			if(size)
			{
				switch (*NowData)
				 {
					 case 0:secondMove(x,y,x+11,y+2,second[9],second[0]);break;	
					 case 1:secondMove(x,y,x+11,y+2,second[0],second[1]);break;	
					 case 2:secondMove(x,y,x+11,y+2,second[1],second[2]);break;	
					 case 3:secondMove(x,y,x+11,y+2,second[2],second[3]);break;	
					 case 4:secondMove(x,y,x+11,y+2,second[3],second[4]);break;	
					 case 5:secondMove(x,y,x+11,y+2,second[4],second[5]);break;	
					 case 6:secondMove(x,y,x+11,y+2,second[5],second[6]);break;	
					 case 7:secondMove(x,y,x+11,y+2,second[6],second[7]);break;	
					 case 8:secondMove(x,y,x+11,y+2,second[7],second[8]);break;	
					 case 9:secondMove(x,y,x+11,y+2,second[8],second[9]);break;	
				 }
			 }
			else
			{
				switch (*NowData)
				 {
		       case 0:BnumUpMove(x,y,x+20,y+4,mid[9],mid[0]);break;	
		       case 1:BnumUpMove(x,y,x+20,y+4,mid[0],mid[1]);break;	
		       case 2:BnumUpMove(x,y,x+20,y+4,mid[1],mid[2]);break;	
		       case 3:BnumUpMove(x,y,x+20,y+4,mid[2],mid[3]);break;	
		       case 4:BnumUpMove(x,y,x+20,y+4,mid[3],mid[4]);break;	
		       case 5:BnumUpMove(x,y,x+20,y+4,mid[4],mid[5]);break;	
		       case 6:BnumUpMove(x,y,x+20,y+4,mid[5],mid[6]);break;	
		       case 7:BnumUpMove(x,y,x+20,y+4,mid[6],mid[7]);break;	
		       case 8:BnumUpMove(x,y,x+20,y+4,mid[7],mid[8]);break;	
		       case 9:BnumUpMove(x,y,x+20,y+4,mid[8],mid[9]);break;	
				 }					 
			}
		*SaveData=*NowData;
	}		 
}
//snake
void OLED_Set_Address(uint8_t column,uint8_t page)
{
   OLED_WR_Byte(OLED_PAGE_Address+page,OLED_CMD); 

   OLED_WR_Byte(OLED_LINE_Address_L+column%16,OLED_CMD);
   OLED_WR_Byte(OLED_LINE_Address_H+column/16,OLED_CMD);  
}

/*************************************************
**�������� Draw_Single_Point
**��������������������
**���������x��y��status��
**�����������
**˵����x��0~127��y��0~63��
**************************************************/
void Draw_Single_Point(uint8_t x,uint8_t y,uint8_t status)
{
   uint8_t page,temp,ColumnCoordinate,PresentData;
	
	 page = y/8;
	 temp = y%8;
	 ColumnCoordinate = 0x01<<temp;
	
	 switch(ColumnCoordinate)
	 {
		  case 0x01: PresentData=0x01;break;
		  case 0x02: PresentData=0x02;break;
		  case 0x04: PresentData=0x04;break;
		  case 0x08: PresentData=0x08;break;
		  case 0x10: PresentData=0x10;break;
		  case 0x20: PresentData=0x20;break;
		  case 0x40: PresentData=0x40;break;
		  case 0x80: PresentData=0x80;break;
		  default: break;
	 }	 
	
	 if(status==DRAW)
	   { SnakeCoordinate[page][x] |=PresentData; }
	 else 
		 if(status==CLEAR)
		 { SnakeCoordinate[page][x] &=~PresentData; }
		 
	 OLED_Set_Address(x,page);
   OLED_WR_Byte(SnakeCoordinate[page][x],OLED_DATA);		 
}
//��ʾһ���ַ��Ŵ�
void OLED_ShowString(unsigned char x,unsigned char y,unsigned char *chr)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j]);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}
void OLED_Clear1(uint8_t data)
{
   uint32_t counter_x,counter_y;
	 for(counter_y=0;counter_y<8;counter_y++)
	 {
	    OLED_WR_Byte(OLED_PAGE_Address+counter_y,OLED_CMD);
		  OLED_WR_Byte(OLED_LINE_Address_L,OLED_CMD);
		  OLED_WR_Byte(OLED_LINE_Address_H,OLED_CMD);
		  
		  for(counter_x=0;counter_x<128;counter_x++)
		     OLED_WR_Byte(data,OLED_DATA);   
	 }
}
/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
void Draw_BMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[])
{
	unsigned int j=0;
	unsigned char x,y;

  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);
	    }
	}
}




















