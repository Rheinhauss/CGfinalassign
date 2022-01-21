#include "Object.h"

//物体列表,所有继承此类的物体都需要加入
vector<Object*> Object::objs;

Object::Object()
{
	this->name = "";
	this->tag = "";
	this->transform = new Transform();
	Object::objs.push_back(this);
}

Object::~Object()
{
	//从物体列表中删除
	for (vector<Object*>::iterator it = Object::objs.begin(); it != Object::objs.end(); )
	{
		if (*it == this)
		{
			it = Object::objs.erase(it);
			break;
		}
		else
		{
			++it;
		}
	}
	delete this->transform;
	//删除附加组件
	for (vector<Object*>::iterator it = this->components.begin(); it != this->components.end(); ++it)
	{
		it = this->components.erase(it);
		delete (*it);
	}
}

//需要绘制的内容,实现即可,会自动根据Transform绘制
void Object::Render() {
	return;
}
//每帧需要执行的内容,实现此函数即可,会自动每帧调用
void Object::Update() {
	return;
}
CVector Object::_up() {
	return this->transform->rotation.ToCMatrix().vecMul(CVector(0, 1, 0));
}
CVector Object::_left() {
	return this->transform->rotation.ToCMatrix().vecMul(CVector(1, 0, 0));
}
CVector Object::_forward() {
	return this->transform->rotation.ToCMatrix().vecMul(CVector(0, 0, 1));
}

float Object::distance(Object& a, Object& b) {
	auto tmp = a.transform->position - b.transform->position;
	return sqrt(tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z);
}
float Object::distance(Object& a, CVector& b) {
	auto tmp = a.transform->position - b;
	return sqrt(tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z);
}