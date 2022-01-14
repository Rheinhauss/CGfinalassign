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

	//物体名称
	string name;
	//标签
	string tag;
	//物体的Transform组件
	Transfrom *transform;
	//需要绘制的内容,实现即可,会自动根据Transform绘制
	virtual void Render();
	//每帧需要执行的内容,实现此函数即可,会自动每帧调用
	virtual void Update();
	//对象拥有的组件均需加入,不包括Collider,Transform
	vector<Object*> components;

	//物体列表,所有继承此类的物体都需要加入
	static vector<Object*> objs;
	static float distance(Object& a, Object& b);
	static float distance(Object& a, CVector& b);

private:
protected:
	CVector _up();
	CVector _left();
	CVector _forward();

};

