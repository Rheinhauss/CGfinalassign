#include "Sun.h"

Sun::Sun()
{
	this->name = "sun";
	this->tag = "sun";
	this->radius = 10;
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
	return;
}
//在太阳位置处设置光源
void Sun::SetLight() {
	return;
}