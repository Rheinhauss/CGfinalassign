#pragma once
#include "Collider.h"
#include "Timer.h"
#include "CVector.h"
#include "MeteRange.h"

class Meteorite :public Collider
{
public:
	Meteorite(MeteRange*);
	~Meteorite();

	//此陨石对象所属的活动范围对象
	MeteRange* mr;

	//override
	void Render();
	void Update();
	void Collision(Collider *col);
	//移动方向
	CVector direction;

private:
	double moveSpeed;

	//更改移动方向的时间间隔
	double interval = 200;

	//计时器
	Timer* timer;



	//绘制陨石
	void DrawMeteorite();

	//移动, 每隔interval更改一次随机移动方向, 如果到达边界, 则移动方向变为相反方向并从0开始计时
	void Move();



};

