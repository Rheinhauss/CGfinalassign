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

	//����ʯ���������Ļ��Χ����
	MeteRange* mr;

	//override
	void Render();
	void Update();
	void Collision(Collider *col);
	//�ƶ�����
	CVector direction;

private:
	double moveSpeed;

	//�����ƶ������ʱ����
	double interval = 200;

	//��ʱ��
	Timer* timer;



	//������ʯ
	void DrawMeteorite();

	//�ƶ�, ÿ��interval����һ������ƶ�����, �������߽�, ���ƶ������Ϊ�෴���򲢴�0��ʼ��ʱ
	void Move();



};

