#include "ButtonText.h"

void ButtonText::show()
{
	//绘制边框
	ShowFrame();
	//设置文本颜色
	settextcolor(text_color);
	settextstyle(height * 0.8, 0, _T("楷体"));//设置字体大小
	int strwidth = textwidth(str.c_str());//字符宽度
	int strheight = textheight(str.c_str());
	//输出文字居中显示
	outtextxy(x +(width- strwidth)/2, y +(height-strheight)/2, str.c_str());

}

void ButtonText::SetText(string str)
{
	this->str = str;
}

string ButtonText::GetText()
{
	return str;
}

void ButtonText::SetText(COLORREF color)
{
	text_color = color;
}
