#ifndef _MYIIC_H
#define _MYIIC_H
#include "main.h"
#include "stm32f1xx_hal.h"

//IO方向设置
#define SDA_IN()  {GPIOB->CRL&=0XFFFF0FFF;GPIOB->CRL|=(unsigned int)8<<12;}	//PB3输入模式 3x4=
#define SDA_OUT() {GPIOB->CRL&=0XFFFF0FFF;GPIOB->CRL|=(unsigned int)3<<12;} 	//PB3输出模式

//IO操作
#define IIC_SCL   PBout(4) //SCL
#define IIC_SDA   PBout(3) //SDA
#define READ_SDA  PBin(3)  //输入SDA


//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(unsigned char txd);			//IIC发送一个字节
unsigned char IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
unsigned char IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

void IIC_Write_One_Byte(unsigned char daddr,unsigned char addr,unsigned char data);
unsigned char IIC_Read_One_Byte(unsigned char daddr,unsigned char addr);	 
#endif

