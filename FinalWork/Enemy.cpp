#include "Enemy.h"
#include "SceneMgr.h"
#include "EnemyMgr.h"

Enemy::Enemy()
{
	this->name = "enemy";
	this->tag = "enemy";
	this->moveSpeed = 8;
	this->interval = 3;
	this->timer = new Timer();
	//ʼ����z=0ƽ����
	this->direction = CVector((float)SceneMgr::random(), (float)SceneMgr::random(), 0);
	//����л��б�
	EnemyMgr::Enemys.push_back(this);
	++EnemyMgr::curEnemyNum;
	/*
	���ݻ��Ƶ�ģ��,������ײ�з�Χ
	this->maxXYZ
	this->minXYZ
	*/
}

Enemy::~Enemy()
{
	for (vector<Enemy*>::iterator it = EnemyMgr::Enemys.begin(); it != EnemyMgr::Enemys.end(); )
	{
		if (*it == this)
		{
			it = EnemyMgr::Enemys.erase(it);
			break;
		}
		else
		{
			++it;
		}
	}
	delete this->timer;
	--EnemyMgr::curEnemyNum;
}


//override
void Enemy::Render() {
	this->DrawEnemy();
}
void Enemy::Update() {
	Move();
}
void Enemy::Collision(Collider *col) {
	EnemyMgr::DestroyEnemy(this);
}

//���Ƶл�
void Enemy::DrawEnemy() {

}

//�ƶ�,ÿ��interval����һ������ƶ�����
void Enemy::Move() {
	//this->Transform->position����λ�� �ٶ�*forward*deltaTime

	//�жϼ�ʱ���Ƿ�>=���
	//��,����ķ���,��ת�л������Ӧ����???(���鸽��)
}