#include "sht20.h"
#include "myiic.h"
#include "delay.h"
unsigned char SHT20_Init(void)
{
	 unsigned char err;
   err = SHT20_SoftReset();
	 return err;
}
unsigned char SHT20_SoftReset(void) //SHT20软件复位
{
	unsigned char err=0;
	IIC_Start();
  IIC_Send_Byte(0x80);
	err = IIC_Wait_Ack();
	IIC_Send_Byte(0xFE);
	err = IIC_Wait_Ack();
	IIC_Stop();
	return err;
}
float SHT20_GetTempPoll(void)
{
    float TEMP;
    unsigned char ack, tmp1, tmp2;
    unsigned short ST;
    unsigned short i=0;
    IIC_Start();				//发送IIC开始信号
    IIC_Send_Byte(I2C_ADR_W);			//IIC发送一个字节 
		ack = IIC_Wait_Ack();	
		IIC_Send_Byte(TRIG_TEMP_MEASUREMENT_POLL);
		ack = IIC_Wait_Ack();
    do {
        delay_ms(1);  			//默认100ms               
        IIC_Start();				//发送IIC开始信号
        IIC_Send_Byte(I2C_ADR_R);	
			  i++;
			  ack = IIC_Wait_Ack();
			  if(i==1000)
					break;
    } while(ack!=0);
    tmp1 = IIC_Read_Byte(1);
    tmp2 = IIC_Read_Byte(1);
		 IIC_Read_Byte(0);
    IIC_Stop();
    
    ST = (tmp1 << 8) | (tmp2 << 0);
	
    ST &= ~0x0003;
    TEMP = ((float)ST * 0.00268127) - 46.85;

    return (TEMP);	  
}
float SHT20_GetHumiPoll(void)
{
    float HUMI;
    unsigned char ack, tmp1, tmp2;
    unsigned short SRH;
		unsigned short i=0;
    
    IIC_Start();				//发送IIC开始信号
    IIC_Send_Byte(I2C_ADR_W);			//IIC发送一个字节 
		ack = IIC_Wait_Ack();	
		IIC_Send_Byte(TRIG_HUMI_MEASUREMENT_POLL);
		ack = IIC_Wait_Ack();    
    do {
        delay_ms(1);				//默认100ms               
        IIC_Start();				//发送IIC开始信号
        IIC_Send_Byte(I2C_ADR_R);	
			  i++;
			  ack = IIC_Wait_Ack();
			  if(i==100)break;
    } while(ack!=0);
    
    tmp1 = IIC_Read_Byte(1);

    tmp2 = IIC_Read_Byte(1);
     IIC_Read_Byte(0);
    IIC_Stop();
    
    SRH = (tmp1 << 8) | (tmp2 << 0);
    SRH &= ~0x0003;
    HUMI = ((float)SRH * 0.00190735) - 6;

    return (HUMI);
}
