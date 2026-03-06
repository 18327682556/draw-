#include "Button.h"

//Button::Button(string str, int x, int y, int w, int h)
//{
//	image = new IMAGE;
//	loadimage(image,str.c_str(),w,h);
//	
//}

Button::~Button()
{
	/*if (image)
		delete image;*/
}

void Button::SetColor(COLORREF fill_color, COLORREF line_color)
{
	this->color_fill = fill_color;
	this->color_frame = line_color;
	//cout << this->color_fill << endl;
}

void Button::SetCoord(int x , int y , int w , int h)
{
	this->x = x;
	this->y = y;
	this->width = w;
	this->height = h;
}

void Button::show()
{
	ShowFrame();
}

COLORREF& Button::GetFillColor()
{
	return color_fill;
}

bool Button::GetLeftClickDOWN(MOUSEMSG& msg)
{
	if (msg.x > x && msg.x < x + width && msg.y>y && msg.y < y + height)
	{
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			return  true;
			//cout << "×ó¼ü" << endl;
		}
	}
	return false;
}

bool Button::GetLeftClickDOWN()
{
	return left_click;
}

bool Button::GetLeftClickUP(MOUSEMSG& msg)
{
	if (msg.x > x && msg.x < x + width && msg.y>y && msg.y < y + height)
	{
		if (msg.uMsg == WM_LBUTTONUP)
		{
			return  true;
		}
	}
	return false;
}

bool Button::GetRightClickDOWN(MOUSEMSG& msg)
{
	if (msg.x > x && msg.x < x + width && msg.y>y && msg.y < y + height)
	{
		if (msg.uMsg == WM_RBUTTONDOWN)
		{
			return true;
			//cout << "ÓÒ¼ü" << endl;
		}
	}
	return false;
}
bool Button::GetRightClickDOWN()
{
	return right_click;
}
void Button::ShowFrame()
{
	//»æÖÆ±ß¿ò
	setlinecolor(color_frame);
	setfillcolor(color_fill);
	if (!trans_frame)
		rectangle(x, y, x + width, y + height);
	if (!trans_fill)
		fillrectangle(x, y, x + width, y + height);
}
//
void Button::SetMsg(MOUSEMSG&msg)
{

	if (msg.x > x && msg.x < x + width && msg.y>y && msg.y < y + height)
	{
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			left_click = true;
			//cout << "×ó¼ü" << endl;
		}
		else
		{
			left_click = false;
		}
		if (msg.uMsg == WM_RBUTTONDOWN)
		{
			right_click = true;
			//cout << "ÓÒ¼ü" << endl;
		}
		else
		{
			right_click = false;
		}
	}
	//return;
}

bool Button::GetRange(MOUSEMSG& msg)
{
	if (msg.x > x && msg.x < x + width && msg.y>y && msg.y < y + height)
	{
		return true;
	}
	return false;
}

bool& Button::SetTransFill()
{
	return trans_fill;
}

bool& Button::SetTransFrame()
{
	return trans_frame;
}

int Button::GetX()
{
	return x;
}

int Button::GetY()
{
	return y;
}

int Button::GetW()
{
	return width;
}

int Button::GetH()
{
	return height;
}
