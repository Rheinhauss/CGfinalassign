#include "Object.h"

//�����б�,���м̳д�������嶼��Ҫ����
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
	//�������б���ɾ��
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
	//ɾ���������
	for (vector<Object*>::iterator it = this->components.begin(); it != this->components.end(); ++it)
	{
		it = this->components.erase(it);
		delete (*it);
	}
}

//��Ҫ���Ƶ�����,ʵ�ּ���,���Զ�����Transform����
void Object::Render() {
	return;
}
//ÿ֡��Ҫִ�е�����,ʵ�ִ˺�������,���Զ�ÿ֡����
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