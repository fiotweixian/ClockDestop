/****************************************************************************************
* 文件名：FONT5_7.H
* 功能：5*7 ASCII码字体显示函数。(头文件)
* 作者：黄绍斌
* 日期：2004.02.26
* 备注：使用GUI_SetColor()函数设置前景颜色及背景色。
****************************************************************************************/
#ifndef  FONT5_7_H
#define  FONT5_7_H


/****************************************************************************
* 名称：GUI_PutChar()
* 功能：显示ASCII码，显示值为20H-7FH(若为其它值，则显示' ')。
* 入口参数： x		指定显示位置，x坐标
*           y		指定显示位置，y坐标
*           ch		要显示的ASCII码值。
* 出口参数：返回值为1时表示操作成功，为0时表示操作失败。
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
extern  uint8  GUI_PutChar(uint32 x, uint32 y, uint8 ch);


/****************************************************************************
* 名称：GUI_PutString()
* 功能：输出显示字符串(没有自动换行功能)。
* 入口参数： x		指定显示位置，x坐标
*           y		指定显示位置，y坐标
*           str		要显示的ASCII码字符串
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
extern  void  GUI_PutString(uint32 x, uint32 y, char *str);


/****************************************************************************
* 名称：GUI_PutNoStr()
* 功能：输出显示字符串(没有自动换行功能)，若显示的字符个数大于指定个数，则直接退出。
* 入口参数： x		指定显示位置，x坐标
*           y		指定显示位置，y坐标
*           str		要显示的ASCII码字符串。
*           no      最大显示字符的个数
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
extern  void  GUI_PutNoStr(uint32 x, uint32 y, char *str, uint8 no);


#endif
