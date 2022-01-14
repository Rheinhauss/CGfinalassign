#include "Aircraft.h"
#include "InputManager.h"
#include "TimeMgr.h"
#include "Bullet.h"
#include "PlayerMgr.h"
#include "glut.h"

Aircraft::Aircraft()
{
	//������������
	this->name = "Player";
	//���������ǩ
	this->tag = "Aircraft";
	//�����ƶ��ٶ� px/s
	this->moveSpeed = 10;
	//������ת�ٶ� ��/s
	this->rotSpeed = 3;
	//���������� s
	this->shootInterval = 0.1;
	//��ʼ����ʱ��
	this->timer = new Timer();
	this->timer->start();
	//��ʼΪ��ʻģʽ
	this->pattern = true;
	//��ʼ��Ŀ��л�,��Ϊ��
	this->target = nullptr;

	/*
	���ݻ��Ƶ�ģ��,������ײ�з�Χ
	this->maxXYZ
	this->minXYZ
	*/

}

Aircraft::~Aircraft()
{
	delete this->timer;
}

//���Ʒɻ�
void Aircraft::DrawAircraft() {
	//����+������ͼ
	//todo
	const double _size = 5;
	glPushMatrix();
	glTranslatef(-_size / 2, -_size / 2, -_size / 2);
	glutSolidCube(_size);
	glPopMatrix();
	return;
}

//��ʻģʽ�ƶ�,ÿ���ƶ�֮�����ж��Ƿ񴥼��߽�,����(0,0,0)�����Ƿ�>=2500,����pos = -pos
void Aircraft::Move() {
	if (InputManager::KEY_UP) {
		//��ȡ��ǰ�ɻ���ǰ����λ���� forward
		//�ɻ���Transform.position += forward * moveSpeed * TimeMgr::deltaTime
		this->transform->position = this->transform->position + _forward() * moveSpeed * TimeMgr::deltaTime;
		//�ж��Ƿ񴥼��߽�,����(0,0,0)�����Ƿ�>=2500,����pos = -pos
		if (Object::distance(*this, CVector(0, 0, 0)) >= 2500)
			this->transform->position = -this->transform->position;
	}
	if (InputManager::KEY_DOWN) {
		//��ȡ��ǰ�ɻ���ǰ����λ���� forward
		//�ɻ���Transform.position += -1 * forward * moveSpeed * TimeMgr::deltaTime
		this->transform->position = this->transform->position - _forward() * moveSpeed * TimeMgr::deltaTime;
		//�ж��Ƿ񴥼��߽�,����(0,0,0)�����Ƿ�>=2500,����pos = -pos
		if (Object::distance(*this, CVector(0, 0, 0)) >= 2500)
			this->transform->position = -this->transform->position;
	}
}

//��ʻģʽ��ת
void Aircraft::Rotate() {
	if (InputManager::KEY_LEFT) {
		//��ȡ�ɻ����Ϸ���λ���� up
		//���·ɻ���Transform����Ԫ��,	�ڵ�ǰ��ת���Ʒɻ���up������ �� ��ת rotSpeed * TimeMgr::deltaTime
		CMatrix m;
		m.SetRotate(-rotSpeed * TimeMgr::deltaTime, _up());
		this->transform->rotation = m.ToCQuaternion() * this->transform->rotation;
	}
	if (InputManager::KEY_RIGHT) {
		//��ȡ�ɻ����Ϸ���λ���� up
		//���·ɻ���Transform����Ԫ��,	�ڵ�ǰ��ת���Ʒɻ���up������ �� ��ת rotSpeed * TimeMgr::deltaTime
		CMatrix m;
		m.SetRotate(rotSpeed * TimeMgr::deltaTime, _up());
		this->transform->rotation = m.ToCQuaternion() * this->transform->rotation;
	}
}

//���,���¿ո�/�ϵ��ӽ�ģʽ����
void Aircraft::Shoot() {
	//��ʱ��ʱ��<��ȴ���,���ܷ����ӵ�
	if (this->timer->time < this->shootInterval) {
		return;
	}
	//��ʻģʽ
	if (this->pattern == true && InputManager::KEY_SPACE) {
		//�����ӵ�
  		new Bullet();
		this->timer->time = 0;
		return;
	}
	//�ϵ��ӽ�ģʽ
	else if(this->pattern == false){
		//�����ӵ�
		new Bullet();
		this->timer->time = 0;
		return;
	}
}

//�ϵ�ģʽ׷���л�
void Aircraft::PursueTarget() {
	//�ж�Ŀ���Ƿ�Ϊ��,Ϊ����ͣ��,���κβ���
	if (this->target == nullptr) {//delete֮��
		return;
	}
	//��Ϊ��

	//postion��rotation��target�ӽ�
	auto vtmp = target->transform->position - this->transform->position;
	/*
	double _phi = acos(vtmp.y) / PI * 180.0, _seta = asin(vtmp.x / sin(_phi)) / PI * 180.0;
	CQuaternion rnow = this->transform->rotation,
				rend = CEuler(_seta, _phi, 0.0).ToQuaternion();
	rnow.Slerp(rend,0.2)
	*/
	//ÿ֡�仯	moveSpeed * TimeMgr::deltaTime	rotSpeed * TimeMgr::deltaTime
	double _ran = atan2(vtmp.x, vtmp.z)/PI*180.0;
	double _ht1 = this->transform->rotation.ToCEuler().h,
		   _ht2 = _ht1 + rotSpeed * TimeMgr::deltaTime;
	this->transform->position = this->transform->position + _forward() * moveSpeed * TimeMgr::deltaTime;
	auto t = this->transform->rotation.ToCEuler();
	if ((_ht1 < _ran && _ran < _ht2) ||
		(_ht2 < _ran && _ran < _ht1) ||
		(_ht1 < _ran + 360.0 && _ran + 360.0 < _ht2) ||
		(_ht2 < _ran + 360.0 && _ran + 360.0 < _ht1)) {
		t.h = fmod(_ran,360.0);
	}
	else {
		t.h = fmod(_ht2, 360.0);
	}
	if (t.h > 180)t.h = t.h - 360.0;
	this->transform->rotation = t.ToQuaternion();

	//�����ӵ�	����this->Shoot()
	this->Shoot();
}

//override
void Aircraft::Render() {
	//ʵ�����к���
	this->DrawAircraft();
}
void Aircraft::Update() {
	//��ʻģʽ
	if (this->pattern == true) {
		this->Move();
		this->Rotate();
		this->Shoot();
	}
	//�ϵ��ӽ�ģʽ
	else {
		this->PursueTarget();
	}
}
void Aircraft::Collision(Collider *col) {
	if (col->tag == "sun" || col->tag == "earth") {
		//Game Over
		return;
	}
	else if (col->tag == "meteorite") {
		++PlayerMgr::colMeteNum;
	}
	else if (col->tag == "enemy") {
		++PlayerMgr::colEnemyNum;
	}
}
