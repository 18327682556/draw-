#include "ColorPlate.h"

Color_Plate::Color_Plate(COLORREF fill_color, COLORREF line_color, int x, int y, int w, int h)
{
	this->color_fill = fill_color;
	this->color_frame = line_color;
	this->x = x;
	this->y = y;
	width = w;
	height = h;

	//color = new COLORREF[20]{RGB(0,0,0),RGB(127,127,127),RGB(136,0,21) ,RGB(237,28,36) ,RGB(255,127,39) ,RGB(255,242,0) ,RGB(34,177,76) ,RGB(0,162,232) ,RGB(63,72,204) ,RGB(163,73,164),
	//RGB(255,255,255),RGB(195,195,195),RGB(185,122,87),RGB(255,174,201),RGB(255,201,14),RGB(237,228,176),RGB(181,230,29),RGB(153,217,234),RGB(112,146,190),RGB(200,191,231) };
	//color[0] = pair<COLORREF, string>(RGB(0, 0, 0), "黑色");
	color[RGB(0, 0, 0)]= "黑色";color[RGB(127, 127, 127)] = "黑色";color[RGB(136, 0, 21)] = "黑色";color[RGB(237, 28, 36)] = "黑色";
	color[RGB(255, 127, 39)] = "黑色";color[RGB(255, 242, 0)] = "黑色";color[RGB(34, 177, 76)] = "黑色";color[RGB(0, 162, 232)] = "黑色";
	color[RGB(63, 72, 204)] = "黑色";color[RGB(163, 73, 164)] = "黑色";color[RGB(255, 255, 255)] = "黑色";color[RGB(195, 195, 195)] = "黑色";
	color[RGB(185, 122, 87)] = "黑色";color[RGB(255, 174, 201)] = "黑色";color[RGB(255, 201, 14)] = "黑色";color[RGB(237, 228, 176)] = "黑色";
	color[RGB(181, 230, 29)] = "黑色"; color[RGB(153, 217, 234)] = "黑色"; color[RGB(112, 146, 190)] = "黑色"; color[RGB(200, 191, 231)] = "黑色";
	auto it = color.begin();
	GetColorbutton = new Button[20];
	for (size_t i = 0; i < 10; i++)//第一行颜色
	{
		GetColorbutton[i].SetColor(it->first/*color[i]*/);
		GetColorbutton[i].SetCoord(h * 0.98+i*h*0.43, h * 0.1,h*0.4, h * 0.4);
		it++;
	}
	for (size_t i = 0; i < 10; i++)//第二行颜色
	{
		GetColorbutton[10+i].SetColor(it->first/*color[10+i]*/);
		GetColorbutton[10+i].SetCoord(h * 0.98 + i * h * 0.43, h * 0.53, h * 0.4, h * 0.4);
		it++;
	}

	current_button = new Button;//创建当前颜色显示窗口
	current_button->SetCoord(h * 0.1, h * 0.1, h*0.8, h*0.8);//绘制当前取色窗口
	current_button->SetColor(BLACK);//设置默认颜色

	tool = new toolbar(GREEN, BLACK, h * 5.30,h*0.05,w-5.30*h,h*0.9);//创建工具栏
	
}

Color_Plate::~Color_Plate()
{
	//delete[] color;
	delete[] GetColorbutton;
	delete current_button;
	delete tool;
	if (Uncolor)
		delete Uncolor;
}

void Color_Plate::show()
{
	//绘制边框
	ShowFrame();
	//绘制取色图形
	for (size_t i = 0; i < 20; i++)
	{
		/*thread show(&Button::show, GetColorbutton[i]);
		show.detach();*/
		GetColorbutton[i].show();
	}
	//绘制显示当前颜色
	current_button->show();//选中颜色显示
	//绘制工具栏
	tool->show();
	//显示万能取色面板
	PtrUncolor();
}

void Color_Plate::PtrUncolor()
{
	if (Uncolor != nullptr)
	{
		Uncolor->show();
		//cout << "显示" << endl;
	}
}

bool& Color_Plate::ShowUncolor()
{
	return showUncolor;
}

void Color_Plate::SetMsg(canvas* canv, MOUSEMSG& msg)
{
	
	if (GetRange(msg))
	{
		for (size_t i = 0; Uncolor == nullptr && i < 20; i++)
		{
			if (GetColorbutton[i].GetLeftClickDOWN(msg))//如果鼠标左键点击了
			{
				//cout << "左键" << endl;
				COLORREF current_color = GetColorbutton[i].GetFillColor();
				current_button->SetColor(current_color);
				GetCurTool().current_color = current_color;//设置颜色
			}
		}
		if(Uncolor == nullptr)
		tool->SetMsg(msg);//工具栏触发
		if (current_button->GetLeftClickDOWN(msg))//显示选中颜色的按钮，单机进入选择更多颜色
		{
			if (Uncolor==nullptr)
			{
				canv->GetImage();
				Uncolor = new  UniversalColor(WHITE, BLACK, current_button->GetFillColor(), width * 0.1, height * 1.1, width * 0.7, height);//创建万能取色板子
				//Uncolor->GetColor()= current_button->GetFillColor();//设置万能取色版的默认颜色
				//cout << "左键单机" << endl;
			}
		}
	}
	else if (Uncolor != nullptr)
	{
		if (Uncolor->GetRange(msg))
		{
			Uncolor->SetMsg(msg);//万能面板操作
			COLORREF current_color=Uncolor->getcolor();
			current_button->SetColor(current_color);
		}
		else if(msg.uMsg == WM_LBUTTONDOWN)
		{
			//cout << "析构" << endl;
			{
				canv->PutImage();
				delete Uncolor;
				Uncolor = nullptr;
			}
		}
		
	}
}

bool Color_Plate::GetUncolor()
{
	return Uncolor!=nullptr;
}
CURTOOL& Color_Plate::GetCurTool()
{
	tool->GetCurTool().current_color = current_button->GetFillColor();
	return tool->GetCurTool();
}

COLORREF& Color_Plate::Getcolor()
{
	return current_button->GetFillColor();
}
