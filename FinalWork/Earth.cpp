#include "Earth.h"
#include"glut.h"
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
	glutSolidSphere(this->radius, 50, 50);
	glPopMatrix();
	//todo
}
//��̫����ת
void Earth::Move() {
	//̫��λ��ΪԲ��,����Բ���˶�
	//����pos
}
//��ת
void Earth::Rotate() {
	//����rot
	CMatrix m;
	m.SetRotate(10, CVector(1, 2, 0));
	this->transform->rotation = (m * this->transform->rotation.ToCMatrix()).ToCQuaternion();

}

//override
void Earth::Render() {
	DrawEarth();
}
void Earth::Update() {
	Move();
	Rotate();
}