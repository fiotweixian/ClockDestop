#ifndef __DISPLAY_H
#define __DISPLAY_H
#include "stm32f1xx_hal.h"
#ifdef __cplusplus
 extern "C" {
#endif
typedef struct _LOCK_OLED{
	unsigned char	Lock;
} LOCK_OLED;
extern LOCK_OLED Lock_OLED;
typedef struct _OLED_Display{
	unsigned char OLED_Page;
	unsigned char OLED_index;
	unsigned char OLED_start;
	unsigned char OLED_time;
	unsigned char OLED_Mode;
	unsigned char OLED_DisplayKey;
	int OLED_Icon;
} OLED_Display_t;
extern OLED_Display_t gOLED_Display;

extern void Boot_Animation(void);
extern void Oled_DisplayPage(void);
void OLED_DeskTop(void);
void DisplayIcon(int keyvalue_t);

#ifdef __cplusplus
}
#endif
#endif

