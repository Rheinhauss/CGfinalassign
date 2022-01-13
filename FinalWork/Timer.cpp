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


//��ʼ��0��ʱ
void Timer::start() {
	this->isStarted = true;
	this->time = 0;
}

//��ʼ��ʱ, ����0
void Timer::restart() {
	this->isStarted = true;
}

//��ͣ��ʱ
void Timer::pause() {
	this->isStarted = false;
}
