#include "snake.h"
#include "string.h"
#include "oled.h"
//snake
uint8_t CheckBuffer[420];//高八位放x坐标，低八位放y坐标
uint16_t MoveCoordinate[420];//高八位放x坐标，低八位放y坐标
uint8_t SnakeCoordinate[8][128];
uint16_t SnakeLength;
uint8_t SnakeCoordinate_x,SnakeCoordinate_y;
uint8_t FoodCoordinate_x,FoodCoordinate_y;
uint8_t MoveDirection;
uint16_t Counter_x=166,Counter_y=1785;
uint8_t runflag=0;
/*************************************************
**函数名： Snake_Init
**功能描述：初始化蛇身长度、坐标和食物坐标
**输入参数：无
**输出参数：无
**说明：无
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
**函数名： SnakeBody_Construct
**功能描述：画出4x4镂空2x2的蛇身
**输入参数：x,y;
**输出参数：无
**说明：x，0~31；y，0~15；
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
**函数名： SnakeHead_Construct
**功能描述：画出4x4的蛇头
**输入参数：x,y;
**输出参数：无
**说明：x，0~31；y，0~15；
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
**函数名： Food_Construct
**功能描述：画出食物
**输入参数：x,y;
**输出参数：无
**说明：x，0~31；y，0~15；
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
**函数名： Wipe_Point
**功能描述：擦出4x4的区域
**输入参数：x,y;
**输出参数：无
**说明：x，0~31；y，0~15；
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
**函数名： Snake_Move
**功能描述：判断蛇是否吃到食物
**输入参数：x,y，status;
**输出参数：无
**说明：x，0~31；y，0~15；status，FOOD，NOFOOD；
**************************************************/
void Snake_Move(uint8_t x,uint8_t y,uint8_t status)
{
	 uint16_t LengthCounter,count;
   if(status==FOOD)//吃到食物
	 {
		  for(count=0;count<SnakeLength;count++)//将蛇身所有坐标存入CheckBuffer
		     CheckBuffer[MoveCoordinate[count]>>8] = MoveCoordinate[count]&0x00ff;
	    for(LengthCounter=SnakeLength-1;LengthCounter>0;LengthCounter--)//每一个蛇身坐标换为前一个的旧坐标
			   MoveCoordinate[LengthCounter]=MoveCoordinate[LengthCounter-1];
      MoveCoordinate[0]=x<<8|y;//更新蛇头坐标
      SnakeHead_Construct(x,y);//画出蛇头
		  SnakeBody_Construct(MoveCoordinate[1]>>8,MoveCoordinate[1]&0x00ff);//覆盖旧头部
      SnakeLength++;
		  do
			{
				 FoodCoordinate_x = Counter_x/166;
				 FoodCoordinate_y = Counter_y/357;
			}while((FoodCoordinate_y<5)||(FoodCoordinate_y>14)||(FoodCoordinate_x<1)||(FoodCoordinate_x>30)||(CheckBuffer[FoodCoordinate_x]==FoodCoordinate_y));//食物坐标边界与蛇身判断
			Food_Construct(FoodCoordinate_x,FoodCoordinate_y);//画出食物点
			for(count=0;count<SnakeLength;count++)//清空CheckBuffer
		     CheckBuffer[count] = 0;
	 }	
   if(status==NOFOOD)//正常移动
	 {
	    Wipe_Point(MoveCoordinate[SnakeLength-1]>>8,MoveCoordinate[SnakeLength-1]&0x00ff);//删除旧蛇尾
		  SnakeBody_Construct(MoveCoordinate[0]>>8,MoveCoordinate[0]&0x00ff);
		  for(LengthCounter=SnakeLength-1;LengthCounter>0;LengthCounter--)
		     MoveCoordinate[LengthCounter]=MoveCoordinate[LengthCounter-1];
		  MoveCoordinate[0]=(x<<8)|y;
		  SnakeHead_Construct(x,y);
		  Wipe_Point(MoveCoordinate[SnakeLength-1]>>8,MoveCoordinate[SnakeLength-1]&0x00ff);
	 }		 
}
/*************************************************
**函数名： Border_Check
**功能描述：边界和蛇身判断
**输入参数：x,y;
**输出参数：
**说明：x，0~31；y，0~15；
**************************************************/
signed char Border_Check(uint8_t x,uint8_t y)
{
   if( (y<5)||(y>14)||(x<1)||(x>30) )//判断是否在边界内
	    return -1;
	 else 
	    if(CheckBuffer[x]==y)//判断蛇头或食物是否与蛇身重合
			   return -1;
	 else
		  return 1;
}
/*************************************************
**函数名： Direction_Process
**功能描述：方向处理
**输入参数：无
**输出参数：无
**说明：无
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
**函数名： Frame_Init
**功能描述：画出边框
**输入参数：无
**输出参数：无
**说明：无
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

