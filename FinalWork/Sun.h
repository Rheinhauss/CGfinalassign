#pragma once
#include "Collider.h"
#include "CVector.h"

class Sun : public Collider
{
public:
	Sun();
	~Sun();
	//override
	void Render();
	//�뾶
	double radius;
	static CVector pos;

private:
	//����̫������+����������ͼ
	void DrawSun();
	//��̫��λ�ô����ù�Դ
	void SetLight();
};

