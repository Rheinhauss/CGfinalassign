#include "Meteorite.h"
#include "SceneMgr.h"
#include "MeteMgr.h"

Meteorite::Meteorite()
{
	this->name = "meteorite";
	this->tag = "meteorite";
	this->timer = new Timer();
	//ʼ����z=0ƽ����
	this->direction = CVector((float)SceneMgr::random(), (float)SceneMgr::random(), 0);
	/*
	���ݻ��Ƶ�ģ��,������ײ�з�Χ
	this->maxXYZ
	this->minXYZ
	*/
}

Meteorite::~Meteorite()
{
	for (vector<Meteorite*>::iterator it = MeteMgr::Metes.begin(); it != MeteMgr::Metes.end(); )
	{
		if (*it == this)
		{
			it = MeteMgr::Metes.erase(it);
			break;
		}
		else
		{
			++it;
		}
	}
	delete this->timer;
}

//������ʯ
void Meteorite::DrawMeteorite() {

}

//�ƶ�, ÿ��interval����һ������ƶ�����, �������߽�, ���ƶ������Ϊ�෴���򲢴�0��ʼ��ʱ
void Meteorite::Move() {
	//this->Transform->position����λ�� �ٶ�*forward*deltaTime

	//�жϼ�ʱ���Ƿ�>=���
	//��,����ķ���,��ת�л������Ӧ����???(���鸽��)

	//�ж��Ƿ񵽴�߽� Բ���� MeteRange* mr
	//�������߽�, ���ƶ������Ϊ�෴���򲢴�0��ʼ��ʱ

	//�Ƿ񳬳��߽�,������ʧ,�ڱ߽紦��������
}

//override
void Meteorite::Render() {
	this->DrawMeteorite();
}
void Meteorite::Update() {
	this->Move();
}
void Meteorite::Collision(Collider *col) {
	if (col->tag == "Aircraft") {
		//��ʧ,�����ڻ��Χ�߽紦
	}
	else if (col->tag == "meteorite") {
		//���෴�����˶�,��0��ʼ��ʱ
	}
}