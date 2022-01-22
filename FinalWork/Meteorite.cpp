#include "Meteorite.h"
#include "SceneMgr.h"
#include "MeteMgr.h"
#include "TimeMgr.h"
#include "DestroyMgr.h"
#include "TextureMgr.h"
#include "Sphere.h"

Meteorite::Meteorite(MeteRange*_mr):mr(_mr)
{
	this->name = "meteorite";
	this->tag = "meteorite";
	this->timer = new Timer();
	timer->start();
	//ʼ����y=0ƽ����
	this->direction = CVector((float)SceneMgr::random(true), 0, (float)SceneMgr::random(true));
	this->moveSpeed = 3;
	MeteMgr::Metes.push_back(this);
	float _r = mr->minRange + SceneMgr::random(false) * (mr->maxRange - mr->minRange),
		_s = SceneMgr::random(false) * 360.0;
	this->transform->position = CVector(_r * cos(_s / 180.0 * PI), 0, _r * sin(_s / 180.0 * PI));
	/*
	���ݻ��Ƶ�ģ��,������ײ�з�Χ
	this->maxXYZ
	this->minXYZ
	*/
	const float t = 1.5;
	this->maxXYZ = CVector(t, t, t);
	this->minXYZ = CVector(-t, -t, -t);
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
	glPushMatrix();
	
	gluQuadricTexture(TextureMgr::e_tex, GLU_TRUE);
	//glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TextureMgr::textures[2]);
	gluSphere(TextureMgr::e_tex, 1.5, 30, 30);
	//cout << gluErrorString(glGetError()) << endl;
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);
	gluQuadricTexture(TextureMgr::e_tex, GLU_FALSE);
	//glutSolidSphere(this->radius, 100, 100);
	//Sphere::Draw(this->radius, 100, 100, TextureMgr::textures[0]);
	glPopMatrix();
}

//�ƶ�, ÿ��interval����һ������ƶ�����, �������߽�, ���ƶ������Ϊ�෴���򲢴�0��ʼ��ʱ
void Meteorite::Move() {
	if (this->timer->time >= interval) {
		this->direction = CVector((float)SceneMgr::random(true), 0, (float)SceneMgr::random(true));
		timer->start();
	}

	//this->Transform->position����λ�� �ٶ�*forward*deltaTime
	this->transform->position = this->transform->position + moveSpeed * direction * TimeMgr::deltaTime;

	//�ж��Ƿ񵽴�߽� Բ���� MeteRange* mr
	//�������߽�, ��ɾ��
	double _x = this->transform->position.x - Sun::pos.x,
		   _z = this->transform->position.z - Sun::pos.z,
		   _r = sqrt(_x * _x + _z * _z);
	if (mr->minRange >= _r || mr->maxRange <= _r) {
		DestroyMgr::add(this);
		MeteMgr::add();
	}

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