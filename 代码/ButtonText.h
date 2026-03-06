#pragma once
#include "Button.h"
class ButtonText ://文本按钮类
    public Button
{
public:
    ButtonText()=default;
    ButtonText(string str,COLORREF color) :str(str),text_color(color) {}
    void show();
    //设置显示文本
    void SetText(string str);
    //获取文本
    string GetText();
    //设置颜色
    void SetText(COLORREF color);
    
private:
    string str;
    COLORREF text_color;//文本颜色
};

