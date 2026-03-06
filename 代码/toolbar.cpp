#include "toolbar.h"


toolbar::toolbar(COLORREF fill_color, COLORREF line_color, int x, int y, int w, int h)
{
	this->color_fill = fill_color;
	this->color_frame = line_color;
	this->x = x;
	this->y = y;
	width = w;
	height = h;
	//默认选中工具
	curtool.tool="画笔";
	curtool.SerNum = 0;
	//线条粗细拖动进度条
	thick = new ProgressBar(LIGHTCYAN, RED,0, 30, x + w * 0.01, y + h * 0.03, w * 0.02, h * 0.8);
	//线号显示
	WireNum.SetColor(fill_color, fill_color);
	WireNum.SetText(0);//黑色
	WireNum.SetCoord(x + w * 0.01, y + h * 0.8, w * 0.02, h * 0.19);
	WireNum.SetText(to_string(curtool.thick));
	//以下工具栏创建
	tool.push_back(ButtonText("画笔",WHITE));
	tool.push_back(ButtonText("直线",WHITE));
	tool.push_back(ButtonText("文字", WHITE));
	tool.push_back(ButtonText("撤销", WHITE));

	tool.push_back(ButtonText("矩形",WHITE));
	tool.push_back(ButtonText("椭圆",WHITE));
	tool.push_back(ButtonText("圆圈", WHITE));
	tool.push_back(ButtonText("清屏",WHITE));
	//设置坐标
	auto it = tool.begin();
	for (size_t i = 0; i < 4; i++)
	{
		
		it->SetCoord(x + w * 0.05 + i * h * 1.05, y + h * 0.1, h, h * 0.4);
		it++;
	}
	for (size_t i = 0; i < 4; i++)
	{
		it->SetCoord(x + w * 0.05 + i * h * 1.05, y + h * 0.55, h, h * 0.4);
		it++;
	}
}

toolbar::~toolbar()
{
	delete thick;
}

void toolbar::show()
{
	
	//选中工具高亮显示
	
	if (curtool.form == "空")//左键空心
	{
		tool[curtool.SerNum].SetColor(YELLOW, YELLOW);
		tool[curtool.SerNum].SetText(RED);
	}
	else//右键实心
	{
		tool[curtool.SerNum].SetColor(LIGHTCYAN, LIGHTCYAN);
		tool[curtool.SerNum].SetText(RED);
	}
	//未选中工具默认显示
	for (size_t i = 0; i < tool.size(); i++)
	{
		if (curtool.SerNum != i)
		{
			tool[i].SetColor(color_fill, color_fill);
			tool[i].SetText(BLACK);
		}
	}
	//绘制边框
	ShowFrame();

	//线条粗细拖动进度条
	thick->show();
	//绘制工具
	for (size_t i = 0; i < tool.size(); i++)
	{
		tool[i].show();
	}
	//线号，粗细文本显示
	WireNum.show();
}

void toolbar::SetMsg(MOUSEMSG& msg)
{
	for (size_t i = 0; i <tool.size(); i++)
	{
		tool[i].SetMsg(msg);
		string str = tool[i].GetText();
		if (str == "清屏"||str=="撤销")//临时保存上一次的
		{
			curtool._CurTool.form = curtool.form;
			curtool._CurTool.SerNum = curtool.SerNum;
			curtool._CurTool.tool = curtool.tool;
		}
		if (tool[i].GetLeftClickDOWN())//如果鼠标左键点击了
		{
			
			if (str != "画笔" && str != "直线" && str != "文字" && str != "清屏" && str != "撤销")
				curtool.form = "空";
			else
				curtool.form = "实";
			curtool.SerNum = i;
			curtool.tool = str;
			break;
		}
		else if (tool[i].GetRightClickDOWN())
		{
			//string str = tool[i].GetText();
			curtool.form = "实";
			curtool.SerNum = i;
			curtool.tool = str;
			break;
		}
	}
	
	//线条粗细拖动进度条
	curtool.thick=thick->Set_Msg(msg);
	WireNum.SetText(to_string(curtool.thick));
}

CURTOOL& toolbar::GetCurTool()
{
	return curtool;
}



