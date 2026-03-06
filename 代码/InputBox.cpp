#include"InputBox.h"
 void Inputbox::GetIMEString(HWND hWnd, string& str)
{
	HIMC hIMC = ImmGetContext(hWnd);//获取HIMC 
	if (hIMC)
	{
		//这里先说明一下，以输入“中国”为例 
		//切换到中文输入法后，输入“zhongguo”，这个字符串称作IME组成字符串 
		//而在输入法列表中选择的字符串“中国”则称作IME结果字符串 
		static bool flag = false;//输入完成标记：在输入中时，IME组成字符串不为空，置true；输入完成后，IME组成字符串为空，置false 
		DWORD dwSize = ImmGetCompositionStringW(hIMC, GCS_COMPSTR, NULL, 0); //获取IME组成输入的字符串的长度 
		if (dwSize > 0)//如果IME组成字符串不为空，且没有错误（此时dwSize为负值），则置输入完成标记为true 
		{
			if (flag == false)
			{
				flag = true;
			}
		}
		else if (dwSize == 0 && flag) //如果IME组成字符串为空，并且标记为true，则获取IME结果字符串 
		{
			int iSize; //IME结果字符串的大小 
			LPSTR pszMultiByte = NULL;//IME结果字符串指针 
			int ChineseSimpleAcp = 936;//宽字节转换时中文的编码 
			WCHAR* lpWideStr = NULL;//宽字节字符数组 
			dwSize = ImmGetCompositionStringW(hIMC, GCS_RESULTSTR, NULL, 0);//获取IME结果字符串的大小 
			if (dwSize > 0) //如果IME结果字符串不为空，且没有错误 
			{
				dwSize += sizeof(WCHAR);//大小要加上NULL结束符 
				//为获取IME结果字符串分配空间 
				if (lpWideStr)
				{
					delete[]lpWideStr;
					lpWideStr = NULL;
				}
				lpWideStr = new WCHAR[dwSize];
				memset(lpWideStr, 0, dwSize); //清空结果空间 
				ImmGetCompositionStringW(hIMC, GCS_RESULTSTR, lpWideStr, dwSize);//获取IME结果字符串，这里获取的是宽字节 
				iSize = WideCharToMultiByte(ChineseSimpleAcp, 0, lpWideStr, -1, NULL, 0, NULL, NULL);//计算将IME结果字符串转换为ASCII标准字节后的大小 
				//为转换分配空间 
				if (pszMultiByte)
				{
					delete[] pszMultiByte;
					pszMultiByte = NULL;
				}
				pszMultiByte = new char[iSize + 1];
				WideCharToMultiByte(ChineseSimpleAcp, 0, lpWideStr, -1, pszMultiByte, iSize, NULL, NULL);//宽字节转换 
				pszMultiByte[iSize] = '\0';
				//int pszwidth = strlen(pszMultiByte)* strwidth;//输入字的宽度
				//if (textwidth(str.c_str()) + pszwidth < width)
				str += pszMultiByte;//添加到string中 
				int pszwidth =str.size() * strwidth;
				//cout << pszwidth << endl;
				while (pszwidth > width)
				{
					str.pop_back();
					str.pop_back();
					pszwidth = str.size() * strwidth;
					//cout << pszwidth << endl;
				}
				
				//释放空间 
				if (lpWideStr)
				{
					delete[]lpWideStr;
					lpWideStr = NULL;
				}
				if (pszMultiByte)
				{
					delete[] pszMultiByte;
					pszMultiByte = NULL;
				}
			}
			flag = false;
		}
		ImmReleaseContext(hWnd, hIMC);//释放HIMC 
	}
}
Inputbox::Inputbox()
{
	cursor_time.Time(600);//设置光标定时器时间
	cursor_time.initial();
	SetText(height - 2, WHITE);
	cursor_x = 2 + x + textwidth(str.c_str());//移动光标到文字后面
	allow = ALLOW_ALL;
}

Inputbox::Inputbox(int x, int y,int wide,int hige, string str, int allow)
{
	this->x = x;
	this->y = y;
	this->width = wide;
	this->height = hige;
	this->str = str;
	this->allow = allow;
	cursor_x = x + 2;
	cursor_time.Time(600);//设置光标定时器时间
	cursor_time.initial();
	SetText(height - 2, WHITE);
	//settextstyle(height-2, 0, _T("楷体"));//设置字体大小
	//strwidth = textwidth("你");//单字符宽度
	cursor_x = 2 + x + textwidth(str.c_str());//移动光标到文字后面
}

void Inputbox::show()
{
	//绘制矩形
	ShowFrame();
	//SetMsg();//获取鼠标信息
	if (cursor_flag)
	{
		gettext();//从键盘获取字符输入
		//cout << str.c_str()<<endl;
	}
	SetText(height, color_text);
	if (cursor_flag && cursor_time.flag())
		line(cursor_x, y + 1, cursor_x, y + height - 1);//画线
	
	//cout << color_text << endl;
	outtextxy(x + 2, y + 2, str.c_str());
}

void Inputbox::GetTime(int T)
{
	cursor_time.Time(T);//设置光标定时器时间
}

bool& Inputbox::GetCursor()
{
	return cursor_flag;
}

void Inputbox::SetMsg(MOUSEMSG& msg)
{
	
	if (GetLeftClickDOWN(msg))
	{
		cursor_flag = true;
		//cout << "开启" << endl;
	}
	else if (!GetRange(msg)&&msg.uMsg == WM_LBUTTONDOWN)
	{
		cursor_flag = false;
		//cout << "关闭" << endl;
	}
}

void Inputbox::gettext()
{
	HWND hWnd = GetHWnd();
	{
		if (_kbhit()) //如果是ASCII输入 
		{
			char c = _getch();
			//printf("%d\n", c);
			if (c == '\b')
			{
				if (str.length() > 0)
				{
					if (str.at(str.length() - 1) & 0x8000)
						str.erase(str.end() - 1);
					str.erase(str.end() - 1);
				}
			}
			else if (c == 27||c==72||c==75||c==77||c==80||c==-32) {}
			else if (textwidth(str.c_str())+ strwidth < width ) 
			{
				if ((allow&ALLOW_NUM)&& (c >= '0' && c <= '9'))
					str += c;
				if ((allow & ALLOW_CAPLET)&& (c >= 'A' && c <= 'Z'))
					str += c;
				if ((allow & ALLOW_LOWLET) && (c >= 'a' && c <= 'z'))
				{
					str += c;
				}
			}
		}
		else if (textwidth(str.c_str())+ strwidth < width ) //除此之外，检测是否有IME输入，如果有，则将输入结果添加到string中 
		{
			
			if (allow & ALLOW_CHINESE)
			GetIMEString(hWnd, str);
		}
	}
	cursor_x=2+x+textwidth(str.c_str());//移动光标到文字后面
}

void Inputbox::SetText(int nHeight, COLORREF color)
{
	//settextstyle(height * 0.8, 0, _T("楷体"));//设置字体大小
	settextstyle(nHeight, 0, _T("楷体"));//设置字体大小
	strwidth = textwidth("a");//单字符宽度
	color_text = color;
	settextcolor(color_text);
	cursor_x = 2 + x + textwidth(str.c_str());//移动光标到文字后面
}

void Inputbox::SetText(COLORREF color)
{
	color_text = color;
}

void Inputbox::SetText(string str)
{
	this->str = str;
	cursor_x = 2 + x + textwidth(str.c_str());//移动光标到文字后面
}

string Inputbox::GetText()
{
	return str;
}

Inputbox::~Inputbox()
{
}

void Inputbox::SetColor(COLORREF color_fill, COLORREF color_frame)
{
	this->color_fill = color_fill;
	this->color_frame = color_frame;
}

void Inputbox::SetCoord(int x, int y, int w, int h)
{
	this->x = x;
	this->y = y;
	this->width = w;
	this->height = h;
}
