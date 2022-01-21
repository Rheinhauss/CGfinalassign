#pragma once
#include "Collider.h"
#include "Timer.h"
#include "Enemy.h"

class Aircraft : public Collider
{
public:
	Aircraft();
	~Aircraft();

	//ģʽ,trueΪ��ʻģʽ,�����������
	bool pattern;
	//ѡ�еĵл�
	Enemy *target;

	bool isChasing = false;;

	//override
	void Render();
	void Update();
	void Collision(Collider *col);

private:
	double moveSpeed;
	double rotSpeed;
	//������
	double shootInterval;
	//�޵�ʱ��
	double crashInterval;
	//��ʱ��
	Timer *timerShoot, *timerCrash;
	bool shootLeft = true;

	//���Ʒɻ�
	void DrawAircraft();

	//��ʻģʽ�ƶ�,ÿ���ƶ�֮�����ж��Ƿ񴥼��߽�,����(0,0,0)�����Ƿ�>=2500,����pos = -pos
	void Move();

	//��ʻģʽ��ת
	void Rotate();

	//���,���¿ո�/�ϵ��ӽ�ģʽ����
	void Shoot();

	//�ϵ�ģʽ׷���л�
	void PursueTarget();
};

