#include "EnemyMgr.h"
#include "SceneMgr.h"
#include "DestroyMgr.h"

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
int EnemyMgr::maxEnemyNum = 8;
//�л�����ʱ����
double EnemyMgr::timeInterval = 1;
//�л����ɼ�ʱ��
Timer* EnemyMgr::timer;
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
	add();
	timer->start();//��0��ʼ��ʱ
	
}
//ɾ���л�
void EnemyMgr::DestroyEnemy(Enemy* e) {
	DestroyMgr::add(e);
}

//��ʼ��,��ʼ����һ�������л����ɵ�͵л�
void EnemyMgr::Init() {
	new EnemySpawn(CVector(80, 0, 80));
	new EnemySpawn(CVector(-80, 0, 80));
	timer = new Timer();
	timer->start();
	add(); add(); add(); add();
	add(); add(); add(); add();
}
void EnemyMgr::add() {
	int n = (int)EnemyMgr::EnemySpawns.size();
	int index = (int)(SceneMgr::random(false) * n);
	Enemy* e = new Enemy();
	e->transform->position =
		EnemyMgr::EnemySpawns[index]->transform->position;
	//float seta = SceneMgr::random(false) * 360.0;
	//CMatrix m;
	//m.SetRotate(seta)
	e->transform->rotation =
		EnemyMgr::EnemySpawns[index]->transform->rotation;
}