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
	//半径
	double radius;

private:
	//绘制地球球体+贴上纹理贴图
	void DrawEarth();
	//绕太阳旋转
	void Move();
	//自转
	void Rotate();
};

