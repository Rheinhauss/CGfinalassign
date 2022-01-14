#pragma once
#include "Object.h"

class Timer : public Object
{
public:
	Timer();
	~Timer();

	//当前时间
	double time;
	//为true则计时
	bool isStarted;

	//开始从0计时
	void start();

	//开始计时, 不置0
	void restart();

	//暂停计时
	void pause();

private:

};

