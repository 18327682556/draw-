#pragma once
#include<iostream>
#include<string>
#include<graphics.h>
using namespace std;

class Button//按钮类默认画矩形
{
public:
	Button() :color_fill(WHITE), color_frame(BLACK), x(0), y(0), width(10), height(10) { /*cout << "" << endl;*/ }
	////用图片填充
	//Button(string str, int x = 0, int y = 0, int w = 10, int h = 10);
	//用颜色填充
	Button(COLORREF fill_color, COLORREF line_color, int x = 0, int y = 0, int w = 10, int h = 10) :color_fill(fill_color), color_frame(line_color), x(x), y(y), width(w), height(h) {}
	virtual~Button();
	//设置颜色
	virtual void SetColor(COLORREF fill_color, COLORREF line_color= BLACK);
	//设置坐标
	virtual void SetCoord(int x = 0, int y = 0, int w = 10, int h = 10);
	//显示图像
	virtual void show();
	//获取填充颜色
	COLORREF& GetFillColor();
	//获取鼠标是否左键按下
	virtual bool GetLeftClickDOWN(MOUSEMSG& msg);
	bool GetLeftClickDOWN();
	//获取鼠标是否左键抬起
	bool GetLeftClickUP(MOUSEMSG& msg);
	//获取鼠标是否右键按下
	virtual bool GetRightClickDOWN(MOUSEMSG& msg);
	bool GetRightClickDOWN();
	//获取鼠标信息
	virtual void SetMsg(MOUSEMSG& msg);
	//获取是否在范围内
	bool GetRange(MOUSEMSG& msg);
	//设置是否透明填充
	bool& SetTransFill();
	//设置是否透明边框
	bool& SetTransFrame();
	int GetX();
	int GetY();
	int GetW();
	int GetH();
protected:
//private:
	//绘制边框
	virtual void ShowFrame();
	bool left_click = false;//鼠标左键激活状态
	bool right_click = false;//鼠标左键激活状态
	int x;
	int y;
	int width;
	int height;
	//IMAGE* image=nullptr;//填充图片
	COLORREF color_fill;//填充颜色
	bool trans_fill = false;//透明填充
	COLORREF color_frame;//边框颜色
	bool trans_frame = false;//透明边框
};