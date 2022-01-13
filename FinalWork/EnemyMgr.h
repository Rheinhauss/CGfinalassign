#pragma once
#include <vector>
#include "EnemySpawn.h"
#include "Enemy.h"

class EnemyMgr
{
public:
	EnemyMgr();
	~EnemyMgr();

	//�л����ɵ��б�, ���ел����ɵ�����ڴ˵Ǽ�
	static vector<EnemySpawn*> EnemySpawns;
	//�л��б�, �������ɵĵл������ڴ˵Ǽ�
	static vector<Enemy*> Enemys;
	//��ǰ�л���
	static int curEnemyNum;
	//���л���
	static int maxEnemyNum;
	//�л�����ʱ����
	static double timeInterval;
	//�л����ɼ�ʱ��
	static Timer* timer;
	//ÿ֡����
	static void CreateEnemy();
	//ɾ���л�
	static void DestroyEnemy(Enemy *e);
	//��ʼ��,��ʼ����һ�������л����ɵ�͵л�
	static void Init();

private:

};

