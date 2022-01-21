#pragma once
#include "Collider.h"
#include "Timer.h"
#include "Enemy.h"

class Aircraft : public Collider
{
public:
	Aircraft();
	~Aircraft();

	//模式,true为驾驶模式,由摄像机更改
	bool pattern;
	//选中的敌机
	Enemy *target;

	bool isChasing = false;;

	//override
	void Render();
	void Update();
	void Collision(Collider *col);

private:
	double moveSpeed;
	double rotSpeed;
	//射击间隔
	double shootInterval;
	//无敌时间
	double crashInterval;
	//计时器
	Timer *timerShoot, *timerCrash;
	bool shootLeft = true;

	//绘制飞机
	void DrawAircraft();

	//驾驶模式移动,每次移动之后需判断是否触及边界,即到(0,0,0)距离是否>=2500,是则pos = -pos
	void Move();

	//驾驶模式旋转
	void Rotate();

	//射击,按下空格/上帝视角模式调用
	void Shoot();

	//上帝模式追击敌机
	void PursueTarget();
};

