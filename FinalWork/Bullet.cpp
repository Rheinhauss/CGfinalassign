#include "Bullet.h"
#include "PlayerMgr.h"

//设置射程
double Bullet::shootRange = 240;

Bullet::Bullet()
{
	//加入 子弹 列表
	PlayerMgr::bullets.push_back(this);
	//设置名称
	this->name = "bullet";
	//设置标签
	this->tag = "bullet";
	//设置速度
	this->moveSpeed = 40;
	//设置发射点,用于判断是否超过射程
	this->point = PlayerMgr::Player->transform->position;
	//初始化子弹的Transform
	/*
		后续可更改,将子弹放置于正确的位置与方向
	*/
	this->transform->position = PlayerMgr::Player->transform->position;
	this->transform->rotation = PlayerMgr::Player->transform->rotation;
	/*
	根据绘制的模型,设置碰撞盒范围
	this->maxXYZ
	this->minXYZ
	*/
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
}


//绘制子弹
void Bullet::DrawBullet() {
	//绘制子弹 + 纹理
}

//每次移动之后需判断是否超过射程
void Bullet::Move() {
	//获取子弹的前方单位向量 forward

	//this->transform->position += forward * moveSpeed * TimeMgr::deltaTime

	//判断是否超过射程,是则删除

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
	if (col->tag == "enemy") {
		++PlayerMgr::hitEnemyNum;
	}
	if (col->tag != "Aircraft") {
		PlayerMgr::DestroyBullet(this);
	}
}