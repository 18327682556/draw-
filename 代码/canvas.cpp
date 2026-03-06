#include "canvas.h"

canvas::canvas(COLORREF fill_color, COLORREF line_color, int x, int y, int w, int h)
{
	this->color_fill = fill_color;
	this->color_frame = line_color;
	this->x = x;
	this->y = y;
	width = w;
	height = h;
	//保存一张空白的起始图像
	GetImage();
	listimage.push_back(image);
}

canvas::~canvas()
{
}

void canvas::show()
{
	ShowFrame();
	PutImage();
	//putimage(x, y, &image);
	Draw();//手动绘图中
	//输入框输入文字中
	if (text != nullptr)
	{
		text->SetText(curtool->current_color);
		//cout << "输出" << endl;
		if (text->SetTransFrame() == true) 
		{
			putimage(x, y, &image_txt);
			text->show();
			GetImage();//保存图像
			listimage.push_back(image);//保存到链表
			//cout << "释放" << endl;
			delete text;
			text = nullptr;
			return;
		}
		text->show();
	}
	
}

void canvas::GetImage()
{
	getimage(&image, x+1, y+1, width-1, height-1);//保存图像
}

void canvas::PutImage()
{
	putimage(x+1, y+1, &image);
}

void canvas::SetCurTool(CURTOOL &curtool)
{
	this->curtool = &curtool;
}

void canvas::SetMsg(MOUSEMSG& msg)
{
	if (GetRange(msg))
	{
		if (text != nullptr/*&&curtool->tool == "文字"*/)
		{
			text->SetMsg(msg);
			if (operation == false && operText==true && (!text->GetRange(msg)) && GetLeftClickDOWN(msg)/* && text->GetCursor() == false*/)
			{
				text->SetTransFrame() = true;//设置透明边框
				//delete text;
				text->GetCursor() = false;
				operText = false;
				//cout << "输出" << endl;
				return;
				//PutImage();
			}
			//Inputbox input(text->GetX(), text->GetY(), text->GetW(), text->GetH());
		}
		//在画布中左键按下
		 if (operation == false && GetLeftClickDOWN(msg))
		{
			x1 = msg.x;
			y1 = msg.y;
			GetImage();//保存图像
			if(curtool->tool == "文字"&& text == nullptr)
			{
				getimage(&image_txt, x, y, width, height);//保存图像
				//cout << "保存图像" << endl;
			}
			operation = true;
		}
		else if (operation == true && GetLeftClickUP(msg))
		{
			
			//else
			{
				GetImage();
				//cout << "保存" << endl;
				
				/*x1 = 0;
				y1 = 0;*/
				
				//y2 = 0;
				//画完后保存到链表中
				if(text == nullptr)
				listimage.push_back(image);
			}
			x2 = 0;
			operation = false;
			
			if (curtool->tool == "文字")
			{
				operText = true;
			}
		}
		else if (operation == true && msg.x > x + 2 && msg.x < x + width - 2 && msg.y>y + 2 && msg.y < y + height - 2)
		{
			x2 = msg.x;
			y2 = msg.y;
		}
		if (GetRightClickDOWN(msg))//在画布中单机鼠标右键切换实心或空心
		{
			if (curtool->form == "空")
			{
				curtool->form = "实";
			}
			else if (curtool->tool == "矩形" || curtool->tool == "椭圆" || curtool->tool == "圆圈")
			{
				curtool->form = "空";
			}
		}
	}
}

void canvas::Draw()
{
	if (operation&& x2 > 0)
	{
		setlinecolor(curtool->current_color);//线条颜色
		setfillcolor(curtool->current_color);//填充颜色
		LINESTYLE pstyle;
		getlinestyle(&pstyle);
		setlinestyle(PS_SOLID, curtool->thick);
		if (curtool->tool == "画笔")
		{
			line(x1, y1, x2, y2);
			x1 = x2;
			y1 = y2;
			GetImage();
		}
		else if (curtool->tool == "直线")
			line(x1, y1, x2, y2);
		else if (curtool->tool == "文字")
			Drawtext(x1, y1, x2, y2);
		else if (curtool->tool == "椭圆"&& curtool->form=="空")
			ellipse(x1, y1, x2, y2);
		else if (curtool->tool == "圆圈" && curtool->form == "空")
			circle((x1 + x2) / 2, (y1 + y2) / 2, sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) / 2);
		else if (curtool->tool == "矩形" && curtool->form == "空")
			rectangle(x1, y1, x2, y2);
		else if (curtool->tool == "矩形" && curtool->form == "实")
			solidrectangle(x1, y1, x2, y2);
		else if (curtool->tool == "椭圆" && curtool->form == "实")
			solidellipse(x1, y1, x2, y2);
		else if (curtool->tool == "圆圈" && curtool->form == "实")
			solidcircle((x1 + x2) / 2, (y1 + y2) / 2, sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) / 2);
		setlinestyle(&pstyle);
	}
	else if (curtool->tool == "清屏")
	{
		clearrectangle(x+1, y+1, x + width-1, y + height-1);
		GetImage();
		x1 = 0;
		y1 = 0;
		x2 = 0;
		y2 = 0;
		//回到原来的工具
		curtool->form= curtool->_CurTool.form;
		curtool->SerNum= curtool->_CurTool.SerNum;
		curtool->tool= curtool->_CurTool.tool;
	}
	else if (curtool->tool == "撤销")
	{
	    //回到上一张画面
		if (listimage.size()>1)
		{
			listimage.pop_back();
			image = listimage.back();
		}
			
		//回到原来的工具
		curtool->form = curtool->_CurTool.form;
		curtool->SerNum = curtool->_CurTool.SerNum;
		curtool->tool = curtool->_CurTool.tool;
	}
}

void canvas::Drawtext(int x1, int y1, int x2, int y2)
{
	if (text == nullptr)
	{
		text = new Inputbox;
		text->GetCursor()=true;
	}
		
	if (x1<x2&&y1<y2)
		text->SetCoord(x1, y1,x2-x1,y2-y1 );
	else if(x1 < x2&& y1> y2)
		text->SetCoord(x1, y2, x2 - x1, y1 - y2);
	text->SetTransFill() = true;
	if(operation == true)
	text->show();
	
}
