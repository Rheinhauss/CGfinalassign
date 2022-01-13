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
	CVector _up();
	CVector _left();
	CVector _forward();

	bool is_allow_changing_pattern = true;

};

