#ifndef _MYIIC_H
#define _MYIIC_H
#include "main.h"
#include "stm32f1xx_hal.h"

//IO��������
#define SDA_IN()  {GPIOB->CRL&=0XFFFF0FFF;GPIOB->CRL|=(unsigned int)8<<12;}	//PB3����ģʽ 3x4=
#define SDA_OUT() {GPIOB->CRL&=0XFFFF0FFF;GPIOB->CRL|=(unsigned int)3<<12;} 	//PB3���ģʽ

//IO����
#define IIC_SCL   PBout(4) //SCL
#define IIC_SDA   PBout(3) //SDA
#define READ_SDA  PBin(3)  //����SDA


//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(unsigned char txd);			//IIC����һ���ֽ�
unsigned char IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
unsigned char IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(unsigned char daddr,unsigned char addr,unsigned char data);
unsigned char IIC_Read_One_Byte(unsigned char daddr,unsigned char addr);	 
#endif

