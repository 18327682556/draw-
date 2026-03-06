#pragma once
#include<time.h>

class timer//定时器切换时间
{
public:
	timer() {}
	//设置切换时间毫秒
	timer(int T):time(T){}
	//设置切换时间毫秒
	void Time(int T)
	{
		this->time = T;
	}
	//设置被比较时间，比较时间,定时时间
	void Time(clock_t time_front, clock_t time_after,clock_t t)
	{
		this->time_front = time_front, this->time_after = time_after, this->time = t;
	}
	//设置被比较时间，比较时间
	void Time(clock_t time_front, clock_t time_after)
	{
		this->time_front = time_front, this->time_after = time_after;
	}
	//初始化倒计时,时间差设置为零
	void initial()//初始化倒计时
	{
		time_front = clock(), time_after = clock();
	}
	////时间到了
	//void setTimeUp()
	//{
	//	time_after = clock(), time_front = time_after - time;
	//}
	
	//判断是否到时间了，返回bool值
	bool decide()
	{
		if (!time)
			return true;
		if ((time_after - time_front) >= time)//间隔100毫秒更样式
		{
			time_flag = !time_flag;
			time_front = time_after;
			return true;
		}
		time_after = clock();
		return false;
	}
	//返回定时器内部bool值，是否发生了翻转
	bool flag()
	{
		decide();
		return time_flag;
	}
private:
	clock_t time_front = clock();//时间前比较时间
	clock_t time_after = clock();//时间后，实时时间
	bool time_flag = true;
	clock_t time=0;//切换到的时间
};
//#ifndef _TIMER_H_
//#define _TIMER_H_
//unsigned long long operator""_h(unsigned long long data)
//{
//	return data * 60 * 60;
//}
//unsigned long long operator""_s(unsigned long long data)
//{
//	return data * 60;
//}
//unsigned long long operator""_ms(unsigned long long data)
//{
//	return data;
//}
//unsigned long long operator""_fps(unsigned long long data)
//{
//	return 1000 / data;
//}
//#endif