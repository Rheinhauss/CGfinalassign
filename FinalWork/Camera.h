#pragma once
#include "Object.h"

class Camera : public Object
{
public:
	Camera();
	~Camera();

	//override
	void Update();
	bool isTrans;//�Ƿ��ڹ���̬
	float moveSpeed;
	float rotSpeed;

private:


	//������ƶ�
	void Move();
	//�������ת
	void Rotate();
	//����ģʽ
	void ChangePattern();

};

