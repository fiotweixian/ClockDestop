#include "snake.h"
#include "string.h"
#include "oled.h"
//snake
uint8_t CheckBuffer[420];//�߰�λ��x���꣬�Ͱ�λ��y����
uint16_t MoveCoordinate[420];//�߰�λ��x���꣬�Ͱ�λ��y����
uint8_t SnakeCoordinate[8][128];
uint16_t SnakeLength;
uint8_t SnakeCoordinate_x,SnakeCoordinate_y;
uint8_t FoodCoordinate_x,FoodCoordinate_y;
uint8_t MoveDirection;
uint16_t Counter_x=166,Counter_y=1785;
uint8_t runflag=0;
/*************************************************
**�������� Snake_Init
**������������ʼ�������ȡ������ʳ������
**�����������
**�����������
**˵������
**************************************************/
void Snake_Init(void)
{
	 memset(CheckBuffer,0,sizeof(CheckBuffer));
	 memset(MoveCoordinate,0,sizeof(MoveCoordinate));
	 memset(SnakeCoordinate,0,sizeof(SnakeCoordinate));
   SnakeLength=3;
	 SnakeHead_Construct(2,8);
	 SnakeBody_Construct(1,8);
	 MoveCoordinate[0]=2<<8|8;
	 MoveCoordinate[1]=1<<8|8;
	 FoodCoordinate_x=20;
	 FoodCoordinate_y=10;
	 Food_Construct(FoodCoordinate_x,FoodCoordinate_y);
}
/*************************************************
**�������� SnakeBody_Construct
**��������������4x4�ο�2x2������
**���������x,y;
**�����������
**˵����x��0~31��y��0~15��
**************************************************/
void SnakeBody_Construct(uint8_t x,uint8_t y)  
{
   uint8_t Row_Number=0,Column_Number=0;
	 
	 Row_Number = y*4;
	 Column_Number = x*4;
	 
	 Draw_Single_Point(Column_Number,Row_Number,DRAW);
	 Draw_Single_Point(Column_Number+1,Row_Number,DRAW);
	 Draw_Single_Point(Column_Number+2,Row_Number,DRAW);
	 Draw_Single_Point(Column_Number+3,Row_Number,DRAW);
	
	 Draw_Single_Point(Column_Number,Row_Number+1,DRAW);
	 Draw_Single_Point(Column_Number+1,Row_Number+1,CLEAR);
	 Draw_Single_Point(Column_Number+2,Row_Number+1,CLEAR);
	 Draw_Single_Point(Column_Number+3,Row_Number+1,DRAW);
	 
	 Draw_Single_Point(Column_Number,Row_Number+2,DRAW);
	 Draw_Single_Point(Column_Number+1,Row_Number+2,CLEAR);
	 Draw_Single_Point(Column_Number+2,Row_Number+2,CLEAR);
	 Draw_Single_Point(Column_Number+3,Row_Number+2,DRAW);
	 
	 Draw_Single_Point(Column_Number,Row_Number+3,DRAW);
	 Draw_Single_Point(Column_Number+1,Row_Number+3,DRAW);
	 Draw_Single_Point(Column_Number+2,Row_Number+3,DRAW);
	 Draw_Single_Point(Column_Number+3,Row_Number+3,DRAW);
}
/*************************************************
**�������� SnakeHead_Construct
**��������������4x4����ͷ
**���������x,y;
**�����������
**˵����x��0~31��y��0~15��
**************************************************/
void SnakeHead_Construct(uint8_t x,uint8_t y)
{
   uint8_t Row_Number=0,Column_Number=0;
	 
	 Row_Number = y*4;
	 Column_Number = x*4;  

   Draw_Single_Point(Column_Number,Row_Number,DRAW);
   Draw_Single_Point(Column_Number+1,Row_Number,DRAW);
   Draw_Single_Point(Column_Number+2,Row_Number,DRAW);
   Draw_Single_Point(Column_Number+3,Row_Number,DRAW);
   
   Draw_Single_Point(Column_Number,Row_Number+1,DRAW);
   Draw_Single_Point(Column_Number+1,Row_Number+1,DRAW);
   Draw_Single_Point(Column_Number+2,Row_Number+1,DRAW);
   Draw_Single_Point(Column_Number+3,Row_Number+1,DRAW);

   Draw_Single_Point(Column_Number,Row_Number+2,DRAW);
   Draw_Single_Point(Column_Number+1,Row_Number+2,DRAW);
   Draw_Single_Point(Column_Number+2,Row_Number+2,DRAW);
   Draw_Single_Point(Column_Number+3,Row_Number+2,DRAW);
 
   Draw_Single_Point(Column_Number,Row_Number+3,DRAW);
	 Draw_Single_Point(Column_Number+1,Row_Number+3,DRAW);
	 Draw_Single_Point(Column_Number+2,Row_Number+3,DRAW);
	 Draw_Single_Point(Column_Number+3,Row_Number+3,DRAW);
}
/*************************************************
**�������� Food_Construct
**��������������ʳ��
**���������x,y;
**�����������
**˵����x��0~31��y��0~15��
**************************************************/
void Food_Construct(uint8_t x,uint8_t y)
{
   uint8_t Row_Number=0,Column_Number=0;
	 
	 Row_Number = y*4;
	 Column_Number = x*4;  

   Draw_Single_Point(Column_Number,Row_Number,CLEAR);
   Draw_Single_Point(Column_Number+1,Row_Number,DRAW);
   Draw_Single_Point(Column_Number+2,Row_Number,DRAW);
   Draw_Single_Point(Column_Number+3,Row_Number,CLEAR);
   
   Draw_Single_Point(Column_Number,Row_Number+1,DRAW);
   Draw_Single_Point(Column_Number+1,Row_Number+1,DRAW);
   Draw_Single_Point(Column_Number+2,Row_Number+1,DRAW);
   Draw_Single_Point(Column_Number+3,Row_Number+1,DRAW);

   Draw_Single_Point(Column_Number,Row_Number+2,DRAW);
   Draw_Single_Point(Column_Number+1,Row_Number+2,DRAW);
   Draw_Single_Point(Column_Number+2,Row_Number+2,DRAW);
   Draw_Single_Point(Column_Number+3,Row_Number+2,DRAW);
 
   Draw_Single_Point(Column_Number,Row_Number+3,CLEAR);
	 Draw_Single_Point(Column_Number+1,Row_Number+3,DRAW);
	 Draw_Single_Point(Column_Number+2,Row_Number+3,DRAW);
	 Draw_Single_Point(Column_Number+3,Row_Number+3,CLEAR);
}
/*************************************************
**�������� Wipe_Point
**��������������4x4������
**���������x,y;
**�����������
**˵����x��0~31��y��0~15��
**************************************************/
void Wipe_Point(uint8_t x,uint8_t y)
{
   uint8_t Row_Number=0,Column_Number=0;
	 
	 Row_Number = y*4;
	 Column_Number = x*4;  

   Draw_Single_Point(Column_Number,Row_Number,CLEAR);
   Draw_Single_Point(Column_Number+1,Row_Number,CLEAR);
   Draw_Single_Point(Column_Number+2,Row_Number,CLEAR);
   Draw_Single_Point(Column_Number+3,Row_Number,CLEAR);
   
   Draw_Single_Point(Column_Number,Row_Number+1,CLEAR);
   Draw_Single_Point(Column_Number+1,Row_Number+1,CLEAR);
   Draw_Single_Point(Column_Number+2,Row_Number+1,CLEAR);
   Draw_Single_Point(Column_Number+3,Row_Number+1,CLEAR);

   Draw_Single_Point(Column_Number,Row_Number+2,CLEAR);
   Draw_Single_Point(Column_Number+1,Row_Number+2,CLEAR);
   Draw_Single_Point(Column_Number+2,Row_Number+2,CLEAR);
   Draw_Single_Point(Column_Number+3,Row_Number+2,CLEAR);
 
   Draw_Single_Point(Column_Number,Row_Number+3,CLEAR);
	 Draw_Single_Point(Column_Number+1,Row_Number+3,CLEAR);
	 Draw_Single_Point(Column_Number+2,Row_Number+3,CLEAR);
	 Draw_Single_Point(Column_Number+3,Row_Number+3,CLEAR);
}
/*************************************************
**�������� Snake_Move
**�����������ж����Ƿ�Ե�ʳ��
**���������x,y��status;
**�����������
**˵����x��0~31��y��0~15��status��FOOD��NOFOOD��
**************************************************/
void Snake_Move(uint8_t x,uint8_t y,uint8_t status)
{
	 uint16_t LengthCounter,count;
   if(status==FOOD)//�Ե�ʳ��
	 {
		  for(count=0;count<SnakeLength;count++)//�����������������CheckBuffer
		     CheckBuffer[MoveCoordinate[count]>>8] = MoveCoordinate[count]&0x00ff;
	    for(LengthCounter=SnakeLength-1;LengthCounter>0;LengthCounter--)//ÿһ���������껻Ϊǰһ���ľ�����
			   MoveCoordinate[LengthCounter]=MoveCoordinate[LengthCounter-1];
      MoveCoordinate[0]=x<<8|y;//������ͷ����
      SnakeHead_Construct(x,y);//������ͷ
		  SnakeBody_Construct(MoveCoordinate[1]>>8,MoveCoordinate[1]&0x00ff);//���Ǿ�ͷ��
      SnakeLength++;
		  do
			{
				 FoodCoordinate_x = Counter_x/166;
				 FoodCoordinate_y = Counter_y/357;
			}while((FoodCoordinate_y<5)||(FoodCoordinate_y>14)||(FoodCoordinate_x<1)||(FoodCoordinate_x>30)||(CheckBuffer[FoodCoordinate_x]==FoodCoordinate_y));//ʳ������߽��������ж�
			Food_Construct(FoodCoordinate_x,FoodCoordinate_y);//����ʳ���
			for(count=0;count<SnakeLength;count++)//���CheckBuffer
		     CheckBuffer[count] = 0;
	 }	
   if(status==NOFOOD)//�����ƶ�
	 {
	    Wipe_Point(MoveCoordinate[SnakeLength-1]>>8,MoveCoordinate[SnakeLength-1]&0x00ff);//ɾ������β
		  SnakeBody_Construct(MoveCoordinate[0]>>8,MoveCoordinate[0]&0x00ff);
		  for(LengthCounter=SnakeLength-1;LengthCounter>0;LengthCounter--)
		     MoveCoordinate[LengthCounter]=MoveCoordinate[LengthCounter-1];
		  MoveCoordinate[0]=(x<<8)|y;
		  SnakeHead_Construct(x,y);
		  Wipe_Point(MoveCoordinate[SnakeLength-1]>>8,MoveCoordinate[SnakeLength-1]&0x00ff);
	 }		 
}
/*************************************************
**�������� Border_Check
**�����������߽�������ж�
**���������x,y;
**���������
**˵����x��0~31��y��0~15��
**************************************************/
signed char Border_Check(uint8_t x,uint8_t y)
{
   if( (y<5)||(y>14)||(x<1)||(x>30) )//�ж��Ƿ��ڱ߽���
	    return -1;
	 else 
	    if(CheckBuffer[x]==y)//�ж���ͷ��ʳ���Ƿ��������غ�
			   return -1;
	 else
		  return 1;
}
/*************************************************
**�������� Direction_Process
**����������������
**�����������
**�����������
**˵������
**************************************************/
void Direction_Process(void)
{	 
   switch(MoveDirection)
	 {
		  case UP: 
      {
			   SnakeCoordinate_x = MoveCoordinate[0]>>8;
				 SnakeCoordinate_y = (MoveCoordinate[0]&0x00ff)-1;
				 
				 if((SnakeCoordinate_x==FoodCoordinate_x)&&(SnakeCoordinate_y==FoodCoordinate_y))
				    Snake_Move(SnakeCoordinate_x,SnakeCoordinate_y,FOOD);
				 else
				    Snake_Move(SnakeCoordinate_x,SnakeCoordinate_y,NOFOOD);
			}break;
      case RIGHT:
      {
			   SnakeCoordinate_x = (MoveCoordinate[0]>>8)+1;
				 SnakeCoordinate_y = MoveCoordinate[0]&0x00ff;
				
				 if((SnakeCoordinate_x==FoodCoordinate_x)&&(SnakeCoordinate_y==FoodCoordinate_y))
				    Snake_Move(SnakeCoordinate_x,SnakeCoordinate_y,FOOD);
				 else
				    Snake_Move(SnakeCoordinate_x,SnakeCoordinate_y,NOFOOD);
			}break;
      case DOWN:
      {
			   SnakeCoordinate_x = MoveCoordinate[0]>>8;
				 SnakeCoordinate_y = (MoveCoordinate[0]&0x00ff)+1;
				
				 if((SnakeCoordinate_x==FoodCoordinate_x)&&(SnakeCoordinate_y==FoodCoordinate_y))
				    Snake_Move(SnakeCoordinate_x,SnakeCoordinate_y,FOOD);
				 else
				    Snake_Move(SnakeCoordinate_x,SnakeCoordinate_y,NOFOOD);
			}break;
      case LEFT:
      {
			   SnakeCoordinate_x = (MoveCoordinate[0]>>8)-1;
				 SnakeCoordinate_y = MoveCoordinate[0]&0x00ff;
				
				 if((SnakeCoordinate_x==FoodCoordinate_x)&&(SnakeCoordinate_y==FoodCoordinate_y))
				    Snake_Move(SnakeCoordinate_x,SnakeCoordinate_y,FOOD);
				 else
				    Snake_Move(SnakeCoordinate_x,SnakeCoordinate_y,NOFOOD);
			}break;	
			default:
			  break;
	 }
}
/*************************************************
**�������� Frame_Init
**���������������߿�
**�����������
**�����������
**˵������
**************************************************/
void Frame_Init(void)
{
   uint8_t i;
	 for(i=0;i<128;i++)
	 {
      Draw_Single_Point(i,16,DRAW);
      Draw_Single_Point(i,63,DRAW);   		 
	 }
	 for(i=5;i<125;i++)
	 {
	  // Draw_Single_Point(i,19,DRAW);   
		  //Draw_Single_Point(i,60,DRAW);   
	 }
	 for(i=16;i<64;i++)
	 {
	    Draw_Single_Point(2,i,DRAW);   
		  Draw_Single_Point(127,i,DRAW);   
	 }
	 for(i=19;i<61;i++)
	 {
	    //Draw_Single_Point(5,i,DRAW);   
		 // Draw_Single_Point(124,i,DRAW);   
	 }
}

