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
	//半径
	double radius;
	double distSE = 100;

private:
	//绘制地球球体+贴上纹理贴图
	void DrawEarth();
	//绕太阳旋转
	void Move();
	//自转
	void Rotate();
	float pub_seta = 0;
	float self_seta = 0;
};

