#pragma once
#include "Timer.h"
#include <vector>
using namespace std;

class TimeMgr
{
public:
	TimeMgr();
	~TimeMgr();

	//当前帧运行时间(不能获取精确时间则使用固定的帧率, FPS设为25，则时间为0.04秒)*scaleTime
	//所有涉及随时间变化之类的都需要乘以 deltaTime, 以确定每秒变化一致
	static double deltaTime;
	//时间流速, 正常流速为1
	static double scaleTime;
	//从开始游戏时计时, Game Over时结束计时, 使用timer计时
	static double currentTime;
	//计时器列表
	static vector<Timer*> timers;

	//统一计时, 遍历timers列表, 处于计时状态的加上当前帧时间, 处于暂停状态跳过
	static void TIMER();
	//删除计时器
	static void DestroyTimer(Timer* t);

private:

};

