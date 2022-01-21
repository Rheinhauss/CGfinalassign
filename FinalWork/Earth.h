#pragma once
#include "Collider.h"
#include "Sun.h"

class Earth : public Collider
{
public:
	Earth();
	~Earth();
	//override
	void Render();
	void Update();
	//�뾶
	double radius;
	double distSE = 100;

private:
	//���Ƶ�������+����������ͼ
	void DrawEarth();
	//��̫����ת
	void Move();
	//��ת
	void Rotate();
	float pub_seta = 0;
	float self_seta = 0;
};

