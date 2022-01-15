#include "glew.h"
#include "glut.h"
#include "Sun.h"
#include "Sphere.h"
#include "TextureMgr.h"

Sun::Sun()
{
	this->name = "sun";
	this->tag = "sun";
	this->radius = 8;
	this->transform->position = CVector(0, 0, 0);
	pos = CVector(0, 0, 0);
}

Sun::~Sun()
{
}

//override
void Sun::Render() {
	this->DrawSun();
	this->SetLight();
}
//����̫������+����������ͼ
void Sun::DrawSun() {
	glPushMatrix();
	//glutSolidSphere(this->radius, 100, 100);
	Sphere::Draw(this->radius, 100, 100, GL_TEXTURE0);
	glPopMatrix();
	//todo
	return;
}
//��̫��λ�ô����ù�Դ
void Sun::SetLight() {
	//todo
	return;
}
CVector Sun::pos = CVector(0, 0, 0);