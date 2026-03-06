#pragma once

#include"Button.h"
#include"ColorPlate.h"
#include<Windows.h>
#include"canvas.h"
#include<thread>
#include"timer.hpp"
#define WIDTH 1100
#define HEIGHT 800

//鼠标操作
void mouse(Color_Plate* pcolorplate, canvas*canv,MOUSEMSG& msg);
//文本操作
void text(HWND hwnd,MOUSEMSG& msg, Color_Plate* colorPlate);