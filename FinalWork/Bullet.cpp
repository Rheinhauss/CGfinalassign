#include "Bullet.h"
#include "PlayerMgr.h"
#include"TimeMgr.h"
#include "CVector.h"
#include"DestroyMgr.h"

//�������
double Bullet::shootRange = 100;

Bullet::Bullet()
{
	//���� �ӵ� �б�
	PlayerMgr::bullets.push_back(this);
	//��������
	this->name = "bullet";
	//���ñ�ǩ
	this->tag = "bullet";
	//�����ٶ�
	this->moveSpeed = 20;
	//���÷����,�����ж��Ƿ񳬹����
	this->point = PlayerMgr::Player->transform->position;
	//��ʼ���ӵ���Transform
	/*
		�����ɸ���,���ӵ���������ȷ��λ���뷽��
	*/
	this->transform->position = PlayerMgr::Player->transform->position;
	this->transform->rotation = PlayerMgr::Player->transform->rotation;
	/*
	���ݻ��Ƶ�ģ��,������ײ�з�Χ
	this->maxXYZ
	this->minXYZ
	*/
	this->maxXYZ = CVector(0.5, 0.5, 0.5);
	this->minXYZ = CVector(0, 0, 0);
	path = new Path;
	path->update_path(this->transform->position);
}

Bullet::~Bullet()
{
	//�� �ӵ� �б� ��ɾ��
	for (vector<Bullet*>::iterator it = PlayerMgr::bullets.begin(); it != PlayerMgr::bullets.end(); )
	{
		if (*it == this)
		{
			it = PlayerMgr::bullets.erase(it);
			break;
		}
		else
		{
			++it;
		}
	}
	delete this->path;
}


//�����ӵ�
void Bullet::DrawBullet() {
	//�����ӵ� + ����
	glPushMatrix();
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
}

//ÿ���ƶ�֮�����ж��Ƿ񳬹����
void Bullet::Move() {
	//��ȡ�ӵ���ǰ����λ���� forward
	CVector forward = this->transform->rotation.ToCMatrix().vecMul(CVector(0, 0, 1));//???
	//this->transform->position += forward * moveSpeed * TimeMgr::deltaTime
	this->transform->position = this->transform->position 
								+ forward * moveSpeed * TimeMgr::deltaTime;
	this->path->update_path(this->transform->position);
	//�ж��Ƿ񳬹����,����ɾ��
	if (Object::distance(*this, this->point) > shootRange)
		//delete this->path;
		DestroyMgr::add(this);
}

//override
void Bullet::Render() {
	//ʵ�����к���
	this->DrawBullet();
}
void Bullet::Update() {
	Move();
}
void Bullet::Collision(Collider *col) {
	if (col->tag == "enemy") {
		++PlayerMgr::hitEnemyNum;
	}
	if (col->tag != "Aircraft") {
		PlayerMgr::DestroyBullet(this);
	}
}