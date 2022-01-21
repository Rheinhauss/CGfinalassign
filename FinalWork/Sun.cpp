#include "glew.h"
#include "glut.h"
#include "Sun.h"
#include "Sphere.h"
#include "TextureMgr.h"

Sun::Sun()
{
	this->name = "sun";
	this->tag = "sun";
	this->radius = 24;
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

	//glEnable(GL_COLOR_MATERIAL);	
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_BLEND);
	//glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SINGLE_COLOR);
	//glShadeModel(GL_SMOOTH);
	//glEnable(GL_LIGHT0);
	//GLfloat sun_mat_ambient[] = { 0.5f, 0.5f, 0.5f, 0.5f };  //定义材质的环境光颜色，为0
	//GLfloat sun_mat_diffuse[] = { 0.5f, 0.5f, 0.5f, 0.5f };  //定义材质的漫反射光颜色，为0
	//GLfloat sun_mat_specular[] = { 0.5f, 0.5f, 0.5f, 0.5f };   //定义材质的镜面反射光颜色，为0
	//GLfloat sun_mat_emission[] = { 0.5f, 0.5f, 0.5f, 0.0f };   //定义材质的辐射广颜色，为偏红色
	//GLfloat sun_mat_shininess = 0.0f;
	//glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
	//glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
	//glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);
	gluQuadricTexture(TextureMgr::e_tex, GLU_TRUE);
	//glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TextureMgr::textures[0]);
	gluSphere(TextureMgr::e_tex, this->radius, 30, 30);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);
	//glPopAttrib();
	gluQuadricTexture(TextureMgr::e_tex, GLU_FALSE);
	//glutSolidSphere(this->radius, 100, 100);
	//Sphere::Draw(this->radius, 100, 100, TextureMgr::textures[0]);
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