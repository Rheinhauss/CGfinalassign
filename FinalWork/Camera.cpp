#include "Camera.h"
#include "InputManager.h"
#include "TimeMgr.h"
#include "PlayerMgr.h"

//驾驶模式下Transform变换为相对飞机的变换
//上帝视角模式下为绝对变换

Camera::Camera()
{
	this->name = "Camera";
	this->tag = "Camera";
	this->moveSpeed = 10;
	this->rotSpeed = 10;
	this->transform->rotation = CEuler(180, 0, 0).ToQuaternion();
}

Camera::~Camera()
{
}

//摄像机移动
void Camera::Move() {
	//???
	if (InputManager::KEY_W) {
		//获取摄像机的up单位向量
		//当前位置  加上 up * moveSpeed * TimeMgr::deltaTime
		this->transform->position = this->transform->position + _up() * moveSpeed * TimeMgr::deltaTime;
	}
	if (InputManager::KEY_S) {
		//获取摄像机的up单位向量
		//当前位置  减去 up * moveSpeed * TimeMgr::deltaTime
		this->transform->position = this->transform->position - _up() * moveSpeed * TimeMgr::deltaTime;
	}
	if (InputManager::KEY_A) {
		//获取摄像机的left单位向量
		//当前位置  加上 left * moveSpeed * TimeMgr::deltaTime
		this->transform->position = this->transform->position + _left() * moveSpeed * TimeMgr::deltaTime;
	}
	if (InputManager::KEY_D) {
		//获取摄像机的left单位向量
		//当前位置  减去 left * moveSpeed * TimeMgr::deltaTime
		this->transform->position = this->transform->position - _left() * moveSpeed * TimeMgr::deltaTime;
	}
	if (InputManager::KEY_Q) {
		//获取摄像机的forward单位向量
		//当前位置  加上 forward * moveSpeed * TimeMgr::deltaTime
		this->transform->position = this->transform->position + _forward() * moveSpeed * TimeMgr::deltaTime;
	}
	if (InputManager::KEY_E) {
		//获取摄像机的forward单位向量
		//当前位置  减去 forward * moveSpeed * TimeMgr::deltaTime
		this->transform->position = this->transform->position - _forward() * moveSpeed * TimeMgr::deltaTime;
	}
}
//摄像机旋转
void Camera::Rotate() {
	//??? 左乘吗?以及顺逆时针是否写对
	if (InputManager::KEY_J) {
		//获取摄像机的up单位向量
		//绕 up 轴 顺时针旋转 rotSpeed * TimeMgr::deltaTime
		CMatrix _m;
		_m.SetRotate(-rotSpeed * TimeMgr::deltaTime, _up());
		this->transform->rotation = _m.ToCQuaternion() * this->transform->rotation;
	}
	if (InputManager::KEY_L) {
		//获取摄像机的up单位向量
		//绕 up 轴 逆时针旋转 rotSpeed * TimeMgr::deltaTime
		CMatrix _m;
		_m.SetRotate(rotSpeed * TimeMgr::deltaTime, _up());
		this->transform->rotation = _m.ToCQuaternion() * this->transform->rotation;
	}
	if (InputManager::KEY_K) {
		//获取摄像机的left单位向量
		//绕 left 轴 顺时针旋转 rotSpeed * TimeMgr::deltaTime
		CMatrix _m;
		_m.SetRotate(-rotSpeed * TimeMgr::deltaTime, _left());
		this->transform->rotation = _m.ToCQuaternion() * this->transform->rotation;
	}
	if (InputManager::KEY_I) {
		//获取摄像机的left单位向量
		//绕 left 轴 逆时针旋转 rotSpeed * TimeMgr::deltaTime
		CMatrix _m;
		_m.SetRotate(rotSpeed * TimeMgr::deltaTime, _left());
		this->transform->rotation = _m.ToCQuaternion() * this->transform->rotation;
	}
	if (InputManager::KEY_U) {
		//获取摄像机的forward单位向量
		//绕 forward 轴 逆时针旋转 rotSpeed * TimeMgr::deltaTime
		CMatrix _m;
		_m.SetRotate(-rotSpeed * TimeMgr::deltaTime, _forward());
		this->transform->rotation = _m.ToCQuaternion() * this->transform->rotation;
	}
	if (InputManager::KEY_O) {
		//获取摄像机的forward单位向量
		//绕 forward 轴 顺时针旋转 rotSpeed * TimeMgr::deltaTime
		CMatrix _m;
		_m.SetRotate(rotSpeed * TimeMgr::deltaTime, _forward());
		this->transform->rotation = _m.ToCQuaternion() * this->transform->rotation;
	}
}
//更改模式
void Camera::ChangePattern() {
	if (InputManager::KEY_X) {
		//过渡阶段 不可更改飞机模式
		//非过渡阶段 可更改飞机的模式
		if (isTrans == false && is_allow_changing_pattern) {
			is_allow_changing_pattern = false;
			isTrans = true;
			//todo_ssh 视角切换平滑过渡
			//如果是 驾驶模式 ->上帝视角模式,将摄像机Transform设置为绝对变换
			//置过渡态为true
			if (PlayerMgr::Player->pattern == true) {
				transform->rotation = PlayerMgr::Player->transform->rotation * transform->rotation;
				transform->position = PlayerMgr::Player->transform->position + transform->position;
			}
		}
	}
	if (isTrans == false) {
		return;
	}
	//如果为过渡阶段,此阶段摄像机设置均为非绑定态下设置
	//此时置 TimeMgr::scaleTime为0，暂停游戏
	//处于更改模式的平滑插值期间,不能更改模式
	//计算一次目标位置和旋转即可
	//插值到目标点
	static float C_target = 0.5f;
	//过渡到驾驶模式
	if (PlayerMgr::Player->pattern == false) {
		//目标:飞机驾驶舱位置 飞机的foward方向
		//过渡期间更改摄像机位置和旋转
		//到达目标后摄像机位置和旋转均置 0	(也可能会调整,使初始视角处于一个更好的位置)，置过渡态isTrans为false,会自动绑定到飞机上
		//todo_wyx -> 确定一下目标处的位置旋转 -> 摄像机位于飞机的起始点的世界transform
		Transform* F_target = new Transform();

		float t = 0.01f;
		//插值
		transform->position = transform->position + (F_target->position - transform->position) * t;
		transform->rotation = transform->rotation.Slerp(F_target->rotation, t);


		//到达目标点
		if ((F_target->position - transform->position).len() < C_target) {
			transform->position = CVector(0, 0, 0);
			transform->rotation = CEuler(0, 0, 0).ToQuaternion();
			bool former_pattern = PlayerMgr::Player->pattern;
			PlayerMgr::Player->pattern = !PlayerMgr::Player->pattern;
			isTrans = false;
		}
	}
	//过渡到上帝模式
	else
	{
		//目标:飞机位于屏幕中心, Z=240 摄像机前方为(0,0,-1)
		//到达目标后,置过渡态isTrans为false
		
		//todo_wyx -> 确定一下目标处的位置旋转 -> 当前屏幕的中心位置的世界transform
		static Transform* T_target;

		float t = 0.01f;
		//插值
		transform->position = transform->position + (T_target->position - transform->position) * t;
		transform->rotation = transform->rotation.Slerp(T_target->rotation, t);


		//到达目标点
		if ((T_target->position - transform->position).len() < C_target) {
			transform->position = T_target->position;
			transform->rotation = T_target->rotation;
			bool former_pattern = PlayerMgr::Player->pattern;
			PlayerMgr::Player->pattern = !PlayerMgr::Player->pattern;
			isTrans = false;
		}
	}
	//到达目标点后置 TimeMgr::scaleTime为1，只能设置一次
}

//override
void Camera::Update() {
	Move();
	Rotate();
	ChangePattern();
}

