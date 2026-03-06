#pragma once
//#ifdef  _UNICODE
//#undef _UNICODE
//#endif
#include "Button.h"
#include"timer.hpp"
#include<conio.h>
#pragma comment(lib,"Imm32.lib")
#define ALLOW_NUM 1//允许数字
#define ALLOW_CAPLET 2//允许大写字母
#define ALLOW_LOWLET 4//允许小写字母
#define ALLOW_CHINESE 8//允许汉字
#define ALLOW_ALL 15//全部允许
//using namespace std;//使用标准命名空间
class Inputbox:public Button
{
public:
	Inputbox();
	Inputbox(int x,int y, int wide = 100, int hige = 30, string str=" ", int allow = ALLOW_ALL);
	~Inputbox();
	//设置颜色
	void SetColor(COLORREF color_fill, COLORREF color_frame = BLACK);
	//设置坐标
	void SetCoord(int x = 0, int y = 0, int w = 10, int h = 10);
	//输出图形
	void show();
	//设置光标闪烁时间ms
	void GetTime(int T);
    //获取光标激活状态
	bool& GetCursor();
	//设置文字高度和颜色
	void SetText(int nHeight, COLORREF color);
	//设置文字颜色
	void SetText(COLORREF color);
	//更改文字
	void SetText(string str);
	//获取文本
	string GetText();
	//获取鼠标信息
	void SetMsg(MOUSEMSG& msg);
	
private:
	//获取键盘信息
	void gettext();
	void GetIMEString(HWND hWnd, string& str);
	int allow;//允许输入的，格式控制
	COLORREF color_cursor = BLACK;//光标颜色
	int cursor_x = x+2;//光标x坐标
	bool cursor_flag = false;//光标激活状态
	timer cursor_time;//光标定时器
	
	string str;//输入的字符
	int strwidth = 0;//单字符宽度
	COLORREF color_text = WHITE;//文本颜色
};
