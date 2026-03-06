#pragma once
#include "Button.h"
#include "progressbar.h"
#include"InputBox.h"
#include<vector>
class UniversalColor ://万能取色版子
    public Button
{
public:
    UniversalColor(COLORREF fill_color, COLORREF line_color, COLORREF color, int x = 0, int y = 0, int w = 10, int h = 10);
    void show();
    void SetMsg(MOUSEMSG& msg);
    //获取显示颜色
    COLORREF& getcolor();
    //显示颜色拖动进度条
    void showProgress();
    //获取选中颜色
    COLORREF& GetColor();
private:
    Button* unColor;//鼠标万能取色板
    COLORREF color;//当前选中颜色
    vector<ProgressBar> PBar;//颜色拖动进度条
    vector<Inputbox>   pinput;//颜色输入框
    //int colornum[3];//进度条的值
};

