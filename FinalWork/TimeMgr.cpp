#include "TimeMgr.h"
#include "iostream"
#include "DestroyMgr.h"

TimeMgr::TimeMgr()
{
}

TimeMgr::~TimeMgr()
{
}

//当前帧运行时间(不能获取精确时间则使用固定的帧率, FPS设为25，则时间为0.04秒)*scaleTime
//所有涉及随时间变化之类的都需要乘以 deltaTime, 以确定每秒变化一致
double TimeMgr::deltaTime = 1/60;
//时间流速, 正常流速为1
double TimeMgr::scaleTime = 1;
//从开始游戏时计时, Game Over时结束计时, 使用timer计时
double TimeMgr::currentTime = 0;
//计时器列表
vector<Timer*> TimeMgr::timers;

//统一计时, 遍历timers列表, 处于计时状态的加上当前帧时间, 处于暂停状态跳过
void TimeMgr::TIMER() {
	if (TimeMgr::timers.empty()) {
		return;
	}
	for (vector<Timer*>::iterator it = TimeMgr::timers.begin(); it != TimeMgr::timers.end(); ++it)
	{
		if ((*it)->isStarted == true) {
			(*it)->time += TimeMgr::deltaTime;
		}
	}
}
//删除计时器
void TimeMgr::DestroyTimer(Timer* t) {
	DestroyMgr::add(t);
}