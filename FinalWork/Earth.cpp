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

//绘制地球球体+贴上纹理贴图
void Earth::DrawEarth() {
	//glPushMatrix();
	////glutSolidSphere(this->radius, 50, 50);
	//Sphere::Draw(this->radius, 100, 100, TextureMgr::textures[1]);
	//glPopMatrix();
	////todo
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
	//GLfloat sun_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射广颜色，为偏红色
	//GLfloat sun_mat_shininess = 0.0f;
	//glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
	//glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
	//glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);
	gluQuadricTexture(TextureMgr::e_tex, GLU_TRUE);
	//glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TextureMgr::textures[1]);
	gluSphere(TextureMgr::e_tex, this->radius, 30, 30);
	glBindTexture(GL_TEXTURE_2D, 0);


	glDisable(GL_TEXTURE_2D);
	//glPopAttrib();
	gluQuadricTexture(TextureMgr::e_tex, GLU_FALSE);
	//glutSolidSphere(this->radius, 100, 100);'
	//Sphere::Draw(this->radius, 100, 100, TextureMgr::textures[0]);
	glPopMatrix();
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