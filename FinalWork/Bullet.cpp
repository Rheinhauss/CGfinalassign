#include "Bullet.h"
#include "PlayerMgr.h"

//�������
double Bullet::shootRange = 240;

Bullet::Bullet()
{
	//���� �ӵ� �б�
	PlayerMgr::bullets.push_back(this);
	//��������
	this->name = "bullet";
	//���ñ�ǩ
	this->tag = "bullet";
	//�����ٶ�
	this->moveSpeed = 40;
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
}


//�����ӵ�
void Bullet::DrawBullet() {
	//�����ӵ� + ����
}

//ÿ���ƶ�֮�����ж��Ƿ񳬹����
void Bullet::Move() {
	//��ȡ�ӵ���ǰ����λ���� forward

	//this->transform->position += forward * moveSpeed * TimeMgr::deltaTime

	//�ж��Ƿ񳬹����,����ɾ��

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