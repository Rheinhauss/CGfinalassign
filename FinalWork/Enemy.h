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
	double moveSpeed;

	//更改移动方向的时间间隔
	double interval;

	//计时器
	Timer* timer;

	//移动方向
	CVector direction;

	//绘制敌机
	void DrawEnemy();

	//移动,每隔interval更改一次随机移动方向
	void Move();
};

