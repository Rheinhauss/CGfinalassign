#pragma once
#include "Collider.h"
#include "Timer.h"
#include "CVector.h"

class Enemy : public Collider
{
public:
	Enemy();
	~Enemy();

	//override
	void Render();
	void Update();
	void Collision(Collider *col);

private:
	double moveSpeed, rotSpeed;
	double seta;
	bool isrotating = false;

	//更改移动方向的时间间隔
	double rinterval,rpinterval;

	//计时器
	Timer* rtimer,*rptimer;

	//移动方向
	CVector direction;

	//绘制敌机
	void DrawEnemy();

	//移动,每隔interval更改一次随机移动方向
	void Move();
};

