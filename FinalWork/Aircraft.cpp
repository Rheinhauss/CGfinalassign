#include "Aircraft.h"
#include "InputManager.h"
#include "TimeMgr.h"
#include "Bullet.h"
#include "PlayerMgr.h"
#include "glut.h"

Aircraft::Aircraft()
{
	//设置物体名称
	this->name = "Player";
	//设置物体标签
	this->tag = "Aircraft";
	//设置移动速度 px/s
	this->moveSpeed = 10;
	//设置旋转速度 度/s
	this->rotSpeed = 3;
	//设置射击间隔 s
	this->shootInterval = 0.1;
	//初始化计时器
	this->timer = new Timer();
	this->timer->start();
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
	//todo
	const double _size = 5;
	glPushMatrix();
	glTranslatef(-_size / 2, -_size / 2, -_size / 2);
	glutSolidCube(_size);
	glPopMatrix();
	return;
}

//驾驶模式移动,每次移动之后需判断是否触及边界,即到(0,0,0)距离是否>=2500,是则pos = -pos
void Aircraft::Move() {
	if (InputManager::KEY_UP) {
		//获取当前飞机的前方单位向量 forward
		//飞机的Transform.position += forward * moveSpeed * TimeMgr::deltaTime
		this->transform->position = this->transform->position + _forward() * moveSpeed * TimeMgr::deltaTime;
		//判断是否触及边界,即到(0,0,0)距离是否>=2500,是则pos = -pos
		if (Object::distance(*this, CVector(0, 0, 0)) >= 2500)
			this->transform->position = -this->transform->position;
	}
	if (InputManager::KEY_DOWN) {
		//获取当前飞机的前方单位向量 forward
		//飞机的Transform.position += -1 * forward * moveSpeed * TimeMgr::deltaTime
		this->transform->position = this->transform->position - _forward() * moveSpeed * TimeMgr::deltaTime;
		//判断是否触及边界,即到(0,0,0)距离是否>=2500,是则pos = -pos
		if (Object::distance(*this, CVector(0, 0, 0)) >= 2500)
			this->transform->position = -this->transform->position;
	}
}

//驾驶模式旋转
void Aircraft::Rotate() {
	if (InputManager::KEY_LEFT) {
		//获取飞机的上方单位向量 up
		//更新飞机的Transform的四元数,	在当前旋转下绕飞机的up向量向 左 旋转 rotSpeed * TimeMgr::deltaTime
		CMatrix m;
		m.SetRotate(-rotSpeed * TimeMgr::deltaTime, _up());
		this->transform->rotation = m.ToCQuaternion() * this->transform->rotation;
	}
	if (InputManager::KEY_RIGHT) {
		//获取飞机的上方单位向量 up
		//更新飞机的Transform的四元数,	在当前旋转下绕飞机的up向量向 右 旋转 rotSpeed * TimeMgr::deltaTime
		CMatrix m;
		m.SetRotate(rotSpeed * TimeMgr::deltaTime, _up());
		this->transform->rotation = m.ToCQuaternion() * this->transform->rotation;
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
  		new Bullet();
		this->timer->time = 0;
		return;
	}
	//上帝视角模式
	else if(this->pattern == false){
		//发射子弹
		new Bullet();
		this->timer->time = 0;
		return;
	}
}

//上帝模式追击敌机
void Aircraft::PursueTarget() {
	//判断目标是否为空,为空则停滞,无任何操作
	if (this->target == nullptr) {//delete之后？
		return;
	}
	//不为空

	//postion和rotation向target接近
	auto vtmp = target->transform->position - this->transform->position;
	/*
	double _phi = acos(vtmp.y) / PI * 180.0, _seta = asin(vtmp.x / sin(_phi)) / PI * 180.0;
	CQuaternion rnow = this->transform->rotation,
				rend = CEuler(_seta, _phi, 0.0).ToQuaternion();
	rnow.Slerp(rend,0.2)
	*/
	//每帧变化	moveSpeed * TimeMgr::deltaTime	rotSpeed * TimeMgr::deltaTime
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

	//发射子弹	调用this->Shoot()
	this->Shoot();
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
