#pragma once
#include "Button.h"
#include<math.h>
class ProgressBar ://进度条类，可拖动
    public Button
{
public:
    ProgressBar(COLORREF fill_color, COLORREF line_color,int num=0, int max=100, int x = 0, int y = 0, int w = 10, int h = 10);
    void show();
    //获取鼠标信息
    int Set_Msg(MOUSEMSG& msg);
    //获取进度条的值
    int& GetNum();
    int& GetNum(int N);
    //获取最大值
    int& GetMax();
    //获取鼠标是否左键按下
    bool GetLeftClickDOWN(MOUSEMSG& msg);

private:
    bool  operation = false;//活动中
    int num=0;//进度条
    int max = 255;//进度条最大值
    double n;//单格 
    int ox;
    int oy;
    int r;
};

