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

//绘制地球球体+贴上纹理贴图
void Earth::DrawEarth() {
	glPushMatrix();
	glutSolidSphere(this->radius, 50, 50);
	glPopMatrix();
	//todo
}
//绕太阳旋转
void Earth::Move() {
	//太阳位置为圆心,匀速圆周运动
	//更改pos
}
//自转
void Earth::Rotate() {
	//更改rot
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