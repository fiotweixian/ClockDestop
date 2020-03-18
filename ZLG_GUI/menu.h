/****************************************************************************************
* 文件名：MENU.H
* 功能：菜单显示及操作，头文件。
* 作者：黄绍斌
* 日期：2004.02.26
* 备注：
****************************************************************************************/
#ifndef  MENU_H
#define  MENU_H


/* 定义主菜单宽度，及最大菜单个数 */
#define MMENU_WIDTH     40      // 主菜单最大宽度
#define MMENU_NO        3       // 主菜单最大数量
#define MMENU_TEXT_LEN  6       // 主菜单列表项文字最大数量，ZXE添加

/* 定义菜单的宽度(下拉菜单)，及最大子菜单个数 */
#define SMENU_WIDTH     76      // 子菜单最大宽度
#define SMENU_NO        3       // 子菜单最大数量
#define SMENU_TEXT_LEN  11      // 子菜单列表项文字最大数量，ZXE添加

/* 定义一子菜单项的数据结构 */
typedef  struct
{
    WINDOWS* win;                       // 所属窗口
    uint8 mmenu_no;                     // 对应的主菜单项号(0-n)
    uint8 no;                           // 子菜单项个数
    char* str[SMENU_NO];                // 子菜单字符串
    uint8 state;                        // 所选择的子菜单
    void(*Function[SMENU_NO])(void);    // 子菜单对应的服务程序
} SMENU;


/* 主菜单数据结构 */
typedef  struct
{
    WINDOWS* win;           // 所属窗口
    uint8 no;               // 主菜单个数
    char* str[MMENU_NO];    // 主菜单字符串
} MMENU;


/* 定义图标菜单数据结构 */
typedef  struct
{  uint32 x;			// 图标菜单位置(左上角的x坐标)
   uint32 y;			// 图标菜单位置(左上角的y坐标) 
   uint8  *icodat;		// 32*32的ICO数据地址
   uint8  *title;       // 相关标题提示 (42*13)
   uint8  state;  		// 图标菜单状态，为0时表示未选中，为1时表示已选中
   
   void   (*Function)(void);	// 对应的服务程序
} MENUICO;


/****************************************************************************
* 名称：GUI_MMenuDraw()
* 功能：显示主菜单，加上边框。
* 入口参数：men		主菜单句柄
* 出口参数：返回0表示操作失败，返回1表示操作成功
****************************************************************************/
extern  uint8  GUI_MMenuDraw(MMENU *men);


/****************************************************************************
* 名称：GUI_MMenuSelect()
* 功能：当前主菜单，加下划线，表示当前主菜单。
* 入口参数：men		主菜单句柄
*          no		所选的主菜单项
* 出口参数：无
****************************************************************************/
extern  void  GUI_MMenuSelect(MMENU *men, uint8 no);


/****************************************************************************
* 名称：GUI_MMenuNSelect()
* 功能：取消当前主菜单，去除下划线。
* 入口参数：men		主菜单句柄
*          no		所选的主菜单项
* 出口参数：无
****************************************************************************/
extern  void  GUI_MMenuNSelect(MMENU *men, uint8 no);



/****************************************************************************
* 名称：GUI_SMenuDraw()
* 功能：显示子菜单，加上边框。
* 入口参数：men		菜单句柄
* 出口参数：返回0表示操作失败，返回1表示操作成功
****************************************************************************/
extern  uint8  GUI_SMenuDraw(SMENU *men);


/****************************************************************************
* 名称：GUI_SMenuSelect()
* 功能：选择新的子菜单。
* 入口参数：men		子菜单句柄
*          old_no	原先选择的子菜单项
*		   new_no	现要选择的子菜单项
* 出口参数：无
****************************************************************************/
extern  void  GUI_SMenuSelect(SMENU *men, uint8 old_no, uint8 new_no);


/****************************************************************************
* 名称：GUI_SMenuHide()
* 功能：消隐子菜单项。
* 入口参数：men		子菜单句柄
* 出口参数：返回0表示操作失败，返回1表示操作成功
****************************************************************************/
extern  uint8  GUI_SMenuHide(SMENU *men);



/****************************************************************************
* 名称：GUI_Button49x14()
* 功能：显示49*14按钮。
* 入口参数： x		指定显示位置，x坐标
*           y		指定显示位置，y坐标
*           dat		显示的数据地址
* 出口参数：返回0表示操作失败，返回1表示操作成功
****************************************************************************/
extern  void  GUI_Button49x14(uint32 x, uint32 y, uint8 *dat);



/****************************************************************************
* 名称：GUI_Button_OK()
* 功能：显示49*14按钮"OK"。
* 入口参数： x		指定显示位置，x坐标
*           y		指定显示位置，y坐标
* 出口参数：返回0表示操作失败，返回1表示操作成功
****************************************************************************/
extern  void  GUI_Button_OK(uint32 x, uint32 y);



/****************************************************************************
* 名称：GUI_Button_OK1()
* 功能：显示49*14按钮，选择状态的"OK"。
* 入口参数： x		指定显示位置，x坐标
*           y		指定显示位置，y坐标
* 出口参数：返回0表示操作失败，返回1表示操作成功
****************************************************************************/
extern  void  GUI_Button_OK1(uint32 x, uint32 y);


/****************************************************************************
* 名称：GUI_Button_Cancle()
* 功能：显示49*14按钮"Cancle"。
* 入口参数： x		指定显示位置，x坐标
*           y		指定显示位置，y坐标
* 出口参数：返回0表示操作失败，返回1表示操作成功
****************************************************************************/
extern  void  GUI_Button_Cancle(uint32 x, uint32 y);



/****************************************************************************
* 名称：GUI_Button_Cancle1()
* 功能：显示49*14按钮，选择状态的"Cancle"。
* 入口参数： x		指定显示位置，x坐标
*           y		指定显示位置，y坐标
* 出口参数：返回0表示操作失败，返回1表示操作成功
****************************************************************************/
extern  void  GUI_Button_Cancle1(uint32 x, uint32 y);


/****************************************************************************
* 名称：GUI_MenuIcoDraw()
* 功能：显示图标菜单。
* 入口参数：ico		图标菜单句柄
* 出口参数：返回0表示操作失败，返回1表示操作成功
****************************************************************************/
extern  uint8  GUI_MenuIcoDraw(MENUICO *ico);



#endif



