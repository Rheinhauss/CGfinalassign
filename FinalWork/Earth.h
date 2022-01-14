#pragma once
#include "Collider.h"

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
	double distSE = 20;

private:
	//���Ƶ�������+����������ͼ
	void DrawEarth();
	//��̫����ת
	void Move();
	//��ת
	void Rotate();
};

