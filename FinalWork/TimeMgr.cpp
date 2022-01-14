#include "TimeMgr.h"
#include "iostream"
#include "DestroyMgr.h"

TimeMgr::TimeMgr()
{
}

TimeMgr::~TimeMgr()
{
}

//��ǰ֡����ʱ��(���ܻ�ȡ��ȷʱ����ʹ�ù̶���֡��, FPS��Ϊ25����ʱ��Ϊ0.04��)*scaleTime
//�����漰��ʱ��仯֮��Ķ���Ҫ���� deltaTime, ��ȷ��ÿ��仯һ��
double TimeMgr::deltaTime = 1/60;
//ʱ������, ��������Ϊ1
double TimeMgr::scaleTime = 1;
//�ӿ�ʼ��Ϸʱ��ʱ, Game Overʱ������ʱ, ʹ��timer��ʱ
double TimeMgr::currentTime = 0;
//��ʱ���б�
vector<Timer*> TimeMgr::timers;

//ͳһ��ʱ, ����timers�б�, ���ڼ�ʱ״̬�ļ��ϵ�ǰ֡ʱ��, ������ͣ״̬����
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
//ɾ����ʱ��
void TimeMgr::DestroyTimer(Timer* t) {
	DestroyMgr::add(t);
}