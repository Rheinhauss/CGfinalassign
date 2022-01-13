#pragma once
#include "Timer.h"
#include <vector>
using namespace std;

class TimeMgr
{
public:
	TimeMgr();
	~TimeMgr();

	//��ǰ֡����ʱ��(���ܻ�ȡ��ȷʱ����ʹ�ù̶���֡��, FPS��Ϊ25����ʱ��Ϊ0.04��)*scaleTime
	//�����漰��ʱ��仯֮��Ķ���Ҫ���� deltaTime, ��ȷ��ÿ��仯һ��
	static double deltaTime;
	//ʱ������, ��������Ϊ1
	static double scaleTime;
	//�ӿ�ʼ��Ϸʱ��ʱ, Game Overʱ������ʱ, ʹ��timer��ʱ
	static double currentTime;
	//��ʱ���б�
	static vector<Timer*> timers;

	//ͳһ��ʱ, ����timers�б�, ���ڼ�ʱ״̬�ļ��ϵ�ǰ֡ʱ��, ������ͣ״̬����
	static void TIMER();
	//ɾ����ʱ��
	static void DestroyTimer(Timer* t);

private:

};

