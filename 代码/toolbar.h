#pragma once
#include "Button.h"
#include"ButtonText.h"
#include "progressbar.h"
#include"curtool.h"
#include<vector>
class toolbar ://工具栏类
    public Button
{
public:
    toolbar(COLORREF fill_color, COLORREF line_color, int x = 0, int y = 0, int w = 10, int h = 10);
    ~toolbar();
    void show();
    void SetMsg(MOUSEMSG& msg);
    //获取选中工具
    CURTOOL& GetCurTool();
private:
    vector<ButtonText>  tool;//工具栏
    ProgressBar* thick;//线条粗细拖动进度条
    ButtonText WireNum;//线号，粗细文本显示
    CURTOOL curtool;//默认选中的工具，向外传递
};

