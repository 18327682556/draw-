#include"main.h"

int main()
{
	HWND hwnd=initgraph(WIDTH, HEIGHT/*, EW_SHOWCONSOLE*/);//创建窗口
	setbkcolor(WHITE);//设置背景颜色
	setbkmode(TRANSPARENT);//背景模式为透明
	cleardevice();//清屏
	Color_Plate* colorPlate =new Color_Plate(WHITE, BLACK, 5, 0, WIDTH*0.98, HEIGHT/8);//创建取色版
	MOUSEMSG msg = GetMouseMsg();//创建鼠标消息
	canvas* canv = new canvas(WHITE, BLACK,5, HEIGHT / 8, WIDTH * 0.98, HEIGHT / 8.0*6.95);//创建画布
	canv->SetCurTool(colorPlate->GetCurTool());//画布信息获取工具
	timer time(33);//创建定时器
	
	
	thread Text(text, hwnd, ref(msg), colorPlate);//创建标题栏信息显示
	while (true)
	{
		thread mou(mouse, colorPlate, canv, ref(msg));//鼠标消息
		if (time.decide())
		{
			BeginBatchDraw();//缓冲绘图
			colorPlate->show();//绘制取色板
			if (!colorPlate->GetUncolor())
			canv->show();//绘制画布
			EndBatchDraw();
		}
		mou.join();
	}
	Text.join();
}

void mouse(Color_Plate* colorPlate, canvas* canv, MOUSEMSG& msg)
{
	if (MouseHit())//是否有鼠标信息
	//if(peekmessage(msg))
	{
		msg = GetMouseMsg();//获取鼠标信息
		//colorPlate->SetMsg(canv, msg);//取色版鼠标操作
		
		if (!colorPlate->GetUncolor())//没有打开万能取色版
		{
		    thread camsg(&canvas::SetMsg, canv, ref(msg));
			camsg.detach();
		}
		colorPlate->SetMsg(canv, msg);//取色版鼠标操作
		
	}
}

void text(HWND hwnd,MOUSEMSG& msg, Color_Plate* colorPlate)
{
	while (true)
	{
		string str= "线粗:";
		str +=to_string(colorPlate->GetCurTool().thick)+ " 坐标" + to_string(msg.x) + "," + to_string(msg.y);
		SetWindowText(hwnd, str.c_str());//标题栏显示鼠标坐标
		this_thread::sleep_for(50ms);
	}
	
}
