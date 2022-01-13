#include "Aircraft.h"
#include "InputManager.h"
#include "Bullet.h"
#include "PlayerMgr.h"

Aircraft::Aircraft()
{
	//������������
	this->name = "Player";
	//���������ǩ
	this->tag = "Aircraft";
	//�����ƶ��ٶ� px/s
	this->moveSpeed = 10;
	//������ת�ٶ� ��/s
	this->rotSpeed = 30;
	//���������� s
	this->shootInterval = 0.1;
	//��ʼ����ʱ��
	this->timer = new Timer();
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
	return;
}

//��ʻģʽ�ƶ�,ÿ���ƶ�֮�����ж��Ƿ񴥼��߽�,����(0,0,0)�����Ƿ�>=2500,����pos = -pos
void Aircraft::Move() {
	if (InputManager::KEY_UP) {
		//��ȡ��ǰ�ɻ���ǰ����λ���� forward

		//�ɻ���Transform.position += forward * moveSpeed * TimeMgr::deltaTime

		//�ж��Ƿ񴥼��߽�,����(0,0,0)�����Ƿ�>=2500,����pos = -pos
	}
	if (InputManager::KEY_DOWN) {
		//��ȡ��ǰ�ɻ���ǰ����λ���� forward

		//�ɻ���Transform.position += -1 * forward * moveSpeed * TimeMgr::deltaTime

		//�ж��Ƿ񴥼��߽�,����(0,0,0)�����Ƿ�>=2500,����pos = -pos
	}
}

//��ʻģʽ��ת
void Aircraft::Rotate() {
	if (InputManager::KEY_LEFT) {
		//��ȡ�ɻ����Ϸ���λ���� up
		//���·ɻ���Transform����Ԫ��,	�ڵ�ǰ��ת���Ʒɻ���up������ �� ��ת rotSpeed * TimeMgr::deltaTime
	}
	if (InputManager::KEY_RIGHT) {
		//��ȡ�ɻ����Ϸ���λ���� up
		//���·ɻ���Transform����Ԫ��,	�ڵ�ǰ��ת���Ʒɻ���up������ �� ��ת rotSpeed * TimeMgr::deltaTime
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
		return;
	}
	//�ϵ��ӽ�ģʽ
	else if(this->pattern == false){
		//�����ӵ�
		return;
	}
}

//�ϵ�ģʽ׷���л�
void Aircraft::PursueTarget() {
	//�ж�Ŀ���Ƿ�Ϊ��,Ϊ����ͣ��,���κβ���
	if (this->target == nullptr) {
		return;
	}
	//��Ϊ��

	//postion��rotation��target�ӽ�
	//ÿ֡�仯	moveSpeed * TimeMgr::deltaTime	rotSpeed * TimeMgr::deltaTime

	//�����ӵ�	����this->Shoot()
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
