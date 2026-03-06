#pragma once
#include "Button.h"
#include"ButtonText.h"
#include"toolbar.h"
#include "UniversalColor.h"
#include"canvas.h"
#include"curtool.h"
#include<map>
#include<thread>
//取色版和工具箱
class Color_Plate :
    public Button
{
public:
    Color_Plate(COLORREF fill_color, COLORREF line_color, int x = 0, int y = 0, int w = 10, int h = 10);
    ~Color_Plate();
    void show();//显示
    //是否创建万能选色窗口
    void PtrUncolor();
    //是否显示万能选色窗口
    bool& ShowUncolor();
    void SetMsg(canvas* canv, MOUSEMSG& msg);
    //万能取色版是否创建
    bool GetUncolor();
    CURTOOL& GetCurTool();
    //获取当前颜色
    COLORREF& Getcolor();
private:
    map<COLORREF,string>color;//所有颜色
    Button* GetColorbutton;//取色点
    Button* current_button;//当前颜色显示
    UniversalColor* Uncolor=nullptr;//万能取色面板
    toolbar* tool;//工具栏
    bool showUncolor = false;
};

