#include "mp3.h"
#include "config.h"
#include "math.h"
#include "stm32_dsp.h"
#include "table_fft.h"
#include "adc.h"
#include "dma.h"
#include "display.h"
uint32_t Adc_SourceData[NEX]={0};
long lBufInArray[NEX];
long lBufOutArray[NEX/2];
long lBufMagArray[NEX/2];
uint8_t prt = 10;	//量化显示的比例
uint8_t Fali_Point[128];	//记录下落点的坐标
void MP3_Init(void)
{
	uint16_t i = 0;
	for(i=0;i<128;i++)
		Fali_Point[i] = 63;	
}
//获取FFT后的直流分量
void FFT_GetDcComponent(void)
{
    signed short lX,lY;
    float X,Y,Mag;
    unsigned short i;
    for(i=0; i<NEX/2; i++)
    {
        lX  = (lBufOutArray[i] << 16) >> 16;
        lY  = (lBufOutArray[i] >> 16);
			
				//除以32768再乘65536是为了符合浮点数计算规律
        X = NEX * ((float)lX) / 32768;
        Y = NEX * ((float)lY) / 32768;
        Mag = sqrt(X * X + Y * Y)*1.0/ NEX;
        if(i == 0)	
            lBufMagArray[i] = (unsigned long)(Mag * 32768);
        else
            lBufMagArray[i] = (unsigned long)(Mag * 65536);
    }
}
/*柱状显示*/
void Mp3_UnColuDisplay(void)
{
	uint16_t i = 0;
	uint8_t x = 0;
	uint8_t y = 0;
	uint8_t points[256];	
	/*******************显示*******************/
	GUI_ClearSCR();
	// 时域
	#if 1
	for(i = 0; i < 128; i++)
	{
		points[2*i] = 2*i;
		points[2*i+1] = Adc_SourceData[i]/128;
		if(points[2*i+1] > 32)	points[2*i+1] = 32;	// 限制在上半屏幕
	}
	GUI_PointS(points, 128, 0x0f);
	#endif
	for(i = 0; i < 32; i++)	//间隔的取32个频率出来显示
	{
		x = (i<<2);	//i*4
		y = 63-(lBufMagArray[x+1]/prt)-2;	//加1是为了丢掉第一个直流分量
		if(y>63) y = 63;

		GUI_LineWith(x,63-y,x,0,3,1);
		
		//画下落的点
		if(Fali_Point[i]>y) Fali_Point[i] = y;
		else
		{
				if(Fali_Point[i]>63) Fali_Point[i]=63;
				GUI_LineWith(x,63 - Fali_Point[i],x,63 - Fali_Point[i],3,1);
				Fali_Point[i] += 2 ;
		}
	}
	GUI_Exec();
}
/*单柱状显示*/
void Mp3_MiniUnColuDisplay(void)
{
	uint16_t i = 0;
	uint8_t y = 0;
	
	/*******************显示*******************/
	GUI_ClearSCR();
	for(i = 1; i < 128; i++)	
	{
		y = 63-(lBufMagArray[i]/prt)-2;
		if(y>63) y = 63;
		
		GUI_RLine(i,63 - y,0,1);		
		//画下落的点
		if(Fali_Point[i]>y) Fali_Point[i] = 63- y;
		else
		{
				if(Fali_Point[i]>63) Fali_Point[i]=63 -y;
				GUI_RLine(i,Fali_Point[i],Fali_Point[i]+1,1);
				Fali_Point[i] += 2 ;
		}
	}
	GUI_Exec();
}
/*柱状显示 中间对称*/
void Mp3_MiddleColuDisplay(void)
{
	uint16_t i = 0;
	uint8_t y = 0;
	
	/*******************显示*******************/
	GUI_ClearSCR();
	for(i = 0; i < 127; i++)	
	{
		y = 31-(lBufMagArray[i+1]/prt)-2;	//加1是为了丢掉第一个直流分量
		if(y>31) y = 31;
		
		GUI_RLine(i,32,y,1);
		GUI_RLine(i,32,63-y,1);
		
		//画下落的点
		if(Fali_Point[i]>y) Fali_Point[i] = y;
		else
		{
				if(Fali_Point[i]>30) Fali_Point[i]=30;
				GUI_RLine(i,Fali_Point[i],Fali_Point[i]+1,1);
				GUI_RLine(i,63-Fali_Point[i],63-(Fali_Point[i]+1),1);
				Fali_Point[i] += 2 ;
		}
	}
	GUI_Exec();
}
/*单柱状显示 中间对称*/
void Mp3_Mi2ddleColuDisplay(void)
{
	uint16_t i = 0;
	uint8_t x = 0;
	uint8_t y = 0;
	
	/*******************显示*******************/
	GUI_ClearSCR();
	for(i = 0; i < 32; i++)	//间隔的取32个频率出来显示
	{
		x = (i<<2);	//i*4
		y = 31-(lBufMagArray[x+1]/prt)-2;	//加1是为了丢掉第一个直流分量
		if(y>31) y = 31;
		
		GUI_LineWith(x,y,x,32,3,1);
		GUI_LineWith(x,63-y,x,32,3,1);
		
		//画下落的点
		if(Fali_Point[i]>y) Fali_Point[i] = y;
		else
		{
				if(Fali_Point[i]>31) Fali_Point[i]=31;
				GUI_LineWith(x,Fali_Point[i],x,Fali_Point[i]+3,3,1);
				GUI_LineWith(x,63 - Fali_Point[i],x,63 - Fali_Point[i]-3,3,1);
				Fali_Point[i] += 2 ;
		}
	}
	GUI_Exec();
}

/*单柱状显示*/
void Mp3_SMiddleColuDisplay(void)
{
	uint16_t i = 0;
	uint8_t y = 0;
	
	/*******************显示*******************/
	GUI_ClearSCR();
	for(i = 1; i < 128; i++)	
	{
		y = 63-(lBufMagArray[i]/prt)-2;
		if(y>63) y = 63;
		
		GUI_RLine(i,63 - y,0,1);		
		//画下落的点
		if(Fali_Point[i]>y) Fali_Point[i] = y;
		else
		{
				if(Fali_Point[i]>63) Fali_Point[i]=y;
				GUI_RLine(i,Fali_Point[i],Fali_Point[i],1);
				Fali_Point[i] += 1 ;
		}
	}
	GUI_Exec();
}
/*单柱状显示*/
void Mp3_RMiddleColuDisplay(void)
{
	uint16_t i = 0;
	uint8_t y = 0;
	
	/*******************显示*******************/
	GUI_ClearSCR();
	for(i = 1; i < 128; i++)	
	{
		y = 63-(lBufMagArray[i]/prt)-2;
		if(y>63) y = 63;
		
		GUI_RLine(i,63 - y,0,1);		
		//画下落的点
		if(Fali_Point[i]>y) Fali_Point[i] = 63;
		else
		{
				if(Fali_Point[i]>63) Fali_Point[i]=63 -y;
				GUI_RLine(i,Fali_Point[i],Fali_Point[i]+1,1);
				Fali_Point[i] += 2 ;
		}
	}
	GUI_Exec();
}
/*柱状显示*/
void Mp3_TMiddleColuDisplay(void)
{
	uint16_t i = 0;
	uint8_t x = 0;
	uint8_t y = 0;
	
	/*******************显示*******************/
	GUI_ClearSCR();
	for(i = 0; i < 64; i++)	//间隔的取32个频率出来显示
	{
		x = (i<<1);	//i*4
		y = 63-(lBufMagArray[x+1]/prt)-2;	//加1是为了丢掉第一个直流分量
		if(y>63) y = 63;

		GUI_LineWith(x,63-y,x,0,3,1);
		
		//画下落的点
		if(Fali_Point[i]>y) Fali_Point[i] = y;
		else
		{
				if(Fali_Point[i]>63) Fali_Point[i]=63;
				GUI_LineWith(x,63 - Fali_Point[i],x,63 - Fali_Point[i],3,1);
				Fali_Point[i] += 2 ;
		}
	}
	GUI_Exec();
}
//ADC DMA传输中断
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	uint16_t i = 0;
	static uint16_t num = 0;	
	HAL_ADC_Stop_DMA(&hadc1);							//完成一次测量 关闭DMA传输
	//填充数组
	for(i=0;i<NEX;i++)
		lBufInArray[i] = ((signed short)(Adc_SourceData[i]-3103)) << 16;		//这里因为单片机的ADC只能测正的电压 所以需要前级加直流偏执
																																	//加入直流偏执后 软件上减去2048即一半 达到负半周期测量的目的
	//cr4_fft_1024_stm32(lBufOutArray, lBufInArray, NEX);							//FFT变换
	cr4_fft_256_stm32(lBufOutArray, lBufInArray, NEX);
	FFT_GetDcComponent();																									//取直流分量对应的AD值
//	//打印出来测试
//	for(i=0;i<NPT/2;i++)
//		printf("i:%3d, f:%.2f, Power:%10d\r\n", i, (float)i*Fs/NEX, lBufMagArray[i]);
	
	
	if(!Mp3_Data.Mode)
	{
		Mp3_Data.Auto = 1;
		if(num>300)
		{
			num = 0;
		}
	}
	else
	{
		Mp3_Data.Auto = 0;
		Mp3_Data.Count = Mp3_Data.DisSort;
	}
	//自动显示
	if(Mp3_Data.Auto == 1)
	{
		num++;
		if(num>300)
		{
			num = 0;
			Mp3_Data.Count++;
			if(Mp3_Data.Count>SHOW_PAGE) Mp3_Data.Count = 1;
		}
	}
	//显示
	switch(Mp3_Data.Count)
	{
		case 1:
			Mp3_UnColuDisplay();
			break;
		case 2:
			Mp3_MiniUnColuDisplay();
			break;
		case 3:
			Mp3_MiddleColuDisplay();
			break;
		case 4:
			Mp3_Mi2ddleColuDisplay();
			break;
		case 5:
			Mp3_SMiddleColuDisplay();
			break;
		case 6:
			Mp3_RMiddleColuDisplay();
			break;
		case 7:
			Mp3_TMiddleColuDisplay();
			break;
		default:
			Mp3_TMiddleColuDisplay();
			break;
	}
	HAL_ADC_Start_DMA(&hadc1, Adc_SourceData, NEX);
}
