#include "btrix.h"
#include "oled.h"
#include "config.h"
#define LGOU 0
#define RGOU 1
#define RZ	2
#define LZ	3
#define T	4
#define GUN 5
#define BOX 6
#define PASSSCORE 20
#define NEWSIGNFLAG 0
#define DEADFLAG 1
#define PAUSEFLAG 2
#define A 48271L
#define M 2147483647L
#define Q (M / A)
#define R (M % A)
#define RESEVER 1
#define CHANGE 2
#define DOWN 3
#define LEFT 4
#define RIGHT 5
#define PAUSE 6

struct Jimu
{
	unsigned int dat;
 	char x;
	unsigned char y;
	unsigned char type;
	unsigned char change;
}Sign[3];//积木结构体
unsigned char SysFlag=0;
static unsigned long Seed = 1;
unsigned char Score=0;
unsigned char Level=1;
unsigned char DelayCnt=5;
unsigned char KeyBuffer=0;
unsigned int num[19+2]={
0xfff,//第1行，最下面
0x801,0x801,0x801,0x801,0x801,0x801,0x801,0x801,0x801,0x801,
0x801,0x801,0x801,0x801,0x801,0x801,0x801,0x801,0x801,//第2行到第20行共19行
0xfff//第21行，最上面

};//定义共21行，其中num[0]为下墙壁行，num[20]为上墙壁行,每行12格，最左一格为左墙壁列，最右一格为右墙壁列
unsigned char Block[28][2]={
/*
*   口     口口口   口口
*   口     口         口      口
*   口口              口  口口口      
*/
{0x88,0xc0},{0xe8,0x00},{0x62,0x20},{0x02,0xe0},
/*
*   口        口口 口口口
*   口 口     口       口
* 口口 口口口 口    
*/
{0x22,0x60},{0x08,0xe0},{0xc8,0x80},{0xe2,0x00},  
/*
*   口
*   口口         口口
*     口       口口
*/
{0x8c,0x40},{0x6c,0x00},{0x8c,0x40},{0x6c,0x00},
/*
*   口        口口
* 口口          口口
* 口
*/
{0x4c,0x80},{0xc6,0x00},{0x4c,0x80},{0xc6,0x00},  
/*
*          口                口
*   口     口口   口口口   口口
* 口口口   口       口       口
*/
{0x04,0xe0},{0x8c,0x80},{0xe4,0x00},{0x26,0x20},
/*口
* 口
* 口       口口口口
* 口
*/
{0x44,0x44},{0x0f,0x00},{0x44,0x44},{0x0f,0x00},  
/*
* 口口
* 口口
*/  
{0x06,0x60},{0x06,0x60},{0x06,0x60},{0x06,0x60}
};
unsigned int MaskTab[16]={
0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080,
0x0100,0x0200,0x0400,0x0800,0x1000,0x2000,0x4000,0x8000
};
/************************************
伪随机数发生器
*************************************/
double Random(void)
{
	long TmpSeed;
	TmpSeed=A*(Seed%Q)-R*(Seed/Q);
	if(TmpSeed>=0)
		Seed=TmpSeed;
	else
		Seed=TmpSeed+M;
	return (double)Seed/M;
}

/**************************************
为伪随机数发生器播种
***************************************/
void InitRandom(unsigned long InitVal)
{
	Seed=InitVal;
}
/**********************************
根据积木图标左下坐标X，Y来画出积木图标
***********************************/
void DrawSign(struct Jimu Temp,unsigned char DrawMode)
{
	unsigned char m,n;
	for(m=0;m<4;m++)
		for(n=0;n<4;n++)
		{
			if((Temp.dat&MaskTab[4*m+n])!=0)
				GUI_Rectangle(Temp.x+n*3,Temp.y-2-3*m,Temp.x+n*3+2,Temp.y-3*m,DrawMode);
		}
}
/*******************************
随机产生一个积木图标放到预产生区域并显示出来
********************************/
void CreatSign(void)
{
	unsigned char n;
	unsigned int Temp;

	DrawSign(Sign[2],0);//先清除

	n=Random()*28;
	Temp=(unsigned int)Block[n][0]<<8;
	Temp=Temp|Block[n][1];
	Sign[2].dat=Temp;
	Sign[2].x=45;
	Sign[2].y=4*3+2;
	Sign[2].type=n/4;
	Sign[2].change=n%4;
	DrawSign(Sign[2],1);//后画出
}

void PrintScore(void)
{
	unsigned char Str[3];
	Str[0]=(Score/10)|0x30;
	Str[1]=(Score%10)|0x30;
	Str[2]=0;
	//Lcd_WriteStr(6,2,Str);
}

void PrintLevel(void)
{
	unsigned char Str[3];
	Str[0]=(Level/10)|0x30;
	Str[1]=(Level%10)|0x30;
	Str[2]=0;
	//Lcd_WriteStr(6,3,Str);
}
/********************************
判断积木图标中方块是否与障碍方块重合
*********************************/
unsigned char CheckIf(void)
{
	unsigned char m,n;
	for(m=0;m<4;m++)//行循环
		for(n=0;n<4;n++)//列循环
		{
			if((Sign[1].dat&MaskTab[4*m+n])!=0)
			{
				if((num[20-(Sign[1].y-2)/3+m]&MaskTab[11-Sign[1].x/3-n])!=0)
					return 0;
			}
		}
	return 1;
}
/********************************
判断积木图标是否可以向左移动
*********************************/
unsigned char CheckIfLeft(void)
{
	Sign[1]=Sign[0];
	Sign[1].x-=3;	
	return CheckIf();
}
/********************************
判断积木图标是否可以向右移动
*********************************/
unsigned char CheckIfRight(void)
{
	Sign[1]=Sign[0];
	Sign[1].x+=3;	
	return CheckIf();
}
/********************************
判断是否可以旋转
*********************************/
unsigned char CheckIfRoll(void)
{
	unsigned char i;
	unsigned int Temp;
	Sign[1]=Sign[0];
	if(++Sign[1].change>3)
		Sign[1].change=0;
   	i=Sign[1].type*4+Sign[1].change;
	Temp=(unsigned int)Block[i][0]<<8;
	Temp=Temp|Block[i][1];
	Sign[1].dat=Temp;
	
	return CheckIf();
}
/********************************
寻找满格的行并做消除处理
最多寻找4个满行并做消除
*********************************/
void DelFull(void)
{
	unsigned char m,n;
	unsigned char Temp;
	unsigned char Flag=0;
	Temp=(Sign[0].y-2)/3;
	if(Temp>=20)//防止越过了下边界
		Temp=1;
	else
		Temp=20-Temp;
	for(n=Temp+3;n>=Temp;n--)//积木图标的最顶行开始寻找满行比较有利于运算
	{
		if(num[n]==0xfff)
		{
			Flag=1;
			for(m=n+1;m<=19;m++)
			{
				num[m-1]=num[m];
			}
			num[m]=0x801;
			Score++;//每找到一个满行，则分数加1
		}
	}
	if(Flag)//为加速而设置并判断的标志，有已固定的积木有满格消行变化则重画积木界面
	{
		for(m=Temp;m<=19;m++)//为加速，不必要重第一行重画起，只需要从积木图标最下行开始往上的重画
			for(n=1;n<=10;n++)
			{
				if((num[m]&MaskTab[n])==0)
				{	
					if(Lcd_ReadPixel(30-(n-1)*3,57-(m-1)*3)!=0)//为加速而做的读象素操作
					{
						GUI_Rectangle(30-(n-1)*3,57-(m-1)*3,30-(n-1)*3+2,57-(m-1)*3+2,0);
					}
				}
			   	else
				{
					if(Lcd_ReadPixel(30-(n-1)*3,57-(m-1)*3)==0)//为加速而做的读象素操作
					{
						GUI_Rectangle(30-(n-1)*3,57-(m-1)*3,30-(n-1)*3+2,57-(m-1)*3+2,1);
					}
				}
			}
	}
}
/********************************
判断积木图标是否可以继续下降一格
********************************/
unsigned char CheckIfDown(void)
{
	Sign[1]=Sign[0];//
	Sign[1].y+=3;//假设下降一格	
	return CheckIf();
	
}
/******************************
画墙壁，初始化界面
*******************************/
void OLED_DrawBoard(void)
{
	unsigned char n;
	for(n=0;n<12;n++)
	{
		GUI_Rectangle(3*n,0,3*n+2,2,1);
		GUI_Rectangle(3*n,60,3*n+2,62,1);
	}
	for(n=0;n<20;n++)
	{
		GUI_Rectangle(0,3*n,2,3*n+2,1);
		GUI_Rectangle(33,3*n,35,3*n+2,1);		
	}
	//OLED_P8x16Str(0,2,"TOTO");
	//OLED_P8x16Str(3,2,"Score:");
	//OLED_P8x16Str(3,3,"Level:");
}
void OLED_GamePlay(void)
{
	unsigned char m,n;
	unsigned int Temp;
	SysFlag|=1<<NEWSIGNFLAG;//刚开始初始化为需要产生新的积木图标
	InitRandom(0);
//	Lcd_WriteStr(3,1,"Playing");
	PrintScore();
	PrintLevel();
	CreatSign();
	while(1)
	{
		if((SysFlag&(1<<NEWSIGNFLAG))==1)//判是否需要产生新的积木图标
		{
			SysFlag&=~(1<<NEWSIGNFLAG);
			Sign[0]=Sign[2];
			CreatSign();
			Sign[0].x=12;
			Sign[0].y=14;

			for(m=0;m<4;m++)//行循环
			{
				for(n=0;n<4;n++)//列循环
				{
					if((Sign[0].dat&MaskTab[15-m*4-n])==0)
						break;
				}
				if(n==4)
					Sign[0].y-=3;
			}//将积木图标出现置顶
			
			for(m=0;m<4;m++)//行循环
				for(n=0;n<4;n++)//列循环
				{
					if((Sign[0].dat&MaskTab[4*m+n])!=0)
					{
						if((num[20-(Sign[0].y-2)/3+m]&MaskTab[11-Sign[0].x/3-n])!=0)
							SysFlag|=1<<DEADFLAG;
					}
				}
			if((SysFlag&(1<<DEADFLAG))!=0)
				break;//如果产生新的积木图标中的方块与已固定好的方块重合，则死亡。游戏结束
			DrawSign(Sign[0],1);	
		}
		switch(KeyBuffer)
		{
			case LEFT:
					KeyBuffer=0;
					if((SysFlag&(1<<PAUSEFLAG))==0)
					{
						if(CheckIfLeft())
						{
							DrawSign(Sign[0],0);
							Sign[0].x-=3;
							DrawSign(Sign[0],1);
						}
					}
					else
					{
						if(++Level>=10)
							Level=1;
						PrintLevel();
					}
					break;
			case RIGHT:
					KeyBuffer=0;
					if((SysFlag&(1<<PAUSEFLAG))==0)
					{
						if(CheckIfRight())
						{
							DrawSign(Sign[0],0);
							Sign[0].x+=3;
							DrawSign(Sign[0],1);	
						}
					}
					else
					{
						if(++Level>=10)
							Level=1;
						PrintLevel();
					}
					break;
			case DOWN:
					KeyBuffer=0;
					if((SysFlag&(1<<PAUSEFLAG))==0)
					{
						if(CheckIfDown())//判断是否能继续下降一格
						{
							DrawSign(Sign[0],0);
							Sign[0].y+=3;
							DrawSign(Sign[0],1);	
						}
					}
					break;
			case CHANGE:
					KeyBuffer=0;
					if((SysFlag&(1<<PAUSEFLAG))==0)
					{
						if(CheckIfRoll())
						{
							DrawSign(Sign[0],0);
							if(++Sign[0].change>3)
								Sign[0].change=0;
						   	m=Sign[0].type*4+Sign[0].change;
							Temp=(unsigned int)Block[m][0]<<8;
							Temp=Temp|Block[m][1];
							Sign[0].dat=Temp;
							DrawSign(Sign[0],1);
						}
					}
					break;
		   	case PAUSE:
					KeyBuffer=0;
					SysFlag^=1<<PAUSEFLAG;
					if((SysFlag&(1<<PAUSEFLAG))==0)
					{
						Lcd_WriteStr(3,1,"          ");
						Lcd_WriteStr(3,1,"Playing");
					}
					else
					{
						Lcd_WriteStr(3,1,"          ");
						Lcd_WriteStr(3,1,"Pause");	
					}
					break;
		    default:
					break;
		}
		if((SysFlag&(1<<PAUSEFLAG))!=0)
			continue;
		Delay(500);
		if(++DelayCnt>=2*(11-Level))
		{
			DelayCnt=0;
			if(CheckIfDown())//判断是否能继续下降一格
			{
				DrawSign(Sign[0],0);
				Sign[0].y+=3;
				DrawSign(Sign[0],1);
			}
			else
			{
				FixSign();
				DelFull();
				PrintScore();
				if(Score>=PASSSCORE)
				{
					SysFlag&=~(1<<DEADFLAG);
					break;//跳出玩游戏过程
				}
				SysFlag|=1<<NEWSIGNFLAG;//新的积木图标产生标志置1
			}
		}		
	}
}

void BTrix_Init(void)
{
		OLED_DrawBoard();
		GUI_Exec();
}