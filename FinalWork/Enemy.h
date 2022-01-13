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

	//�����ƶ������ʱ����
	double interval;

	//��ʱ��
	Timer* timer;

	//�ƶ�����
	CVector direction;

	//���Ƶл�
	void DrawEnemy();

	//�ƶ�,ÿ��interval����һ������ƶ�����
	void Move();
};

