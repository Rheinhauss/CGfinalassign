#pragma once

class Timer
{
public:
	Timer();
	~Timer();

	//��ǰʱ��
	double time;
	//Ϊtrue���ʱ
	bool isStarted;

	//��ʼ��0��ʱ
	void start();

	//��ʼ��ʱ, ����0
	void restart();

	//��ͣ��ʱ
	void pause();

private:

};

