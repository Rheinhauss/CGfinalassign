#include "Aircraft.h"
#include "InputManager.h"
#include "Bullet.h"
#include "PlayerMgr.h"

Aircraft::Aircraft()
{
	//设置物体名称
	this->name = "Player";
	//设置物体标签
	this->tag = "Aircraft";
	//设置移动速度 px/s
	this->moveSpeed = 10;
	//设置旋转速度 度/s
	this->rotSpeed = 30;
	//设置射击间隔 s
	this->shootInterval = 0.1;
	//初始化计时器
	this->timer = new Timer();
	//初始为驾驶模式
	this->pattern = true;
	//初始化目标敌机,置为空
	this->target = nullptr;

	/*
	根据绘制的模型,设置碰撞盒范围
	this->maxXYZ
	this->minXYZ
	*/

}

Aircraft::~Aircraft()
{
	delete this->timer;
}

//绘制飞机
void Aircraft::DrawAircraft() {
	//绘制+纹理贴图
	return;
}

//驾驶模式移动,每次移动之后需判断是否触及边界,即到(0,0,0)距离是否>=2500,是则pos = -pos
void Aircraft::Move() {
	if (InputManager::KEY_UP) {
		//获取当前飞机的前方单位向量 forward

		//飞机的Transform.position += forward * moveSpeed * TimeMgr::deltaTime

		//判断是否触及边界,即到(0,0,0)距离是否>=2500,是则pos = -pos
	}
	if (InputManager::KEY_DOWN) {
		//获取当前飞机的前方单位向量 forward

		//飞机的Transform.position += -1 * forward * moveSpeed * TimeMgr::deltaTime

		//判断是否触及边界,即到(0,0,0)距离是否>=2500,是则pos = -pos
	}
}

//驾驶模式旋转
void Aircraft::Rotate() {
	if (InputManager::KEY_LEFT) {
		//获取飞机的上方单位向量 up
		//更新飞机的Transform的四元数,	在当前旋转下绕飞机的up向量向 左 旋转 rotSpeed * TimeMgr::deltaTime
	}
	if (InputManager::KEY_RIGHT) {
		//获取飞机的上方单位向量 up
		//更新飞机的Transform的四元数,	在当前旋转下绕飞机的up向量向 右 旋转 rotSpeed * TimeMgr::deltaTime
	}
}

//射击,按下空格/上帝视角模式调用
void Aircraft::Shoot() {
	//计时器时间<冷却间隔,不能发射子弹
	if (this->timer->time < this->shootInterval) {
		return;
	}
	//驾驶模式
	if (this->pattern == true && InputManager::KEY_SPACE) {
		//发射子弹
		return;
	}
	//上帝视角模式
	else if(this->pattern == false){
		//发射子弹
		return;
	}
}

//上帝模式追击敌机
void Aircraft::PursueTarget() {
	//判断目标是否为空,为空则停滞,无任何操作
	if (this->target == nullptr) {
		return;
	}
	//不为空

	//postion和rotation向target接近
	//每帧变化	moveSpeed * TimeMgr::deltaTime	rotSpeed * TimeMgr::deltaTime

	//发射子弹	调用this->Shoot()
}

//override
void Aircraft::Render() {
	//实现下列函数
	this->DrawAircraft();
}
void Aircraft::Update() {
	//驾驶模式
	if (this->pattern == true) {
		this->Move();
		this->Rotate();
		this->Shoot();
	}
	//上帝视角模式
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
