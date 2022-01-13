#include "Object.h"

//�����б�,���м̳д�������嶼��Ҫ����
vector<Object*> Object::objs;

Object::Object()
{
	this->name = "";
	this->tag = "";
	this->transform = new Transfrom();
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
