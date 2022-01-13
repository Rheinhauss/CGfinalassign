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
	//始终在z=0平面内
	this->direction = CVector((float)SceneMgr::random(), (float)SceneMgr::random(), 0);
	//加入敌机列表
	EnemyMgr::Enemys.push_back(this);
	++EnemyMgr::curEnemyNum;
	/*
	根据绘制的模型,设置碰撞盒范围
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

//绘制敌机
void Enemy::DrawEnemy() {

}

//移动,每隔interval更改一次随机移动方向
void Enemy::Move() {
	//this->Transform->position更改位置 速度*forward*deltaTime

	//判断计时器是否>=间隔
	//是,则更改方向,旋转敌机朝向对应方向???(酌情附加)
}