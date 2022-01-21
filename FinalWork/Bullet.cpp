#include "Bullet.h"
#include "PlayerMgr.h"
#include"TimeMgr.h"
#include "CVector.h"
#include"DestroyMgr.h"

//�������
double Bullet::shootRange = 100;
float Bullet::size = 0.1;
Bullet::Bullet(bool left)
{
	//���� �ӵ� �б�
	PlayerMgr::bullets.push_back(this);
	//��������
	this->name = "bullet";
	//���ñ�ǩ
	this->tag = "bullet";
	//�����ٶ�
	this->moveSpeed = 70;
	//���÷����,�����ж��Ƿ񳬹����
	
	if (left) {
		this->point = PlayerMgr::Player->transform->position - CVector(-0.2, 0.2, 0);
	}
	else {
		this->point = PlayerMgr::Player->transform->position - CVector(0.2, 0.2, 0);
	}
	//��ʼ���ӵ���Transform
	/*
		�����ɸ���,���ӵ���������ȷ��λ���뷽��
	*/
	this->transform->position = this->point;
	this->transform->rotation = PlayerMgr::Player->transform->rotation;
	/*
	���ݻ��Ƶ�ģ��,������ײ�з�Χ
	this->maxXYZ
	this->minXYZ
	*/
	//const float t = 0.25;
	const float t = Bullet::size;
	this->maxXYZ = CVector(t, t, t);
	this->minXYZ = CVector(-t, -t, -t);
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
	glDisable(GL_LIGHTING);
	glColor3f(0.8, 0.3, 0.3);
	glutSolidSphere(Bullet::size, 10, 10);
	glEnable(GL_LIGHTING);
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
	cout << "1";
	if (col->tag == "enemy") {
		++PlayerMgr::hitEnemyNum;
		cout << "!" << endl;
	}
	if (col->tag == "meteorite") {
		cout << "?" << endl;
	}
   	if (col->tag != "Aircraft") {
		PlayerMgr::DestroyBullet(this);
	}
}