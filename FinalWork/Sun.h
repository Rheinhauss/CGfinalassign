#pragma once
#include "Collider.h"

class Sun : public Collider
{
public:
	Sun();
	~Sun();
	//override
	void Render();
	//�뾶
	double radius;

private:
	//����̫������+����������ͼ
	void DrawSun();
	//��̫��λ�ô����ù�Դ
	void SetLight();
};

