#pragma once
#include"Button.h"
#include"curtool.h"
#include "ButtonText.h"
#include"InputBox.h"
#include<list>
class canvas ://画布类
	public Button
{
public:
	canvas(COLORREF fill_color, COLORREF line_color, int x = 0, int y = 0, int w = 10, int h = 10);
	~canvas();
	void show() ;
	// 保存图像
	void GetImage();
	// 输出图像
	void PutImage();
	//设置颜色和工具
	void SetCurTool(CURTOOL& curtool);
	//获取鼠标信息
	void SetMsg(MOUSEMSG& msg);
	//画图中
	void Draw();
	//画文字
	void Drawtext(int x1,int y1,int x2,int y2);
private:
	int x1;
	int y1;
	int x2;
	int y2;
	CURTOOL* curtool;//默认选中的工具
	bool  operation = false;//活动中
	list<IMAGE> listimage;//保存临时图像，回溯
	IMAGE image;//保存临时图像
	//ButtonText* text=nullptr;//插入文本时的对象
	Inputbox* text = nullptr;//插入文本的输入框对象
	IMAGE image_txt;//保存插入文本前临时图像
	bool  operText = false;//输入框创建完毕
};

