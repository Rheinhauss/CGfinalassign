#include "Bullet.h"
#include "PlayerMgr.h"
#include"TimeMgr.h"
#include "CVector.h"
#include"DestroyMgr.h"

//设置射程
double Bullet::shootRange = 100;
float Bullet::size = 0.1;
Bullet::Bullet(bool left)
{
	//加入 子弹 列表
	PlayerMgr::bullets.push_back(this);
	//设置名称
	this->name = "bullet";
	//设置标签
	this->tag = "bullet";
	//设置速度
	this->moveSpeed = 70;
	//设置发射点,用于判断是否超过射程
	
	if (left) {
		this->point = PlayerMgr::Player->transform->position - CVector(-0.2, 0.2, 0);
	}
	else {
		this->point = PlayerMgr::Player->transform->position - CVector(0.2, 0.2, 0);
	}
	//初始化子弹的Transform
	/*
		后续可更改,将子弹放置于正确的位置与方向
	*/
	this->transform->position = this->point;
	this->transform->rotation = PlayerMgr::Player->transform->rotation;
	/*
	根据绘制的模型,设置碰撞盒范围
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
	//从 子弹 列表 中删除
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


//绘制子弹
void Bullet::DrawBullet() {
	//绘制子弹 + 纹理
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3f(0.8, 0.3, 0.3);
	glutSolidSphere(Bullet::size, 10, 10);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

//每次移动之后需判断是否超过射程
void Bullet::Move() {
	//获取子弹的前方单位向量 forward
	CVector forward = this->transform->rotation.ToCMatrix().vecMul(CVector(0, 0, 1));//???
	//this->transform->position += forward * moveSpeed * TimeMgr::deltaTime
	this->transform->position = this->transform->position 
								+ forward * moveSpeed * TimeMgr::deltaTime;
	this->path->update_path(this->transform->position);
	//判断是否超过射程,是则删除
	if (Object::distance(*this, this->point) > shootRange)
		//delete this->path;
		DestroyMgr::add(this);
}

//override
void Bullet::Render() {
	//实现下列函数
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