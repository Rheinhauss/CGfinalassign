#include "Earth.h"
#include "Sun.h"
#include "TextureMgr.h"
#include"Sphere.h"
Earth::Earth()
{
	this->name = "earth";
	this->tag = "earth";
	this->radius = 5;
}

Earth::~Earth()
{
}

//���Ƶ�������+����������ͼ
void Earth::DrawEarth() {
	glPushMatrix();
	//glutSolidSphere(this->radius, 50, 50);
	Sphere::Draw(this->radius, 100, 100, TextureMgr::textures[1]);
	glPopMatrix();
	//todo
}
//��̫����ת
void Earth::Move() {
	pub_seta += 0.3;
	this->transform->position = CVector(cos(pub_seta / 180 * PI) * distSE + Sun::pos.x,
										0,
										sin(pub_seta / 180 * PI) * distSE + Sun::pos.z);
	//̫��λ��ΪԲ��,����Բ���˶�
	//����pos
}
//��ת
void Earth::Rotate() {
	//����rot
	self_seta += 0.1f;
	if (self_seta >= 360) {
		self_seta -= 360;
	}
	this->transform->rotation.SetAngle(self_seta, CVector(0, 1, 0));

}

//override
void Earth::Render() {
	DrawEarth();
}
void Earth::Update() {
	Move();
	Rotate();
}