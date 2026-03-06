#include "UniversalColor.h"

UniversalColor::UniversalColor(COLORREF fill_color, COLORREF line_color, COLORREF color, int x, int y, int w, int h)
{
	this->color_fill = fill_color;
	this->color_frame = line_color;
	this->x = x;
	this->y = y;
	width = w;
	height = h;
	this-> color = color;
	PBar.push_back(ProgressBar(RED, 0x65FFD4, GetRValue(color),255,x+w*0.05,y+h*0.1,w*0.6,h*0.2));//红
	pinput.push_back(Inputbox(x + w * 0.7, y + h * 0.1,w*0.1,h*0.2,to_string(PBar.back().GetNum()), ALLOW_NUM));
	pinput.back().SetText(RED);
	PBar.push_back(ProgressBar(GREEN, 0x65FFD4, GetGValue(color),255, x + w * 0.05, y + h * 0.4, w * 0.6, h * 0.2));//绿
	pinput.push_back(Inputbox(x + w * 0.7, y + h * 0.4, w * 0.1, h * 0.2, to_string(PBar.back().GetNum()), ALLOW_NUM));
	pinput.back().SetText(GREEN);
	PBar.push_back(ProgressBar(BLUE, 0x65FFD4, GetBValue(color),255, x + w * 0.05, y + h * 0.7, w * 0.6, h * 0.2));//蓝
	pinput.push_back(Inputbox(x + w * 0.7, y + h * 0.7, w * 0.1, h * 0.2, to_string(PBar.back().GetNum()), ALLOW_NUM));
	pinput.back().SetText(BLUE);
}

void UniversalColor::show()
{
	//绘制边框
	ShowFrame();
	//显示颜色拖动进度条
	showProgress();
}

void UniversalColor::SetMsg(MOUSEMSG& msg)
{
	if (GetRange(msg))//是否在范围内
	{
		//所有可拖动进度条
		for (size_t i = 0; i < PBar.size(); i++)
		{
			//鼠标操作，将值赋值到输入框
			pinput[i].SetText(to_string(PBar[i].Set_Msg(msg)));
			
			//cout << colornum[i]<<" ";
			pinput[i].SetMsg(msg);
		}
		//cout << endl;
		color = RGB(PBar[0].GetNum(), PBar[1].GetNum(), PBar[2].GetNum());
	}
}

COLORREF& UniversalColor::getcolor()
{
	return color;
}

void UniversalColor::showProgress()
{
	//显示所有可拖动进度条
	for (size_t i = 0; i < PBar.size(); i++)
	{
		PBar[i].show();
		pinput[i].show();
		if (!pinput[i].GetText().empty())//将输入框的值赋值到进度条
		{
			int num = stoi(pinput[i].GetText());
			if (num > 255)
			{
				num = 255;
				pinput[i].GetText() = "255";
			}
				
			PBar[i].GetNum(num);
			//cout << num << endl;
		}
		
	}
}

COLORREF& UniversalColor::GetColor()
{
	return color;
}
