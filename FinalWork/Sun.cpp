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
//绘制太阳球体+贴上纹理贴图
void Sun::DrawSun() {
	glPushMatrix();
	//glutSolidSphere(this->radius, 100, 100);
	Sphere::Draw(this->radius, 100, 100, GL_TEXTURE0);
	glPopMatrix();
	//todo
	return;
}
//在太阳位置处设置光源
void Sun::SetLight() {
	//todo
	return;
}
CVector Sun::pos = CVector(0, 0, 0);