/****************************************************************************************
*	File Name				:	drawRain.h
*	CopyRight				:	LPF
*	ModuleName				:	drawRain
*
*	CPU						:   Inter Core 7
*	RTOS					:
*
*	Create Data				:	2015/12/20
*	Author/Corportation		:	Li PeiFeng
*
*	Abstract Description	:	Declared the struct and function for drawRain
*
*--------------------------------Revision History----------------------------------------
*	No	version		Data		Revised By			Item			Description
*	1							LPF									first coding
*
****************************************************************************************/

/****************************************************************************************
*	Multi-Include-Prevent Section
****************************************************************************************/
#ifndef DRAWRAIN_H_INCLUDED
#define DRAWRAIN_H_INCLUDED

/*****************************************************************************************
*	Macro Define Section
*****************************************************************************************/
#define PI 3.14159265

/****************************************************************************************
*	Include File Section
****************************************************************************************/
#include "list.h"
#include <stdlib.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>
#include <math.h>
#include "displayOthers.h"
#include "thunder.h"

/****************************************************************************************
*	Macro Define Section
****************************************************************************************/
#define MAX_NUM_OF_NODE 1000	//初始时链表结点数
#define MAX_NUM_OF_LEAVES 30	//荷叶数目
#define SMOOTH_DEGREE 64		//涟漪光滑程度
#define MAX_NUM_OF_MOUNT 20		//山的数目

#define WINDOW_WIDTH 1590		//窗口宽度
#define WINDOW_HEIGHT 830		//窗口高度

typedef struct leave leave;
typedef struct Mount Mount;
/****************************************************************************************
*	Prototype Declare Section
****************************************************************************************/
/****************************************************************************************
*@Name............: void initRainScreen(void)
*@Description.....: 初始化绘雨场景
*@Parameters......: void
*@Return values...: void
*@PreCondition....：需在绘图之前被调用，从而实现功能
*@PostCondition...：无
*****************************************************************************************/
void InitRainScreen(void);

//初始化全局世界
void InitWorld(void);

//初始化控制屏幕
void InitControlScreen(void);

/****************************************************************************************
*@Name............: void ResizeDisplayScreen(int width, int height)
*@Description.....: 控制窗口变化事件
*@Parameters......: width	:窗口宽度
*					height	:窗口高度
*@Return values...: void
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
void ResizeDisplayScreen(int width, int height);

//处理全局世界窗口改变事件
void ResizeWorld(int width, int height);

//处理控制屏幕窗口改变事件
void ResizeControlScreen(int width, int height);
/****************************************************************************************
*@Name............: void DisplayRainScreen(void)
*@Description.....: 落雨场景显示函数
*@Parameters......: void
*@Return values...: void
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
void DisplayRainScreen(void);

//绘制控制屏幕
void DisplayControlScreen(void);

//绘制全局世界
void DisplayWorld(void);
void RedisplayAll(void);
/****************************************************************************************
*@Name............: void idle(void)
*@Description.....: 空闲函数
*@Parameters......: void
*@Return values...: void
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
void Idle(void);

//根据半径radius画椭圆
void DrawCircle(double radius);

//设置荷叶属性
void SetLeavesAttribute(leave leaves[], int num);

//设置山的属性
void SetMountAttribute(Mount mount[], int num);

//绘制荷叶
void DrawLeaves(leave leaves[]);

//画山
void DrawMountain(Mount mount);

//绘制闪电
void DrawThunder(Thunders *thunders);

//根据半径radius,曲率curvature及x、z坐标画实心椭圆
void DrawSolidCircle(double x, double z, double radius, double curvature, int lineGap);
/****************************************************************************************
*@Name............: void keyBoard(unsigned char key, int x, int y)
*@Description.....: 按键处理函数
*@Parameters......: key		:按下的‘键’
*@Return values...: void
*@PreCondition....：无
*@PostCondition...：无
*****************************************************************************************/
void KeyBoard(unsigned char key, int x, int y);

//特殊按键，特指数字和字母外的一些功能键
void SpecialKeyBoard(unsigned char key, int x, int y);

//鼠标按键点击事件
void MouseMotion(int button, int state, int x, int y);

#endif