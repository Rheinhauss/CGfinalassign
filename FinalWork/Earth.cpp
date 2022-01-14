#include "Earth.h"
#include"glut.h"
#include "Sun.h"
Earth::Earth()
{
	this->name = "earth";
	this->tag = "earth";
	this->radius = 5;
}

Earth::~Earth()
{
}

//绘制地球球体+贴上纹理贴图
void Earth::DrawEarth() {
	glPushMatrix();
	glutSolidSphere(this->radius, 50, 50);
	glPopMatrix();
	//todo
}
//绕太阳旋转
void Earth::Move() {
	pub_seta += 0.3;
	this->transform->position = CVector(cos(pub_seta / 180 * PI) * distSE + Sun::pos.x,
										0,
										sin(pub_seta / 180 * PI) * distSE + Sun::pos.z);
	//太阳位置为圆心,匀速圆周运动
	//更改pos
}
//自转
void Earth::Rotate() {
	//更改rot
	self_seta += 0.1;
	CMatrix m;
	m.SetRotate(self_seta, CVector(0, 1, 0));
	this->transform->rotation = m.ToCQuaternion();

}

//override
void Earth::Render() {
	DrawEarth();
}
void Earth::Update() {
	Move();
	Rotate();
}