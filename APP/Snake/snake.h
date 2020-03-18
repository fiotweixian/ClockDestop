#ifndef __SNAKE_H
#define __SNAKE_H

#include "stm32f1xx_hal.h" 

#define Solid 0x01
#define Hollow 0x02
#define Frame 0x03
#define UP 0x04
#define RIGHT 0x05
#define DOWN 0x06
#define LEFT 0x09
#define DRAW 0x10
#define CLEAR 0x11
#define FOOD 0x12
#define NOFOOD 0x13
#define GAMEOVER 0x14

extern uint8_t SnakeCoordinate[8][128];
extern uint16_t MoveCoordinate[420];
extern uint8_t SnakeCoordinate_x,SnakeCoordinate_y;
extern uint8_t FoodCoordinate_x,FoodCoordinate_y;
extern uint8_t MoveDirection;
extern uint16_t SnakeLength;
extern uint16_t Counter_x,Counter_y;
extern uint8_t CheckBuffer[420];
extern uint8_t runflag;

void Snake_Init(void);
void SnakeBody_Construct(uint8_t x,uint8_t y);
void SnakeHead_Construct(uint8_t x,uint8_t y);
void Wipe_Point(uint8_t x,uint8_t y);
void Food_Construct(uint8_t x,uint8_t y);
void Frame_Init(void);
void Snake_Move(uint8_t x,uint8_t y,uint8_t status);
void Direction_Process(void);
signed char Border_Check(uint8_t x,uint8_t y);

#endif

