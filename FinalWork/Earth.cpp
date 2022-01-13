#include "Earth.h"

Earth::Earth()
{
	this->name = "earth";
	this->tag = "earth";
	this->radius = 400;
}

Earth::~Earth()
{
}

//绘制地球球体+贴上纹理贴图
void Earth::DrawEarth() {

}
//绕太阳旋转
void Earth::Move() {
	//太阳位置为圆心,匀速圆周运动
	//更改pos
}
//自转
void Earth::Rotate() {
	//更改rot
}

//override
void Earth::Render() {
	DrawEarth();
}
void Earth::Update() {
	Move();
	Rotate();
}