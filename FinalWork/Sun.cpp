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
//����̫������+����������ͼ
void Sun::DrawSun() {
	glPushMatrix();

	//glEnable(GL_COLOR_MATERIAL);	
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_BLEND);
	//glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SINGLE_COLOR);
	//glShadeModel(GL_SMOOTH);
	//glEnable(GL_LIGHT0);
	//GLfloat sun_mat_ambient[] = { 0.5f, 0.5f, 0.5f, 0.5f };  //������ʵĻ�������ɫ��Ϊ0
	//GLfloat sun_mat_diffuse[] = { 0.5f, 0.5f, 0.5f, 0.5f };  //������ʵ����������ɫ��Ϊ0
	//GLfloat sun_mat_specular[] = { 0.5f, 0.5f, 0.5f, 0.5f };   //������ʵľ��淴�����ɫ��Ϊ0
	//GLfloat sun_mat_emission[] = { 0.5f, 0.5f, 0.5f, 0.0f };   //������ʵķ������ɫ��Ϊƫ��ɫ
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
//��̫��λ�ô����ù�Դ
void Sun::SetLight() {
	//todo
	return;
}
CVector Sun::pos = CVector(0, 0, 0);