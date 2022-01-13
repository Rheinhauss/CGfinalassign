#pragma once
#include "Collider.h"
#include "CVector.h"

class Bullet : public Collider
{
public:
	Bullet();
	~Bullet();

	//�����,������ʱ��λ��,�����ж��Ƿ񳬹����,ʵ��trailЧ��,�ɽ�trailЧ��д��һ�����component
	CVector point;

	//override
	void Render();
	void Update();
	void Collision(Collider *col);

private:
	double moveSpeed;
	//���,�����������ʧ
	static double shootRange;

	//�����ӵ�
	void DrawBullet();

	//ÿ���ƶ�֮�����ж��Ƿ񳬹����
	void Move();

};

