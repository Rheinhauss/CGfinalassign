#include "Enemy.h"
#include "SceneMgr.h"
#include "EnemyMgr.h"
#include "TimeMgr.h"
#include "glut.h"

Enemy::Enemy()
{
	this->name = "enemy";
	this->tag = "enemy";
	this->rinterval = 1;
	this->rpinterval = 0.5;
	this->seta = SceneMgr::randint() % 360;
	//this->seta = 0;
	CMatrix m;
	m.SetRotate(seta, CVector(0, 1, 0));
	this->transform->rotation = m.ToCQuaternion();
	this->rtimer = new Timer();
	rtimer->start();
	this->rptimer = new Timer();
	//始终在y=0平面内
	this->direction = CVector(cos(seta/180*PI), 0, sin(seta / 180 * PI));
	this->moveSpeed = 0.05;
	this->rotSpeed = 2;
	//加入敌机列表
	EnemyMgr::Enemys.push_back(this);
	++EnemyMgr::curEnemyNum;
	/*
	根据绘制的模型,设置碰撞盒范围
	this->maxXYZ
	this->minXYZ
	*/	
	this->maxXYZ = CVector(6, 3, 3);
	this->minXYZ = CVector(0, -3, -3);
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
	delete this->rtimer;
	--EnemyMgr::curEnemyNum;
}


//override
void Enemy::Render() {
	this->DrawEnemy();
}
void Enemy::Update() {
	Move();
	//proj*view*model
	auto z = SceneMgr::ProjMatrix * SceneMgr::ViewMatrix;
	auto r = this->transform->rotation.ToCMatrix();
	auto a = z.posMul(r.posMul(this->transform->position) + this->minXYZ);
	auto b = z.posMul(r.posMul(this->transform->position) + this->maxXYZ);
	ScreenMaxXY.x = max(a.x, b.x);
	ScreenMinXY.x = min(a.x, b.x); 
	ScreenMaxXY.y = max(a.y, b.y);
	ScreenMinXY.y = min(a.y, b.y);
}
void Enemy::Collision(Collider *col) {
	if ((col->tag == "enemy"))return;
	else if ((col->tag == "Aircraft"))return;
	else if ((col->tag == "meteorite"))return;
	else 
		EnemyMgr::DestroyEnemy(this);
}

//绘制敌机
void Enemy::DrawEnemy() {
	glPushMatrix();
	glColor3f(1, 0, 0);
	glRotatef(90, 0, 1, 0);
	glutSolidCone(3, 6, 10, 10);
	glPopMatrix();

}

//移动,每隔interval更改一次随机移动方向
void Enemy::Move() {
	this->direction = CVector(cos(seta / 180 * PI), 0, sin(seta / 180 * PI));
	//this->Transform->position更改位置 速度*forward*deltaTime
	this->transform->position = this->transform->position +
			direction * this->moveSpeed * TimeMgr::deltaTime;
	CMatrix m;
	m.SetRotate(seta, CVector(0, -1, 0));
	this->transform->rotation = m.ToCQuaternion();
	if (!isrotating) {
		if (rtimer->time >= rinterval) {
			rptimer->start();
			rtimer->pause();
			isrotating = true;
		}
	}
	else {
		seta = fmod(seta + rotSpeed, 360.0);
		if (rptimer->time >= rpinterval) {
			rtimer->start();
			rptimer->pause();
			isrotating = false;
		}
	}

	//判断计时器是否>=间隔
	//是,则更改方向,旋转敌机朝向对应方向???(酌情附加)
}