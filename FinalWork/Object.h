#pragma once
#include <iostream>
using namespace std;
#include "Transform.h"
class Transform;
#include <vector>

class Object
{
public:
	Object();
	virtual ~Object();

	//��������
	string name;
	//��ǩ
	string tag;
	//�����Transform���
	Transfrom *transform;
	//��Ҫ���Ƶ�����,ʵ�ּ���,���Զ�����Transform����
	virtual void Render();
	//ÿ֡��Ҫִ�е�����,ʵ�ִ˺�������,���Զ�ÿ֡����
	virtual void Update();
	//����ӵ�е�����������,������Collider,Transform
	vector<Object*> components;

	//�����б�,���м̳д�������嶼��Ҫ����
	static vector<Object*> objs;
	static float distance(Object& a, Object& b);
	static float distance(Object& a, CVector& b);

private:
protected:
	CVector _up();
	CVector _left();
	CVector _forward();

};

