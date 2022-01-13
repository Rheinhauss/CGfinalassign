#pragma once
#include "Collider.h"
#include "CVector.h"
#include "Path.h"

class Bullet : public Collider
{
public:
	Bullet();
	~Bullet();

	//发射点,即发射时的位置,用于判断是否超过射程,实现trail效果,可将trail效果写成一个组件component
	CVector point;
	Path path;

	//override
	void Render();
	void Update();
	void Collision(Collider *col);

private:
	double moveSpeed;
	//射程,超过射程则消失
	static double shootRange;

	//绘制子弹
	void DrawBullet();

	//每次移动之后需判断是否超过射程
	void Move();

};

