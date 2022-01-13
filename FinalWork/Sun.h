#pragma once
#include "Collider.h"

class Sun : public Collider
{
public:
	Sun();
	~Sun();
	//override
	void Render();
	//半径
	double radius;

private:
	//绘制太阳球体+贴上纹理贴图
	void DrawSun();
	//在太阳位置处设置光源
	void SetLight();
};

