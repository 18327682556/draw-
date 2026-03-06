#pragma once
#include<string>
using namespace std;
struct  CurTool
{
	//序号
	int SerNum;
	//形态空或实
	string form;
	//工具
	string tool;
};

struct  CURTOOL
{
	//序号
	int SerNum;
	//线条粗细拖动进度条
	int thick;
	//当前选中颜色
	COLORREF current_color;
	//形态空或实
	string form;
	//工具
	string tool;
	//上一次的工具记录
	CurTool _CurTool;
};

