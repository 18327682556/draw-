#include "progressbar.h"

ProgressBar::ProgressBar(COLORREF fill_color, COLORREF line_color, int num, int max, int x, int y, int w, int h)
{
	this->color_fill = fill_color;
	this->color_frame = line_color;
	this->x = x;
	this->y = y;
	width = w;
	height = h;
	this->num = num;
	this->max = max;
	if (width > height)//水平
	{
		//level = true;
		//初始化圆数据
		r = height / 2;
		n = (width - 2 * r) / (double)max;
		ox = x + n * num + r;
		oy = y + r;
	}
	else //垂直
	{
		//level = false;
		//初始化圆数据
		r = width / 2;
		n = (height - 2 * r) / (double)max;
		oy = y + n * num + r;
		ox = x + r;
	}
	
}

void ProgressBar::show()
{
	//绘制边框
	setlinecolor(color_fill);
	setfillcolor(color_fill);
	fillrectangle(x, y, x + width, y + height);

	//画圆圈
	setfillcolor(color_frame);
	solidcircle(ox, oy, r);
}

int ProgressBar::Set_Msg(MOUSEMSG& msg)
{
	if (msg.wheel == 0)
	{
		if (operation == false && GetLeftClickDOWN(msg))//左键按下
		{
			operation = true;

		}
		else if (operation == true && msg.uMsg == WM_LBUTTONUP)//左键抬起
		{
			operation = false;
		}
		else if (operation == true /*&& msg.uMsg == WM_LBUTTONDOWN*/)//滑动中
		{
			if (width > height)//水平
			{
				if (msg.x < x + r)
					ox = x + r;
				else if (msg.x > (x + width - r))
					ox = x + width - r;
				else
					ox = msg.x;
				num = (ox - r - x) / n;
			}
			else
			{
				if (msg.y < y + r)
					oy = y + r;
				else if (msg.y > (y + height - r))
					oy = y + height - r;
				else
					oy = msg.y;
				num = (oy - r - y) / n;
			}
		}
	}
	else
	{
		if (operation == false && GetRange(msg))//鼠标滚轮操作
		{
			if (num >= 0 && num < max && msg.wheel < 0)
			{
				++num;
				if (width > height)//水平
				    ox = x + n * num + r;
				else
					oy = y + n * num + r;
			}
			else if (num > 0 && num <= max && msg.wheel > 0)
			{
				--num;
				if (width > height)//水平
					ox = x + n * num + r;
				else
					oy = y + n * num + r;
			}
			//cout << msg.wheel << endl;
		}
	}
	return num;
}

int& ProgressBar::GetNum()
{
	return num;
}

int& ProgressBar::GetNum(int N)
{
	this->num = N;
	if (width > height)//水平
		ox = x + n * num + r;
	else
		oy = y + n * num + r;
	return num;
}

int& ProgressBar::GetMax()
{
	return max;
}

bool ProgressBar::GetLeftClickDOWN(MOUSEMSG& msg)
{
	//鼠标是否点击了在圆上
	int distance = pow(msg.x - ox, 2) + pow(msg.y - oy, 2);
	if (distance <pow(r,2))
	{
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			return  true;
		}
	}
	return false;
}
