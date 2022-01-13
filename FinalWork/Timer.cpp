#include "Timer.h"
#include "TimeMgr.h"

Timer::Timer()
{
	TimeMgr::timers.push_back(this);
	this->time = 0;
	this->isStarted = false;
}

Timer::~Timer()
{
	for (vector<Timer*>::iterator it = TimeMgr::timers.begin(); it != TimeMgr::timers.end(); )
	{
		if (*it == this)
		{
			it = TimeMgr::timers.erase(it);
			break;
		}
		else
		{
			++it;
		}
	}
}


//开始从0计时
void Timer::start() {
	this->isStarted = true;
	this->time = 0;
}

//开始计时, 不置0
void Timer::restart() {
	this->isStarted = true;
}

//暂停计时
void Timer::pause() {
	this->isStarted = false;
}
