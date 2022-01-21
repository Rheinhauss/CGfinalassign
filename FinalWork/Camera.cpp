#include "Camera.h"
#include "InputManager.h"
#include "TimeMgr.h"
#include "PlayerMgr.h"

//��ʻģʽ��Transform�任Ϊ��Էɻ��ı任
//�ϵ��ӽ�ģʽ��Ϊ���Ա任

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

//������ƶ�
void Camera::Move() {
	//???
	if (InputManager::KEY_W) {
		//��ȡ�������up��λ����
		//��ǰλ��  ���� up * moveSpeed * TimeMgr::deltaTime
		this->transform->position = this->transform->position + _up() * moveSpeed * TimeMgr::deltaTime;
	}
	if (InputManager::KEY_S) {
		//��ȡ�������up��λ����
		//��ǰλ��  ��ȥ up * moveSpeed * TimeMgr::deltaTime
		this->transform->position = this->transform->position - _up() * moveSpeed * TimeMgr::deltaTime;
	}
	if (InputManager::KEY_A) {
		//��ȡ�������left��λ����
		//��ǰλ��  ���� left * moveSpeed * TimeMgr::deltaTime
		this->transform->position = this->transform->position + _left() * moveSpeed * TimeMgr::deltaTime;
	}
	if (InputManager::KEY_D) {
		//��ȡ�������left��λ����
		//��ǰλ��  ��ȥ left * moveSpeed * TimeMgr::deltaTime
		this->transform->position = this->transform->position - _left() * moveSpeed * TimeMgr::deltaTime;
	}
	if (InputManager::KEY_Q) {
		//��ȡ�������forward��λ����
		//��ǰλ��  ���� forward * moveSpeed * TimeMgr::deltaTime
		this->transform->position = this->transform->position + _forward() * moveSpeed * TimeMgr::deltaTime;
	}
	if (InputManager::KEY_E) {
		//��ȡ�������forward��λ����
		//��ǰλ��  ��ȥ forward * moveSpeed * TimeMgr::deltaTime
		this->transform->position = this->transform->position - _forward() * moveSpeed * TimeMgr::deltaTime;
	}
}
//�������ת
void Camera::Rotate() {
	//??? �����?�Լ�˳��ʱ���Ƿ�д��
	if (InputManager::KEY_J) {
		//��ȡ�������up��λ����
		//�� up �� ˳ʱ����ת rotSpeed * TimeMgr::deltaTime
		CMatrix _m;
		_m.SetRotate(-rotSpeed * TimeMgr::deltaTime, _up());
		this->transform->rotation = _m.ToCQuaternion() * this->transform->rotation;
	}
	if (InputManager::KEY_L) {
		//��ȡ�������up��λ����
		//�� up �� ��ʱ����ת rotSpeed * TimeMgr::deltaTime
		CMatrix _m;
		_m.SetRotate(rotSpeed * TimeMgr::deltaTime, _up());
		this->transform->rotation = _m.ToCQuaternion() * this->transform->rotation;
	}
	if (InputManager::KEY_K) {
		//��ȡ�������left��λ����
		//�� left �� ˳ʱ����ת rotSpeed * TimeMgr::deltaTime
		CMatrix _m;
		_m.SetRotate(-rotSpeed * TimeMgr::deltaTime, _left());
		this->transform->rotation = _m.ToCQuaternion() * this->transform->rotation;
	}
	if (InputManager::KEY_I) {
		//��ȡ�������left��λ����
		//�� left �� ��ʱ����ת rotSpeed * TimeMgr::deltaTime
		CMatrix _m;
		_m.SetRotate(rotSpeed * TimeMgr::deltaTime, _left());
		this->transform->rotation = _m.ToCQuaternion() * this->transform->rotation;
	}
	if (InputManager::KEY_U) {
		//��ȡ�������forward��λ����
		//�� forward �� ��ʱ����ת rotSpeed * TimeMgr::deltaTime
		CMatrix _m;
		_m.SetRotate(-rotSpeed * TimeMgr::deltaTime, _forward());
		this->transform->rotation = _m.ToCQuaternion() * this->transform->rotation;
	}
	if (InputManager::KEY_O) {
		//��ȡ�������forward��λ����
		//�� forward �� ˳ʱ����ת rotSpeed * TimeMgr::deltaTime
		CMatrix _m;
		_m.SetRotate(rotSpeed * TimeMgr::deltaTime, _forward());
		this->transform->rotation = _m.ToCQuaternion() * this->transform->rotation;
	}
}
//����ģʽ
void Camera::ChangePattern() {
	if (InputManager::KEY_X) {
		//���ɽ׶� ���ɸ��ķɻ�ģʽ
		//�ǹ��ɽ׶� �ɸ��ķɻ���ģʽ
		if (isTrans == false && is_allow_changing_pattern) {
			is_allow_changing_pattern = false;
			isTrans = true;
			//todo_ssh �ӽ��л�ƽ������
			//����� ��ʻģʽ ->�ϵ��ӽ�ģʽ,�������Transform����Ϊ���Ա任
			//�ù���̬Ϊtrue
			if (PlayerMgr::Player->pattern == true) {
				transform->rotation = PlayerMgr::Player->transform->rotation * transform->rotation;
				transform->position = PlayerMgr::Player->transform->position + transform->position;
			}
		}
	}
	if (isTrans == false) {
		return;
	}
	//���Ϊ���ɽ׶�,�˽׶���������þ�Ϊ�ǰ�̬������
	//��ʱ�� TimeMgr::scaleTimeΪ0����ͣ��Ϸ
	//���ڸ���ģʽ��ƽ����ֵ�ڼ�,���ܸ���ģʽ
	//����һ��Ŀ��λ�ú���ת����
	//��ֵ��Ŀ���
	static float C_target = 0.5f;
	//���ɵ���ʻģʽ
	if (PlayerMgr::Player->pattern == false) {
		//Ŀ��:�ɻ���ʻ��λ�� �ɻ���foward����
		//�����ڼ���������λ�ú���ת
		//����Ŀ��������λ�ú���ת���� 0	(Ҳ���ܻ����,ʹ��ʼ�ӽǴ���һ�����õ�λ��)���ù���̬isTransΪfalse,���Զ��󶨵��ɻ���
		//todo_wyx -> ȷ��һ��Ŀ�괦��λ����ת -> �����λ�ڷɻ�����ʼ�������transform
		Transform* F_target = new Transform();

		float t = 0.01f;
		//��ֵ
		transform->position = transform->position + (F_target->position - transform->position) * t;
		transform->rotation = transform->rotation.Slerp(F_target->rotation, t);


		//����Ŀ���
		if ((F_target->position - transform->position).len() < C_target) {
			transform->position = CVector(0, 0, 0);
			transform->rotation = CEuler(0, 0, 0).ToQuaternion();
			bool former_pattern = PlayerMgr::Player->pattern;
			PlayerMgr::Player->pattern = !PlayerMgr::Player->pattern;
			isTrans = false;
		}
	}
	//���ɵ��ϵ�ģʽ
	else
	{
		//Ŀ��:�ɻ�λ����Ļ����, Z=240 �����ǰ��Ϊ(0,0,-1)
		//����Ŀ���,�ù���̬isTransΪfalse
		
		//todo_wyx -> ȷ��һ��Ŀ�괦��λ����ת -> ��ǰ��Ļ������λ�õ�����transform
		static Transform* T_target;

		float t = 0.01f;
		//��ֵ
		transform->position = transform->position + (T_target->position - transform->position) * t;
		transform->rotation = transform->rotation.Slerp(T_target->rotation, t);


		//����Ŀ���
		if ((T_target->position - transform->position).len() < C_target) {
			transform->position = T_target->position;
			transform->rotation = T_target->rotation;
			bool former_pattern = PlayerMgr::Player->pattern;
			PlayerMgr::Player->pattern = !PlayerMgr::Player->pattern;
			isTrans = false;
		}
	}
	//����Ŀ������ TimeMgr::scaleTimeΪ1��ֻ������һ��
}

//override
void Camera::Update() {
	Move();
	Rotate();
	ChangePattern();
}

