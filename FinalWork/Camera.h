#pragma once
#include "Object.h"

class Camera : public Object
{
public:
	Camera();
	~Camera();

	//override
	void Update();
	bool isTrans;//是否处于过渡态
	float moveSpeed;
	float rotSpeed;

private:


	//摄像机移动
	void Move();
	//摄像机旋转
	void Rotate();
	//更改模式
	void ChangePattern();

};

