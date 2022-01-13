#include "Meteorite.h"
#include "SceneMgr.h"
#include "MeteMgr.h"

Meteorite::Meteorite()
{
	this->name = "meteorite";
	this->tag = "meteorite";
	this->timer = new Timer();
	//始终在z=0平面内
	this->direction = CVector((float)SceneMgr::random(), (float)SceneMgr::random(), 0);
	/*
	根据绘制的模型,设置碰撞盒范围
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

//绘制陨石
void Meteorite::DrawMeteorite() {

}

//移动, 每隔interval更改一次随机移动方向, 如果到达边界, 则移动方向变为相反方向并从0开始计时
void Meteorite::Move() {
	//this->Transform->position更改位置 速度*forward*deltaTime

	//判断计时器是否>=间隔
	//是,则更改方向,旋转敌机朝向对应方向???(酌情附加)

	//判断是否到达边界 圆环带 MeteRange* mr
	//如果到达边界, 则移动方向变为相反方向并从0开始计时

	//是否超出边界,是则消失,在边界处重新生成
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
		//消失,出现在活动范围边界处
	}
	else if (col->tag == "meteorite") {
		//向相反方向运动,从0开始计时
	}
}