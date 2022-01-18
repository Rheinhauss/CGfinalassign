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
	this->moveSpeed = 2;
	this->rotSpeed = 0.2;
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
		if (is_allow_changing_pattern) {
			is_allow_changing_pattern = false;
		}

		bool former_pattern = PlayerMgr::Player->pattern;
		PlayerMgr::Player->pattern = !PlayerMgr::Player->pattern;
		//todo_ssh �ӽ��л�ƽ������
		//����� ��ʻģʽ ->�ϵ��ӽ�ģʽ,�������Transform����Ϊ���Ա任
		//�ù���̬Ϊtrue

	}
	//���Ϊ���ɽ׶�,�˽׶���������þ�Ϊ�ǰ�̬������
	//��ʱ�� TimeMgr::scaleTimeΪ0����ͣ��Ϸ
	//���ڸ���ģʽ��ƽ����ֵ�ڼ�,���ܸ���ģʽ
	//����һ��Ŀ��λ�ú���ת����
	//��ֵ��Ŀ���
	//if (PlayerMgr::Player->pattern == true) {
	//	//Ŀ��:�ɻ���ʻ��λ�� �ɻ���foward����
	//	//�����ڼ���������λ�ú���ת
	//	//����Ŀ��������λ�ú���ת���� 0	(Ҳ���ܻ����,ʹ��ʼ�ӽǴ���һ�����õ�λ��)���ù���̬isTransΪfalse,���Զ��󶨵��ɻ���
	//	return;
	//}
	//else
	//{
	//	//Ŀ��:�ɻ�λ����Ļ����, Z=240 �����ǰ��Ϊ(0,0,-1)
	//	//����Ŀ���,�ù���̬isTransΪtrue
	//	return;
	//}
	//����Ŀ������ TimeMgr::scaleTimeΪ1��ֻ������һ��
}

//override
void Camera::Update() {
	Move();
	Rotate();
	ChangePattern();
}

