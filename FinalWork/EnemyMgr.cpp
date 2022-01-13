#include "EnemyMgr.h"
#include "SceneMgr.h"

EnemyMgr::EnemyMgr()
{
}

EnemyMgr::~EnemyMgr()
{
}


//�л����ɵ��б�, ���ел����ɵ�����ڴ˵Ǽ�
vector<EnemySpawn*> EnemyMgr::EnemySpawns;
//�л��б�, �������ɵĵл������ڴ˵Ǽ�
vector<Enemy*> EnemyMgr::Enemys;
//��ǰ�л���
int EnemyMgr::curEnemyNum = 0;
//���л���
int EnemyMgr::maxEnemyNum = 20;
//�л�����ʱ����
double EnemyMgr::timeInterval = 5;
//�л����ɼ�ʱ��
Timer* EnemyMgr::timer = new Timer();
//ÿ֡����
void EnemyMgr::CreateEnemy() {
	if (EnemyMgr::curEnemyNum >= EnemyMgr::maxEnemyNum) {
		return;
	}
	//��ʱ��ʱ�� >= ���
	//��������
	if (timer->time < EnemyMgr::timeInterval) {
		return;
	}
	int n = (int)EnemyMgr::EnemySpawns.size();
	int index = (int)(SceneMgr::random() * n);
	Enemy* e = new Enemy();
	e->transform->position = EnemyMgr::EnemySpawns[index]->transform->position;
	e->transform->rotation = EnemyMgr::EnemySpawns[index]->transform->rotation;
	timer->start();//��0��ʼ��ʱ
}
//ɾ���л�
void EnemyMgr::DestroyEnemy(Enemy* e) {
	delete e;
}

//��ʼ��,��ʼ����һ�������л����ɵ�͵л�
void EnemyMgr::Init() {
	//����һ�������ĵл����ɵ�,�����ú�λ���뷽λ
	//new
	//set Transform,����Ҫ�ֶ������б�

	//����һ�������ĳ�ʼ���л�
	//����Ҫ���ĵ�ǰ����
}