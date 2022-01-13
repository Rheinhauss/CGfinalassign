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

private:
	//���Ƶ�������+����������ͼ
	void DrawEarth();
	//��̫����ת
	void Move();
	//��ת
	void Rotate();
};

